#include "sendarticedialog.h"
#include "Config.h"

SendArticeDialog::SendArticeDialog(QWidget *parent)
    : QWidget(parent)
{
    setup();

    sendFileBtn = new QPushButton(tr("发文"));

    textEdit = new QTextEdit(this);
    textEdit->setText("");

    spinBox = new QSpinBox();
    spinBox->setValue(spinValue);

    QStringList files = Util::getFileNames(filePath);
    fileList = new QListWidget(this);

    fileList->addItem(new QListWidgetItem("剪贴板", fileList));
    for(int i=0;i<files.size();i++){
            fileList->addItem(new QListWidgetItem(QString("%1").arg(files.at(i)),fileList));
    }
    connect(fileList,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(listItemClicked(QListWidgetItem *)));
    wordSizeLabel = new QLabel();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(fileList);
    layout->addWidget(textEdit);
    layout->addWidget(wordSizeLabel);
    layout->addWidget(spinBox);
    layout->addWidget(sendFileBtn);

    connect(sendFileBtn, &QPushButton::clicked, this, &SendArticeDialog::sendArticeSlot);

    setLayout(layout);
}

SendArticeDialog::~SendArticeDialog()
{

}

void SendArticeDialog::setup()
{
    articleName = "";
    articleSize = -1;
    spinValue = 0;

    filePath = qApp->applicationDirPath() + "/" + ARTICLE_DIR_FILE; // 跟打文章目录的绝对路径

    setWindowTitle(tr("发文"));
    resize(300, 300);
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
    QString itemText = item->text();
    QString content = "";
    if (itemText == "剪贴板") {
        content = Util::getClipboardContent();
    } else {
        articleName = itemText.split(".").first();
        QString path = filePath + "/" + itemText;
        content = Util::readFile(path);
    }

    textEdit->setText(content);
    articleSize = content.length();
    wordSizeLabel->setText(QString("%1字").arg(articleSize));
}

void SendArticeDialog::sendArticeSlot()
{
    int n = spinBox->text().toInt(); // 文章每次发送 n 个字
    QString content = textEdit->toPlainText();

    emit sendSpinValue(content, n, articleName, articleSize);
    close();
}
