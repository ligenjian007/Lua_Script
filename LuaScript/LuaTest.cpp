#include "stdafx.h"
#include "ScriptPB.pb.h"
#define SERVER_H_
#include ".\VirtualCloudServer\interface.h"
#include "LuaShell.h"
#include "interface.h"
#include "VirtualDriverFrame.pb.h"
#include "ScriptPB.pb.h"

//#define TEST_SERVER

#ifdef TEST_SERVER

CWinApp theApp;

using namespace std;
using namespace VirtualDriverFramePB;
using namespace LuaScriptPB;

void OnLuaMessage(CCHANDLE pSender, IOPCompleteArgs *pIOP,void *&pInBuffer,int &InBufferLen);

typedef struct tagRequestQueue
{
	IOPCompleteArgs * pIOP;
	RequestInfo ReqInfo;
	BYTE * pInBuffer;
	int InBufferLen;
	int nCounter;
} RequestQueue;


vector<RequestQueue> vectRequestQueue;

CRITICAL_SECTION lockRequestQueue;
CCHANDLE hVirtualCloudServer=NULL;
bool bBeginProcess=false;

UINT ProcessRequest(LPVOID lpParam);

DWORD nRecv,nPreProcess,nAsyProcess,nPostProcess;

BOOL _ExitFlag = 0;

LuaClass luaShell;


BOOL WINAPI ConsoleHandler(DWORD msgType)
{
    if (msgType == CTRL_C_EVENT)
    {
        printf("Ctrl-C!\n");
        _ExitFlag = 1;
        return TRUE;
    }
    else if (msgType == CTRL_CLOSE_EVENT)
    {
        printf("Close console window!\n");
        _ExitFlag = 1;
        /* Note: The system gives you very limited time to exit in this condition */
        return TRUE;
    }

    /*
        Other messages:
        CTRL_BREAK_EVENT         Ctrl-Break pressed
        CTRL_LOGOFF_EVENT        User log off
        CTRL_SHUTDOWN_EVENT      System shutdown
    */

    return FALSE;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	
	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: 在此处为应用程序的行为编写代码。
	}


	luaShell.Init();

	nRecv=nPreProcess=nAsyProcess=nPostProcess=0;
	CWinThread*   pThread;
	SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	InitializeCriticalSection(&lockRequestQueue);
	hVirtualCloudServer=CreateVirtualCloudServer();
	if(hVirtualCloudServer==NULL)return -1;

	SetServerAddress(hVirtualCloudServer,"127.0.0.1");
	SetCmdPort(hVirtualCloudServer,12298);
	SetDataPort(hVirtualCloudServer,12299);
	SetUsername(hVirtualCloudServer,"tester");
	SetPassword(hVirtualCloudServer,"123456");
	SetPrePackageCount(hVirtualCloudServer,50);

	if(Connect(hVirtualCloudServer))
	{
		bBeginProcess=true;
		pThread=AfxBeginThread(ProcessRequest, NULL);
		int FuncID=12345;
		int Location=3;
		int Sync=2;
		char DriverName[]="CloudServerLua";
		char DeviceName[]="CloudServerLua";
		unsigned int Object;
		int MajorCmd=1;
		int MinorCmd=0;
		unsigned char pInBuffer[]="ASDFG";
		unsigned int InBufferLen=5;
		unsigned char *pOutBuffer=NULL;
		unsigned int OutBufferLen=0;
		unsigned char *pErrorInfo=NULL;
		unsigned int ErrorInfoLen=0;
		unsigned int ErrorCode=0;
		IOState StateCode=IO_STATE_NONE;
		char *ErrMsg;
		ErrMsg=new char[1000];
		CTime t;
		t=CTime::GetCurrentTime();
		bool bSuccess;
        if(RegServer(hVirtualCloudServer,FuncID, Location, Sync, DriverName, DeviceName, (PIOCOMPEX)OnLuaMessage,NULL, &ErrMsg))
    		printf("%02d%02d%02d: RegServer: %s\n",t.GetHour(),t.GetMinute(),t.GetSecond(),ErrMsg);
		else printf("%02d%02d%02d: RegServer: Error: %s\n",t.GetHour(),t.GetMinute(),t.GetSecond(),ErrMsg);
		delete ErrMsg;
		//SetPrePackageCount(hVirtualCloudServer,20);
        while (!_ExitFlag) 
		{
			printf("\r                                                                               ");
			printf("\r %ld recieved %ld preprocessed %ld asyprocessed %ld postprocessed",nRecv,nPreProcess,nAsyProcess,nPostProcess);
			Sleep(1000);
		}
		bBeginProcess=false;
		WaitForSingleObject(pThread->m_hThread,INFINITE);
		Disconnect(hVirtualCloudServer);
	}
	CloseVirtualCloudServer(hVirtualCloudServer);
	
	return nRetCode;
}

