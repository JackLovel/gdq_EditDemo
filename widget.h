#ifndef WIDGET_H
#define WIDGET_H

#include "richtextfont.h"
#include "color.h"
#include "sendarticedialog.h"
#include "Config.h"
#include "util.h"
#include "aboutdialog.h"
#include "configdialog.h"

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>

namespace Ui {
class Widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void setup();
    RichTextFont *font;
    QVector<QString> contents;
    QVector<RichTextFont*> fonts;
    void convertToVector(QString);
    void setDisplayContent(QVector<RichTextFont*> fonts);
    void checkSpell(QString text);

    void getNextParagraph();

    void logFonts(QVector<RichTextFont*> fonts);
    void logVector(QVector<QString> s);
    int alreadySendWordSize();
    int restWordSize();
    double wordPercent();
    void sendArticleStatus();
    void clearInputEdit();
    void setProgressBar(int);

protected:
    bool eventFilter(QObject *o, QEvent *e);

private slots:
    void LogInput();
    void recordTimeSlot();
    void getSendDialog(QString, int, QString, int);
    void loadRectFile();

private:
    Ui::Widget *ui;
    SendArticeDialog *sendDialog;
    AboutDialog *aboutDialog;
    ConfigDialog *configDialog;

    qint32 storeIndex; // 用于存放 输入 时的索引
    bool revision; // 输入框 是否回改
    bool isRevision(int currentIndex);
    qint32  revisionCount; // 回改数
    void setFontBackground(int index, QString color);
    qint32 recordTime; // 记录输入的时间
    QTimer *timer;
    bool canTimer; // 是否可以被计时

    qint32 typeNumber; // 获取按键次数

    qint32 totalParagraphIndex;
    qint32 currentParagraphIndex; // 记录当前为第几段文本
    qint32 paragraphStep;  // 文本第次发送 n 个字
    qint32 paragraphSize;  // 文本共有n 个字

    QString artileName;

    // 进度条
    qint32 progressBarMax = 100;
    qint32 progressBarInit = 0;

    /***菜单***/
    QMenu *sendFileMenu;
    QMenu *helpMenu;
    QMenu *optionMenu;
    QMenu *recentFileMenu;

    QAction *aboutAction;
    QAction* sendFileAction;
    QAction *nextParagraphAction; // 发送下一段文本
    QAction *clearInputAction; // 重打

    QAction *configAction;
};

#endif // WIDGET_H
