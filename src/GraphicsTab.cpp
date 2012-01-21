#include "inc/GraphicsTab.h"
#include "ui_GraphicsTab.h"

GraphicsTab::GraphicsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicsTab)
{
    ui->setupUi(this);
}

GraphicsTab::~GraphicsTab()
{
    delete ui;
}
