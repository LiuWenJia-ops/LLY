#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstring.h"
#include "qfiledialog.h"
#include "qdir.h"
//----------------------
#include <QTextCursor>
#include <QObject>
#include <QTextEdit>
#include <QKeyEvent>
#include <QTextBlock>
//----------------------
#include <iostream>
#include <fstream>
#define CTYPE char
using namespace std;
class lineheAD;
class temText;
class myTextEdit;

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
    void setSize(int n);//TODO:包括修改其他参数的内容
    CTYPE *chs;
private:
    int strSize;
    lineheAD * next;//下一个行头
    lineheAD * pre;
}lineheAD;
lineheAD::lineheAD()
{
    this->pre=nullptr;
    this->next = nullptr;
    chs=(CTYPE*)malloc(sizeof(CTYPE)*101);
    chs[0]='\0';
    strSize=0;
}
lineheAD::~lineheAD()//释放当前行后的blocks
{
    free(chs);
}
void lineheAD::setSize(int n)
{
    strSize=n;
    this->chs[n]='\0';
}
//-------------------------------------------------
typedef class temText//文字编辑内存
{
    friend class myTextEdit;
public:
    temText();
    ~temText();
    // myTextEdit *cur;
    lineheAD* newLine(void);//在最后加一行
    lineheAD* insertLine(lineheAD* preLine,CTYPE* str,int n);//在指定行后插一行
    lineheAD* getFirst() { return firstLine; }
    bool deleteLine(lineheAD* target);//删除行
    int linecounter;//行计数
private:
    lineheAD * firstLine;//第一行
    bool changeMode;//换行模式flag,true为非自动变化

}temText;

