#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "historydelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->insertItem(0, "新纪元.novel\n~/marco/新纪元.novel#1");
    ui->listWidget->insertItem(0, "新纪元1.novel\n~/marco/新纪元1.novel#2");
    ui->listWidget->setItemDelegate(new HistoryDelegate());
}

MainWindow::~MainWindow()
{
    delete ui;
}
