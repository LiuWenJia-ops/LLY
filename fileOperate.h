#include "classDef.h"
#include "textcashe.h"
#include <QFileDialog>
#include<iostream>


bool vacantBody(){//清空body

}

void newfile(const char* & addr){
    if(addr)
         //TODO:询问是否保存当前文件并新建,
         // 若否，直接返回；若是，保存文件并清空body，还原cur位置
}

temText * openfile(const char* & addr,temText & body){//XXX:打开文件的操作只有系统化文件夹窗口里选取，不过应该够了U•ェ•*U
    //TODO:如果已经打开了一份文件还想打开第二份
    // if(addr){//已经打开过一份
    //     //TODO:询问是否保存并重新打开,
    //     // 若否，直接返回；若是，保存并清空body，还原cur位置；
    // }//否则直接打开
    QString filename = QFileDialog::getOpenFileName(//得到文件路径
                        this,
                        "Open Document",
                        QDir::currentPath(),//打开程序地址下的目录
                        "Text files (*.txt )");//file filter,只能打开txt

    if (!filename.isNull()) { //用户选择了文件
        QByteArray ba=filename.toLatin1();  
        addr=ba.data();//add存储的是绝对地址 TOTEST:（函数内部的const是全局不变的吗？）
        
        ifstream buf(addr);
        //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)   
        string media;
        while(buf.getline(media)))
            body.cur->insertStr(media)//TODO:将string插入到linehead里
        return body; 
    } else // 用户取消选择
        return NULL;
}
//TODO: 退出之前询问是否保存
bool savefile(const char* & addr,temText & body){
    if(!addr){//TODO:新建的文件无原地址，应该有什么打开系统文件夹的操作
    }else{//否则直接保存到ch
        ofstream buf(addr);
        //FIXME:偷懒,没有检查打开失败的情况 (●'◡'●)   
        linehead * tem=body.firstLine;
        while(tem!=body.firstLine){
            buf<<tem.chs<<endl;
            tem=tem->next;
        }
    }
}



