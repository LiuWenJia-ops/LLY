#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <QToolBar>
#include <QFontComboBox>
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
    QTextEdit * getTextEdit(){return this->textEdit;};
protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件过滤器
    void setTwoEnd(int & r,int & c);//返回块选的第二个坐标
    void flush();//内存向显示模块刷新
    void correctEditCursor(int row,int col);//统一内存坐标和显示模块的坐标
private slots:
//-----------------------------------文本编辑功能操作槽函数----------------------------
    //----------------文件操作----------------
    void on_actionopen_triggered();//打开文件

    void on_actionnew_triggered();//新建文件

    void on_actionsave_triggered();//保存文件
    //----------------搜索操作----------------
    void on_actionfind_triggered();//查找字符串

    void on_actionreplace_triggered();//替换字符串
    //----------------块操作-----------------
    void on_actioncut_triggered();//剪切

    void on_actionpaste_triggered();//粘贴

    void on_actioncopy_triggered();//复制

//--------------------------------------创建排版控制工具栏---------------------------
    void ShowCurrentFormatChanged(const QFont &fmt);

    void ShowSizeSpinBox(QString);
    
    void ShowFontComboBox(QString);

    void ShowItalictooBar();

    void ShowBoldtooBar();

    void ShowUnderlinetooBar();

    void ShowTextRowCol();//状态栏显示
private:
    QTextEdit *textEdit;//显示组件
//-----------------------------------文本编辑功能操作菜单栏显示------------------------------ 
    QAction * openAction;
    QAction * saveAction;
    QAction * newAction;
    QAction * cutAction;
    QAction * pasteAction;
    QAction * copyAction;
    QAction * findAction;
    QAction * replaceAction;
    QLabel * position;//光标状态显示
//--------------------------------------查找子窗口------------------------------------------
    FindWindow * findWin;//查找窗口
    ReplaceWindow * replaceWin;//替换窗口

    myTextEdit textBody;//自定义文本内存
    std::string addr;//文件地址
    std::string clipboard;//临时剪切板
    QTextCursor tcursor;//用于修改显示光标的中转光标
    bool isUP=false;//大小写标志
    bool flushFlag=1;//刷新保护标志
//-----------------------------------------排版控件-------------------------------------------
    QLabel *fontLabel;                          //字体设置项
    QFontComboBox *fontComboBox;                //字体选框
    QLabel *fontLabel2;                         //大小
    QComboBox *sizeComboBox;                    //大小选框
    QToolButton *BoldtooBar;                       //加粗按钮
    QToolButton *ItalictooBar;                     //斜体
    QToolButton *UnderlinetooBar;                  //下划线
    QToolBar *FonttoolBar;                      //字体工具栏
};

#endif // MAINWINDOW_H
