#include <cstdlib>
#include <string>
#define CTYPE char

typedef class cursor//逻辑上的光标，不是实际的那个，用于在链表中定位
{
public:
	cursor();
	~cursor();
	void setFirstLine(linehead* lp){
		this->firstLine=lp;
	}
	void axisToPtr(int row);//TODO:由行数修改指针
	void insertStr(std::string str);//TODO:插入字符串,判断换行
	// void deleteChar(bool isback);//TODO:删除前后字符，删除行
	// CTYPE* copyStr(CP* sPtr,CP* ePtr);//new一段字符串数组返回 TODO:考虑清楚是用头指针还是尾指针
private:
    linehead* firstLine;
    linehead* nowLine;
	int row;//从1开始计算
	int col;//从1开始计算，表示光标后字符的序号
}cursor;
cursor::cursor()
{
    nowLine=firstLine;
    row=1;
    col=1;
}
typedef class linehead//行链表，双向链表
{
    friend class cursor;
public:
	linehead();
	~linehead();
	linehead * getNext(void){ 
		return this->next;
	}
	void setNext(linehead* np){ 
		this->next=np;
	}
    linehead* getPre(void){
		return pre;
	}
	void setPre(linehead* np){
		pre=np;
	}
    int getSize(void){
		return strSize;
	}
	void setSize(int n);//TODO:包括修改其他参数的内容
	CTYPE *chs;
private:
    int strSize;
	linehead * next;//下一个行头
    linehead * pre;
}linehead;
linehead::linehead()
{
	this->next = nullptr;
    chs=(CTYPE*)malloc(sizeof(CTYPE)*101);
    chs[0]='\0';
    strSize=0;
}
linehead::~linehead()//释放当前行后的blocks
{
    free(chs);
}
void linehead::setSize(int n)
{
    strSize=n;
    this->chs[n]='\0';
}

typedef class temText//文字编辑内存
{
public:
	temText();
	~temText();
	cursor *cur;
    linehead* newLine(void);//在最后加一行
    linehead* insertLine(linehead* preLine,CTYPE* str,int n);//在指定行后插一行
    bool deleteLine(linehead* target);//删除行
private:
	int linecounter;//行计数
	linehead * firstLine;//第一行
	bool changeMode;//换行模式flag,true为非自动变化

}temText;

temText::temText()
{
	linecounter=1;
	firstLine = newLine();
	cur=new cursor;
	cur->setFirstLine(firstLine);
	changeMode=true;
}
temText::~temText()
{
    linehead* tem=this->firstLine;	
	linehead* nextLine;
	while(!tem){
		nextLine=tem->getNext();
		delete tem;
		tem=nextLine;
	}	
}
linehead* temText::newLine(void)//TOTEST:
{
	linehead* tem=new linehead;
	if(this->firstLine==nullptr){
		this->firstLine=tem;
		this->firstLine->setPre(this->firstLine);
	}
	else{//行链表的尾结点的next为空
		linehead* lastLine=this->firstLine->getPre();
		lastLine->setNext(tem);
		tem->setPre(lastLine);
		this->firstLine->setPre(tem);
	}
    this->linecounter++;
	return tem;
}
linehead* temText::insertLine(linehead* preLine,CTYPE* str,int n)//TOTEST:
{
    linehead* tempB;
    if(preLine->getNext()==nullptr)
        tempB=this->newLine();
    else{
        tempB=new linehead;
        tempB->setPre(preLine);
        tempB->setNext(preLine->getNext());
        tempB->getNext()->setPre(tempB);
        preLine->setNext(tempB);
    }
    for(int i=0;i<n;i++)
        tempB->chs[i]=str[i];
    tempB->setSize(n);
    return tempB;
}
bool temText::deleteLine(linehead* target)//TOTEST:
{
	if(target==nullptr)
			return false;
	//TODO:有空可以优化成一个临时变量
    target->getPre()->setNext(target->getNext());
    target->getNext()->setPre(target->getPre());
	delete target;
	this->linecounter--;
	return true;
}
