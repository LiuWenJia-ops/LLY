#include<iostream>
class cursor
{
public:
	cursor();
	~cursor();

private:
	char * ch;//ָ���ַ�,���ǰ����
	linehead * liH;//ָ����ͷ
	block * bl;//ָ���
			   //�ݶ�,������Ʋ��� 
};

cursor::cursor()
{
}

cursor::~cursor()
{
}
class block//�ַ���
{
public:
	block();
	~block();


private:
	char ch[101];//�ַ���,��Ч�ַ�\0
	int head, tail;//��ͷ,��β
	int textSize;//����
	block * next;//��һblock
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

class linehead//��ͷ���
{
public:
	linehead();
	~linehead();

	block* newBlock();//������new block 
	bool deleteBlock(block* target);

private:
	int
		block * firstBlock;//ָ���һ��block
	linehead * next;//��һ����ͷ

};

linehead::linehead()
{
	this->firstBlock = NULL;
	this->next = NULL;
}
block* linehead::newBlock() {//�ڹ����ָ��block֮������µ�block
	block* tem = new block;
	return tem;
}
bool linehead::deleteBlock(block* target) {
	if (!target)
		return false;
	delete target;
	return true;
}
linehead::~linehead()//�ͷŵ�ǰ�к��blocks
{
	block* tem = this->firstBlock;
	block* nextblk;
	while (!tem) {
		nextblk = tem->next;
		delete tem;
		tem = nextblk;
	}
}

class temText//���ֱ༭�ڴ�
{
public:
	temText();
	~temText();

private:
	int parcounter;//�μ���
	linehead * head;//��ͷ����ͷ���
	bool changeMode;//����ģʽ,trueΪ���Զ��仯

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