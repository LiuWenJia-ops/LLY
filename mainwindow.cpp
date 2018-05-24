#include "mainwindow.h"
#include "arrayline.h"
#include "ui_mainwindow.h"

std::string buffer;//lwj(报错→+std::？

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//    setWindowTitle("Miniword");

//    textEdit = new QTextEdit;
//    textEdit->installEventFilter(this);
//    //textEdit->viewPort()->installEventFilter(this);
//}

//刷新（wj
void MainWindow::flush(){
    QString qstr;
    this->textEdit->clear();
    lineheAD *tem=textBody.getFirstLine();
    while(tem!=nullptr){
        qstr=tem->chs;
        this->textEdit->append(qstr);
    }
}
//wj
void MainWindow::setTwoEnd(int & r,int & c){//FIXME:不能传ui???
    int r2,c2;
    QTextCursor cursor = this->textEdit->textCursor();
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

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    //+状态栏;
    MyEvent myEvent;
    //int row,col;
    if (obj == textEdit) {

         if (event->type() == QEvent::KeyPress) {
             tcursor = textEdit->textCursor();
             //强制转换事件类型
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

             //键盘移动光标位置
             if (keyEvent->key() == Qt::Key_Left){
                 ui->textEdit->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
                 int col = tcursor.position() - tcursor.block().position();
                 int row = tcursor.blockNumber();
                 //接口
                 textBody.setAxis(row,col);
                 //setKeyAction(left,row,col);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Right){
                 ui->textEdit->moveCursor(QTextCursor::Right, QTextCursor::MoveAnchor);
                 int col = tcursor.position() - tcursor.block().position();
                 int row = tcursor.blockNumber();
                 //接口
                 textBody.setAxis(row,col);
                 //setKeyAction(right,row,col);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Up){
                 ui->textEdit->moveCursor(QTextCursor::Up, QTextCursor::MoveAnchor);
                 int col = tcursor.position() - tcursor.block().position();
                 int row = tcursor.blockNumber();
                 //接口
                 textBody.setAxis(row,col);
                 //setKeyAction(up,row,col);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Down){
                 ui->textEdit->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
                 int col = tcursor.position() - tcursor.block().position();
                 int row = tcursor.blockNumber();
                 //接口
                 textBody.setAxis(row,col);
                 //setKeyAction(down,row,col);
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_End){
                 ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
                 int col = tcursor.position() - tcursor.block().position();
                 int row = tcursor.blockNumber();
                 //接口
                 textBody.setAxis(row,col);
                 //setKeyAction(end,row,col);
                 return true;
             }
             //删除
             else if (keyEvent->key() == Qt::Key_Backspace){
                 int col = tcursor.position() - tcursor.block().position();
                 int row = tcursor.blockNumber();
                 if (tcursor.hasSelection()){//已做块选择
                     textBody.delBlock(row,col);
                     //tcursor.clearSelection();
                 }
                 else {
                     textBody.delC(1);//前删
                     //tcursor.deletePreviousChar();
                 }
                 return true;
             }
             else if (keyEvent->key() == Qt::Key_Delete){
                 int col = tcursor.position() - tcursor.block().position();
                 int row = tcursor.blockNumber();
                 if (tcursor.hasSelection()){//已做块选择
                     textBody.delBlock(row,col);
                     //tcursor.clearSelection();
                 }
                 else {
                     textBody.delC(0);//后删
                     //tcursor.deletePreviousChar();
                 }
                 return true;
             }

             //快捷键
             else if (keyEvent->modifiers() == Qt::ShiftModifier){
                 //Q:能否能保持keep;选区能否自己识别前后关系;刷新后能否保持选区
                 if (keyEvent->key() == Qt::Key_Left)
                     ui->textEdit->moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);
                 if (keyEvent->key() == Qt::Key_Right)
                     ui->textEdit->moveCursor(QTextCursor::Right, QTextCursor::KeepAnchor);
                 else
                     myEvent.keyPressEvent(keyEvent);
             }

             //wj
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
                 setTwoEnd(ui,r2,c2);//Q:参数不一致
                 if(keyEvent->key()==Qt::Key_C)//复制
                     buffer=textBody.copyBlock(r2,c2);//Q:wj改了参数？似乎没有同步？
                 if(keyEvent->key()==Qt::Key_X)//剪切
                     buffer=textBody.cutBlock(r2,c2);
             }
             //输入字符（暂时只处理字母数字（wj
             else if (keyEvent->key()<=int(Qt::Key_Z)&&keyEvent->key()>=int(Qt::Key_A)){//Q:输入字符
                 //TODO:加入标点符号
                 std::string tem;//lwj(报错→+std::？
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

             return true;
         }
         else if (event->type() == QEvent::MouseButtonPress){
              QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

             if (mouseEvent->button() == Qt::LeftButton){
                 myEvent.mousePressEvent(mouseEvent);
                 tcursor = textEdit->textCursor();
                 int col = tcursor.position() - tcursor.block().position();
                 int row = tcursor.blockNumber();
                 //接口
                 textBody.setAxis(row,col);
                 //setMouseAction(move,row,col);

                 if (event->type() == QEvent::MouseMove)//Q:同时？待测试
                     myEvent.mouseMoveEvent(mouseEvent);

                 if (event->type() == QEvent::MouseButtonRelease){//Q:同时？待测试
                     myEvent.mouseReleaseEvent(mouseEvent);
                     tcursor = textEdit->textCursor();
                     int col = tcursor.position() - tcursor.block().position();
                     int row = tcursor.blockNumber();
                     //接口
                     //setMouseAction(move,row,col);
                 }
                 return true;
             }
             else{
                 return QMainWindow::eventFilter(obj, event);
             }
         }
         else {
             return false;
             //return QMainWindow::eventFilter(obj, event);
         }
         this->flush();//将内存写入显示框内
         return true;
     }
     else{
         // pass the event on to the parent class
         return QMainWindow::eventFilter(obj, event);
     }
}
