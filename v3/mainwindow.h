#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
//#include <QKeySequence>

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

//signals:
//    void cut();

private slots:

    void on_actionopen_triggered();

    void on_actionnew_triggered();

    void on_actionsave_triggered();

    void on_actionfind_triggered();

    void on_actioncut_triggered();

    void on_actionpaste_triggered();

    void on_actioncopy_triggered();

    void ShowTextRowCol();

//    void on_actionreplace_triggered();
private:
//    Ui::MainWindow *ui; 尝试去掉namespace ui
    QTextEdit *textEdit;
    QAction * openAction;
    QAction * saveAction;
    QAction * newAction;
    QAction * findAction;
    QAction * cutAction;
    QAction * pasteAction;
    QAction * copyAction;
    QLabel * position;
//    QAction * replaceAction;

    FindWindow * findWin;
    //=====================
    myTextEdit textBody;
    std::string addr;
    std::string clipboard;
    QTextCursor tcursor;
    bool isUP=false;
    bool flushFlag=1;
    //bool hasSelection;

};

// class FindWindow : public   QWidget
// {
//     Q_OBJECT
// public:
//     FindWindow();
//     ~FindWindow();

// }

#endif // MAINWINDOW_H
