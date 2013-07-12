/*****************************************************************
 
	�ļ���:��ȡ��ǰĿ¼��CIniFile���ļ�
	����:2004-1-18
	����:chao_jie
	E_Mail:chaojie2003@yahoo.com.cn
 
	����:ϵͳ�ṩ��WriteProfileInt()�Ⱥ�����д��ע����
		 ϵͳini�ļ�����ñȽ��鷳�����һ�ռ��ע�����
		 Դ�����������ϵ�ini���������ֲ�̫˳�֣����Բ���
		 д��һ����ȡ��ǰĿ¼��ini�ļ����ࡣ��������ϸ��
		 ע�ͣ���ӭ����ָ����

*****************************************************************/

/*//////////////////////////////////////////////////////////////////
ʹ�÷���:
1.�Ȱ�IniFile.h��IniFile.ccp����Porject����Ҫʹ�ø����ͷ�ļ��м���
	#include "IniFile.h"����CIniFile IniFile;

2.��ȡ��д��:
	string = IniFile.GetString("section","item","Ĭ��");
	int = IniFile.GetInt("section","item",666);

	IniFile.SetString("section","item","����ֵ");
	IniFile.SetInt("section","item",666);

3.ini�ļ�����·���ڳ�ʼ��ʱ����SetFileName()����

ע������:ini�ļ����̫������ȡ�ٶȻ����������ʹ�ö��ini�ļ�

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
