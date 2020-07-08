#include "showdatetime.h"

#include <QDateTime>

ShowDateTime::ShowDateTime(QObject *parent)
    : QObject(parent)
{
    labDateTime = 0;
    labLive = 0;
    lcdNumber = 0;

    day = 0;
    hour = 0;
    minute = 0;
    seconds = 0;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ShowDateTime::showTime);
}

ShowDateTime::~ShowDateTime()
{

}

void ShowDateTime::setLab(QLabel *labDateTime)
{
    this->labDateTime = labDateTime;
//    this->labLive = labLive;
    setTimeInfo();
}

void ShowDateTime::setLcdNumber(QLCDNumber *lcdNumber)
{
    this->lcdNumber = lcdNumber;
}

void ShowDateTime::start(int interval)
{
    timer->start(interval);
}

void ShowDateTime::stop()
{
    timer->stop();
}

void ShowDateTime::showTime()
{
    seconds++;
    if (seconds == 60) {
        minute++;
        seconds = 0;
    }
    if (minute == 60) {
        hour++;
        minute = 0;
    }
    if (hour == 24) {
        day++;
        hour = 0;
    }

    setTimeInfo();
}

void ShowDateTime::setTimeInfo()
{
    this->labDateTime->setText(QString("%1天%2时%3分%4秒").arg(day).arg(hour).arg(minute).arg(seconds));
}

void ShowDateTime::clear()
{
    this->stop();
    day = 0;
    hour = 0;
    minute = 0;
    seconds = 0;
    this->setTimeInfo();
}

