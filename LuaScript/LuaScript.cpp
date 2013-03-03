// LuaScript.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "interface.h"
#include <vector>
#include "HSComm.pb.h"


extern "C"  
{  
    #include "lua.h"  
    #include "lauxlib.h"  
    #include "lualib.h"  
}  

using namespace std;
using namespace HSCommPB;

CCHANDLE hVirtualCloudClient=NULL;
DWORD nSend,nRecv,nSucc,nFail;

void CallBack_Entrust(CCHANDLE pSender, IOPCompleteArgs *pIOP);
void CallBack_Query(CCHANDLE pSender, IOPCompleteArgs *pIOP);
void CallBack_Query_Order(CCHANDLE pSender, IOPCompleteArgs *pIOP);


static int Connection(lua_State *L)
{
	nSend=nRecv=nSucc=nFail=0;
	hVirtualCloudClient=CreateVirtualCloudClient();
	if(hVirtualCloudClient==NULL)return -1;
	SetServerAddress(hVirtualCloudClient,"10.1.105.113");
	SetCmdPort(hVirtualCloudClient,12298);
	SetDataPort(hVirtualCloudClient,12299);
	SetUsername(hVirtualCloudClient,"tester");
	SetPassword(hVirtualCloudClient,"123456");
	if (Connect(hVirtualCloudClient))
	{
		lua_pushboolean(L,true);
		return 1;
	}
	else
	{
		lua_pushboolean(L,false);
		return 1;
	}
}

static int Entrust(lua_State *L)
{
	/*set arguements of postIO*/
	int FuncID=13250;
	int Location=3;
	int Sync=2;
	char DriverName[]="CloudServerB";
	char DeviceName[]="CloudServerB";
	unsigned int Object=0;
	int MajorCmd=1;
	int MinorCmd=0;
	unsigned char *pInBuffer;
	unsigned int InBufferLen=0;
	unsigned char *pOutBuffer=NULL;
	unsigned int OutBufferLen=0;
	unsigned char *pErrorInfo=NULL;
	unsigned int ErrorInfoLen=0;
	unsigned int ErrorCode=0;
	IOState StateCode=IO_STATE_NONE;
	DWORD nHandle=0;
	char outstr[1000];
	ZeroMemory(outstr,1000);

	/*fill in the request data */
	entrustStockRequest *data=new entrustStockRequest();
	entrustStockRequest_call *req=data->add_requests();
	req->set_localid(0);
	req->set_branchno("");
	req->set_fundaccount("test2011");
	req->set_password("123456");
	req->set_exchangetype(enums_exchangeType_shanghai);
	req->set_stockaccount("");
	req->set_stockcode("601988");
	req->set_entrustamount(100);
	req->set_entrustprice(27600);
	req->set_entrustbs(enums_entrustBS_buy);

	req->set_fundaccount(lua_tostring(L,1));
	req->set_password(lua_tostring(L,2));
	req->set_stockcode(lua_tostring(L,3));
	req->set_entrustamount(lua_tointeger(L,4));
	req->set_entrustprice(lua_tointeger(L,5));

	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=L;
	/*post the request and wait for callback */
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_Entrust, usrdata ,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(L,0);
}

void CallBack_Entrust(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{
	entrustStockResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);
	entrustStockResponse_result result=response.responses(0);
	lua_State *L=(lua_State*)(pIOP->UserData);
	lua_pushboolean(L,true);
	lua_pushinteger(L,result.localid());
	lua_pushstring(L,result.entrustno().c_str());
//	delete pIOP;
	lua_resume(L,3);
}



