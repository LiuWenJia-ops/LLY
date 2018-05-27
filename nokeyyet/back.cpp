#include "back.h"
lineheAD::lineheAD()
{
    this->pre=nullptr;
    this->next = nullptr;
    chs=(CTYPE*)malloc(sizeof(CTYPE)*101);
    chs[0]='\0';
    strSize=0;
    arySIze=101;
}
lineheAD::~lineheAD()//释放当前行后的blocks
{
    free(chs);
}
void lineheAD::setSize(int n)
{
    strSize=n;
    this->chs[n]='\0';
}
//-------------------------------------------------
temText::temText()
{
    linecounter=0;
    // cur=nullptr;
    firstLine=nullptr;
    firstLine = newLine();
    changeMode=true;
}
temText::~temText()
{
    lineheAD* tem=this->firstLine;
    lineheAD* nextLine;
    while(!tem){
        nextLine=tem->getNext();
        delete tem;
        tem=nextLine;
    }
}
lineheAD* temText::newLine(void)
{
    lineheAD* tem=new lineheAD;
    if(this->firstLine==nullptr){
        this->firstLine=tem;
        this->firstLine->setPre(tem);
    }
    else{//行链表的尾结点的next为空
        lineheAD* lastLine=this->firstLine->getPre();
        lastLine->setNext(tem);
        tem->setPre(lastLine);
        this->firstLine->setPre(tem);
    }
    this->linecounter++;
    return tem;
}
lineheAD* temText::insertLine(lineheAD* preLine,CTYPE* str,int n)//
{
    lineheAD* tempB;
    if(preLine->getNext()==nullptr)
        tempB=this->newLine();
    else{
        tempB=new lineheAD;
        tempB->setPre(preLine);
        tempB->setNext(preLine->getNext());
        tempB->getNext()->setPre(tempB);
        preLine->setNext(tempB);
        this->linecounter++;//上一个分支newline()内部有inc
    }
    for(int i=0;i<n;i++)
        tempB->chs[i]=str[i];
    tempB->setSize(n);
    return tempB;
}
bool temText::deleteLine(lineheAD* target)
{
    if(target==nullptr){
        std::cout<<"target line not exist"<<std::endl;
        return false;
    }
    target->getPre()->setNext(target->getNext());
    if(target->getNext()!=nullptr)
        target->getNext()->setPre(target->getPre());
    delete target;
    this->linecounter--;
    return true;
}

//----------------------------------------

myTextEdit::myTextEdit()
{
    nowLine=nullptr;
    firstLine=nullptr;
    WHOLETEXT=new temText;
    this->setFirstLine(WHOLETEXT->firstLine);
    this->setNowLine(WHOLETEXT->firstLine);
    this->row=1;
    this->col=1;
}
myTextEdit::~myTextEdit()
{
    delete WHOLETEXT;
}
void myTextEdit::setAxis(int tR,int tC)
{
    this->row=tR;
    this->col=tC;
    nowLine=axisToPtr(tR);
}
lineheAD* myTextEdit::axisToPtr(int row)
{
    lineheAD* tLine=this->firstLine;
    int i=1;
    while(i<row){
        tLine=tLine->getNext();
        i++;
    }
    return tLine;
}

void myTextEdit::insertStr(std::string str)
{
    int lineBEgin=0,lineENd;
    std::string nowTEXT,taIL;
    if(col<=nowLine->getSize())
        taIL.append(&(nowLine->chs[col-1]),nowLine->getSize()-col+1);
    while(lineBEgin<(int)str.size()){
        //deal string
        lineENd=str.find('\n',lineBEgin);
        if(lineENd==std::string::npos)
            lineENd=str.size();
        nowTEXT=str.substr(lineBEgin,lineENd-lineBEgin);
        lineBEgin=lineENd+1;
        //if memory not enough
        if((int)nowTEXT.length()+nowLine->getSize()-10>nowLine->arySIze){
            nowLine->chs=(CTYPE*)realloc(nowLine->chs,nowLine->arySIze+100);
            nowLine->arySIze+=100;
        }
        //copy
        for(int i=0;i<(int)nowTEXT.length();i++,col++)
            nowLine->chs[col-1]=nowTEXT.at(i);
        // col--;
        nowLine->setSize(col-1);
        if(lineBEgin<str.size()){
            nowLine=WHOLETEXT->insertLine(this->nowLine,nullptr,0);
            row++;col=1;
        }
    }
    // //FIXME:
    // std::cout<<"debug nowLine size here: "<<nowLine->getSize()<<std::endl;
    if(taIL.size()>0){
        insertStr(taIL);
        col-=taIL.size();
    }

}

