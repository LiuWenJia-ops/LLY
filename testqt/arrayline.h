#ifndef ARRAY_H
#define ARRAY_H
#include <cstdlib>
#include <string>
#include <iostream>
#define CTYPE char

class cursor;
class linehead;
class temText;

typedef class linehead//行链表，双向链表
{
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
	this->pre=nullptr;
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
	friend class cursor;
public:
	temText();
	~temText();
	// cursor *cur;
    linehead* newLine(void);//在最后加一行
    linehead* insertLine(linehead* preLine,CTYPE* str,int n);//在指定行后插一行
	linehead* getFirst() { return firstLine; }
    bool deleteLine(linehead* target);//删除行
	int linecounter;//行计数
private:
	linehead * firstLine;//第一行
	bool changeMode;//换行模式flag,true为非自动变化

}temText;

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
    linehead* tem=this->firstLine;	
	linehead* nextLine;
	while(!tem){
		nextLine=tem->getNext();
		delete tem;
		tem=nextLine;
	}
}
linehead* temText::newLine(void)
{
	linehead* tem=new linehead;
	if(this->firstLine==nullptr){
		this->firstLine=tem;
		this->firstLine->setPre(tem);
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
linehead* temText::insertLine(linehead* preLine,CTYPE* str,int n)//
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
		this->linecounter++;//上一个分支newline()内部有inc
    }
    for(int i=0;i<n;i++)
        tempB->chs[i]=str[i];
    tempB->setSize(n);
    return tempB;
}
bool temText::deleteLine(linehead* target)
{
	if(target==nullptr){
		std::cout<<"target line not exist"<<std::endl;
		return false;	
	}
	//TODO:有空可以优化成一个临时变量
	linehead* pre=target->getPre();
	linehead* next=target->getNext();
	target->getPre()->setNext(target->getNext());
	if(target->getNext()!=nullptr)
		target->getNext()->setPre(target->getPre());
	delete target;
	this->linecounter--;
	return true;
}
typedef class cursor//逻辑上的光标，不是实际的那个，用于在链表中定位
{
public:
	cursor();
	~cursor();
	linehead* getNowLine(){return nowLine;}
	linehead* getFirstLine(){return firstLine;}
	int getLineN(){return WHOLETEXT->linecounter;}
	void getAxis(void){std::cout<<'('<<row<<','<<col<<')'<<std::endl;}

	void setFirstLine(linehead* lp){this->firstLine=lp;}
	void setNowLine(linehead* lp){nowLine=lp;}
	void setAxis(int tR,int tC);//更改坐标，并修改nowline指针
	linehead* axisToPtr(int row);//由行数修改指针

	//TODO:insert需要进化注释在内部
	void insertStr(std::string str);//需要先移动光标，插入字符串,判断换行，包含块插入，不修改坐标
	void delFULL(void);// 删库
	void delNL(int type);//清空1/删除10当前行；若删除，则行坐标和指针-1
	void delC(int isbackspace);//需要预设坐标，删除单字符，使用moveArray和delBlcok//TOTEST:得等insert改了才能测试，insert不会自动修改坐标
	
	//块操作
	std::string cutBlock(int r2,int c2);//需要先移动光标剪切，用了copy和del
	void delBlock(int r2,int c2);//需要移动光标，删除从(r1,c1)到(r2,c2)的内容，注意删完坐标不变
	std::string copyBlock(int r1,int c1,int r2,int c2);//不用先移动光标,取块，string中转,QCHAR的转换函数
	void moveArray(linehead* t,int index,int n);//包含index，删除此后n个字符

	//FIXME:测试打印函数
	void printNL(void);//print current
	void printFULL(void);//注意print完在指针在最后一行
private:
    linehead* firstLine;
    linehead* nowLine;
	temText* WHOLETEXT;
	int row;//从1开始计算
	int col;//从1开始计算，表示光标后字符的序号
}cursor;
cursor::cursor()
{
	nowLine=nullptr;
	firstLine=nullptr;
	WHOLETEXT=new temText;
	this->setFirstLine(WHOLETEXT->firstLine);
	this->setNowLine(WHOLETEXT->firstLine);
	this->row=1;
	this->col=1;
}
void cursor::setAxis(int tR,int tC)
{
	this->row=tR;
	this->col=tC;
	nowLine=axisToPtr(tR); 
}
linehead* cursor::axisToPtr(int row)
{
    linehead* tLine=this->firstLine;
	int i=1;
    while(i<row){
        tLine=tLine->getNext();
        i++;  
    }
	return tLine;
}

