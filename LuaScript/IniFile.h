/*****************************************************************
 
	文件名:读取当前目录下CIniFile类文件
	日期:2004-1-18
	作者:chao_jie
	E_Mail:chaojie2003@yahoo.com.cn
 
	功能:系统提供的WriteProfileInt()等函数，写到注册表或
		 系统ini文件里，调用比较麻烦，而且会占用注册表资
		 源，下载了网上的ini类用起来又不太顺手，所以参照
		 写了一个读取当前目录下ini文件的类。程序有详细的
		 注释，欢迎批评指正。

*****************************************************************/

/*//////////////////////////////////////////////////////////////////
使用方法:
1.先把IniFile.h，IniFile.ccp加入Porject，在要使用该类的头文件中加入
	#include "IniFile.h"，及CIniFile IniFile;

2.读取和写入:
	string = IniFile.GetString("section","item","默认");
	int = IniFile.GetInt("section","item",666);

	IniFile.SetString("section","item","设置值");
	IniFile.SetInt("section","item",666);

3.ini文件名及路径在初始化时，用SetFileName()设置

注意事项:ini文件如果太长，读取速度会变慢，可以使用多个ini文件

//////////////////////////////////////////////////////////////////*/
// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__33CAF5C6_7820_43EB_8D84_42CC1856C35C__INCLUDED_)
#define AFX_INIFILE_H__33CAF5C6_7820_43EB_8D84_42CC1856C35C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
public:
	void SetFileName(CString FileName);

	void WriteFileString(CString Section, CString Item, CString Value);
	CString GetFileString(CString Section, CString Item, CString Value);

	CString GetString(CString Section, CString Item, CString Value);
	int GetInt(CString Section, CString Item, int Value);

	void SetString(CString Section, CString Item, CString Value);
	void SetInt(CString Section, CString Item, int Value);

	BOOL WriteIniFile();
	BOOL ReadIniFile();

	CIniFile();
	virtual ~CIniFile();

	//ini file
	CString m_sFileName;
	CStdioFile IniFile;
	BOOL  bFileExist;
	CStringArray FileContainer;

};

#endif // !defined(AFX_INIFILE_H__33CAF5C6_7820_43EB_8D84_42CC1856C35C__INCLUDED_)
