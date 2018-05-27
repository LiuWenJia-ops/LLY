#include <fstream>
int main(void)
{
    std::fstream newfile;
    newfile.open("re.txt",std::ios::out|std::ios::trunc);
    for(int i=1;i<=9;i++){
        newfile<<"line"<<i<<":-----E"<<std::endl;
    }
    newfile<<"total 12 characters per line above";
    newfile.close();
    return 0;
}