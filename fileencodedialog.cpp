#include "fileencodedialog.h"
#include "ui_fileencodedialog.h"
#include "util.h"

#include <qfiledialog.h>
#include <QDebug>

FileEncodeDialog::FileEncodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileEncodeDialog)
{
    ui->setupUi(this);
    currentFilePath = "";
    QStringList encodeList = {
        "UTF-8",
//        "GBK", // GB2312
    };
    ui->comboBox->addItems(encodeList);
    ui->comboBox->setCurrentIndex(0);
    currentEncode = "UTF-8";
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setEncode(QString)));

    setWindowTitle("文件编码转换");
}

FileEncodeDialog::~FileEncodeDialog()
{
    delete ui;
}

void FileEncodeDialog::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                    "open file");
    if (path.isEmpty()) {
        return;
    } else {
       currentFilePath = path;
    }
}

// 点击转换
void FileEncodeDialog::on_pushButton_3_clicked()
{
    if (currentFilePath.isEmpty()) {
        return;
    }
    if (currentEncode == "UTF-8") {
        Util::FileGbkToUtf8(currentFilePath);
    } else if (currentEncode == "GBK") {
        qDebug() << "这个函数实现暂时有问题";
//        Util::FileUtf8ToGbk(currentFilePath);
    }
    ui->label->setText("文件编码转换成功");
}

void FileEncodeDialog::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                                    "添加目录",
                                                    "./");
    QStringList filePaths;
    if(path.isEmpty())
    {
        return;
    }
    else
    {

        QDir dir(path);
        QStringList nameFilters;
        nameFilters << "*.txt";
        QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

        QString p;
        for (auto f : files) {
            p =  path + "/" + f;
            filePaths.push_back(p);
        }

        for (auto p : filePaths) {
            if (currentEncode == "UTF-8") {
                 Util::FileGbkToUtf8(p);
            } else if (currentEncode == "GBK") {
                qDebug() << "这个函数实现暂时有bug";
        //        Util::FileUtf8ToGbk(currentFilePath);
            }
        }
    }
}

void FileEncodeDialog::setEncode(QString item)
{
    currentEncode = item;
    qDebug() << item;
    QString title = "";
    if (item == "UTF-8") {
         title = "gbk 转 utf-8";
    } else if (item == "GBK") {
        qDebug() << "这个函数实现暂时有bug";
        title = "utf-8 转 gbk";
//        Util::FileUtf8ToGbk(currentFilePath);
    }
    setWindowTitle(title);
}
