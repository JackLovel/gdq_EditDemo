#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0, "关于白猫跟打器");
    ui->tabWidget->setTabText(1, "许可");

    QString t1 = Util::readFile(LICENSE_PATH);
    ui->textBrowser->setText(t1);

    QString t2 = Util::readFile(ABOUT_PATH);
    ui->textEdit->setText(t2);

    setWindowTitle(QString("%1(%2)").arg(APP_NAME).arg(APP_VERSION));
    resize(ABOUT_Dialog_WIDTH, ABOUT_Dialog_HEIGHT);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
