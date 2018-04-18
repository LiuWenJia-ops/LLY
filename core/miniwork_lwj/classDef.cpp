#include<iostream>
class cursor
{
public:
	cursor();
	~cursor();

private:
	char * ch;//指向字符,光标前的字
	linehead * liH;//指向行头
	block * bl;//指向块
			   //暂定,界面绘制参数 
};

cursor::cursor()
{
}

cursor::~cursor()
{
}
class block//字符块
{
public:
	block();
	~block();


private:
	char ch[101];//字符串,无效字符\0
	int head, tail;//串头,串尾
	int textSize;//串长
	block * next;//下一block
	friend class linehead;
};

block::block()
{
	ch = NULL;
	head = NULL; tail = NULL;
	textSize = 0;
	next = NULL;
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

private:
	int
		block * firstBlock;//指向第一个block
	linehead * next;//下一个行头

};

linehead::linehead()
{
	this->firstBlock = NULL;
	this->next = NULL;
}
block* linehead::newBlock() {//在光标所指的block之后插入新的block
	block* tem = new block;
	return tem;
}
bool linehead::deleteBlock(block* target) {
	if (!target)
		return false;
	delete target;
	return true;
}
linehead::~linehead()//释放当前行后的blocks
{
	block* tem = this->firstBlock;
	block* nextblk;
	while (!tem) {
		nextblk = tem->next;
		delete tem;
		tem = nextblk;
	}
}

class temText//文字编辑内存
{
public:
	temText();
	~temText();

private:
	int parcounter;//段计数
	linehead * head;//行头链表头结点
	bool changeMode;//换行模式,true为非自动变化

};

temText::temText()
{
	parcounter = 0;
	head = NULL;
	changeMode = true;
}

temText::~temText()
{
	linehead * tem = head->next;
	line* nexthd;
	while (!tem) {
		nexthd = tem->next;
		delete tem;
		tem = nexthd;
	}
}