void myTextEdit::delFULL(void)
{
    delete WHOLETEXT;
    WHOLETEXT= new temText;
    this->setFirstLine(WHOLETEXT->firstLine);
    this->setNowLine(WHOLETEXT->firstLine);
    this->row=1;
    this->col=1;
}
void myTextEdit::delNL(int type)
{
    if(type==1||nowLine==firstLine){
        col=1;
        nowLine->setSize(0);
    }
    if(type==10){
        WHOLETEXT->deleteLine(nowLine);
        row--;
        nowLine=axisToPtr(row);
        col=nowLine->getSize()+1;
    }
}
void myTextEdit::delC(int isbackspace)
{
    std::string temp;
    if(isbackspace<=0){
        if(row==getLineN()&&col>nowLine->getSize()){
            std::cout<<"could not delete here"<<std::endl;
            return;
        }
    }else{
        if(row==1&&col<=1){
            std::cout<<"could not backspace here"<<std::endl;
            return;
        }
    }
    if(isbackspace>0){
        if(col==1){
            temp=copyBlock(row,1,row,nowLine->getSize()+1);
            nowLine=nowLine->getPre();
            row--;col=nowLine->getSize()+1;
            insertStr(temp);
            col-=temp.length();//TOTEST:axis notchage
            getAxis();
            WHOLETEXT->deleteLine(nowLine->getNext());
        }else{
            moveArray(nowLine,col-2,1);
            col--;
            nowLine->setSize(nowLine->getSize()-1);
        }
    }else{
        // std::cout<<nowLine->getSize();getAxis();
        if(col==nowLine->getSize()+1){
            temp=copyBlock(row+1,1,row+1,nowLine->getNext()->getSize()+1);
            insertStr(temp);
            col-=temp.length();//TOTEST:axis notchage
            getAxis();
            WHOLETEXT->deleteLine(nowLine->getNext());
        }else{
            moveArray(nowLine,col-1,1);
            nowLine->setSize(nowLine->getSize()-1);
        }
    }
}


void myTextEdit::moveArray(lineheAD* t,int index,int n)
{
    int DELTA=t->getSize()-(index+n);
    for(int i=0;i<=DELTA;i++)//=号是因为把终结符也移动了
        t->chs[index+i]=t->chs[index+n+i];
}

std::string myTextEdit::cutBlock(int r2,int c2)
{
    std::string rs=copyBlock(row,col,r2,c2);
    delBlock(r2,c2);
    return rs;
}
void myTextEdit::delBlock(int r2,int c2)
{
    int oC=col;
    lineheAD* endL=axisToPtr(r2);
    if(row==r2){
        moveArray(nowLine,col-1,c2-col+1);
        nowLine->setSize(nowLine->getSize()-(c2-col+1));
    }
    else{
        moveArray(nowLine,col-1,nowLine->getSize()-col+1);
        std::string mt=copyBlock(r2,c2,r2,endL->getSize()+1);
        std::cout<<mt<<std::endl;
        // getAxis();//FIXME:
        insertStr(mt);
        // getAxis();
        for(int i=0;i<nowLine->getSize();i++)
            std::cout<<nowLine->chs[i];
        std::cout<<std::endl;
        while(nowLine->getNext()!=endL){
            WHOLETEXT->deleteLine(nowLine->getNext());
        }
        int DELTA=endL->getSize()-c2;
        WHOLETEXT->deleteLine(endL);
        nowLine->setSize(oC+DELTA);
        //FIXME:
        // std::cout<<"delBLOCK nowLine size here: "<<nowLine->getSize()<<std::endl;
    }
    col=oC;
    std::cout<<"axis after delete a block: ";getAxis();
}

std::string myTextEdit::copyBlock(int r1,int c1,int r2,int c2)
{
    c2--;
    std::string rs;
    std::string add;
    lineheAD* iLine=axisToPtr(r1);
    if(r1==r2)
        rs.append(&(iLine->chs[c1-1]),c2-c1+1);
    else{
        add=&(iLine->chs[c1-1]);
        rs.append(add);
        int i=r1+1;
        while(i<r2){
            rs.append("\n");
            iLine=iLine->getNext();
            rs.append(iLine->chs);
            i++;
        }
        iLine=iLine->getNext();
        rs.append("\n");
        rs.append(iLine->chs,c2);
    }
    return rs;
}
std::string myTextEdit::copyBlock(int r2,int c2)
{
    std::string rs;
    std::string add;
    lineheAD* iLine=axisToPtr(row);
    if(row==r2)
        rs.append(&(iLine->chs[col-1]),c2-col+1);
    else{
        add=&(iLine->chs[col-1]);
        rs.append(add);
        int i=row+1;
        while(i<r2){
            rs.append("\n");
            iLine=iLine->getNext();
            rs.append(iLine->chs);
            i++;
        }
        iLine=iLine->getNext();
        rs.append("\n");
        rs.append(iLine->chs,c2);
    }
    return rs;
}
void myTextEdit::printNL(void)
{
    for(int i=0;nowLine->chs[i]!='\0';i++)
        std::cout<<nowLine->chs[i];
    std::cout<<std::endl;
}
void myTextEdit::printFULL(void)
{
    for(int i=1;i<=WHOLETEXT->linecounter;i++){
        setAxis(i,1);
        printNL();
//        std::cout<<std::endl;
    }
    setAxis(row,nowLine->getSize()+1);
}
