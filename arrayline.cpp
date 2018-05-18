#include "arrayline.h"

int main(void)
{   
    
    cursor* cur=new cursor;	

    // std::cout<<"--------debug "<<2<<" -------"<<std::endl;//FIXME:
    std::string tx="ojbkkkkkkkkkkkkkkk\npierlewio\nhehe\ncdcdcd";
    cur->insertStr(tx);//row=1,col=1

    std::cout<<"fulltext:"<<std::endl;
    cur->setAxis(1,1);
    cur->printFULL();
    
    cur->delFULL();
    std::cout<<"fulltext:"<<std::endl;
    cur->setAxis(1,1);
    cur->printFULL();

    int quit;
    std::cin>>quit;
}