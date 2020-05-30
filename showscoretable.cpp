#include "showscoretable.h"

ShowScoreTable::ShowScoreTable(QObject *parent)
    : QObject(parent)
{
    // 跟打结果显示图表
//    QStandardItemModel  *model = new QStandardItemModel();

//    model->setColumnCount(2);
//    model->setHeaderData(0,Qt::Horizontal,"速度");
//    model->setHeaderData(1,Qt::Horizontal,"击键");

//    model->setItem(0, 0, new QStandardItem("90.0"));
//    model->setItem(0, 1, new QStandardItem("33"));

//    model->item(0, 0)->setTextAlignment(Qt::AlignCenter);
//    model->item(0, 1)->setTextAlignment(Qt::AlignCenter);

//    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableView->setModel(model);
//    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
//    ui->tableView->horizontalHeader()->setMinimumSectionSize(100);
}

ShowScoreTable::~ShowScoreTable()
{

}

void ShowScoreTable::setTable(QTableWidget *table)
{
    this->tableWidget = table;
    showTableInfo();
}

void ShowScoreTable::showTableInfo()
{
    this->tableWidget->setColumnCount(2);
    this->tableWidget->setRowCount(2);
    QStringList tableHead;
    tableHead << "速度" << "击键";
    this->tableWidget->setHorizontalHeaderLabels(tableHead);
    this->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
    this->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    this->tableWidget->setItem(0,0,new QTableWidgetItem("zhangsan"));
    this->tableWidget->setItem(0,1,new QTableWidgetItem("1"));
//    this->tableWidget->verticalHeader()->setV (false);   //隐藏列表头

    this->tableWidget->setItem(1,0,new QTableWidgetItem("lisi"));
    this->tableWidget->setItem(1,1,new QTableWidgetItem("20"));
    this->tableWidget->selectRow(0);
}
