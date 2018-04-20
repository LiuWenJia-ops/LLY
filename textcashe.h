#include "classDef.h"
#include<iostream>//TODO: 待删
// 1. 坐标值和数据结构位置转换的函数
// 2. 插入字符、行
// 3. 删除字符、行，包括向前向后
// 4. 光标位置存储
bool linehead::charInsert(unsigned int col,char c)
{
    if(!this->firstBlock)
        firstBlock=newBlock();
    
}

linehead * temText::curToRow(cursor cur)
{
    unsigned int t=cur.getRow();
    linehead* now_line=this->head;
    while(t>0){
        if(!now_line)//TODO:报错提示，如果确保其他地方无误就可以去掉
            std::cout<<"error:the cursor row number is longer than the line number"<<std::endl;
        else
            now_line=now_line->getNext();
        t--;
    }
    return now_line;
}
bool temText::charInsert(cursor &cur,char c)
{
    linehead* nowline=this->curToRow(cur);

}
