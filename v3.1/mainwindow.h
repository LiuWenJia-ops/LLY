#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

#include <QTextEdit>
#include <QTextCursor>
#include <QTextBlock>
#include "findwindow.h"
#include "replacewindow.h"

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

    void on_actionreplace_triggered();

    void on_actioncut_triggered();

    void on_actionpaste_triggered();

    void on_actioncopy_triggered();

    void ShowTextRowCol();

private:
//    Ui::MainWindow *ui; 尝试去掉namespace ui
    QTextEdit *textEdit;
    QAction * openAction;
    QAction * saveAction;
    QAction * newAction;
    QAction * cutAction;
    QAction * pasteAction;
    QAction * copyAction;
    QAction * findAction;
    QAction * replaceAction;
    QLabel * position;

    FindWindow * findWin;
    ReplaceWindow * replaceWin;
    //=====================
    myTextEdit textBody;
    std::string addr;
    std::string clipboard;//临时剪切板
    QTextCursor tcursor;
    bool isUP=false;
    bool flushFlag=1;
};

#endif // MAINWINDOW_H
