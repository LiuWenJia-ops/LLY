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
	string * firstBlock;//ָ���һ��block
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
	int counter;//�μ���
	linehead * head;//��ͷ����ͷ
	bool changeMode;//����ģʽ

};

temText::temText()
{
	head = NULL;
}

temText::~temText()
{
}