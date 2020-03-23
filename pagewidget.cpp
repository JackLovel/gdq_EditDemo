#include "pagewidget.h"
#include "ui_pagewidget.h"

PageWidget::PageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageWidget)
{
    ui->setupUi(this);
}

PageWidget::~PageWidget()
{
    delete ui;
}

void PageWidget::setWidgetText(const QString &str)
{
    ui->label->setText(str);
}
