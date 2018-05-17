#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileOperate.h"

static char addr[1000];
static cursor cur;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::openfile(char* addr,cursor & cur){//XXX:打开文件的操作:系统化文件夹窗口里选取
//    //TODO:如果已经打开了一份文件还想打开第二份
//    if(addr[0]){//已经打开过一份
//       // TODO:询问是否保存当前文件并新建,
//        //若否，直接返回；
//        //若是，保存文件
//        {
//            savefile(addr,cur);
//        }
//    }//清空body，还原cur位置
    QString filename = QFileDialog::getOpenFileName(//得到文件路径
                        this,
                        tr("Open Document"),
                        QDir::currentPath(),//打开程序地址下的目录
                        "Text files (*.txt )");//file filter,只能打开txt

    if (!filename.isNull()) { //用户选择了文件
        QByteArray ba=filename.toLatin1();
        addr=ba.data();//add存储的是绝对地址 TOTEST:（函数内部的const是全局不变的吗？）

        ifstream buf(addr);
        //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)
        string media;
        while (getline(buf,media)){
            media.append("\n");
            cur.insertStr(media);//TODO:将string插入到linehead里
        }
        return true;
    } else // 用户取消选择
        return false;
}
//TODO: 退出之前询问是否保存

bool MainWindow::savefile(char*  addr,cursor & cur){
//    if(!addr[0]){//TODO:新建的文件无原地址，应该有什么打开系统文件夹的操作
//        //TODO:输入保存路径
//    }
    ofstream buf(addr);
    //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)
    linehead * tem=cur.getFirstLine();
    while(tem!=nullptr){
        buf<<tem->chs<<std::endl;
        tem=tem->getNext();
    }
 //   addr[0]="\0";
    return true;
}

void MainWindow::newfile(char* addr,cursor & cur){
//   if(addr[0]){
//       // TODO:询问是否保存当前文件并新建,
//        //若否，直接返回；
//        //若是，保存文件
//        {
//            savefile(addr,cur);
//            addr[0]="\0";
//        }
//   }//清空body，还原cur位置
   cur.delFULL();
}
void MainWindow::on_actionnew_triggered()
{
    newfile(addr,cur);
}

void MainWindow::on_actionsave_triggered()
{
    savefile(addr,cur);
}

void MainWindow::on_actionopen_triggered()
{
    openfile(addr,cur);
}
