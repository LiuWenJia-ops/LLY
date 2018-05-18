#include "mainwindow.h"

#include "ui_mainwindow.h"

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
             int flaf = 0;


         if (event->type() == QEvent::KeyPress) {
             tcursor = textEdit->textCursor();
             //强制转换事件类型
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

             //键盘移动光标位置
             if (keyEvent->key == Qt::Key_Left){
                 textEdit->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
                 //int row = tcursor.position() - tcursor.block().position();
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(left,line,row);
                 return true;
             }
             else if (keyEvent->key == Qt::Key_Right){
                 textEdit->moveCursor(QTextCursor::Right, QTextCursor::MoveAnchor);
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(right,line,row);
                 return true;
             }
             else if (keyEvent->key == Qt::Key_Up){
                 textEdit->moveCursor(QTextCursor::Up, QTextCursor::MoveAnchor);
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(up,line,row);
                 return true;
             }
             else if (keyEvent->key == Qt::Key_Down){
                 textEdit->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(down,line,row);
                 return true;
             }
             else if (keyEvent->key == Qt::Key_End){
                 textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //接口
                 //setKeyAction(end,line,row);
                 return true;
             }

             else if (keyEvent->key == Qt::Key_Backspace){
                 if (flag == 1)//已做块选择
                     tcursor.clearSelection();
                 tcursor.deletePreviousChar();
                 int row = tcursor.columnNumber();
                 int line = tcursor.blockNumber();
                 //if (!cursor.atStart())
                 //接口(区分段落？首尾？
                 //setKeyAction(backspace,line,row);
                 return true;
             }
             else if (keyEvent->key == Qt::Key_Delete){
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
                 if (event->key() == Qt::Key_Left)
                     textEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
                 if (event->key() == Qt::Key_Right)
                     textEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);


                 else
                     QTextEdit::keyPressEvent(event);
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
