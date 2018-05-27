#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstring.h"
#include "qfiledialog.h"
#include "qdir.h"

#include "back.h"



//---------------------------------------------------
myTextEdit textBody;
//char * addr;  char*会在open之后被释放
std::string addr;
QTextCursor tcursor;
bool isUP=false;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    //initialization
    setWindowTitle(tr("Miniword"));
    setGeometry(200,200,800,600);
    textEdit = new QTextEdit();
    textEdit->setFont(QFont("Consolas", 20));
    setCentralWidget(textEdit);
    textEdit->installEventFilter(this);
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

    //添加QAction到菜单栏
    QMenu * file=menuBar()->addMenu(tr("&File Operation"));
    QStatusBar * status=statusBar();
    //添加open
    file->addAction(openAction);
    status->addAction(openAction);
    //添加save
    file->addAction(saveAction);
    status->addAction(saveAction);
    //---------------------------------------------添加显示控件----------------------------------------
//    label
}

MainWindow::~MainWindow()
{
//    delete ui;
}
//-------------------------------------------------
//-------------------------------------------------
void MainWindow::on_actionopen_triggered()
{
    //    //TODO:如果已经打开了一份文件还想打开第二份
    //    if(addr[0]){//已经打开过一份
    //       // TODO:询问是否保存当前文件并新建,
    //        //若否，直接返回；
    //        //若是，保存文件
    //        {
    //            savefile(addr,textBody);
    //        }
    //    }//清空body，还原cur位置
        QString qsStr;
        QString filename = QFileDialog::getOpenFileName(//得到文件路径
                            this,
                            tr("Open Document"),
                            QDir::currentPath(),//打开程序地址下的目录
                            "Text files (*.txt )");//file filter,只能打开txt

        if (!filename.isNull()) { //用户选择了文件
            QByteArray ba=filename.toUtf8();
            addr=ba.data();//add存储的是绝对地址 TOTEST:（函数内部的const是全局不变的吗？）
            std::ifstream buf(addr);
            //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)
            std::string media;
            std::string whl;
            while (std::getline(buf,media)){
                qsStr = QString(media.c_str());
                /*ui->*/textEdit->append(qsStr);//显示到textedit
                whl.append(media);whl.append("\n");
//                textBody.insertStr(media);//TODO:将string插入到linehead里
            }
            textBody.insertStr(whl);
            textBody.setAxis(1,12);
            textBody.printFULL();
            std::cout<<addr<<std::endl;
            tcursor=textEdit->textCursor();//设置光标
            buf.close();
         }

}

void MainWindow::on_actionnew_triggered()
{
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
      /*ui->*/textEdit->clear();
}

void MainWindow::on_actionsave_triggered()
{
    //    if(!addr[0]){//TODO:新建的文件无原地址，应该有什么打开系统文件夹的操作
    //        //TODO:输入保存路径
    //    }
//        std::cout<<addr<<std::endl;
        std::ofstream buf(addr);
        std::cout<<"run save: "<<addr<<std::endl;
        //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)
        lineheAD * tem=textBody.getFirstLine();
        if(tem==nullptr)
            std::cout<<"cashe empty"<<std::endl;
        else
            while(tem!=nullptr){
               buf<<tem->chs<<'\n';
                tem=tem->getNext();
            }
//        free(addr);
//       *addr='\0';
}

void MainWindow::on_textEdit_textChanged()
{

}

