#include "findwindow.h"
#include "mainwindow.h"
int getAbsadd(int * relativeAdd,myTextEdit * textTBFptr);

FindWindow::FindWindow(QWidget* parent,myTextEdit * textBodyIn):
    QDialog(parent),textTBFptr(textBodyIn)
{
    mode=1;//默认不区分大小写
    hasResult=false;
    nowResult=1;
    this->setWindowTitle(tr("Find"));
    this->setGeometry(100,100,400,300);
    //------------------参数初始化------------
    QLabel *findLabel = new QLabel(tr("Mode:"),this);    
    QComboBox *findComboBox = new QComboBox(this);
    findComboBox->addItem(tr("Ingnore C"));
    findComboBox->addItem(tr("Don't ingnore C"));
    findLineEdit = new QLineEdit(this);
    QPushButton *btn= new QPushButton(tr("Find next"), this);

    QVBoxLayout *layout= new QVBoxLayout(this);
    layout->addWidget(findLineEdit);
    layout->addWidget(findLabel);
    layout->addWidget(findComboBox);
    layout->addWidget(btn);
    setLayout(layout);
    //---------------绘制完成-----------------
    connect(findComboBox, SIGNAL(activated(int)),this, SLOT(modeChanged(int)));
    connect(btn, &QPushButton::pressed, this, &FindWindow::showFindText);
    connect(findLineEdit,SIGNAL(textChanged(QString)),this,SLOT(renewSearchResult()));
}

FindWindow::~FindWindow()
{
}
void FindWindow::renewSearchResult(){//文本内容一旦变化,结果参数也变化
    hasResult=false;
    nowResult=1;
    qDebug()<<"renew hasflag:"<<int(hasResult);
}
void FindWindow::showFindText()
{
    qDebug()<<"start hasflag:"<<int(hasResult);
    if(!hasResult){
        qDebug()<<"first hasflag:"<<int(hasResult);
        QString qstr = findLineEdit->text();
        std::string str=qstr.toLocal8Bit().constData();//QString->string
        resultPtr=new searchResult(this->textTBFptr,str,this->mode);
       
        number=resultPtr->getNumber();
        if(!number){//没搜索到结果
            //TODE:提示窗口没找到
            int ret = QMessageBox::warning(this, tr("NO RESULT!"),
                                           tr("Change your string,idiot."),
                                           QMessageBox::Ok | QMessageBox::Ok
                                           | QMessageBox::Ok,
                                           QMessageBox::Ok);
             qDebug()<<"FIND:no result";
            return;
        }
       //------------------有结果---------------------
        nowResult=1;
        hasResult=true;
        qDebug()<<"change hasflag:"<<int(hasResult);
        mwPtr=(MainWindow *)parentWidget();
        mwTextEditPtr=mwPtr->getTextEdit();//指向父窗口private成员textedit
        temCursor=mwTextEditPtr->textCursor();
        qDebug()<<"nowresult:"<<nowResult;
        if(nowResult<=number){
            memcpy(nowWhere,resultPtr->getSpecificOne(nowResult),3*sizeof(int));
            int absadd=getAbsadd(nowWhere,textTBFptr);
            temCursor.setPosition(absadd);
            textTBFptr->setAxis(temCursor.blockNumber()+1,temCursor.position() - temCursor.block().position()+1); //自定义内存里只存了选区域的开头
            temCursor.setPosition(absadd+nowWhere[2]-nowWhere[1],QTextCursor::KeepAnchor);
            mwTextEditPtr->setTextCursor(temCursor);//显示更新
        }
        nowResult=nowResult%number+1;//循环显示
    }else{
         qDebug()<<"nowresult:"<<nowResult;
        if(nowResult<=number){
            memcpy(nowWhere,resultPtr->getSpecificOne(nowResult),3*sizeof(int));
            int absadd=getAbsadd(nowWhere,textTBFptr);
            temCursor.setPosition(absadd);
            textTBFptr->setAxis(temCursor.blockNumber()+1,temCursor.position() - temCursor.block().position()+1); //自定义内存里只存了选区域的开头
            temCursor.setPosition(absadd+nowWhere[2]-nowWhere[1],QTextCursor::KeepAnchor);
            mwTextEditPtr->setTextCursor(temCursor);//显示更新
        }
        nowResult=nowResult%number+1;//循环显示
    }
}

void FindWindow::modeChanged(int index)
{
    if(index==0){
            this->mode=1;//无视大小写
            qDebug()<<"mode change:"<<mode;
    }else if(index==1){
            this->mode=0;//区分大小写
            qDebug()<<"mode change:"<<mode;
    }
}

int getAbsadd(int * relativeAdd,myTextEdit * textTBFptr){
    int add=0;
    int rowCount=relativeAdd[0],colCount=relativeAdd[1];
     qDebug()<<"row:"<<rowCount;
     qDebug()<<"col:"<<colCount;
    lineheAD* linePtr=textTBFptr->getFirstLine();
    for(int i=1;i<rowCount;i++){
        add+=1+linePtr->getSize();//TOTEST:size 包不包括回车啊?
        linePtr=linePtr->getNext();
    }
    for(int i=1;i<colCount;i++)//TOTEST:不知道有没有加一问题
        add++;
    qDebug()<<"add:"<<add;
    return add;
}
