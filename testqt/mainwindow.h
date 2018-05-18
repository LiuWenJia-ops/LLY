#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#define CTYPE char
typedef class lineheAD//行链表，双向链表
{
public:
    lineheAD();
    ~lineheAD();
    lineheAD * getNext(void){
        return this->next;
    }
    void setNext(lineheAD* np){
        this->next=np;
    }
    lineheAD* getPre(void){
        return pre;
    }
    void setPre(lineheAD* np){
        pre=np;
    }
    int getSize(void){
        return strSize;
    }
    void setSize(int n);//TODO:包括修改其他参数的内容
    CTYPE *chs;
private:
    int strSize;
    lineheAD * next;//下一个行头
    lineheAD * pre;
}lineheAD;

typedef class temText//文字编辑内存
{
    friend class curSOR;
public:
    temText();
    ~temText();
    // curSOR *cur;
    lineheAD* newLine(void);//在最后加一行
    lineheAD* insertLine(lineheAD* preLine,CTYPE* str,int n);//在指定行后插一行
    lineheAD* getFirst() { return firstLine; }
    bool deleteLine(lineheAD* target);//删除行
    int linecounter;//行计数
private:
    lineheAD * firstLine;//第一行
    bool changeMode;//换行模式flag,true为非自动变化

}temText;

typedef class curSOR//逻辑上的光标，不是实际的那个，用于在链表中定位
{
public:
    curSOR();
    ~curSOR();
    lineheAD* getNowLine(){return nowLine;}
    lineheAD* getFirstLine(){return firstLine;}
    int getLineN(){return WHOLETEXT->linecounter;}
    void getAxis(void){std::cout<<'('<<row<<','<<col<<')'<<std::endl;}

    void setFirstLine(lineheAD* lp){this->firstLine=lp;}
    void setNowLine(lineheAD* lp){nowLine=lp;}
    void setAxis(int tR,int tC);//更改坐标，并修改nowline指针
    lineheAD* axisToPtr(int row);//由行数修改指针

    //TODO:insert需要进化注释在内部
    void insertStr(std::string str);//需要先移动光标，插入字符串,判断换行，包含块插入，不修改坐标
    void delFULL(void);// 删库
    void delNL(int type);//清空1/删除10当前行；若删除，则行坐标和指针-1
    void delC(int isbackspace);//需要预设坐标，删除单字符，使用moveArray和delBlcok//TOTEST:得等insert改了才能测试，insert不会自动修改坐标

    //块操作
    std::string cutBlock(int r2,int c2);//需要先移动光标剪切，用了copy和del
    void delBlock(int r2,int c2);//需要移动光标，删除从(r1,c1)到(r2,c2)的内容，注意删完坐标不变
    std::string copyBlock(int r1,int c1,int r2,int c2);//不用先移动光标,取块，string中转,QCHAR的转换函数
    void moveArray(lineheAD* t,int index,int n);//包含index，删除此后n个字符

    //FIXME:测试打印函数
    void printNL(void);//print current
    void printFULL(void);//注意print完在指针在最后一行
private:
    lineheAD* firstLine;
    lineheAD* nowLine;
    temText* WHOLETEXT;
    int row;//从1开始计算
    int col;//从1开始计算，表示光标后字符的序号
}curSOR;

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

    bool openfile(char* addr,curSOR & cur);

    bool savefile(char* addr,curSOR & cur);

    bool newfile(char* addr,curSOR & cur);
private:
    Ui::MainWindow *ui;
};


#endif
 // MAINWINDOW_H
