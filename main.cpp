#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <io.h>
#include <string>
#include <direct.h>
#include <Windows.h>


using namespace std;


void getFiles( string path, vector<string>& files )  
{  
	//文件句柄;
	long   hFile   =   0;  
	//文件信息;  
	struct _finddata_t fileinfo;  
	string p;  
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			//如果是目录,迭代之;  
			//如果不是,加入列表;  
			if((fileinfo.attrib &  _A_SUBDIR))  
			{  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
					getFiles( p.assign(path).append("\\").append(fileinfo.name), files );  
			}  
			else  
			{  
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
			}  
		}while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile);  
	}  
} 
//creat a dir 
bool creatDir(const string & strDir){
	unique_ptr<char []> tmp(new char [256]);
	for(int i=0;i!=strDir.size();++i)
		tmp[i]=strDir[i];
	tmp[strDir.size()+1]='\0';
	char * strDirPath=tmp.get();

	if (strlen(strDirPath)>MAX_PATH)
	{
		return false;
	}
	int ipathLength=strlen(strDirPath);
	int ileaveLength=0;
	int iCreatedLength=0;
	char szPathTemp[MAX_PATH]={0};
	for (int i=0;(NULL!=strchr(strDirPath+iCreatedLength,'\\'));i++)
	{
		ileaveLength=strlen(strchr(strDirPath+iCreatedLength,'\\'))-1;
		iCreatedLength=ipathLength-ileaveLength;
		strncpy_s(szPathTemp,strDirPath,iCreatedLength);
		_mkdir(szPathTemp);
	}
	if (iCreatedLength<ipathLength)
	{
		_mkdir(strDirPath);
	}
	
	return true;
}

int main(void){

	//get the file dir ,save in @fieDir;
	vector<string> fileDir;
	string rootDir="C:\\Users\\weijian.zou\\Desktop\\leige\\a";
	getFiles(rootDir,fileDir);


	for(auto iter=fileDir.begin();iter!=fileDir.end();++iter){
		
		cout<<"the fileDir is :"<<*iter<<endl;
		//remove the rootDir ,get the rest dir name 
		string rmRootDirStr(iter->substr(rootDir.size()));
		cout<<"[rm the rootdir is :]"<<rmRootDirStr<<endl;
		//remove file name 
		string rmFileNameStr(rmRootDirStr.substr(0,rmRootDirStr.find_last_of("\\")));
		cout<<"[rm the filename is :]"<<rmFileNameStr<<endl;
		string restFileNameStr=(rmRootDirStr.substr(rmRootDirStr.find_last_of("\\")));
		cout<<"[the rest file name is :]"<<restFileNameStr<<endl;
		cout<<"*************************"<<endl;
		//add a suffix with the root dir and creat the new dir 
		string dirSuffix("_2");
		string newrootDir=rootDir+dirSuffix+rmFileNameStr;
		string newfileDir=rootDir+dirSuffix+rmFileNameStr+restFileNameStr;
		//creat the new root dir 
		creatDir(newrootDir);
		//do some thing to deal the pic here!
		//
		//save the pic 

		cout<<"[the new file dir is :]"<<newfileDir<<endl;
		cout<<"*************************"<<endl<<endl<<endl;
		
	}


	system("pause");
	return 0;
}
