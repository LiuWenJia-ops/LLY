#pragma once
#include<iostream>
class cursor//�߼��ϵĹ�꣬����ʵ�ʵ��Ǹ��������������ж�λ
{
public:
	cursor();
	~cursor();
	unsigned int getRow(void) { return this->row; }
	unsigned int getCol(void) { return this->col; }
	void setRow(unsigned n) { this->row = n; }
	void setCol(unsigned n) { this->col = n; }
private:
	Qchar * ch;//ָ���ַ�,���ǰ����
	linehead * liH;//ָ����ͷ
	block * bl;//ָ���
			   //�ݶ�,������Ʋ���
	unsigned int row;//��1��ʼ����
	unsigned int col;//��1��ʼ���� 
};

cursor::cursor()
{
	row = 1;
	col = 1;
}

cursor::~cursor()
{
}
class block//�ַ���
{
public:
	block();
	~block();
	block* getNext(void) { return next; }
	block* setNext(block* np) { next = np; }
	int getSize(void) { return textSize; }
private:
	Qchar ch[101];//�ַ���,��Ч�ַ�\0
	int head, tail;//��ͷ,��β
	int textSize;//����
	block * next;//��һblock
	friend class linehead;
};

block::block()
{
	ch[0] = '\0'; //ch={""};�������
	head = 0;
	tail = 0;
	textSize = 0;
	next = nullptr;
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
	linehead * getNext(void) { return this->next; }
	void setNext(linehead* np) { this->next = np; }
	bool QcharInsert(unsigned int col, Qchar c);//���ݹ������ַ������޸Ĺ��
	bool stringInsert();//TODO: �����ַ������ȴ���������ȷ��D
private:
	int num;//TODO: ���û���þ�ɾ��
	linehead * next;//��һ����ͷ
	block * firstBlock;//ָ���һ��block

};

linehead::linehead()
{
	this->firstBlock = nullptr;
	this->next = nullptr;
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
	linehead * curToRow(cursor cur);//���ݹ�귵���н��
	bool QcharInsert(cursor &cur, Qchar c);//���ݹ������ַ������޸Ĺ��
	bool stringInsert();//TODO: �����ַ������ȴ���������ȷ��D
	bool QcharDel(cursor &cur, bool isFoward);//ɾ���ַ����ж�ǰ��
private:
	int parcounter;//�μ���
	linehead * head;//��ͷ����ͷ���,������
	bool changeMode;//����ģʽ,trueΪ���Զ��仯

};

temText::temText()
{
	parcounter = 0;
	head = new linehead;
	head->setNext(new linehead);
	changeMode = true;
}