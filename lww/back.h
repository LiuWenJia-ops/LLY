#ifndef BACK_H
#define BACK_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#define CTYPE char
//using namespace std;
class lineheAD;
class temText;
class myTextEdit;
class searchResult;

typedef class searchResult
{
public:
    searchResult();
    searchResult(myTextEdit* TEXT,std::string toFind);
    ~searchResult();
    int getNumber(void){
        return Number;
    }
    int* getSpecificOne(int INDEX){
        return allResults.at(INDEX);
    }
    int nowINDEX;
    void printALL(void);
    void getNextVal(std::string substr,int* next);
    int Index_KMP(std::string S,std::string T,int pos,const int* const next, bool ignCap);
private:
    void search(void);
    std::string toFind;
    int Number;
    myTextEdit* TEXT;
    std::vector<int*> allResults;//[n][3]
}searchResult;
//-------------------------------------------
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
    void setSize(int n);//包括修改其他参数的内容
    CTYPE *chs;
    int arySIze;//size of chs
private:
    int strSize;
    lineheAD * next;//下一个行头
    lineheAD * pre;
}lineheAD;

typedef class temText//文字编辑内存
{
    friend class myTextEdit;
public:
    temText();
    ~temText();
    // myTextEdit *cur;
    lineheAD* newLine(void);//在最后加一行
    lineheAD* insertLine(lineheAD* preLine,CTYPE* str,int n);//在指定行后插一行
    bool deleteLine(lineheAD* target);//删除行
    int linecounter;//行计数
private:
    lineheAD * firstLine;//第一行
    bool changeMode;//换行模式flag,true为非自动变化

}temText;

//-------------------------------------------------
typedef class myTextEdit//row和col等价于实际光标
{
public:
    myTextEdit();
    ~myTextEdit();
    lineheAD* getFirstLine(void) {return firstLine;}
    lineheAD* getNowLine(){return nowLine;}
    int getLineN(){return WHOLETEXT->linecounter;}
    void getAxis(void){std::cout<<'('<<row<<','<<col<<')'<<std::endl;}
    int getRow(){return row;}
    int getCol(){return col;}

    void setFirstLine(lineheAD* lp){this->firstLine=lp;}
    void setNowLine(lineheAD* lp){nowLine=lp;}
    void setAxis(int tR,int tC);//更改坐标，并修改nowline指针
    lineheAD* axisToPtr(int row);//由行数修改指针
    //TODO: txt space problem
    void insertStr(std::string str);//需要先移动光标，插入字符串,包含判断换行，结束后光标在插入块的后面
    void delFULL(void);// 删库
    void delNL(int type);//清空1/删除10当前行；若删除，则行坐标和指针-1
    void delC(int isbackspace);//需要预设坐标，删除单字符，使用moveArray和delBlcok

    //块操作
    std::string cutBlock(int r2,int c2);//TOTEST:需要先移动光标剪切，用了copy和del
    void delBlock(int r2,int c2);//需要移动光标，删除从(r1,c1)到(r2,c2)的内容，注意删完坐标不变
    std::string copyBlock(int r1,int c1,int r2,int c2);//不用先移动光标,取块，string中转,QCHAR的转换函数
    std::string copyBlock(int r2,int c2);
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
}myTextEdit;


//---------------------------------------------------

#endif // BACK_H
