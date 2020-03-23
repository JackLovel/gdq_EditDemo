#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFont>
#include <QDebug>
#include <QtMath>

Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setup();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setup()
{
    revision = false; // 默认值 没有回改
    storeIndex = -1; // 如果没有输入，默认值为 -1;
    revisionCount = 0;
    currentParagraphIndex = -1; // 默认当前第 -1 段文本，表示没有分段
    totalParagraphIndex = -1; // 默认文本总共第-1段文本，表示没有分段
    paragraphStep = -1;
    paragraphSize = -1;
    artileName = "";


    timer = new QTimer;
    timer->setInterval(1000); // 1s
    timer->start();
    recordTime = 0;
    canTimer = false;
    connect(timer, &QTimer::timeout, this, &Widget::recordTimeSlot);

    // 打开时的提示信息
    QString content = OPEN_PROMPT;
    convertToVector(content);
    setDisplayContent(fonts);

    typeNumber = 0;
    ui->textEditInput->installEventFilter(this);

    QFont font;
    font.setFamily("宋体");
    font.setPixelSize(50);
    ui->textEdit->setFont(font);

    /***菜单栏相关代码**/
    sendFileMenu = new QMenu("发文");
    sendFileAction = new QAction("发文对话框");
    nextParagraphAction = new QAction("发送下一段");
    nextParagraphAction->setShortcut(tr("ALT+P"));
    nextParagraphAction->setEnabled(false);

    clearInputAction = new QAction("重打");
    clearInputAction->setShortcut(tr("F3"));
    clearInputAction->setEnabled(false);

    sendFileMenu->addAction(sendFileAction);
    sendFileMenu->addAction(nextParagraphAction);
    sendFileMenu->addAction(clearInputAction);

    menuBar()->addMenu(sendFileMenu);

    sendDialog = new SendArticeDialog;
    connect(sendFileAction, &QAction::triggered, this, [=](){
        sendDialog->show();
    });
    connect(nextParagraphAction, &QAction::triggered, this, &Widget::getNextParagraph);
    connect(clearInputAction, &QAction::triggered, this, &Widget::clearInputEdit);

    connect(sendDialog, SIGNAL(sendSpinValue(QString, int, QString, int)), this,
            SLOT(getSendDialog(QString, int, QString, int)));

    connect(ui->textEditInput, &QTextEdit::cursorPositionChanged, this, &Widget::LogInput);

    ui->textEdit->setReadOnly(true);
    ui->textEditInput->setFocus();
    ui->lineEditArticleTitle->setText(artileName);

    setWindowTitle(APP_NAME);
}

void Widget::convertToVector(QString input)
{
    QStringList list = input.split("",QString::SkipEmptyParts);
    fonts.clear();
    for(int i = 0; i < list.size(); i++) {
        QString text = list.at(i);
        fonts.push_back(new RichTextFont(text));
    }
}

void Widget::setDisplayContent(QVector<RichTextFont*> fonts) {
    QString content = "";
    RichTextFont *f = new RichTextFont();
    for(int i = 0; i < fonts.size(); i++) {
        f = fonts.at(i);
        content += f->formatColor();
    }

    ui->textEdit->setHtml(content);
}

void Widget::LogInput()
{

    canTimer = true;
    QString content = ui->textEditInput->toPlainText();
    qint32 wordSize = content.size();
    ui->labelInputWordSize->setText(QString("%1").arg(wordSize));

    qint32 index = wordSize - 1;
    revision = isRevision(index);

//    qDebug() << "内容：" << content
//             << "字数：" << wordSize
//             << "光标索引" << index
//             << "之前的索引" << storeIndex
//             << "回改：" << (revision ? "回改" : "没有回改");

    // ("", "这", "是", "一", "个", "测", "试", "d", "e", "m", "o", "")
//    qDebug() << ui->textEdit->toPlainText().split("");
    QStringList displayContent = ui->textEdit->toPlainText().split("");
    int numberLimit = displayContent.size() - 2; // 排除两端的为空
    if (wordSize >= numberLimit) {
        timer->stop();
        ui->textEditInput->setReadOnly(true);
    }
    checkSpell(content);
    setDisplayContent(fonts);
    storeIndex = index;
    clearInputAction->setEnabled(true);
}

