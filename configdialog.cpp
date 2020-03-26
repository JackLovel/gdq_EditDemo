#include "configdialog.h"
#include "ui_configdialog.h"

#include "Config.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0, "快捷键");
    ui->tabWidget->setTabText(1, "常规");

    ui->checkBoxExit->setText(tr("使用Esc键退出"));
    exitAction = new QAction();
    exitAction->setShortcut(tr("ESC"));
    connect(exitAction, &QAction::triggered, [=]() {
        if (ui->checkBoxExit->isChecked()) {
            close();
        }
    });


    // 字体与背景颜色
    ui->btn1->setStyleSheet(("QPushButton{background-color: rgb(0,120,215)}"));
    ui->btn1->setText("");
    ui->btn1->setFixedSize(30, 40);
    ui->btn2->setStyleSheet(("QPushButton{background-color:rgb(245,152,214)}"));
    ui->btn2->setText("");
    ui->btn2->setFixedSize(30, 40);

    ui->labelDisplay->setText(tr("选择"));
    ui->labelDisplay->setFixedSize(60, 40);
    ui->labelDisplay->setStyleSheet("QLabel{background-color: rgb(0,120,215)}");
    connect(ui->btn1, &QPushButton::clicked, [=]{
        ui->labelDisplay->setStyleSheet("QLabel{background-color: rgb(0,120,215)}");
    });
    connect(ui->btn2, &QPushButton::clicked, [=]{
        ui->labelDisplay->setStyleSheet("QLabel{background-color: rgb(245,152,214)}");
    });

    QStringList list = {"自动", "黑色", "白色"};
    ui->comboFont->addItems(list);

    setWindowTitle(CONFIG_DIALOG_TITLE);
    resize(CONFIG_DIALOG_WIDTH, CONFIG_DIALOG_HEIGHT);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}
