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

PYBIND11_ADD_EMBEDDED_MODULE(master)(py::module &m) {
    py::class_<QListWidget>(m, "QListWidget")
            .def("insertItem", (void (QListWidget::*)(int, const QString&))&QListWidget::insertItem);

    py::class_<QString>(m, "QString");
    m.def("makeQString", &makeQString, "Convert Python string to QString");
}

void GlobalManager::setHistoryListItems(QListWidget *widget)
{
//    py::object obj = py::cast(static_cast<void *>(widget));
//    pyMainModule.attr("setHistoryListItems")(py::cast(widget));
    try {

        pyMainModule.attr("setHistoryListItems")(widget);
    } catch (const py::error_already_set &e) {
        qDebug() << ">>> Error! Uncaught exception! \n";
        qDebug() << e.what();
    }
}

//PYBIND11_PLUGIN(master) {
//    py::module m("master", "master");
//    py::class_<QListWidget>(m, "QListWidget")
//            .def("insertItem", (void (QListWidget::*)(int, const QString&))&QListWidget::insertItem);

//    py::class_<QString>(m, "QString");
//    m.def("makeQString", &makeQString);
//}


GlobalManager::GlobalManager()
{
    _instance = this;
    qDebug() << "Init";
    try {

        Py_Initialize();
//        pybind11_init();

        qDebug() << "After Py_Initialize()";

        QString scriptPath = QCoreApplication::applicationDirPath() + "/../Resources/scripts/";

        py::object main = py::module::import("__main__");
        qDebug() << "After get main";
        py::object globals = main.attr("__dict__");
        qDebug() << "After get globals";
        pyMainModule = import("main", scriptPath.toStdString(), globals);
        qDebug() << "After get pyMainModule";

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
}

py::object GlobalManager::import(const std::string &module, const std::string &path, pybind11::object &globals)
{
    py::dict locals;
    locals["module_name"] = module;
    locals["path"] = path;

    qDebug() << "before eval";

    py::eval<py::eval_statements>(
                "print('haha')\n"
                "import imp\n"
                "print(module_name)\n"
                "print(path)\n"
                "print(type(module_name))\n"
                "r = imp.find_module(module_name, [path])\n"
                "print(r)\n"
                "if r:\n"
                "    new_module = imp.load_module(module_name, r[0], path, ('py', 'U', imp.PY_SOURCE))\n",
//                "new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n",
                globals,
//                py::globals(),
                locals
    );

    qDebug() << "after eval";

    return locals["new_module"];
}
