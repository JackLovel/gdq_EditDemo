#ifndef FILEENCODEDIALOG_H
#define FILEENCODEDIALOG_H

#include <QDialog>

namespace Ui {
class FileEncodeDialog;
}

class FileEncodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileEncodeDialog(QWidget *parent = nullptr);
    ~FileEncodeDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();
    void setEncode(QString item);

private:
    Ui::FileEncodeDialog *ui;

    QString currentFilePath;
    QString currentEncode;

//    typedef enum Encode{
//        utf8=1,
//        gbk,
//    } FileEncoding;
};

#endif // FILEENCODEDIALOG_H
