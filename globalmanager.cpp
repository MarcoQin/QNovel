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

PYBIND11_PLUGIN(master) {
    py::module m("master", "master");
    py::class_<QListWidget>(m, "QListWidget")
            .def("insertItem", (void (QListWidget::*)(int, const QString&))&QListWidget::insertItem);

    py::class_<QString>(m, "QString");
    m.def("makeQString", &makeQString);
}

GlobalManager::GlobalManager()
{
    try {
        Py_Initialize();
        pybind11_init();

        QString scriptPath = QCoreApplication::applicationDirPath() + "/../Resources/scripts/";
        QString bootFile = scriptPath + "main.py";

        py::object main = py::module::import("__main__");
        py::object globals = main.attr("__dict__");
        pyMainModule = import("main", bootFile.toStdString(), globals);

        py::object test = pyMainModule.attr("test")();
        test.attr("p")();
        py::object r = test.attr("haha")();
        qDebug() << std::string(py::str(r)).c_str() ;

    } catch (const py::error_already_set &e) {
        qDebug() << ">>> Error! Uncaught exception! \n";
        qDebug() << e.what();
    }
}

py::object GlobalManager::import(const std::string &module, const std::string &path, pybind11::object &globals)
{
    py::dict locals;
    locals["module_name"] = py::cast(module);
    locals["path"] = py::cast(path);

    py::eval<py::eval_statements>(
                "import imp\n"
                "new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n",
                globals,
                locals
    );

    return locals["new_module"];
}