//---------------------------------------------textEdit----------------------------------------
void MainWindow::correctEditCursor(int row,int col)
{
    tcursor.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
    tcursor.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,row-1);
    tcursor.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor,col-1);
    textEdit->setTextCursor(tcursor);
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
    QString qstr;
    this->textEdit->clear();
    lineheAD *tem=textBody.getFirstLine();
    while(tem!=nullptr){
        qstr=QString::fromUtf8(tem->chs);
        this->textEdit->append(qstr);
        tem=tem->getNext();
    }
    correctEditCursor(textBody.getRow(),textBody.getCol());
}
//---------------------------------------------事件过滤器----------------------------------------
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    MyEvent myEvent;
    int r2,c2;
    if (obj == textEdit) {
        //响应按键事件，注意：快捷键Ctr+O和Ctr+S已经加在了菜单栏
        if (event->type() == QEvent::KeyPress) {
            qDebug()<<"detect keyPress Event";
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//            --------------------键盘移动光标位置---------------
//            用下列代码测试键盘移动光标后，在内存中的坐标是正确的（经测试发现行、列数应该+1）
//            textBody.getAxis();
//            qDebug()<<"current axis in back is: "<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
            if (keyEvent->key() == Qt::Key_Left){
//                if(k->state() == Qt::ShiftButton){
                    //TODO:查看QTextCursor的移动如何实现
                    //猜测用keep/moveanchor来区别shift+R/L
//                }else{
                    textEdit->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
                    tcursor=textEdit->textCursor();
                    textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                    qDebug()<<"complete action responsing to key [←]";
//                }
            }else if (keyEvent->key() == Qt::Key_Right){
                textEdit->moveCursor(QTextCursor::Right, QTextCursor::MoveAnchor);
                tcursor=textEdit->textCursor();
                textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                qDebug()<<"complete action responsing to key [→]";
            }else if (keyEvent->key() == Qt::Key_Up){
                textEdit->moveCursor(QTextCursor::Up, QTextCursor::MoveAnchor);
                tcursor=textEdit->textCursor();
                textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                qDebug()<<"complete action responsing to key [↑]";
            }else if (keyEvent->key() == Qt::Key_Down){
                textEdit->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
                tcursor=textEdit->textCursor();
                textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
                qDebug()<<"complete action responsing to key [↓]";
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
                 }else
                    textBody.delC(1);
//                qDebug()<<"the block begin is: "<<'('<<textBody.getRow()<<','<<textBody.getCol()<<')';
//                qDebug()<<"the block end is: "<<'('<<r2<<','<<c2<<')';
            }else if (keyEvent->key() == Qt::Key_Delete){
                if (tcursor.hasSelection()){//已做块选择
                  int r2,c2;
//                    setTwoEnd(ui,r2,c2);
                  setTwoEnd(r2,c2);
                  textBody.delBlock(r2,c2);//FIXME:块尾
                }else
                    textBody.delC(0);

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
            }
            else if (keyEvent->key()<=int(Qt::Key_9)&&keyEvent->key()>=int(Qt::Key_0)){
                std::string tem;
                tem.push_back(char(int(keyEvent->key())-int(Qt::Key_0)+int('0')));
                textBody.insertStr(tem);
            }
//            --------------------快捷键操作(不可用)---------------
//            else if (keyEvent->modifiers() == Qt::ShiftModifier){
//                //Q:能否能保持keep;选区能否自己识别前后关系;刷新后能否保持选区
//                if (keyEvent->key() == Qt::Key_Left)
//                    textEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
//                if (keyEvent->key() == Qt::Key_Right)
//                    textEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);
//                else
//                    myEvent.keyPressEvent(keyEvent);
//            }
//            --------------------common operation---------------
            else{//注：不在这里调用父类，无响应的情况课用作调试
                qDebug()<<"|-------------------------|";
                qDebug()<<"|undifined keyPress Action|";
                qDebug()<<"|-------------------------|";
            }

            flush();
            qDebug()<<"tcursor AFTER event: "<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
            return true;
        }
//        //响应鼠标事件
//        else if (event->type() == QEvent::MouseButtonPress){
//            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

//           if (mouseEvent->button() == Qt::LeftButton){
//               QTextEdit::mousePressEvent(mouseEvent);//FIXEME:派生类访问protected
//               tcursor = textEdit->textCursor();
//               textBody.setAxis(tcursor.blockNumber()+1,tcursor.position() - tcursor.block().position()+1);
//           }
//       }
        else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}
