#ifndef SHOWDATETIME_H
#define SHOWDATETIME_H

#include <QLCDNumber>
#include <QLabel>
#include <QObject>
#include <QTimer>

/****
 * 跟打器的计时工具
 * */
class ShowDateTime : public QObject
{
    Q_OBJECT
public:
    ShowDateTime(QObject *parent = nullptr);
    ~ShowDateTime();

    void setLab(QLabel *labDateTime/*, QLabel *labLive*/);
    void setLcdNumber(QLCDNumber *lcdNumber);
    void start(int interval);
    void stop();
    void clear();

private:
    int day;                //天数
    int hour;               //时钟数
    int minute;             //分钟数
    int seconds;            //秒钟数
    QTimer *timer;          //定时器获取时间
    QLabel *labDateTime;    //显示日期时间的载体
    QLabel *labLive;        //显示已运行
    QLCDNumber *lcdNumber;  //显示日期时间的LCD控件

private slots:
    void setTimeInfo();
    void showTime();

signals:

public slots:

};

#endif // SHOWDATETIME_H
