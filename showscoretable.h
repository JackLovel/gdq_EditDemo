#ifndef SHOWSCORETABLE_H
#define SHOWSCORETABLE_H

#include <QObject>
#include <QTableWidget>

class ShowScoreTable : QObject
{
    Q_OBJECT

public:
    ShowScoreTable(QObject *parent = nullptr);
    ~ShowScoreTable();
    void setTable(QTableWidget *tableWidget);
    void showTableInfo();

private:
    QTableWidget *tableWidget; // 显示跟打数据的表格
};

#endif // SHOWSCORETABLE_H
