#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qstring.h"
#include "qfiledialog.h"
#include "qdir.h"
#include "qmessagebox.h"
#include <QToolButton>
#include <QTextCharFormat>
#include <QFont>
#include "back.h"
//---------------------------------------------------


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    //initialization
    setWindowTitle(tr("Miniword"));
    setGeometry(200,200,1000,600);

    textEdit = new QTextEdit();
    textEdit->setFont(QFont("Consolas", 15));
    setCentralWidget(textEdit);
    textEdit->installEventFilter(this);

    textBody.getAxis();
    
    findWin=new FindWindow(this,&textBody);
    replaceWin=new ReplaceWindow(this,&textBody);
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
    //实际在eventfilter中实现shortcut
    //定义CutAction
    cutAction =new QAction(tr("cut"),this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut"));
    connect(cutAction,&QAction::triggered,this,&MainWindow::on_actioncut_triggered);
    //定义PasteAction
    pasteAction =new QAction(tr("paste"),this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste"));
    connect(pasteAction,&QAction::triggered,this,&MainWindow::on_actionpaste_triggered);
    //定义CopyAction
    copyAction =new QAction(tr("copy"),this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy"));
    connect(copyAction,&QAction::triggered,this,&MainWindow::on_actioncopy_triggered);
    //同步按钮----------------
    // syncAction =new QAction(tr("Sync Trigger"),this);
    // syncAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    // syncAction->setStatusTip(tr("Sync Trigger"));
    // connect(syncActio,&QAction::triggered,this,&MainWindow::on_actionsync_triggered);
    //定义上传
    uploadAction =new QAction(tr("upload files"),this);
    uploadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    uploadAction->setStatusTip(tr("Upload"));
    connect(findAction,&QAction::triggered,this,&MainWindow::on_actionupload_triggered);
    //定义下载
    downloadAction =new QAction(tr("download files"),this);
    downloadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    downloadAction->setStatusTip(tr("Download"));
    connect(findAction,&QAction::triggered,this,&MainWindow:: on_actiondownload_triggered);
    //-----------------
    //定义findAction
    findAction =new QAction(tr("find string"),this);
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("Find"));
    connect(findAction,&QAction::triggered,this,&MainWindow::on_actionfind_triggered);
    //定义replaceAction
    replaceAction =new QAction(tr("replace a string"),this);
    replaceAction->setShortcut(QKeySequence::Replace);
    replaceAction->setStatusTip(tr("Replace"));
    connect(replaceAction,&QAction::triggered,this,&MainWindow::on_actionreplace_triggered);

    // 添加图标
     openAction->setIcon(QIcon(":/open.png"));
     newAction->setIcon(QIcon(":/new.png"));
     saveAction->setIcon(QIcon(":/save.png"));
     cutAction->setIcon(QIcon(":/cut.png"));
     copyAction->setIcon(QIcon(":/copy.png"));
     pasteAction->setIcon(QIcon(":/paste.png"));
     findAction->setIcon(QIcon(":/find.png"));
     replaceAction->setIcon(QIcon(":/replace.png"));
     uploadAction->setIcon(QIcon(":/upload.png"));
     downloadAction->setIcon(QIcon(":/download.png"));

    //添加QAction到菜单栏
    QMenu * file=menuBar()->addMenu(tr("&File Operation"));
    QMenu * edit=menuBar()->addMenu(tr("&Text Operation"));
    QMenu * search=menuBar()->addMenu(tr("&Search Operation"));
    QMenu * cloud=menuBar()->addMenu(tr("&Cloud Operation"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
    QStatusBar * status=statusBar();

    //添加open
    file->addAction(openAction);
    status->addAction(openAction);
    //添加save
    file->addAction(saveAction);
    status->addAction(saveAction);
    //添加new
    file->addAction(newAction);
    fileToolBar->addAction(newAction);
    status->addAction(newAction);
    //添加cut
    edit->addAction(cutAction);
    status->addAction(cutAction);
    //添加paste
    edit->addAction(pasteAction);
    status->addAction(pasteAction);
    //添加copy
    edit->addAction(copyAction);
    fileToolBar->addAction(copyAction);
    status->addAction(copyAction);

    //添加find
    search->addAction(findAction);
    fileToolBar->addAction(findAction);
    status->addAction(findAction);
    //添加replace
    search->addAction(replaceAction);
    fileToolBar->addAction(replaceAction);
    status->addAction(replaceAction);

    //添加上传
    cloud->addAction(uploadAction);
    fileToolBar->addAction(uploadAction);
    status->addAction(uploadAction);
    //添加下载
    cloud->addAction(downloadAction);
    fileToolBar->addAction(downloadAction);
    status->addAction(downloadAction);
    //-----------------------------------------创建排版控制工具栏---------------------------
     //在工具栏上嵌入控件:字体，大小，粗体，斜体
     fontLabel = new QLabel(tr("Font:"));
     fontComboBox = new QFontComboBox;
     //列出所有字体
     fontComboBox->setFontFilters (QFontComboBox::ScalableFonts);
     //字号
     fontLabel2 = new QLabel(tr("Size:"));
     sizeComboBox = new QComboBox;
     //QFontDatabase-实现在字号下拉列表框中填充各种不同的字号条目
     QFontDatabase db;
     foreach (int size, db.standardSizes ())
         sizeComboBox->addItem (QString::number (size)); //将它们插入到字号下拉框中

     //加粗
     BoldtooBar = new QToolButton;
     BoldtooBar->setIcon (QIcon(":/bold.png"));
     BoldtooBar->setStatusTip("Bold");
     //设置成是否是开关(toggle)按钮(true)---即可复选的
     BoldtooBar->setCheckable (true);

     //斜体
     ItalictooBar = new QToolButton;
     ItalictooBar->setIcon (QIcon(":/italic.png"));
     ItalictooBar->setStatusTip("Italic");
     ItalictooBar->setCheckable (true);

     //下划线
     UnderlinetooBar = new QToolButton;
     UnderlinetooBar->setIcon (QIcon(":/underline.png"));
     UnderlinetooBar->setStatusTip("Underline");
     UnderlinetooBar->setCheckable (true);


     //字体工具条
     FonttoolBar = addToolBar ("Font");
     FonttoolBar->addWidget (fontLabel);
     FonttoolBar->addWidget (fontComboBox);
     FonttoolBar->addWidget (fontLabel2);
     FonttoolBar->addWidget (sizeComboBox);
     FonttoolBar->addSeparator ();
     FonttoolBar->addWidget (BoldtooBar);
     FonttoolBar->addWidget (ItalictooBar);
     FonttoolBar->addWidget (UnderlinetooBar);

     //连接槽函数
      connect (fontComboBox, SIGNAL(activated(QString)), this, SLOT(ShowFontComboBox(QString)));
      connect (sizeComboBox, SIGNAL(activated(QString)), this, SLOT(ShowSizeSpinBox(QString)));
      connect (BoldtooBar, SIGNAL(clicked(bool)), this, SLOT(ShowBoldtooBar()));
      connect (ItalictooBar, SIGNAL(clicked(bool)), this, SLOT(ShowItalictooBar()));
      connect (UnderlinetooBar, SIGNAL(clicked(bool)), this, SLOT(ShowUnderlinetooBar()));
    //---------------------------------------------状态栏----------------------------------------
    position = new QLabel(this);
    status->addPermanentWidget(position);
    connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(ShowTextRowCol()));
}


MainWindow::~MainWindow()
{

}

//---------------------------------格式设置------------------------------------- 
void MainWindow::ShowCurrentFormatChanged(const QFont&fmt)
{  
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.family()));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.pointSize())));
    BoldtooBar->setChecked(fmt.bold());
    ItalictooBar->setChecked(fmt.italic());
    UnderlinetooBar->setChecked(fmt.underline());
    flush();
}  

