#include "arrayline.h"

void cursor::axisToPtr(int row)
{
    this->nowLine=this->firstLine;
    int i=1;
    while(i<row){
        this->nowLine=this->nowLine->getNext();
        i++;    
    }
}
void cursor::insertStr(std::string str)
{
    
}