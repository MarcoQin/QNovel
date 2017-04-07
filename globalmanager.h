#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H


#include <pybind11/pybind11.h>
#include <pybind11/eval.h>
#include <pybind11/embedded.h>
#undef B0


#include <QObject>
#include <QString>
#include <QListWidget>
#include <QLabel>


#include "newfilewindow.h"
#include "mainwindow.h"
namespace py = pybind11;


class GlobalManager : public QObject
{
    Q_OBJECT
public:
    static GlobalManager *instance();
    void setHistoryListItems(QListWidget *widget);
    void setHistoryLabelInfo(const QString &s, QLabel *label);
    void showMainWindow();
    void showNewFileWindow();


private:
    static GlobalManager *_instance;
    explicit GlobalManager();
    py::object import(const std::string &module, const std::string &path);
    py::object pyMainModule;

    NewFileWindow *newFileWindow;
    MainWindow *mainWindow;

signals:

public slots:
};

#endif // GLOBALMANAGER_H
