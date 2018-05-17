#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arrayline.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionnew_triggered();

    void on_actionsave_triggered();

    void on_actionopen_triggered();

    bool openfile(char* addr,cursor & cur);

    bool savefile(char* addr,cursor & cur);

    bool newfile(char* addr,cursor & cur);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
