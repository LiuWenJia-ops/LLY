#include "arrayline.h"

int main(void)
{   
    
    cursor* cur=new cursor;	

    // std::cout<<"--------debug "<<2<<" -------"<<std::endl;//FIXME:
    
    char* bigstr=(char*)malloc(sizeof(char)*150);

    std::string tx="ojbkkk\npierlewio\nhehe\ncdcdcd";

    // memset(bigstr,'a',sizeof(char)*146);
    // bigstr[0]='\n';
    // tx.append(bigstr);
    
    cur->insertStr(tx);//row=1,col=1
    cur->getAxis();
    
    std::cout<<"fulltext:"<<std::endl;
    cur->setAxis(1,1);
    cur->printFULL();

    // cur->setAxis(1,1);
    // cur->delBlock(4,3);
    // cur->getAxis();

    // std::cout<<"fulltext:"<<std::endl;
    // cur->setAxis(1,1);
    // cur->printFULL();
    
    // cur->setAxis(2,5);
    // cur->delBlock(5,140);

    // std::cout<<"fulltext after delB:"<<std::endl;
    // cur->setAxis(1,1);
    // cur->printFULL();

    std::cout<<std::endl<<"delC() test:"<<std::endl;
    cur->setAxis(1,1);
    cur->delC(1);
    cur->setAxis(4,7);
    cur->delC(-1);

    // cur->setAxis(2,1);cur->delC(1);
    cur->setAxis(1,7);cur->delC(-1);
    std::cout<<"delC fulltext:"<<std::endl;
    cur->setAxis(1,1);
    cur->printFULL();

    // int quit;
    // std::cin>>quit;
}