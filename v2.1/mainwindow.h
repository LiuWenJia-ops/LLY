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


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void setTwoEnd(int & r,int & c);
    void flush();
    void correctEditCursor(int row,int col);
private slots:

    void on_textEdit_textChanged();

    void on_actionopen_triggered();

    void on_actionnew_triggered();

    void on_actionsave_triggered();

    void ShowTextRowCol();

private:
//    Ui::MainWindow *ui; 尝试去掉namespace ui
    QTextEdit * textEdit;
    QAction * openAction;
    QAction * saveAction;
    QAction * newAction;
    QLabel * position;
};

#endif // MAINWINDOW_H
