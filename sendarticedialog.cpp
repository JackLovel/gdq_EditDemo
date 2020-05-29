#include "sendarticedialog.h"
#include "Config.h"

SendArticeDialog::SendArticeDialog(QWidget *parent)
    : QWidget(parent)
{
    setup();
}

SendArticeDialog::~SendArticeDialog()
{

}

void SendArticeDialog::setup()
{
    articleName = "";
    articleSize = -1;
    spinValue = 0;

    setupUi();
    setupArticleList();

    connect(fileList,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(listItemClicked(QListWidgetItem *)));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(fileList);
    layout->addWidget(textEdit);
    layout->addWidget(wordSizeLabel);
    layout->addWidget(spinBox);
    layout->addWidget(sendFileBtn);

    connect(sendFileBtn, &QPushButton::clicked, this, &SendArticeDialog::sendArticeSlot);

    setLayout(layout);
    setWindowTitle(tr("发文"));
    resize(800, 500);
}

void SendArticeDialog::setupArticleList()
{
    fileList = new QListWidget(this);

    fileList->addItem(new QListWidgetItem("剪贴板", fileList));

    putFileDir = qApp->applicationDirPath() + "/" + ARTICLE_DIR_FILE;
    Util::checkDirExist(putFileDir);
    QStringList files = Util::getFileNames(putFileDir);
    for (auto f: files) {
        auto a = new Article(f, 0);
        articles.push_back(a);
    }
    for(int i=0;i<files.size();i++){
            fileList->addItem(new QListWidgetItem(QString("%1").arg(articles.at(i)->name), fileList));
    }
    //
    fileList->addItem(new QListWidgetItem("---本地文件---", fileList));
    // todo: 本地文件
    QStringList localFiles = {
                                "冰灯.txt",
                                "四季.txt",
                                "常用单字中五百.txt",
                                "常用词组.txt",
                                "心的出口.txt",
                                "我的文章.txt",
                             };

    for (auto a: localFiles) {
        auto article = new Article(a, 1);
        localArticles.push_back(article);
    }
    for(int i=0;i<localArticles.size();i++){
            fileList->addItem(new QListWidgetItem(
                                  QString("%1").arg(localArticles.at(i)->name),
                                  fileList));
    }

    splitIndex = 1 + files.length();
}

void SendArticeDialog::setupUi()
{

    sendFileBtn = new QPushButton(tr("发文"));

    textEdit = new QTextEdit(this);
    textEdit->setText("");
    textEdit->setReadOnly(true);

    spinBox = new QSpinBox();
    spinBox->setValue(spinValue);

    wordSizeLabel = new QLabel();
}
void SendArticeDialog::switchPage()
{
    int count = stackedWidget->count();
    int index = stackedWidget->currentIndex();

    ++index;
    if (index >= count) {
        index = 0;
    }

    stackedWidget->setCurrentIndex(index);
}

void SendArticeDialog::listItemClicked(QListWidgetItem *item)
{
    QString content = "";
    qint32 selectIndex = fileList->row(item);
    Article *a;
    QString fileSize = "";
    QString fileName = item->text();

    if (selectIndex == 0) {
        content = Util::getClipboardContent();
        articleSize = content.size();
        fileSize = "";
    } else if (selectIndex < splitIndex) {
        a = articles.at(selectIndex - 1);
        content = a->content;
        articleSize = a->wordSize;
        fileSize = a->fileSize;
    } else if (selectIndex == splitIndex) {
        content = "下面的文章为本地文章";
        articleSize = content.size();
        fileSize = "";
    } else if (selectIndex > splitIndex) {
        int index = selectIndex - splitIndex - 1;
        a = localArticles[index];
        content = a->content;
        articleSize = a->wordSize;
        fileSize = a->fileSize;
    }

    textEdit->setText(content);
    wordSizeLabel->setText(QString("%1字").arg(articleSize));
    setWindowTitle(QString("%1--%2").arg(fileName).arg(fileSize));
}

void SendArticeDialog::sendArticeSlot()
{
    int n = spinBox->text().toInt(); // 文章每次发送 n 个字
    QString content = textEdit->toPlainText();

    emit sendSpinValue(content, n, articleName, articleSize);
    close();
}