void cursor::insertStr(std::string str)
{
	// std::cout<<"BEGIN insert!!"<<std::endl; //FIXME:	
    //TODO:大于100的情况
	//TODO:没有考虑在字符串中间插入的情况
    int cnt=1;
    for(int i=0;i<str.size();i++,cnt++){
        if(str.at(i)=='\n'){//插入新行，移动坐标
            nowLine->setSize(col-1+cnt-1);
            cnt=1;
			row++; col=1;
			nowLine=WHOLETEXT->insertLine(this->nowLine,nullptr,0);
        }else{
			this->nowLine->chs[col-1]=str.at(i);
		    col++;
            int newsize=nowLine->getSize()+1;
			nowLine->setSize(newsize);
        }

    }
}
void cursor::delFULL(void)
{
	delete WHOLETEXT;
	WHOLETEXT= new temText;
	this->setFirstLine(WHOLETEXT->firstLine);
	this->setNowLine(WHOLETEXT->firstLine);
	this->row=1;
	this->col=1;
}
void cursor::delNL(int type)
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
void cursor::delC(int isbackspace)
{
	std::string temp;
	if(isbackspace>0){
		if(col==1){
			temp=copyBlock(row,1,row,nowLine->getSize());
			nowLine=nowLine->getPre();
			row--;col=nowLine->getSize()+1;
			insertStr(temp);
			WHOLETEXT->deleteLine(nowLine->getNext());
		}else{
			moveArray(nowLine,col-1,1);
			col--;
			nowLine->setSize(nowLine->getSize()-1);
		}
	}else{
		if(col==nowLine->getSize()+1){
			temp=copyBlock(row+1,1,row+1,nowLine->getNext()->getSize());
			insertStr(temp);
			WHOLETEXT->deleteLine(nowLine->getNext());
		}else{
			moveArray(nowLine,col,1);
			nowLine->setSize(nowLine->getSize()-1);
		}
	}	
}


void cursor::moveArray(linehead* t,int index,int n)
{
	int DELTA=t->getSize()-(index+n);
	for(int i=0;i<=DELTA;i++)//=号是因为把终结符也移动了
		t->chs[index+i]=t->chs[index+n+i];
}

std::string cursor::cutBlock(int r2,int c2)
{
	std::string rs=copyBlock(row,col,r2,c2);
	delBlock(r2,c2);
	return rs;
}
void cursor::delBlock(int r2,int c2)
{
	int oC=col;
	linehead* endL=axisToPtr(r2);
	if(row==r2){
		moveArray(nowLine,col-1,c2-col+1);
		nowLine->setSize(nowLine->getSize()-(c2-col+1));
	}
	else{
		moveArray(nowLine,col-1,nowLine->getSize()-col+1);
		std::string mt=copyBlock(r2,1,r2,c2);
		std::cout<<mt<<std::endl;
		insertStr(mt);
		while(nowLine->getNext()!=endL){
			WHOLETEXT->deleteLine(nowLine->getNext());
		}
		WHOLETEXT->deleteLine(endL);
		nowLine->setSize(oC+c2-1);
	}
	col=oC;
	getAxis();
}

std::string cursor::copyBlock(int r1,int c1,int r2,int c2)
{
	std::string rs;
	std::string add;
	linehead* iLine=axisToPtr(r1);
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

void cursor::printNL(void)
{       
	for(int i=0;nowLine->chs[i]!='\0';i++)
		std::cout<<nowLine->chs[i];
	std::cout<<std::endl;

}
void cursor::printFULL(void)
{
	for(int i=1;i<=WHOLETEXT->linecounter;i++){
		setAxis(i,1);
		printNL();
	}
}

#endif
