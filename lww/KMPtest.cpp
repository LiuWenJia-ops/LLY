// #include <vector>
// #include <string>
// #include <iostream>
// typedef class searchResult
// {
// public:
//     searchResult();
//     int getNumber(void){
//         return this->Number;
//     }
//     int* getSpecificOne(int INDEX){
//         return allResults.at(INDEX);
//     }
//     int nowINDEX;
//     void getNext(std::string substr,int* next);
//     int Index_KMP(std::string S,std::string T,int pos,const int* const next);
// private:
//     void search(void);
//     std::string content;
//     int Number;
//     std::vector<int[3]> allResults;//[n][3]
// }searchResult;
// searchResult::searchResult()
// {
//     Number=0;
//     nowINDEX=1;
// }

// void searchResult::search(void)
// {
//     int lineNumber=TEXT.getLineN();
//     for(int row=1;row<=lineNumber;row++){
        
//     }
// }
// void searchResult::getNext(std::string substr,int* next){
// 	unsigned int i=1,j=0;
// 	next[0]=-1;next[1]=0;
// 	while(i<substr.length()-1){
// 		if(j==0||substr.at(i)==substr.at(j)){
// 			++i;++j;
// 			next[i]=j;
// 		}else
// 			j=next[j];
// 	}
// }
// int searchReasult::Index_KMP(std::string S,std::string T,int pos,const int* const next){
// 	unsigned int i= pos,j=1;
// 	while(i<=S.length()-1&&j<=T.length()-1){
// 		if(j==0 || S.at(i)==T.at(j)){ 
// 			i++;
// 			j++;
// 		}else
// 			j=next[j];
// 	}
// 	if(j>T.length()-1)
// 		return i-(T.length()-1);
// 	else return 0;
// }
// #include "back.h"
#include "back.cpp"
int main(void)
{   
    searchResult sr;
    std::string S("1234567890987654321");
    std::string T("2");
    int next[T.size()+1];
    sr.getNextVal(T,next);
    for(int i=0;i<T.size()+1;i++)
        std::cout<<next[i]<<' ';
    std::cout<<std::endl;
    std::cout<<sr.Index_KMP(S,T,5,next);
    return 1;
}
aaaaaaa