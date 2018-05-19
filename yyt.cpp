#include "mainwindow.h"

#include "ui_mainwindow.h"

static myTextEdit superText;
string buffer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Miniword");

    textEdit = new QTextEdit;
    textEdit->installEventFilter(this);
    textEdit->viewPort->installEventFilter(this);
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
                     tcursor.clearSelection();//删除块
                 else
                     tcursor.deletePreviousChar();//向后删除单个字符

                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //if (!cursor.atStart())
                 //接口(区分段落？首尾？
                 //setKeyAction(backspace,line,row);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Delete){
                 if (flag == 1)
                     tcursor.clearSelection();
                 else
                    tcursor.deleteChar();//前向删除一个字符
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //if (!cursor.atStart())
                 //接口(区分段落？首尾？
                 //setKeyAction(delete,line,row);
                 return true;
             }
             //快捷键
             else if (keyEvent->modifiers() == Qt::ShiftModifier){//shift修饰符
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
