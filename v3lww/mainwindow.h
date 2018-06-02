#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include "findwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTextEdit * getTextEdit()
    {return this->textEdit;};

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void setTwoEnd(int & r,int & c);
    void flush();
    void correctEditCursor(int row,int col);
private slots:

    void on_actionopen_triggered();

    void on_actionnew_triggered();

    void on_actionsave_triggered();

    void on_actionfind_triggered();

//    void on_actionreplace_triggered();
private:
//    Ui::MainWindow *ui; 尝试去掉namespace ui
    QTextEdit *textEdit;
    QAction * openAction;
    QAction * saveAction;
    QAction * newAction;
    QAction * findAction;
//    QAction * replaceAction;

    FindWindow * findWin;
    //=====================
    myTextEdit textBody;
    std::string addr;
    QTextCursor tcursor;
    bool isUP=false;
    bool flushFlag=1;
};

// class FindWindow : public   QWidget
// {
//     Q_OBJECT
// public:
//     FindWindow();
//     ~FindWindow();

// }

#endif // MAINWINDOW_H
