#include "globalmanager.h"

#include "newfilewindow.h"
#include "ui_newfilewindow.h"

NewFileWindow::NewFileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewFileWindow)
{
    ui->setupUi(this);
}

NewFileWindow::~NewFileWindow()
{
    delete ui;
}

void NewFileWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    GlobalManager::instance()->showMainWindow();
}