void MainWindow::ShowItalictooBar()
{
    QFont fmt=textEdit->currentFont();
    if(ItalictooBar->isChecked())
        fmt.setItalic(true);  
    else
        fmt.setItalic(false); 
    textEdit->setCurrentFont(fmt);
    ShowCurrentFormatChanged(fmt);
}

void MainWindow::ShowUnderlinetooBar()
{
    QFont fmt=textEdit->currentFont();
    if(UnderlinetooBar->isChecked())
        fmt.setUnderline(true);  
    else
        fmt.setUnderline(false);   
    textEdit->setCurrentFont(fmt);
    ShowCurrentFormatChanged(fmt);
}

void MainWindow::ShowBoldtooBar()
{
    QFont fmt=textEdit->currentFont();
    if(BoldtooBar->isChecked())
        fmt.setBold(true);  
    else
        fmt.setBold(false);  
    textEdit->setCurrentFont(fmt);
     ShowCurrentFormatChanged(fmt);
}
void MainWindow::ShowSizeSpinBox(QString spinValue)  
{  
    QFont fmt=textEdit->currentFont(); 
    fmt.setPointSize(spinValue.toFloat());    //设置字体大小  
    textEdit->setCurrentFont(fmt);
    ShowCurrentFormatChanged(fmt);
}  

