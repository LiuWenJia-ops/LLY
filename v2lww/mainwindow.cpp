#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstring.h"
#include "qfiledialog.h"
#include "qdir.h"
#include "qmessagebox.h"

#include "back.h"
//---------------------------------------------------
myTextEdit textBody;
//char * addr;  char*会在open之后被释放
std::string addr;
QTextCursor tcursor;
bool isUP=false;
bool flushFlag=1;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    //initialization
    setWindowTitle(tr("Miniword"));
    setGeometry(200,200,800,600);
    textEdit = new QTextEdit();
    textEdit->setFont(QFont("Consolas", 20));
    setCentralWidget(textEdit);
    textEdit->installEventFilter(this);
    textBody.getAxis();
    //on_actionnew_triggered();
    //---------------------------------------------创建菜单栏----------------------------------------
    //定义openAction
    openAction =new QAction(tr("open file"),this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction,&QAction::triggered,this,&MainWindow::on_actionopen_triggered);
    //定义saveAction
    saveAction =new QAction(tr("save file"),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the current file"));
    connect(saveAction,&QAction::triggered,this,&MainWindow::on_actionsave_triggered);
    //定义newAction
    newAction =new QAction(tr("new file"),this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Start a new file"));
    connect(newAction,&QAction::triggered,this,&MainWindow::on_actionnew_triggered);
   
    //添加QAction到菜单栏
    QMenu * file=menuBar()->addMenu(tr("&File Operation"));
    QStatusBar * status=statusBar();
    //添加open
    file->addAction(openAction);
    status->addAction(openAction);
    //添加save
    file->addAction(saveAction);
    status->addAction(saveAction);
    //添加new
    file->addAction(newAction);
    status->addAction(newAction);

    //connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT());
    //connect(textEdit,&MyEvent::mousePressEvent,this,&MainWindow::mouseCursorChanged);



    //---------------------------------------------添加显示控件----------------------------------------
//    label
}

//void MainWindow::mouseCursorChanged()
//{
//    tcursor=this->textEdit->textCursor();
//    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
//}

MainWindow::~MainWindow()
{
}
//-------------------------------------------------
//-------------------------------------------------
void MainWindow::on_actionopen_triggered()
{
    if(!addr.empty()){//已经打开过一份
        QMessageBox::StandardButton rb = QMessageBox::question(this, "Open file", 
                                                        "Do you want to save the changes of the current text?",
                                                            QMessageBox::Yes | QMessageBox::No, 
                                                            QMessageBox::Yes); 
            if(rb == QMessageBox::Yes)//保存文本框内容到地址
            { 
                    on_actionsave_triggered();
                    addr.clear();//清空地址
            }
    }//清空body，还原cur位置

    textBody.delFULL();
    this->textEdit->clear();
    QString qsStr;
    QString filename = QFileDialog::getOpenFileName(//得到文件路径
                        this,
                        tr("Open Document"),
                        QDir::currentPath(),//打开程序地址下的目录
                        "lly files (*.lly )");//file filter,只能打开txt

    if (!filename.isNull()) { //用户选择了文件
        QByteArray ba=filename.toUtf8();
        addr=ba.data();//用户选择的文件所在位置

        std::ifstream buf(addr);
        if(buf.fail()){//打开失败
            int failure = QMessageBox::warning(this, "Fail to open file!!!",
                                                            "Please choose right format",
                                                                QMessageBox::Ok,
                                                                QMessageBox::Ok);
            addr.clear();//清空地址
            return;
        }
        std::string media;
        std::string whl;
        while (std::getline(buf,media)){
            qsStr = QString(media.c_str());
            textEdit->append(qsStr);//显示到textedit
            whl.append(media);whl.append("\n");
        }
        textBody.insertStr(whl);
        textBody.setAxis(1,12);//????
        textBody.printFULL();
        //std::cout<<addr<<std::endl;
        tcursor=textEdit->textCursor();//设置光标
        buf.close();
     }
}

void MainWindow::on_actionnew_triggered()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "New file",
                                                            "Do you want to save the changes of the current text?",
                                                             QMessageBox::Yes | QMessageBox::No, 
                                                             QMessageBox::Yes); 
    if(rb == QMessageBox::Yes)//保存文本框内容到地址
    { 
            on_actionsave_triggered();
    }
    textBody.delFULL();
    flush();
    textBody.setAxis(1,1);
    addr.clear();//清空地址
}