void OnLuaMessage(CCHANDLE pSender, IOPCompleteArgs *pIOP,void *&pInBuffer,int &InBufferLen)
{
	VirtualDriverFrame tempFrame;
	if(pIOP==NULL)return;
	if(!tempFrame.ParseFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen))return;
	InBufferLen=0;
	pInBuffer=NULL;
	if (tempFrame.majorcmd()==201)
	{
		LScriptRequest lua_req;
		lua_req.ParseFromArray(tempFrame.body().c_str(),tempFrame.body().size());
		string script=lua_req.requests(0).content();

		LScriptResponse rsp;
		LScriptResponse_result *result=rsp.add_responses();
		result->set_content(luaShell.executeScript(script));
		result->set_scriptno(lua_req.requests(0).scriptno());
		InBufferLen=rsp.ByteSize();
		pInBuffer=new BYTE[InBufferLen];
		rsp.SerializeWithCachedSizesToArray((unsigned char*)(pInBuffer));
	}
}


UINT ProcessRequest(LPVOID lpParam)
{
	while(bBeginProcess)
	{
		if(hVirtualCloudServer==NULL)
		{
			Sleep(2000);
			continue;
		}
		EnterCriticalSection(&lockRequestQueue);
		for(vector<RequestQueue>::iterator iter=vectRequestQueue.begin();iter!=vectRequestQueue.end();)
		{
			if(iter->nCounter<=0)
			{
				char *Request;
				char *Response;
				int Length=iter->InBufferLen;
				Request=new char[Length+1];
				Response=new char[Length+1];
				ZeroMemory(Request,Length+1);
				ZeroMemory(Response,Length+1);
				BYTE * pBuffer=NULL;
				int nBufferLen;	
				pBuffer=new BYTE[iter->InBufferLen];
				for (int i=0;i<iter->InBufferLen;i++)
				{
					pBuffer[i]=iter->pInBuffer[i]+1;
				}
				nBufferLen=iter->InBufferLen;
				memcpy(Request,iter->pInBuffer,Length);
				memcpy(Response,pBuffer,Length);
				CTime t;
				t=CTime::GetCurrentTime();
				//printf("%02d%02d%02d: PostIO  Request:%s AsyProcess:%s\n",t.GetHour(),t.GetMinute(),t.GetSecond(),Request,Response);
				delete Request;
				Request=NULL;
				delete Response;
				Response=NULL;
				SetTriggerEvent(hVirtualCloudServer,iter->ReqInfo.ReqDev.nFuncID,iter->ReqInfo.ReqDev.nLocation,iter->ReqInfo.ReqDev.nSync,iter->ReqInfo.ReqDev.szDriverName,iter->ReqInfo.ReqDev.szDeviceName,iter->ReqInfo.nQueueHandle,iter->ReqInfo.nRequestID,(void*)pBuffer,nBufferLen);
				if(iter->pInBuffer!=NULL)
				{
					delete iter->pInBuffer;
					iter->pInBuffer=NULL;
				}
				iter=vectRequestQueue.erase(iter);
				if(pBuffer!=NULL)
				{
					delete pBuffer;
					pBuffer=NULL;
				}
				nAsyProcess++;
				break;
			}
			else
			{
				iter->nCounter--;
				iter++;
			}
		}
		LeaveCriticalSection(&lockRequestQueue);
		Sleep(1000);
	}
	return 0;
}

#else

int main()
{
	LuaClass *shell=new LuaClass();
	shell->Init();
	shell->executeMain("correlation.lua");
	return 0;
}

#endif
