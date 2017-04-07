#include "globalmanager.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "historydelegate.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GlobalManager::instance()->setHistoryListItems(ui->listWidget);
    ui->listWidget->setItemDelegate(new HistoryDelegate());

    connect(ui->listWidget, &QListWidget::currentItemChanged, this, [this](QListWidgetItem *current, QListWidgetItem *prev){
        Q_UNUSED(prev)
        GlobalManager::instance()->setHistoryLabelInfo(qvariant_cast<QString>(current->data(0)), ui->infoLabel);
    });

    ui->listWidget->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