void MainWindow::ShowFontComboBox(QString comboStr)
{  
    QFont fmt=textEdit->currentFont();
    fmt.setFamily(comboStr);
    textEdit->setCurrentFont(fmt);
    ShowCurrentFormatChanged(fmt);
}  

//-------------------------------------文件操作槽函数-------------------------------------------
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
                        "txt files (*.txt )");//file filter,只能打开txt

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
        while (!buf.eof()){//没到文件尾
            getline(buf,media);
            qsStr = QString(media.c_str());
            textEdit->append(qsStr);//显示到textedit
            whl.append(media);whl.append("\n");
        }
        textBody.insertStr(whl);
        textBody.printFULL();
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
                                    "txt files (*.txt )");//file filter,只能打开txt

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
            buf<<tem->chs<<'\n';//可是明明whl里不是有\n吗...
            tem=tem->getNext();
        }
    buf.close();
}
//------------------------------------块操作------------------------------------
void MainWindow::on_actioncut_triggered()
{
    QTextCursor cursor = textEdit->textCursor();
    if (cursor.hasSelection()){
        int r,c;
        setTwoEnd(r,c);
        clipboard = textBody.cutBlock(r,c);
        QString string = QString::fromStdString(clipboard);
        qDebug()<<"cut:"<<string;
        flush();
    }
}
void MainWindow::on_actionpaste_triggered()
{
    QTextCursor cursor = textEdit->textCursor();
    if (cursor.hasSelection()){
        int r,c;
        setTwoEnd(r,c);
        textBody.delBlock(r,c);
    }
    textBody.insertStr(clipboard);
    QString string = QString::fromStdString(clipboard);
    qDebug()<<"paste:"<<string;
    flush();
}
void MainWindow::on_actioncopy_triggered()
{//保持选区
    QTextCursor cursor = textEdit->textCursor();
    if (cursor.hasSelection()){
        int r,c;
        setTwoEnd(r,c);
        clipboard = textBody.copyBlock(r,c-1);//解决多拷贝一位的问题
        cursor.setPosition(cursor.selectionStart());
        cursor.setPosition(cursor.selectionEnd(), QTextCursor::KeepAnchor);

        QString string = QString::fromStdString(clipboard);
        qDebug()<<"copy:"<<string;
        //flush();
    }
}
//---------------------搜索操作槽函数----------------------------
void MainWindow::on_actionfind_triggered()
{    
    findWin->show();
}