static int Query(lua_State *L)
{
	int FuncID=13250;
	int Location=3;
	int Sync=2;
	char DriverName[]="CloudServerB";
	char DeviceName[]="CloudServerB";
	unsigned int Object=0;
	int MajorCmd=2;
	int MinorCmd=0;
	unsigned char *pInBuffer;
	unsigned int InBufferLen=0;
	unsigned char *pOutBuffer=NULL;
	unsigned int OutBufferLen=0;
	unsigned char *pErrorInfo=NULL;
	unsigned int ErrorInfoLen=0;
	unsigned int ErrorCode=0;
	IOState StateCode=IO_STATE_NONE;
	DWORD nHandle=0;
	char outstr[1000];
	ZeroMemory(outstr,1000);

	/*fill in the request data */
	queryEntrustRequest  *data=new queryEntrustRequest ();
	queryEntrustRequest_call *req=data->add_requests();
	req->set_branchno("");
	req->set_fundaccount("test2011");
	req->set_password("123456");
	req->set_entrustno("10");
	req->set_queryonlycancelable(true);
	req->set_requestnumber(1);
	req->set_lastpositionstring("");
	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=L;

	/*post the request and wait for callback */
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_Query, usrdata,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(L,0);
}

void CallBack_Query(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{
	queryEntrustResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);
	lua_State *L=(lua_State*)(pIOP->UserData);
	lua_pushboolean(L,true);
	lua_resume(L,1);
}

static int Query_Order(lua_State *L)
{
	int FuncID=13250;
	int Location=3;
	int Sync=2;
	char DriverName[]="CloudServerB";
	char DeviceName[]="CloudServerB";
	unsigned int Object=0;
	int MajorCmd=3;
	int MinorCmd=0;
	unsigned char *pInBuffer;
	unsigned int InBufferLen=0;
	unsigned char *pOutBuffer=NULL;
	unsigned int OutBufferLen=0;
	unsigned char *pErrorInfo=NULL;
	unsigned int ErrorInfoLen=0;
	unsigned int ErrorCode=0;
	IOState StateCode=IO_STATE_NONE;
	DWORD nHandle=0;
	char outstr[1000];
	ZeroMemory(outstr,1000);

	queryOrdersRequest *data=new queryOrdersRequest();
	queryOrdersRequest_call *req=data->add_requests();
	req->set_date(20120826);
	req->set_password("123456");
	req->set_username("test2011");

	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=L;

	/*post the request and wait for callback */
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_Query_Order, usrdata,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(L,0);
}

void CallBack_Query_Order(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{
	queryOrdersResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);
	lua_State *L=(lua_State*)(pIOP->UserData);
	google::protobuf::RepeatedPtrField<::HSCommPB::queryOrdersResponse_result> result=response.responses();
	google::protobuf::RepeatedPtrField<::HSCommPB::queryOrdersResponse_result>::iterator iter;
	for (iter=result.begin();iter!=result.end();iter++)
	{
		

		//cout<<iter->returndate()<<endl;
	}
	/*queryOrdersResponse_result_query result_query=result.queries(0);*/
	lua_resume(L,0);
}




static int Lua_Sleep(lua_State *L)
{
	int seconds;
	seconds=lua_tointeger(L,1);
	Sleep(seconds);
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int iError;

	lua_State *L;
	L = lua_open();
    luaopen_base(L);  
    luaopen_table(L);  
    luaL_openlibs(L);  
    luaopen_string(L);  
    luaopen_math(L);  
	lua_register(L, "connect", Connection);
	lua_register(L, "entrust", Entrust);
	lua_register(L, "query", Query);
	lua_register(L, "checkall",Query_Order);
	lua_register(L,"sleep",Lua_Sleep);
  
    iError = luaL_loadfile(L, "lib.lua");  
	if (iError)
	{
		cout << "Load library script FAILED!" << lua_tostring(L, -1)<< endl;  
		lua_close(L);
		return 0;
	}
	iError = lua_pcall(L, 0, 0, 0);  
	if (iError)  
    {  
        cout << "Loading library failed"<< lua_tostring(L, -1)<< iError<< endl;  
        lua_close(L);  
        return 0;  
    }  
	iError = luaL_loadfile(L, "test.lua");  
	if (iError)
	{
		cout << "Load test script FAILED!" << lua_tostring(L, -1)<< endl;  
		lua_close(L);
		return 0;
	}
	iError = lua_pcall(L, 0, 0, 0);  
	if (iError)  
    {  
        cout << "excuting script failed"<< lua_tostring(L, -1)<< iError<< endl;  
        lua_close(L);  
        return 0;  
    } 

	lua_pop(L,2);
	lua_close(L);
	return 0;
}