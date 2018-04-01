#include "def.h"
class block
{
public:
	block();
	~block();

private:
	string text;
	int head, tail;
	int textSize;
	block * next;
};

block::block()
{
}

block::~block()
{
}

class linehead
{
public:
	linehead();
	~linehead();

private:
	string * firstBlock;//指向第一个block
	linehead * next;

};

linehead::linehead()
{
	this->firstBlock = NULL;
	this->next = NULL;
}

linehead::~linehead()
{
}

class temText
{
public:
	temText();
	~temText();

private:
	int counter;//段计数
	linehead * head;//行头链表头
	bool changeMode;//换行模式

};

temText::temText()
{
	head = NULL;
}

temText::~temText()
{
}