void MainWindow::on_actionreplace_triggered()
{
    replaceWin->show();
}
//-------------------------------------------状态栏----------------------------------------
void MainWindow::ShowTextRowCol()
{
    if (!tcursor.hasSelection())
        this->position->setText(tr("Row:%1 Col:%2 | PreTotal:%3").arg(tcursor.blockNumber()+1).arg(tcursor.position()-tcursor.block().position()+1).arg(tcursor.position()));
    else
        this->position->setText(tr("Row:%1 Col:%2 | Selection:%3").arg(tcursor.blockNumber()+1).arg(tcursor.position()-tcursor.block().position()+1).arg(tcursor.selectionEnd()-tcursor.selectionStart()+1));
}

//---------------------------------------------刷新操作----------------------------------------
void MainWindow::correctEditCursor(int row,int col)
{
    qDebug()<<"row:"<<row;
    qDebug()<<"col:"<<col;//2.2
    // QTextCursor ncs;
    // ncs=textEdit->textCursor();
    // qDebug()<<"correct cursor---:"<<ncs.blockNumber()<<','<<ncs.position() - ncs.block().position();
    // ncs.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
    // qDebug()<<"correct cursor---:"<<ncs.blockNumber()<<','<<ncs.position() - ncs.block().position();
    // ncs.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,row-1);
    // qDebug()<<"correct cursor+++:"<<ncs.blockNumber()<<','<<ncs.position() - ncs.block().position();
    // ncs.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor,col-1);
    // qDebug()<<"correct cursor===:"<<ncs.blockNumber()<<','<<ncs.position() - ncs.block().position();
    // textEdit->setTextCursor(ncs);
    // qDebug()<<"correct cursor:ncs"<<ncs.blockNumber()+1<<','<<ncs.position() - ncs.block().position()+1;
    tcursor=textEdit->textCursor();
    // qDebug()<<"correct cursor---:"<<tcursor.blockNumber()<<','<<tcursor.position() - tcursor.block().position();
    tcursor.movePosition(QTextCursor::Start,QTextCursor::MoveAnchor,1);
    // qDebug()<<"correct cursor---:"<<tcursor.blockNumber()<<','<<tcursor.position() - tcursor.block().position();
    tcursor.movePosition(QTextCursor::NextBlock,QTextCursor::MoveAnchor,row-1);
    // qDebug()<<"correct cursor+++:"<<tcursor.blockNumber()<<','<<tcursor.position() - tcursor.block().position();
    tcursor.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor,col-1);
    // qDebug()<<"correct cursor===:"<<tcursor.blockNumber()<<','<<tcursor.position() - tcursor.block().position();
    textEdit->setTextCursor(tcursor);
    qDebug()<<"correct cursor:tcursor"<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
    qDebug()<<"correct cursor:axis in cashe AFTER event: "<<textBody.getRow()<<','<<textBody.getCol();//1.2
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
    // QFont fmt=textEdit->currentFont();
    // qDebug()<<fmt;
    this->textEdit->clear();
    lineheAD *tem=textBody.getFirstLine();
    while(tem!=nullptr){
        qstr=QString::fromUtf8(tem->chs);
        qDebug()<<qstr;
        this->textEdit->append(qstr);
        tem=tem->getNext();
    }
     tcursor=textEdit->textCursor();
    qDebug()<<"textedit total lines"<<tcursor.blockNumber()+1;
    flushFlag=1;
    correctEditCursor(textBody.getRow(),textBody.getCol());
    // textEdit->setCurrentFont(fmt);
    SyncFile();
}
//---------------------------------------------事件过滤器----------------------------------------
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    int r2,c2;
    if (obj == textEdit) {
//        qDebug()<<"Event:"<<event;
        //响应按键事件，注意：快捷键Ctr+O和Ctr+S已经加在了菜单栏
        if (event->type() == QEvent::KeyPress) {
           // qDebug()<<"detect keyPress Event";
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
           }else if (keyEvent->modifiers()==Qt::ControlModifier){
                if (keyEvent->key()== Qt::Key_X){
                    this->on_actioncut_triggered();
                    //emit cut();
                }else if (keyEvent->key()== Qt::Key_C)
                    this->on_actioncopy_triggered();
                else if (keyEvent->key()== Qt::Key_V)
                        this->on_actionpaste_triggered();
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
                return QMainWindow::eventFilter(obj, event);//
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
            // qDebug()<<"else:tcursor AFTER event: "<<tcursor.blockNumber()+1<<','<<tcursor.position() - tcursor.block().position()+1;
            // qDebug()<<"else:axis in cashe AFTER event: "<<textBody.getRow()<<','<<textBody.getCol();
            return true;
        }else
            return QMainWindow::eventFilter(obj, event);
    } else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}

