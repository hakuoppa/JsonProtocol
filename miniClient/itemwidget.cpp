#include "itemwidget.h"
#include "ui_itemwidget.h"

ItemWidget::ItemWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ItemWidget)
{
    ui->setupUi(this);
}

ItemWidget::~ItemWidget()
{
    delete ui;
}
