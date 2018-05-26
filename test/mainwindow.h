#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QObject>
#include <QTextEdit>
#include <QTextCursor>
#include <QKeyEvent>
#include <QTextBlock>

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

    void on_textEdit_textChanged();

    void on_actionopen_triggered();

    void on_actionnew_triggered();

    void on_actionsave_triggered();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void flush();//
    void setTwoEnd(int & r,int & c);//

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QTextCursor tcursor;
};

//只有在派生类中才可以通过派生类对象访问基类的protected成员。
//可以被该类中的函数、子类的函数、以及其友元函数访问,但不能被该类的对象访问
class MyEvent : private QTextEdit
{
public:
    void keyPressEvent(QKeyEvent *e){
        QTextEdit::keyPressEvent(e);
    }
    void mousePressEvent(QMouseEvent *e){
        QTextEdit::mousePressEvent(e);
    }
    void mouseMoveEvent(QMouseEvent *e){
        QTextEdit::mouseMoveEvent(e);
    }
    void mouseReleaseEvent(QMouseEvent *e){
        QTextEdit::mouseReleaseEvent(e);
    }
};

#endif // MAINWINDOW_H
