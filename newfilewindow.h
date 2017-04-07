#ifndef NEWFILEWINDOW_H
#define NEWFILEWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewFileWindow;
}

class NewFileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewFileWindow(QWidget *parent = 0);
    ~NewFileWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::NewFileWindow *ui;
};

#endif // NEWFILEWINDOW_H
