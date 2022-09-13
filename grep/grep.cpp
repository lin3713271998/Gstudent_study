#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include  <sys/io.h>  
#include <iostream>  
#include <vector> 
using namespace std;
 
bool isFolderExist(string folder)//判断路径是否存在 
{
	char* ads = new char[strlen(folder.c_str()) + 1];;
    strcpy(ads, folder.c_str());
	int ret = 0;
	ret = _access(ads, 0);
	if (ret == 0)
		ret = true;
	else
		ret = false;
	return ret;
}
void getFiles(string path, vector<string>& files){//查找所有文件名 
    intptr_t hFile = 0;
    struct _finddata_t fileinfo;
    string p;  
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//若查找成功，则进入
    {
        do
        {
            //如果是目录,迭代之（即文件夹内还有文件夹）  
            if ((fileinfo.attrib &  _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            } 
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        //_findclose函数结束查找
        _findclose(hFile);
    }
}
 
int main( int argc, char* argv[])//从命令框传递参数 
{
while(1){
if(argv[0].find("grep")==0){
		if(isFolderExist(argv[2])){
	    vector<string> FileName_List;	 
	    getFiles(argv[2], FileName_List);
	    for (int i = 0; i < FileName_List.size(); i++){//做文件名匹配 
	    	if(FileName_List[i].find(argv[1])>=0&&FileName_List[i].find(argv[1])<=1000){
			cout << FileName_List[i]<< endl;    		
			}
		}
	}
	else
		cout<<"路径错误"<<endl; 
	}
	else
		cout<<"命令错误"<<endl; 
		getchar();
	
} 
}
