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

    setWindowTitle(CONFIG_DIALOG_TITLE);
    resize(CONFIG_DIALOG_WIDTH, CONFIG_DIALOG_HEIGHT);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}