temText::temText()
{
    linecounter=0;
    // cur=nullptr;
    firstLine=nullptr;
    firstLine = newLine();
    changeMode=true;
}
temText::~temText()
{
    lineheAD* tem=this->firstLine;
    lineheAD* nextLine;
    while(!tem){
        nextLine=tem->getNext();
        delete tem;
        tem=nextLine;
    }
}
lineheAD* temText::newLine(void)
{
    lineheAD* tem=new lineheAD;
    if(this->firstLine==nullptr){
        this->firstLine=tem;
        this->firstLine->setPre(tem);
    }
    else{//行链表的尾结点的next为空
        lineheAD* lastLine=this->firstLine->getPre();
        lastLine->setNext(tem);
        tem->setPre(lastLine);
        this->firstLine->setPre(tem);
    }
    this->linecounter++;
    return tem;
}
lineheAD* temText::insertLine(lineheAD* preLine,CTYPE* str,int n)//
{
    lineheAD* tempB;
    if(preLine->getNext()==nullptr)
        tempB=this->newLine();
    else{
        tempB=new lineheAD;
        tempB->setPre(preLine);
        tempB->setNext(preLine->getNext());
        tempB->getNext()->setPre(tempB);
        preLine->setNext(tempB);
        this->linecounter++;//上一个分支newline()内部有inc
    }
    for(int i=0;i<n;i++)
        tempB->chs[i]=str[i];
    tempB->setSize(n);
    return tempB;
}
bool temText::deleteLine(lineheAD* target)
{
    if(target==nullptr){
        std::cout<<"target line not exist"<<std::endl;
        return false;
    }
    //TODO:有空可以优化成一个临时变量
    lineheAD* pre=target->getPre();
    lineheAD* next=target->getNext();
    target->getPre()->setNext(target->getNext());
    if(target->getNext()!=nullptr)
        target->getNext()->setPre(target->getPre());
    delete target;
    this->linecounter--;
    return true;
}
//-------------------------------------------------
typedef class myTextEdit//逻辑上的光标，不是实际的那个，用于在链表中定位
{
public:
    myTextEdit();
    ~myTextEdit();
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
    void delNL(int type);//清空1/删除10当前行;若删除，则行坐标和指针-1
    void delC(int isbackspace);//需要预设坐标，删除单字符，使用moveArray和delBlcok//TOTEST:得等insert改了才能测试，insert不会自动修改坐标

    //块操作
    std::string cutBlock(int r2,int c2);//需要先移动光标剪切，用了copy和del
    void delBlock(int r2,int c2);//需要移动光标，删除从(r1,c1)到(r2,c2)的内容，注意删完坐标不变
    std::string copyBlock(int r1,int c1,int r2,int c2);//不用先移动光标,取块，string中转,QCHAR的转换函数
     std::string copyBlock(int r2,int c2);//重载
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
myTextEdit::myTextEdit()
{
    nowLine=nullptr;
    firstLine=nullptr;
    WHOLETEXT=new temText;
    this->setFirstLine(WHOLETEXT->firstLine);
    this->setNowLine(WHOLETEXT->firstLine);
    this->row=1;
    this->col=1;
}
myTextEdit::~myTextEdit(){

}
void myTextEdit::setAxis(int tR,int tC)
{
    this->row=tR;
    this->col=tC;
    nowLine=axisToPtr(tR);
}
lineheAD* myTextEdit::axisToPtr(int row)
{
    lineheAD* tLine=this->firstLine;
    int i=1;
    while(i<row){
        tLine=tLine->getNext();
        i++;
    }
    return tLine;
}

void myTextEdit::insertStr(std::string str)
{
    // std::cout<<"BEGIN insert!!"<<std::endl; //FIXME:
    //TODO:大于100的情况
    //TODO:没有考虑在字符串中间插入的情况
    int cnt=1;
    for(int i=0;i<str.size();i++,cnt++){
        if(str.at(i)=='\n'){//插入新行，移动坐标
            nowLine->setSize(col-1+cnt-1);
            cnt=1;
            row++; col=1;
            nowLine=WHOLETEXT->insertLine(this->nowLine,nullptr,0);
        }else{
            this->nowLine->chs[col-1]=str.at(i);
            col++;
            int newsize=nowLine->getSize()+1;
            nowLine->setSize(newsize);
        }

    }
}
void myTextEdit::delFULL(void)
{
    delete WHOLETEXT;
    WHOLETEXT= new temText;
    this->setFirstLine(WHOLETEXT->firstLine);
    this->setNowLine(WHOLETEXT->firstLine);
    this->row=1;
    this->col=1;
}
void myTextEdit::delNL(int type)
{
    if(type==1||nowLine==firstLine){
        col=1;
        nowLine->setSize(0);
    }
    if(type==10){
        WHOLETEXT->deleteLine(nowLine);
        row--;
        nowLine=axisToPtr(row);
        col=nowLine->getSize()+1;
    }
}
void myTextEdit::delC(int isbackspace)
{
    std::string temp;
    if(isbackspace>0){
        if(col==1){
            temp=copyBlock(row,1,row,nowLine->getSize());
            nowLine=nowLine->getPre();
            row--;col=nowLine->getSize()+1;
            insertStr(temp);
            WHOLETEXT->deleteLine(nowLine->getNext());
        }else{
            moveArray(nowLine,col-1,1);
            col--;
            nowLine->setSize(nowLine->getSize()-1);
        }
    }else{
        if(col==nowLine->getSize()+1){
            temp=copyBlock(row+1,1,row+1,nowLine->getNext()->getSize());
            insertStr(temp);
            WHOLETEXT->deleteLine(nowLine->getNext());
        }else{
            moveArray(nowLine,col,1);
            nowLine->setSize(nowLine->getSize()-1);
        }
    }
}
void myTextEdit::moveArray(lineheAD* t,int index,int n)
{
    int DELTA=t->getSize()-(index+n);
    for(int i=0;i<=DELTA;i++)//=号是因为把终结符也移动了
        t->chs[index+i]=t->chs[index+n+i];
}

std::string myTextEdit::cutBlock(int r2,int c2)
{
    std::string rs=copyBlock(row,col,r2,c2);
    delBlock(r2,c2);
    return rs;
}
void myTextEdit::delBlock(int r2,int c2)
{
    int oC=col;
    lineheAD* endL=axisToPtr(r2);
    if(row==r2){
        moveArray(nowLine,col-1,c2-col+1);
        nowLine->setSize(nowLine->getSize()-(c2-col+1));
    }
    else{
        moveArray(nowLine,col-1,nowLine->getSize()-col+1);
        std::string mt=copyBlock(r2,1,r2,c2);
        std::cout<<mt<<std::endl;
        insertStr(mt);
        while(nowLine->getNext()!=endL){
            WHOLETEXT->deleteLine(nowLine->getNext());
        }
        WHOLETEXT->deleteLine(endL);
        nowLine->setSize(oC+c2-1);
    }
    col=oC;
    getAxis();
}

std::string myTextEdit::copyBlock(int r1,int c1,int r2,int c2)
{
    std::string rs;
    std::string add;
    lineheAD* iLine=axisToPtr(r1);
    if(r1==r2)
        rs.append(&(iLine->chs[c1-1]),c2-c1+1);
    else{
        add=&(iLine->chs[c1-1]);
        rs.append(add);
        int i=r1+1;
        while(i<r2){
            rs.append("\n");
            iLine=iLine->getNext();
            rs.append(iLine->chs);
            i++;
        }
        iLine=iLine->getNext();
        rs.append("\n");
        rs.append(iLine->chs,c2);
    }
    return rs;
}
std::string myTextEdit::copyBlock(int r2,int c2)
{
    std::string rs;
    std::string add;
    lineheAD* iLine=axisToPtr(row);
    if(row==r2)
        rs.append(&(iLine->chs[col-1]),c2-col+1);
    else{
        add=&(iLine->chs[col-1]);
        rs.append(add);
        int i=row+1;
        while(i<r2){
            rs.append("\n");
            iLine=iLine->getNext();
            rs.append(iLine->chs);
            i++;
        }
        iLine=iLine->getNext();
        rs.append("\n");
        rs.append(iLine->chs,c2);
    }
    return rs;
}


void myTextEdit::printNL(void)
{
    for(int i=0;nowLine->chs[i]!='\0';i++)
        std::cout<<nowLine->chs[i];
    std::cout<<std::endl;

}
void myTextEdit::printFULL(void)
{
    for(int i=1;i<=WHOLETEXT->linecounter;i++){
        setAxis(i,1);
        printNL();
    }
}
//---------------------------------------------------
myTextEdit textBody;
char * addr;
string buffer;
//------------------------------------------------
void flush(Ui::MainWindow * uimw){
    QString qstr;
    uimw->textEdit->clear();
    lineheAD *tem=textBody.getFirstLine();
    while(tem!=nullptr){
        qstr=tem->chs;
        uimw->textEdit->append(qstr);
    }
}
void setTwoEnd(Ui::MainWindow * uimw,int & r,int & c){//FIXME:不能传ui???
    int r2,c2;
    QTextCursor cursor = uimw->textEdit->textCursor();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    if(!cursor.hasSelection())
        return; // No selection available

    cursor.setPosition(start);
    textBody.setAxis(cursor.blockNumber(),cursor.position() - cursor.block().position());
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    r=cursor.blockNumber();
    c=cursor.position() - cursor.block().position();
}
//-------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Miniword");

       ui->textEdit = new QTextEdit;
       ui->textEdit->installEventFilter(this);
       //textEdit->viewPort()->installEventFilter(this);
       //TODO:tcursor未初始化
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{ 
    QTextCursor tcursor;
    //+状态栏
     if (obj == ui->textEdit) {
        //  int flag;
        //  if (tcursor.hasSelection())
        //     flag = 1;
        //  else
        //     flag = 0;

         if (event->type() == QEvent::KeyPress) {
             tcursor = ui->textEdit->textCursor();
             //强制转换事件类型
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

             //键盘移动光标位置
             if (keyEvent->key() == Qt::Key_Left){
                 ui->textEdit->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
                 textBody.setAxis(tcursor.blockNumber(),tcursor.position() - tcursor.block().position());
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Right){
                 ui->textEdit->moveCursor(QTextCursor::Right, QTextCursor::MoveAnchor);
                 textBody.setAxis(tcursor.blockNumber(),tcursor.position() - tcursor.block().position());
                 //接口
                 //setKeyAction(right,line,row);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Up){
                 ui->textEdit->moveCursor(QTextCursor::Up, QTextCursor::MoveAnchor);
                 textBody.setAxis(tcursor.blockNumber(),tcursor.position() - tcursor.block().position());
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Down){
                 ui->textEdit->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
                 textBody.setAxis(tcursor.blockNumber(),tcursor.position() - tcursor.block().position());
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_End){
                 ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
                 textBody.setAxis(tcursor.blockNumber(),tcursor.position() - tcursor.block().position());
                 return true;
             }

             else if (keyEvent->key() == Qt::Key_Backspace){
                  if (tcursor.hasSelection()){//已做块选择
                    int r2,c2;
                    setTwoEnd(ui,r2,c2);
                    textBody.delBlock(r2,c2);//FIXME:块尾
                  }
                 textBody.delC(1);
             }
             else if (keyEvent->key() == Qt::Key_Delete){
                  if (tcursor.hasSelection()){//已做块选择
                    int r2,c2;
                    setTwoEnd(ui,r2,c2);
                    textBody.delBlock(r2,c2);//FIXME:块尾
                  }
                  textBody.delC(0);
             }
            //  //快捷键
            //  else if (event->modifiers() == Qt::ShiftModifier){
            //      //Q:能否能保持keep
            //      if (keyEvent->key() == Qt::Key_Left)
            //          textEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
            //      if (keyEvent->key() == Qt::Key_Right)
            //          textEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);
            //      else
            //          QTextEdit::keyPressEvent(event);
            //  }
             else if(keyEvent->modifiers() == Qt::ControlModifier){
                if(keyEvent->key()==Qt::Key_V){//粘贴
                    textBody.insertStr(buffer);   
                }
                if(keyEvent->key()==Qt::Key_F){//查找
                    //弹窗，请求输入
                    QString target;
                    //TODO:查找模式：向前向后，全字匹配，大小写
                    //写成循环，每返回一个值都要刷新输出
                }
                if(keyEvent->key()==Qt::Key_H){//替代
                    //弹窗，请求两个输入
                    QString target,filler;
                    //TODO:替代模式：向前向后，
                                //全字匹配，大小写，
                                //逐个替换，全部替换:区别在于刷新输出的时机不同
                    //将每次查找得到的块尾坐标作为参数传给替代函数
                    
                }
                int r2,c2;//头已经在textBody里面了
                setTwoEnd(ui,r2,c2);
                if(keyEvent->key()==Qt::Key_C)//复制
                    buffer=textBody.copyBlock(r2,c2);
                if(keyEvent->key()==Qt::Key_X)//剪切
                    buffer=textBody.cutBlock(r2,c2);
             }
             else if (keyEvent->key()<=int(Qt::Key_Z)&&keyEvent->key()>=int(Qt::Key_A)){//Q:输入字符
                    //TODO:加入标点符号
                string tem;
                tem.push_back(char(int(keyEvent->key())-int(Qt::Key_A)+int('A')));
                textBody.insertStr(tem);
             }
             else if (keyEvent->key()<=int(Qt::Key_9)&&keyEvent->key()>=int(Qt::Key_0)){
                 string tem;
                 tem.push_back(char(int(keyEvent->key())-int(Qt::Key_0)+int('0')));
                 textBody.insertStr(tem);
             }
             else{
                 // pass the event on to the parent class
                 return QMainWindow::eventFilter(obj, event);
             }
            
         }
//         else if (event->type() == QEvent::MouseButtonPress){
//              QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

//             if (mouseEvent->button() == Qt::LeftButton){
//                 QTextEdit::mousePressEvent(mouseEvent);
//                 tcursor = textEdit->textCursor();
//                 int row = tcursor.columnNumber();
//                 int line = tcursor.blockNumber();
//                 //接口
//                 //setMouseAction(move,line,row);
                 
//             }
//         }
//         else if (event->type() == QEvent::MouseMove){
//             QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

//             if (){

//                 textEdit->moveCursor(QTextCursor::, QTextCursor::KeepAnchor)
//             }
//         }
         else {
             return false;
         }

         flush(ui);//将内存写入显示框内
         return true;
     }
     else{
         // pass the event on to the parent class
         return QMainWindow::eventFilter(obj, event);
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}
//-------------------------------------------------
void MainWindow::on_actionopen_triggered()
{
    //    //TODO:如果已经打开了一份文件还想打开第二份
    //    if(addr[0]){//已经打开过一份
    //       // TODO:询问是否保存当前文件并新建,
    //        //若否，直接返回;
    //        //若是，保存文件
    //        {
    //            savefile(addr,textBody);
    //        }
    //    }//清空body，还原cur位置
        QString qsStr;
        std::string media;
        QString filename = QFileDialog::getOpenFileName(//得到文件路径
                            this,
                            tr("Open Document"),
                            QDir::currentPath(),//打开程序地址下的目录
                            "Text files (*.txt )");//file filter,只能打开txt
        if (!filename.isNull()) { //用户选择了文件
            QByteArray ba=filename.toLatin1();
            addr=ba.data();//add存储的是绝对地址
            std::ifstream buf(addr);
            //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)

            while (std::getline(buf,media)){
                media.append("\n");
                qsStr = QString(media.c_str());
                ui->textEdit->append(qsStr);//显示到textedit
                textBody.insertStr(media);//TODO:将string插入到linehead里
            }
         }
}

void MainWindow::on_actionnew_triggered()
{
    //   if(addr[0]){
    //       // TODO:询问是否保存当前文件并新建,
    //        //若否，直接返回;
    //        //若是，保存文件
    //        {
    //            savefile(addr,textBody);
    //            addr[0]="\0";
    //        }
    //   }//清空body，还原cur位置
      textBody.delFULL();
      ui->textEdit->clear();
}

void MainWindow::on_actionsave_triggered()
{
    //    if(!addr[0]){//TODO:新建的文件无原地址，应该有什么打开系统文件夹的操作
    //        //TODO:输入保存路径
    //    }
        std::ofstream buf(addr);
        //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)
        lineheAD * tem=textBody.getFirstLine();
        while(tem!=nullptr){
           buf<<tem->chs<<std::endl;
            tem=tem->getNext();
        }
       *addr='\0';
}

void MainWindow::on_textEdit_textChanged()
{

}



