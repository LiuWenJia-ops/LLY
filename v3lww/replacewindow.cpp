#include "replacewindow.h"
#include "mainwindow.h"

ReplaceWindow::ReplaceWindow(QWidget* parent,myTextEdit * textBodyIn):
    QDialog(parent),textTBFptr(textBodyIn)
{
    mode=1;//默认不区分大小写
    hasResult=false;
    nowResult=1;
    renewFlag=0;
    this->setWindowTitle(tr("Replace"));
    this->setGeometry(100,100,400,300);
    //------------------参数初始化------------
    QLabel *findLineLabel = new QLabel(tr("Find:"),this);    
    findLineEdit = new QLineEdit(this);//待查找的串
    QLabel *replaceLineLabel = new QLabel(tr("Replace:"),this);
    replaceLineEdit = new QLineEdit(this);//替换的串 
    QLabel *findLabel = new QLabel(tr("Mode:"),this);    
    QComboBox *findComboBox = new QComboBox(this);
    findComboBox->addItem(tr("Ingnore C"));
    findComboBox->addItem(tr("Don't ingnore C"));
    QPushButton *btn1= new QPushButton(tr("Find next"), this);
    QPushButton *btn2= new QPushButton(tr("Replace"), this);

    QVBoxLayout *layout= new QVBoxLayout(this);
    layout->addWidget(findLineLabel);
    layout->addWidget(findLineEdit);
    layout->addWidget(replaceLineLabel);
    layout->addWidget(replaceLineEdit);
    layout->addWidget(findLabel);
    layout->addWidget(findComboBox);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    setLayout(layout);
    //---------------绘制完成-----------------
    connect(findComboBox, SIGNAL(activated(int)),this, SLOT(modeChanged(int)));
    connect(btn1, &QPushButton::pressed, this, &ReplaceWindow::showFindText);
    connect(btn2, &QPushButton::pressed, this, &ReplaceWindow::replaceFindText);
    connect(findLineEdit,SIGNAL(textChanged(QString)),this,SLOT(renewSearchResult()));
}

ReplaceWindow::~ReplaceWindow()
{
    delete resultPtr;
}
void ReplaceWindow::renewSearchResult()
{//文本内容一旦变化,结果参数也变化
    hasResult=false;
    nowResult=1;
    qDebug()<<"renew hasflag:"<<int(hasResult);
}

void ReplaceWindow::replaceFindText()//FIXME:如果replace多次的话，因为nowresult数字不会变，而number会变，从而会自动往下走。。。需要解决重复replace的问题
{
    qDebug()<<"in replace";
    if(!hasResult)//TODO:没结果不能替换
        return;
    if(renewFlag){//防止重复replace自动前进
        QString rpstr=replaceLineEdit->text();
        std::string putstr=rpstr.toLocal8Bit().constData();//QString->string
        qDebug()<<"replace the"<<nowResult<<"result";
        qDebug()<<"put in string:"<<rpstr;
        resultPtr->replace(nowResult,putstr);
        qDebug()<<"back from replace";
        flush(putstr);
        if(nowResult==1||nowResult==number)
            nowResult=number-1;
        else
            nowResult--;
        number=resultPtr->getNumber();
        renewFlag=0;
    }
}
void ReplaceWindow::showFindText()
{
    qDebug()<<"start hasflag:"<<int(hasResult);
    if(!hasResult){
        qDebug()<<"first hasflag:"<<int(hasResult);
        QString qstr = findLineEdit->text();//查找内容的
        str=qstr.toLocal8Bit().constData();//QString->string
        resultPtr=new searchResult(this->textTBFptr,str,this->mode);
       
        number=resultPtr->getNumber();
        if(!number){//没搜索到结果
            //TODE:提示窗口没找到
            int ret = QMessageBox::warning(this, tr("NO RESULT!"),
                                           tr("Change your string,idiot."),
                                           QMessageBox::Ok | QMessageBox::Ok
                                           | QMessageBox::Ok,
                                           QMessageBox::Ok);//FIXME:???为啥我要这么写
             qDebug()<<"FIND:no result";
            return;
        }
       //------------------有结果---------------------
        nowResult=1;
        hasResult=true;

        mwPtr=(MainWindow *)parentWidget();
        mwTextEditPtr=mwPtr->getTextEdit();//指向父窗口private成员textedit
        temCursor=mwTextEditPtr->textCursor();
        correctEditCursor(nowResult);
    }else{
         qDebug()<<"nowresult:"<<nowResult;
         if(number&&nowResult<=number){//还没替换完
            qDebug()<<"nownumber:"<<number;
            nowResult=nowResult%number+1;//循环显示
            qDebug()<<"nowresult:"<<nowResult;
            correctEditCursor(nowResult);
        }else{
            int ret = QMessageBox::warning(this, tr("REPLACED ALL!"),
                                           tr("All the strings have been replaced."),
                                           QMessageBox::Ok | QMessageBox::Ok
                                           | QMessageBox::Ok,//FIXME:???为啥我要这么写
                                           QMessageBox::Ok);
            return;
        }
    }
}

void ReplaceWindow::modeChanged(int index)
{
    if(index==0){
            this->mode=1;//无视大小写
            qDebug()<<"mode change:"<<mode;
    }else if(index==1){
            this->mode=0;//区分大小写
            qDebug()<<"mode change:"<<mode;
    }
}

int  ReplaceWindow::getAbsadd(int rowCount, int colCount)
{
    int add=0;
    lineheAD* linePtr=textTBFptr->getFirstLine();
    for(int i=1;i<rowCount;i++){
        add+=1+linePtr->getSize();
        linePtr=linePtr->getNext();
    }
    for(int i=1;i<colCount;i++)
        add++;
    return add;
}

void ReplaceWindow::correctEditCursor(std::string PUTin)
{
        textTBFptr->setAxis(textTBFptr->getRow(),textTBFptr->getCol()-PUTin.size());//插入后col要向前退
        int absadd=getAbsadd(textTBFptr->getRow(),textTBFptr->getCol());
        temCursor.setPosition(absadd);//TextEdit里的光标
        temCursor.setPosition(absadd+PUTin.size(),QTextCursor::KeepAnchor);
        mwTextEditPtr->setTextCursor(temCursor);//显示更新
}
void ReplaceWindow::correctEditCursor(int now)
{
    renewFlag=1;//向下搜索后才有flag给replace
    int * nowWhere=resultPtr->getSpecificOne(now);
    textTBFptr->setAxis(nowWhere[0],nowWhere[1]);
    int absadd=getAbsadd(textTBFptr->getRow(),textTBFptr->getCol());
    temCursor.setPosition(absadd);//TextEdit里的光标
    temCursor.setPosition(absadd+str.size(),QTextCursor::KeepAnchor);//str总是存储最新的目标string
    mwTextEditPtr->setTextCursor(temCursor);//显示更新
}
void ReplaceWindow::flush(std::string putin)
{//TESTDONE: flush后必须矫正坐标
    QString qstr;
    mwTextEditPtr->clear();
    lineheAD *tem=textTBFptr->getFirstLine();
    qDebug()<<"---check text from memory---";
    while(tem!=nullptr){
        qstr=QString::fromUtf8(tem->chs);
        qDebug()<<qstr;
        mwTextEditPtr->append(qstr);
        tem=tem->getNext();
    }
    qDebug()<<"---------------------";
    correctEditCursor(putin);
}
