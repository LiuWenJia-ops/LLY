
class cursor//逻辑上的光标，不是实际的那个，用于在链表中定位
{
public:
	cursor();
	~cursor();
	unsigned int getRow(void){return this->row;}
	unsigned int getCol(void){return this->col;}
	void setRow(unsigned n){this->row=n;}
	void setCol(unsigned n){this->col=n;}
private:
	char * ch;//指向字符,光标前的字
	linehead * liH;//指向行头
	block * bl;//指向块
	//暂定,界面绘制参数
	unsigned int row;//从1开始计算
	unsigned int col;//从1开始计算 
};

cursor::cursor()
{
	row=1;
	col=1;
}

cursor::~cursor()
{
}
class block//字符块
{
public:
	block();
	~block();
	block* getNext(void){return next;}
	block* setNext(block* np){next=np;}
	int getSize(void){return textSize;}
private:
	char ch[101];//字符串,无效字符\0
	int head, tail;//串头,串尾
	int textSize;//串长
	block * next;//下一block
	friend class linehead;
};

block::block()
{
	ch[0]='\0'; //ch={""};这个不行
	head=0;
	tail=0;
	textSize=0;
	next=nullptr;
}

block::~block()
{
}

class linehead//行头结点
{
public:
	linehead();
	~linehead();
	block* newBlock();//仅申请new block 
	bool deleteBlock(block* target);
	linehead * getNext(void){ return this->next;}
	void setNext(linehead* np){ this->next=np;}
	bool charInsert(unsigned int col,char c);//根据光标插入字符，并修改光标
	bool stringInsert();//TODO: 插入字符串，等待数据类型确定D
private:
	int num;//TODO: 如果没有用就删掉
	linehead * next;//下一个行头
	block * firstBlock;//指向第一个block
	
};

linehead::linehead()
{
	this->firstBlock = nullptr;
	this->next = nullptr;
}
block* linehead::newBlock(){//在光标所指的block之后插入新的block
	block* tem=new block;
	return tem;
}
bool linehead::deleteBlock(block* target){
	if(!target)
			return false;
	delete target;
	return true;
}
linehead::~linehead()//释放当前行后的blocks
{
	block* tem=this->firstBlock;	
	block* nextblk;
	while(!tem){
		nextblk=tem->next;
		delete tem;
		tem=nextblk;
	}	
}

class temText//文字编辑内存
{
public:
	temText();
	~temText();
	linehead * curToRow(cursor cur);//根据光标返回行结点
	bool charInsert(cursor &cur,char c);//根据光标插入字符，并修改光标
	bool stringInsert();//TODO: 插入字符串，等待数据类型确定D
	bool charDel(cursor &cur,bool isFoward);//删除字符，判断前后
private:
	int parcounter;//段计数
	linehead * head;//行头链表头结点,无内容
	bool changeMode;//换行模式,true为非自动变化

};

temText::temText()
{
	parcounter=0;
	head = new linehead;
	head->setNext(new linehead);
	changeMode=true;
}