void MainWindow::on_actionsave_triggered()
{
    if(addr.empty()){//新建的文件无原地址，打开系统文件夹
        QString filepath = QFileDialog::getSaveFileName(//得到文件路径
                                    this,
                                    tr("Save Document"),
                                    QDir::currentPath(),//打开程序地址下的目录
                                    "lly files (*.lly )");//file filter,只能打开txt

        if (!filepath.isNull()) { //用户选择了地址,改变地址到这里
            QByteArray ba=filepath.toUtf8();
            addr=ba.data();//addr存储的是绝对地址 
        }else//用户取消保存
            return;
    }
    std::ofstream buf(addr);
    if(buf.fail()){//打开失败
        int failure = QMessageBox::warning(this, "Fail to open file!!!",
                                                        "Please choose right format",
                                                            QMessageBox::Ok,
                                                            QMessageBox::Ok);
        addr.clear();//清空地址
        return;
    }
    std::cout<<"run save: "<<addr<<std::endl;
    lineheAD * tem=textBody.getFirstLine();
    if(tem==nullptr)
        std::cout<<"cashe empty"<<std::endl;
    else
        while(tem!=nullptr){
            buf<<tem->chs<<'\n';
            tem=tem->getNext();
        }
    buf.close();
}



void MainWindow::on_textEdit_textChanged()
{

}

