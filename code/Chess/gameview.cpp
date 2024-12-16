#include "gameview.h"
#include "ui_gameview.h"

gameview::gameview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameview)
{
    ui->setupUi(this);
}

gameview::~gameview()
{
    delete ui;
}
