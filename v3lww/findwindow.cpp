#include "findwindow.h"
#include "mainwindow.h"
int getAbsadd(int * relativeAdd,myTextEdit * textTBFptr);

FindWindow::FindWindow(QWidget* parent): QDialog(parent)
{

}
FindWindow::FindWindow(QWidget* parent,myTextEdit * textBodyIn):
    QDialog(parent),textTBFptr(textBodyIn)
{
    this->mode=1;//默认不区分大小写

    this->setWindowTitle(tr("Find"));
    this->setGeometry(100,100,400,300);

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

    connect(findComboBox, SIGNAL(activated(int)),this, SLOT(modeChanged(int)));
    connect(btn, &QPushButton::pressed, this, &FindWindow::showFindText);
}

FindWindow::~FindWindow()
{
}

void FindWindow::showFindText()
{
    qDebug()<<"Start find";
    qDebug()<<"mode in find:"<<mode;

    QString qstr = findLineEdit->text();
    std::string str=qstr.toLocal8Bit().constData();//QString->string
    resultPtr=new searchResult(this->textTBFptr,str,this->mode);

    qDebug()<<"textbody check:"<<textTBFptr->getFirstLine()->getSize();
    qDebug()<<"input:"<<qstr;

    int number=resultPtr->getNumber();
    if(!number){//没搜索到结果
        //TODE:提示窗口没找到
         qDebug()<<"FIND:no result";
        return;
    }

    int nowWhere[3];

    MainWindow * mwPtr=(MainWindow *)parentWidget();
    QTextEdit * mwTextEditPtr=mwPtr->getTextEdit();//指向父窗口private成员textedit
    QTextCursor temCursor=mwTextEditPtr->textCursor();

    for(;resultPtr->nowINDEX<=number;resultPtr->nowINDEX++){//TOTEST:一次显示
        memccpy(nowWhere,resultPtr->getSpecificOne(resultPtr->nowINDEX),3,sizeof(int));
        int absadd=getAbsadd(nowWhere,textTBFptr);
        temCursor.setPosition(absadd);//FIXME:需要一个绝对的地址
        textTBFptr->setAxis(temCursor.blockNumber()+1,temCursor.position() - temCursor.block().position()+1); //自定义内存里只存了选区域的开头
        temCursor.setPosition(absadd+nowWhere[2]-nowWhere[1],QTextCursor::KeepAnchor);
        mwTextEditPtr->setTextCursor(temCursor);//显示更新
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
    lineheAD* linePtr=textTBFptr->getFirstLine();
    for(int i=1;i<rowCount;i++){
        add+=linePtr->getSize();
        linePtr=linePtr->getNext();
    }
    for(int i=1;i<=colCount;i++)//TOTEST:不知道有没有加一问题
        add++;
    return add;
}
