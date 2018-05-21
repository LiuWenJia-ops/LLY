
#include "C:/Users/sophie1998/Documents/GitHub/LLY/testqt/mainwindow.h"
#include "ui_mainwindow.h"
//file operation
#include "qstring.h"
#include "qfiledialog.h"
#include "qdir.h"

static char addr[1000];
static myTextEdit superText;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Miniword");

       textEdit = new QTextEdit;
       textEdit->installEventFilter(this);
       //textEdit->viewPort()->installEventFilter(this);
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    //+状态栏
     if (obj == textEdit) {
         if (tcursor.hasSelection())
             int flag = 1;
         else
             int flag = 0;


         if (event->type() == QEvent::KeyPress) {
             tcursor = textEdit->textCursor();
             //强制转换事件类型
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

             //键盘移动光标位置
             if (keyEvent->key() == Qt::Key_Left){
                 textEdit->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
                 //int row = tcursor.position() - tcursor.block().position();
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(left,line,row);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Right){
                 textEdit->moveCursor(QTextCursor::Right, QTextCursor::MoveAnchor);
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(right,line,row);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Up){
                 textEdit->moveCursor(QTextCursor::Up, QTextCursor::MoveAnchor);
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(up,line,row);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Down){
                 textEdit->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(down,line,row);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_End){
                 textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(end,line,row);
                 return true;
             }

             else if (keyEvent->key() == Qt::Key_Backspace){
                 if (flag == 1)//已做块选择
                     tcursor.clearSelection();
                 tcursor.deletePreviousChar();
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //if (!myTextEdit.atStart())
                 //接口(区分段落？首尾？
                 //setKeyAction(backspace,line,row);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Delete){
                 if (flag == 1)
                     tcursor.clearSelection();
                 tcursor.deleteChar();//Q
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //if (!cursor.atStart())
                 //接口(区分段落？首尾？
                 //setKeyAction(delete,line,row);
                 return true;
             }
             //快捷键
             else if (event->modifiers() == Qt::ShiftModifier){
                 //Q:能否能保持keep
                 if (keyEvent->key() == Qt::Key_Left)
                     textEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
                 if (keyEvent->key() == Qt::Key_Right)
                     textEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);


                 else
                     QTextEdit::keyPressEvent(event);
             }
             else if(keyEvent->modifiers() == Qt::ControlModifier){
                if(KeyEvent->key()==Qt::Key_V){//粘贴
                    //curSOR内有起始光标
                    //把buffer插入光标以后
                    superText.insertStr(buffer);
                    //显示变化
                    
                }

                int row2,col2;//头已经在superText里面了
                 //得到块首位的行列号，
                    //把返回的string存到全局变量buffer里面
                if(KeyEvent->key()==Qt::Key_C&&flag == 1){//复制
                    buffer=superText.copyBlock(row2,col2);
                }
                if(KeyEvent->key()==Qt::Key_X&&flag == 1){//剪切
                     buffer=superText.cutBlock(row2,col2);
                      //显示变化
            }

             else if (){//Q:输入字符



             }
             else{
                 // pass the event on to the parent class
                 return QMainWindow::eventFilter(obj, event);
             }

             return true;
         }
         else if (event->type() == QEvent::MouseButtonPress){
              QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

             if (mouseEvent->button() == Qt::LeftButton){
                 QTextEdit::mousePressEvent(mouseEvent);
                 tcursor = textEdit->textCursor();
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setMouseAction(move,line,row);
                 return true;
             }
         }
         else if (event->type() == QEvent::MouseMove){
             QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

             if (){

                 textEdit->moveCursor(QTextCursor::     , QTextCursor::KeepAnchor)
             }
         }
         else {
             return false;
         }
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

bool MainWindow::openfile(char* addr,myTextEdit & textBody){//XXX:打开文件的操作:系统化文件夹窗口里选取
//    //TODO:如果已经打开了一份文件还想打开第二份
//    if(addr[0]){//已经打开过一份
//       // TODO:询问是否保存当前文件并新建,
//        //若否，直接返回；
//        //若是，保存文件
//        {
//            savefile(addr,textBody);
//        }
//    }//清空body，还原cur位置
    QString filename = QFileDialog::getOpenFileName(//得到文件路径
                        this,
                        tr("Open Document"),
                        QDir::currentPath(),//打开程序地址下的目录
                        "Text files (*.txt )");//file filter,只能打开txt

    if (!filename.isNull()) { //用户选择了文件
        QByteArray ba=filename.toUTF8();
        addr=ba.data();//add存储的是绝对地址 TOTEST:（函数内部的const是全局不变的吗？）

        std::ifstream buf(addr);
        //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)
        std::string media;
        while (std::getline(buf,media)){
            media.append("\n");
            textBody.insertStr(media);//TODO:将string插入到linehead里
            qsStr = QString(media.c_str());
            ui->textEdit->append(qsStr);//显示到textedit
        }
        return true;
    } else // 用户取消选择
        return false;
}
//TODO: 退出之前询问是否保存

bool MainWindow::savefile(char*  addr,myTextEdit & textBody){
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
 //   addr[0]="\0";
    return true;
}

bool MainWindow::newfile(char* addr,myTextEdit & textBody){
//   if(addr[0]){
//       // TODO:询问是否保存当前文件并新建,
//        //若否，直接返回；
//        //若是，保存文件
//        {
//            savefile(addr,superText);
//            addr[0]="\0";
//        }
//   }//清空body，还原cur位置
  textBody.delFULL();
}
void MainWindow::on_actionnew_triggered()
{
    newfile(addr,superText);
}

void MainWindow::on_actionsave_triggered()
{
    savefile(addr,superText);
}

void MainWindow::on_actionopen_triggered()
{
    openfile(addr,superText);
}
//------------------------------------------------------------------------

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
//------------------------------------

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

//----------------------------------
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
