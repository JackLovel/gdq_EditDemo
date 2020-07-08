#ifndef SENDARTICEDIALOG_H
#define SENDARTICEDIALOG_H

#include "pagewidget.h"
#include "util.h"
#include "article.h"

#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QApplication>
#include <QDir>
#include <QTextEdit>
#include <QLabel>
#include <QSpinBox>

class SendArticeDialog : public QWidget
{
    Q_OBJECT
public:
    explicit SendArticeDialog(QWidget *parent = nullptr);
    ~SendArticeDialog();

signals:
    void sendSpinValue(QString, int, QString, int);

private slots:
    void switchPage();
    void listItemClicked(QListWidgetItem *item);
    void sendArticeSlot();

private:
    QString articleName;
    int articleSize;

    QStackedWidget *stackedWidget;
    QListWidget *fileList;
    QTextEdit *textEdit;
    QString putFileDir; // 这是自已放置文件的目录

    QLabel *wordSizeLabel;
    QSpinBox *spinBox;
    qint32 spinValue;
    QPushButton *sendFileBtn;

    void setup();
    void setupUi();
    void setupArticleList();

    QVector<Article*> articles;
    int splitIndex;
    QVector<Article*> localArticles;
};

#endif // SENDARTICEDIALOG_H