void Widget::recordTimeSlot()
{
    if (canTimer) {
        ++recordTime;
        ui->labelTime->setText(QString("%1秒").arg(recordTime));
    }
}

void Widget::getSendDialog(QString content, int value, QString name, int articleSize)
{
    paragraphSize = articleSize;
    contents.clear();
    if (value != 0) {
        totalParagraphIndex = qCeil(double(content.length()) / double(value));
        for(int i = 0; i < totalParagraphIndex; i++) {
            int v = value;
            QString str = content.mid(v * i, v);
            contents.push_back(str);
        }
    } else {
        contents.push_back(content);
    }

    paragraphStep = value;
    currentParagraphIndex = 0;
    convertToVector(contents.at(currentParagraphIndex));
    setDisplayContent(fonts);

    artileName = name;
    sendArticleStatus();

    nextParagraphAction->setEnabled(true);
}

void Widget::getNextParagraph() {
    ++currentParagraphIndex;
    if (currentParagraphIndex >= totalParagraphIndex - 1) {
        currentParagraphIndex = totalParagraphIndex - 1;
    }

    QString content = contents.at(currentParagraphIndex);
    convertToVector(content);
    setDisplayContent(fonts);

    ui->textEditInput->clear();
    ui->textEditInput->setReadOnly(false);

    sendArticleStatus();
}

// input error: RED
// input corrent: GREY
// no input: WHITE
void Widget::checkSpell(QString text)
{
    QStringList inputList = text.split("");
    int inputSize = inputList.size() - 1;
    if (!revision) {
        // 不回改的情景下
    //    qDebug() << inputList; // ("", "这", "是", "一", "个", "人", "")
        for(int i = 1; i < inputList.length() - 1; i++) {
            bool b = inputList.at(i) == fonts.at(i - 1)->text;
            if (b == false) {
                setFontBackground(i-1, RED);
            } else {
                setFontBackground(i-1, GREY);
            }
        }
    } else {
       // 回改的情景下
       for(int i = inputSize - 1; i <= storeIndex; i++) {
            ++revisionCount;
            ui->labelRevisionCount->setText(QString("%1").arg(revisionCount));
            setFontBackground(i, WHITE);
       }
    }
}

bool Widget::isRevision(int currentIndex) {
    int i = currentIndex;
    return storeIndex > i;
}

void Widget::setFontBackground(int index, QString color) {
    int i = index;
    fonts.at(i)->color = color;
}

bool Widget::eventFilter(QObject *o, QEvent *e)
{
     if (o == ui->textEditInput)
     {
         if (e->type() == QEvent::KeyPress)
         {
             ++typeNumber;
             ui->labelTypeNumber->setText(QString("%1")
                                          .arg(typeNumber));
        }
    }
    return QObject::eventFilter(o, e);
}

void Widget::logFonts(QVector<RichTextFont*> fonts) {
    for(int i = 0; i < fonts.size(); i++) {
        qDebug() << fonts.at(i)->text;
    }
}

void Widget::logVector(QVector<QString> s) {
    for(int i = 0; i < s.size(); i++) {
        qDebug() << s.at(i);
    }
}

void Widget::clearInputEdit() {
    if (ui->textEditInput->toPlainText().isEmpty()) {
        return;
    }

    ui->textEditInput->clear();
    ui->textEditInput->setReadOnly(false);
    clearInputAction->setEnabled(false);
}

int Widget::alreadySendWordSize() {
    if (currentParagraphIndex < totalParagraphIndex - 1) {
        return (currentParagraphIndex + 1) * paragraphStep;
    } else {
        return paragraphSize;
    }
}

int Widget::restWordSize() {
    return paragraphSize - alreadySendWordSize();
}

double Widget::wordPercent() {
     return qCeil((double(alreadySendWordSize()) /
                            double(paragraphSize)) * 100);
}

// 发文状态的相关信息
void Widget::sendArticleStatus()
{
    ui->lineEditArticleTitle->setText(artileName);
    ui->lineEditAlreadySendParagraph->setText(QString("%1").arg(currentParagraphIndex + 1));
    ui->lineEditTotalWord->setText(QString("%1").arg(paragraphSize));
    ui->lineEditRestWord->setText(QString("%1").arg(restWordSize()));
    ui->lineEditProcess->setText(QString("%1%").arg(wordPercent()));
}