//云同步--------------------------------------------------
bool isSync=false;
bool hasGot=false;
void MainWindow::on_actionsync_triggered(void)
{
    isSync= !isSync;
    SyncFile();
}
void  MainWindow::on_actionupload_triggered(void)
{

}
void  MainWindow:: on_actiondownload_triggered(void)
{

}
void MainWindow::SyncFile(void)
{
    if(!isSync)
        return ;
    QString toSyncFileAddress;
    toSyncFileAddress=QString("c:/tempSync.txt");
    if(!hasGot){
        getServerFile(toSyncFileAddress,"synctest1.txt");
        textBody.delFULL();
        this->textEdit->clear();
        QByteArray ba=toSyncFileAddress.toUtf8();
        addr=ba.data();//用户选择的文件所在位置
        std::ifstream buf(addr);
        std::string media;
        std::string whl;
        QString qsStr;
        while (!buf.eof()){//没到文件尾
            getline(buf,media);
            qsStr = QString(media.c_str());
            textEdit->append(qsStr);//显示到textedit
            whl.append(media);whl.append("\n");
        }
        textBody.insertStr(whl);
        textBody.printFULL();
        tcursor=textEdit->textCursor();//设置光标
        buf.close();
        hasGot=true;
        return;
    }
    //=====save first
    std::ofstream buf(toSyncFileAddress.toStdString());
    std::cout<<"run sync save: "<<toSyncFileAddress.toStdString()<<std::endl;
    lineheAD * tem=textBody.getFirstLine();
    if(tem==nullptr)
        std::cout<<"cashe empty"<<std::endl;
    else
        while(tem!=nullptr){
            buf<<tem->chs<<'\n';//可是明明whl里不是有\n吗...
            tem=tem->getNext();
        }
    buf.close();
    putServerFile(toSyncFileAddress,"synctest1.txt");

}
void MainWindow::getServerFile(QString localAdd,QString serverFile)    //下载文件
{
//    file = new QFile(QApplication::applicationDirPath() + "/" + ui->lineEdit->text() + ".txt");
    file =new QFile(localAdd);
    file->open(QIODevice::WriteOnly);

    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    QUrl url("ftp://140.143.0.220/pub/"+serverFile);
    url.setPort(21);
    url.setUserName("ftpuser");
    url.setPassword("z__A915O");

    QNetworkRequest request(url);
    reply = accessManager->get(request);
    connect((QObject *)reply, SIGNAL(readyRead()), this, SLOT(readContent()));
}

void MainWindow::readContent()    //下载时向本地文件中写入数据
{
    file->write(reply->readAll());
    reply->deleteLater();
    file->flush();
    file->close();
    delete file;
}
void MainWindow::putServerFile(QString localAdd,QString serverFile)//上传
{
    file = new QFile(localAdd);
    file->open(QIODevice::ReadWrite);
    QByteArray byte_file = file->readAll();
    QNetworkAccessManager *accessManager = new QNetworkAccessManager;
    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    QUrl url("ftp://140.143.0.220/pub/"+serverFile);
    url.setPort(21);
    url.setUserName("ftpuser");
    url.setPassword("z__A915O");
    QNetworkRequest request(url);
    accessManager->put(request, byte_file);
    file->close();
    delete file;
}