//---------------------------------------------textEdit----------------------------------------
void MainWindow::correctEditCursor(int row,int col)
{
    qDebug()<<"row:"<<row;
    qDebug()<<"col:"<<col;
    tcursor=textEdit->textCursor();
    tcursor.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
    tcursor.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,row-1);
    tcursor.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor,col-1);
    textEdit->setTextCursor(tcursor);
    qDebug()<<"correct cursor:tcursor"<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
    qDebug()<<"correct cursor:axis in cashe AFTER event: "<<textBody.getRow()<<','<<textBody.getCol();
}
void MainWindow::setTwoEnd(int & r,int & c){//TOTEST:确认结束点是否正确
    QTextCursor cursor = textEdit->textCursor();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    if(!cursor.hasSelection())
        return; // No selection available

    cursor.setPosition(start);
    textBody.setAxis(cursor.blockNumber()+1,cursor.position() - cursor.block().position()+1);
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    r=cursor.blockNumber()+1;
    c=cursor.position() - cursor.block().position()+1;
}
void MainWindow::flush(){//TESTDONE: flush后必须矫正坐标
    flushFlag=0;
    QString qstr;
    this->textEdit->clear();
    lineheAD *tem=textBody.getFirstLine();
    while(tem!=nullptr){
        qstr=QString::fromUtf8(tem->chs);
        qDebug()<<qstr;
        this->textEdit->append(qstr);
        tem=tem->getNext();
    }
    flushFlag=1;
    correctEditCursor(textBody.getRow(),textBody.getCol());
}
//---------------------------------------------事件过滤器----------------------------------------
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    MyEvent myEvent;
    int r2,c2,click=0;
    if (obj == textEdit) {
        qDebug()<<"Event:"<<event;
//        qDebug()<<"event start:tcursor AFTER event: "<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
//        qDebug()<<"event start:axis in cashe AFTER event: "<<textBody.getRow()<<','<<textBody.getCol();
        if (tcursor.hasSelection()){
            qDebug()<<"detect Selection";
        }
        //响应按键事件，注意：快捷键Ctr+O和Ctr+S已经加在了菜单栏
        if (event->type() == QEvent::KeyPress) {
            qDebug()<<"detect keyPress Event";
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//            --------------------键盘移动光标位置---------------
            if (keyEvent->key() == Qt::Key_Left){
                if (keyEvent->modifiers() == Qt::ShiftModifier){
                    //TODO:查看QTextCursor的移动如何实现
                    //猜测用keep/moveanchor来区别shift+R/L
                    textEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [shift]+[←]";
                }else{
                    textEdit->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [←]";
                }
            }else if (keyEvent->key() == Qt::Key_Right){
                if (keyEvent->modifiers() == Qt::ShiftModifier){
                    //TODO:查看QTextCursor的移动如何实现
                    //猜测用keep/moveanchor来区别shift+R/L
                    textEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [shift]+[→]";
                }else{
                    textEdit->moveCursor(QTextCursor::Right, QTextCursor::MoveAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [→]";
                }
            }else if (keyEvent->key() == Qt::Key_Up){
                if (keyEvent->modifiers() == Qt::ShiftModifier){
                    //TODO:查看QTextCursor的移动如何实现
                    //猜测用keep/moveanchor来区别shift+R/L
                    textEdit->moveCursor(QTextCursor::Up, QTextCursor::KeepAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [shift]+[↑]";
                }else{
                    textEdit->moveCursor(QTextCursor::Up, QTextCursor::MoveAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [↑]";
                }
            }else if (keyEvent->key() == Qt::Key_Down){
                if (keyEvent->modifiers() == Qt::ShiftModifier){
                    //TODO:查看QTextCursor的移动如何实现
                    //猜测用keep/moveanchor来区别shift+R/L
                    textEdit->moveCursor(QTextCursor::Down, QTextCursor::KeepAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [shift]+[↑]";
                }else{
                    textEdit->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [↓]";
                }
            }else if (keyEvent->key() == Qt::Key_End){
                textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
                tcursor=textEdit->textCursor();
                textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                qDebug()<<"complete action responsing to key [End]";
            }
//            --------------------删除操作---------------
            else if (keyEvent->key() == Qt::Key_Backspace){
                 if (tcursor.hasSelection()){//已做块选择
                   setTwoEnd(r2,c2);
                   textBody.delBlock(r2,c2);//FIXME:块尾
                 }else{
                    textBody.delC(1);
                 }
                 qDebug()<<"bs before flush:tcursor AFTER event: "<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
                 qDebug()<<"bs before flush:axis in cashe AFTER event: "<<textBody.getRow()<<','<<textBody.getCol();
                 flush(); 
                 qDebug()<<"bs after flush:tcursor AFTER event: "<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
                 qDebug()<<"bs after flush:axis in cashe AFTER event: "<<textBody.getRow()<<','<<textBody.getCol();
            }else if (keyEvent->key() == Qt::Key_Delete){
                if (tcursor.hasSelection()){//已做块选择
                  setTwoEnd(r2,c2);
                  textBody.delBlock(r2,c2);//FIXME:块尾
                }else
                    textBody.delC(0);
                flush();
           }
//            --------------------键入操作---------------
            else if(keyEvent->key() == Qt::Key_CapsLock){
                isUP=!isUP;
            }
            else if (keyEvent->key()<=int(Qt::Key_Z)&&keyEvent->key()>=int(Qt::Key_A)){//Q:输入字符
               std::string tem;
               if(isUP)
                   tem.push_back(char(int(keyEvent->key())-int(Qt::Key_A)+int('A')));
               else
                   tem.push_back(char(int(keyEvent->key())-int(Qt::Key_A)+int('a')));
               textBody.insertStr(tem);
               flush();
            }
            else if (keyEvent->key()<=int(Qt::Key_QuoteLeft)&&keyEvent->key()>=int(Qt::Key_BracketLeft)){
                std::string tem;
                tem.push_back(char(int(keyEvent->key())-int(Qt::Key_BracketLeft)+int('[')));
                textBody.insertStr(tem);
                flush();
            }
            else if (keyEvent->key()<=int(Qt::Key_AsciiTilde)&&keyEvent->key()>=int(Qt::Key_BraceLeft)){
                std::string tem;
                tem.push_back(char(int(keyEvent->key())-int(Qt::Key_BraceLeft)+int('{')));
                textBody.insertStr(tem);
                flush();
            }
            else if (keyEvent->key()<=int(Qt::Key_At)&&keyEvent->key()>=int(Qt::Key_Space)){
                std::string tem;
                tem.push_back(char(int(keyEvent->key())-int(Qt::Key_Space)+int(' ')));
                textBody.insertStr(tem);
                flush();
            }
            else if(keyEvent->key()==int(Qt::Key_Return)){
                std::string enTer("\n\n");
                textBody.insertStr(enTer);
                flush();
            }
//            --------------------不可识别的操作---------------
            else{//注：不在这里调用父类，无响应的情况课用作调试
                qDebug()<<"|-------------------------|";
                qDebug()<<"|undifined keyPress Action|";
                qDebug()<<"|-------------------------|";
            }

            qDebug()<<"tcursor AFTER event: "<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
            qDebug()<<"axis in cashe AFTER event: "<<textBody.getRow()<<','<<textBody.getCol();
            return true;
        }
//          --------------------响应鼠标事件--------------------
        else if(event->type()==QEvent::InputMethodQuery){            
            if(flushFlag){//在flush中触发的inputmethod的事件来自对textedit文本的修改，
                          //这时我们拒绝让被文本控制的tcursor控制textbody的光标
                tcursor=textEdit->textCursor();
                textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
            }    
            qDebug()<<"else:tcursor AFTER event: "<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
            qDebug()<<"else:axis in cashe AFTER event: "<<textBody.getRow()<<','<<textBody.getCol();
            return true;
        }else
            return QMainWindow::eventFilter(obj, event);
    } else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}
