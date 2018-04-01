#include "def.h"
class block//字符块
{
public:
	block();
	~block();

private:
	string text;//字符串
	int head, tail;//串头,串尾
	int textSize;//串长
	block * next;//下一block
};

block::block()
{
}

block::~block()
{
}

class linehead//行头结点
{
public:
	linehead();
	~linehead();

private:
	string * firstBlock;//指向第一个block
	linehead * next;//下一个行头

};

linehead::linehead()
{
	this->firstBlock = NULL;
	this->next = NULL;
}

linehead::~linehead()
{
}

class temText//文字编辑内存
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
