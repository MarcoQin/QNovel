#include "globalmanager.h"
#include <QDebug>
#include <QApplication>

GlobalManager *GlobalManager::_instance = nullptr;

GlobalManager *GlobalManager::instance()
{
    return _instance ? _instance : new GlobalManager();
}

QString makeQString(py::object s) {
    return QString(std::string(py::str(s)).c_str());
}

void GlobalManager::setHistoryListItems(QListWidget *widget)
{
    try {
        pyMainModule.attr("setHistoryListItems")(widget);
    } catch (const py::error_already_set &e) {
        qDebug() << ">>> Error! Uncaught exception! \n";
        qDebug() << e.what();
    }
}

void GlobalManager::setHistoryLabelInfo(const QString &s, QLabel *label)
{
    QString id = (QString) s.split("#").at(1);
    pyMainModule.attr("setHistoryLabelInfo")(id.toStdString().c_str(), label);
}

//PYBIND11_PLUGIN(master) {
//    py::module m("master", "master");
//    py::class_<QListWidget>(m, "QListWidget")
//            .def("insertItem", (void (QListWidget::*)(int, const QString&))&QListWidget::insertItem);

//    py::class_<QString>(m, "QString");
//    m.def("makeQString", &makeQString);
//}

PYBIND11_ADD_EMBEDDED_MODULE(master)(py::module &m) {
    py::class_<QListWidget>(m, "QListWidget")
            .def("insertItem", (void (QListWidget::*)(int, const QString&))&QListWidget::insertItem)
            .def("addItem", (void (QListWidget::*)(const QString&))&QListWidget::addItem);

    py::class_<QLabel>(m, "QLabel")
            .def("setText", (void (QLabel::*)(const QString&))&QLabel::setText);

    py::class_<QString>(m, "QString");
    m.def("makeQString", &makeQString, "Convert Python string to QString");
}

GlobalManager::GlobalManager()
{
    _instance = this;


    try {

        Py_Initialize();

        QString scriptPath = QCoreApplication::applicationDirPath() + "/../Resources/scripts/";

        pyMainModule = import("main", scriptPath.toStdString());

        //test call py function from cpp
//        pyMainModule.attr("func")();

//        py::object test = pyMainModule.attr("test")();
//        test.attr("p")();
//        py::object r = test.attr("haha")();
//        qDebug() << std::string(py::str(r)).c_str() ;

    } catch (const py::error_already_set &e) {
        qDebug() << ">>> Error! Uncaught exception! \n";
        qDebug() << e.what();
    }

    newFileWindow = new NewFileWindow();
    mainWindow = new MainWindow();
}

void GlobalManager::showMainWindow()
{
    newFileWindow->hide();
    mainWindow->show();
}

void GlobalManager::showNewFileWindow()
{
    mainWindow->hide();
    newFileWindow->show();
}

py::object GlobalManager::import(const std::string &module, const std::string &path)
{
    py::dict locals;
    locals["module_name"] = module;
    locals["path"] = path;

    py::eval<py::eval_statements>(
                "import imp\n"
                "r = imp.find_module(module_name, [path])\n"
                "if r:\n"
                "    new_module = imp.load_module(module_name, r[0], path, ('py', 'U', imp.PY_SOURCE))\n",
                py::globals(),
                locals
    );

    return locals["new_module"];
}
