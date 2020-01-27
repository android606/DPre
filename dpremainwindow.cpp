#include "dpremainwindow.h"
#include "ui_dpremainwindow.h"

DPreMainWindow::DPreMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DPreMainWindow)
{
    ui->setupUi(this);
}

DPreMainWindow::~DPreMainWindow()
{
    delete ui;
}

