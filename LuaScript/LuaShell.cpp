#include "stdafx.h"
#include "LuaShell.h"
#include <iostream>
#include <windows.h>
#include <fstream>

//#define USER_DATA_ON
#define HISTORY_PAPA_ON

using namespace std;


void* LuaClass::svrAddr;
void* LuaClass::hvcClient;
void* LuaClass::hstrClient;
char LuaClass::result_text[2048];

LuaClass::LuaClass()
{
	if (this->svrAddr==NULL)
		this->svrAddr=(void*)malloc(sizeof(char));
	if (this->hvcClient==NULL)
		this->hvcClient=(void*)malloc(sizeof(char));
	if (this->hstrClient==NULL)
		this->hstrClient=(void*)malloc(sizeof(char));
	/*
	this->usrName=(void*)malloc(sizeof(char));
	*/
//	this->Init();
}


int	LuaClass::Init(string serverAddress, int cmdPort, int dataPort)
{
	CCHANDLE hVirtualCloudClient;
	CCHANDLE hHistoryCloudClient;

	this->serverAddress=serverAddress;
	this->cmdPort	=cmdPort;
	this->dataPort	=dataPort;
	
	/* Init the lua state part of the Simulator*/
	pMainShell		=lua_open();
	luaopen_base(pMainShell);  
    luaopen_table(pMainShell);  
    luaL_openlibs(pMainShell);  
    luaopen_string(pMainShell);  
    luaopen_math(pMainShell); 
	luaopen_pluto(pMainShell);

	for (int i=0;i<MAX_THREAD_NUM;i++)	pCoroutines[i]=NULL;

	lua_register(pMainShell,"connect", shell_connect);// connect(severaddress,username,cmdport,dataport)
	lua_register(pMainShell,"entrust", shell_entrust);//entrust(account,password,stockcode,entrustamount,entrustprice)
	lua_register(pMainShell,"query_entrust",shell_query_entrust);//query_entrust(account,password,entrustno,queryOnlyCancelable,requestNumber,lastPositionString)
	lua_register(pMainShell,"query_orders",shell_query_orders);
	lua_register(pMainShell,"query_capital",shell_query_capital);
	lua_register(pMainShell,"history_data",LuaF_history_data);
	lua_register(pMainShell,"sleep",shell_sleep);
	
	nSend=nRecv=nSucc=nFail=0;

	hVirtualCloudClient=CreateVirtualCloudServer();
	hHistoryCloudClient=CreateVirtualCloudServer();

	box_userdata(pMainShell,"hvcClient",hVirtualCloudClient);
	box_userdata(pMainShell,"hstrClient",hHistoryCloudClient);
	
	return 0;
}

void LuaClass::box_userdata(lua_State *pState, char slot_name[20],void* & userdata)
{
	void *pSlot;
	if (strcmp(slot_name,"hvcClient")==0)
		pSlot=(void*)hvcClient;
	else if (strcmp(slot_name,"hstrClient")==0)
		pSlot=(void*)hstrClient;
	
	lua_pushlightuserdata(pState,pSlot);
	lua_pushlightuserdata(pState,userdata);
	lua_settable(pState, LUA_REGISTRYINDEX);
}

void LuaClass::unbox_userdata(lua_State *pState,char slot_name[20],void* & userdata)
{
	void *pSlot;
	if (strcmp(slot_name,"hvcClient")==0)
		pSlot=(void*)hvcClient;
	else if (strcmp(slot_name,"hstrClient")==0)
		pSlot=(void*)hstrClient;

	lua_pushlightuserdata(pState, pSlot);
	lua_gettable(pState, LUA_REGISTRYINDEX);
	userdata=lua_touserdata(pState,-1);
}


int LuaClass::executeMain(string filename)
{

	int iError;
	iError = luaL_loadfile(pMainShell, filename.c_str());  
	if (iError)
	{
		sprintf(result_text,"Load test script FAILED! %s",lua_tostring(pMainShell, -1));  
		lua_close(pMainShell);
		return 0;
	}
	iError = lua_pcall(pMainShell, 0, 0, 0);
	if (iError)
	{
		sprintf(result_text,"Load test script FAILED! %s",lua_tostring(pMainShell, -1));  
		return 0;
	}
	return 1;
}


string LuaClass::executeScript(string script)
{

	int iError;
	string pre_code;
	FILE *out;
	ofstream code("full.code");

	pre_code.append("result_out=io.open(\"result_text_file.res\",\"a\")\n");
	pre_code.append(script);
	code<<pre_code;
	
	iError=luaL_loadfile(pMainShell,"full.code");
	if (iError)
	{
		sprintf(result_text,"Load test script FAILED! %s",lua_tostring(pMainShell, -1));  
		lua_close(pMainShell);
		return result_text;
	}
	iError = lua_pcall(pMainShell, 0, 0, 0);
	if (iError)
	{
		sprintf(result_text,"Load test script FAILED! %s",lua_tostring(pMainShell, -1));  
		return result_text;
	}
	out=fopen("result_text_file.res","r");
	char buf[200];
	while (fscanf(out,"%s",buf)!=0)
	{
		strcat(result_text,buf);
		strcat(result_text,"\n");
	}
	return result_text;
}

int LuaClass::shell_sleep(lua_State *pState)
{
	int seconds;
	seconds=lua_tointeger(pState,1);
	Sleep(seconds);
	return 0;
}

int LuaClass::shell_connect(lua_State *pState)
{

	CCHANDLE hVirtualCloudClient,hHistoryCloudClient;
	DWORD nSend,nRecv,nSucc,nFail;

	nSend=nRecv=nSucc=nFail=0;

	unbox_userdata(pState,"hvcClient",hVirtualCloudClient);
	unbox_userdata(pState,"hstrClient",hHistoryCloudClient);

	if(hVirtualCloudClient==NULL)	return -1;
	if (hHistoryCloudClient==NULL) return -1;
	SetServerAddress(hVirtualCloudClient,"127.0.0.1");
	SetCmdPort(hVirtualCloudClient,12298);
	SetDataPort(hVirtualCloudClient,12299);
	SetUsername(hVirtualCloudClient,"tester");
	SetPassword(hVirtualCloudClient,"123456");

	SetServerAddress(hHistoryCloudClient,"127.0.0.1");
	SetCmdPort(hHistoryCloudClient,12298);
	SetDataPort(hHistoryCloudClient,12299);
	SetUsername(hHistoryCloudClient,"tester");
	SetPassword(hHistoryCloudClient,"123456");

	if (Connect(hVirtualCloudClient))
	{
		lua_pushboolean(pState,true);
	}
	else
	{
		lua_pushboolean(pState,false);
	}
	if (Connect(hHistoryCloudClient))
	{
		lua_pushboolean(pState,true);
	}
	else
	{
		lua_pushboolean(pState,false);
	}
	return 2;
}

/*
	the function entrust is called with the function entrust.
	entrust(account,password,stockcode,entrustamount,entrustprice)
	entrust(string,string,string,int,int)
*/

int LuaClass::shell_entrust(lua_State *pState)
{

	CCHANDLE hVirtualCloudClient;
	DWORD nSend,nRecv,nSucc,nFail;

	nSend=nRecv=nSucc=nFail=0;
	
	unbox_userdata(pState,"hvcClient",hVirtualCloudClient);

	//set arguements of postIO
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

	//fill in the request data 
	entrustStockRequest *data=new entrustStockRequest();
	entrustStockRequest_call *req=data->add_requests();

#ifdef USER_DATA_ON
	req->set_fundaccount(lua_tostring(pState,1));
	req->set_password(lua_tostring(pState,2));
	req->set_stockcode(lua_tostring(pState,3));
	req->set_entrustamount(lua_tointeger(pState,4));
	req->set_entrustprice(lua_tointeger(pState,5));

#else 
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
#endif 

	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=pState;
	//post the request and wait for callback 
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_Entrust, usrdata ,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(pState,0);
}

void LuaClass::CallBack_Entrust(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{
	entrustStockResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);

	entrustStockResponse_result result=response.responses(0);
	lua_State *L=(lua_State*)(pIOP->UserData);

	lua_pushboolean(L,true);

	lua_newtable(L);
	lua_pushstring(L,"local_id");
	lua_pushinteger(L,result.localid());
	lua_settable(L,-3);
	lua_pushstring(L,"entrust_no");
	lua_pushstring(L,result.entrustno().c_str());
	lua_settable(L,-3);

	/*set the return value as a lua table
	whith the format:
		{local_id=XXX, entrust_no=XXX}
	*/

//	free(pIOP->pOutBuffer);
//	free(pIOP->pErrorInfo);
	lua_resume(L,2);
}


int LuaClass::shell_query_entrust(lua_State *pState)
{

	CCHANDLE hVirtualCloudClient;
	DWORD nSend,nRecv,nSucc,nFail;

	nSend=nRecv=nSucc=nFail=0;

	
	lua_pushlightuserdata(pState, (void*)hvcClient);
	lua_gettable(pState, LUA_REGISTRYINDEX);
	hVirtualCloudClient=(void*)lua_touserdata(pState,-1);

	/*set arguements of postIO*/
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
	queryEntrustRequest *data=new queryEntrustRequest;
	queryEntrustRequest_call *req=data->add_requests();
	req->set_branchno("");
	req->set_entrustno("10");
	req->set_fundaccount("test2011");
	req->set_lastpositionstring("");
	req->set_password("123456");
	req->set_queryonlycancelable(true);
	req->set_requestnumber(1);

	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=pState;
	/*post the request and wait for callback */
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_Query_entrust, usrdata ,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(pState,0);
}

void LuaClass::CallBack_Query_entrust(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{

	queryEntrustResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);
	queryEntrustResponse_result result=response.responses(0);
	queryEntrustResponse_result_entrust entrust=result.entrusts(0);
	lua_State *L=(lua_State*)(pIOP->UserData);
	lua_pushboolean(L,true);
	lua_newtable(L);
	lua_pushstring(L,"entrust_no");
	lua_pushstring(L,entrust.entrustno().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"stock_code");
	lua_pushstring(L,entrust.stockcode().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"stock_name");
	lua_pushstring(L,entrust.stockname().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"entrust_amount");
	lua_pushinteger(L,entrust.entrustamount());
	lua_settable(L,-3);
	lua_pushstring(L,"entrust_price");
	lua_pushinteger(L,entrust.entrustprice());
	lua_settable(L,-3);
//	lua_pushinteger(L,entrust.businessamount());
//	lua_pushinteger(L,entrust.businessPrice());
	lua_pushstring(L,"cancel_vol");
	lua_pushinteger(L,entrust.cancelvol());
	lua_settable(L,-3);
	lua_pushstring(L,"internal_sid");
	lua_pushinteger(L,entrust.internalsid());
	lua_settable(L,-3);
//	lua_pushinteger(L,entrust.FEEandTAX());
	lua_pushstring(L,"tradedone");
	lua_pushinteger(L,entrust.tradedone());
	lua_settable(L,-3);
	lua_pushstring(L,"success");
	lua_pushinteger(L,entrust.success());
	lua_settable(L,-3);
	lua_resume(L,2);
}


int LuaClass::shell_query_orders(lua_State *pState)
{

	CCHANDLE hVirtualCloudClient;
	DWORD nSend,nRecv,nSucc,nFail;

	nSend=nRecv=nSucc=nFail=0;

	
	lua_pushlightuserdata(pState, (void*)hvcClient);
	lua_gettable(pState, LUA_REGISTRYINDEX);
	hVirtualCloudClient=(void*)lua_touserdata(pState,-1);

	/*set arguements of postIO*/
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

	/*fill in the request data */
	queryOrdersRequest *data=new queryOrdersRequest;
	queryOrdersRequest_call *req=data->add_requests();
	req->set_date(20120826);
	req->set_username("test2011");
	req->set_password("123456");

	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=pState;
	/*post the request and wait for callback */
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_Query_orders, usrdata ,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(pState,0);
}

void LuaClass::CallBack_Query_orders(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{

	queryOrdersResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);
	queryOrdersResponse_result result=response.responses(0);
	queryOrdersResponse_result_query query=result.queries(0);
	lua_State *L=(lua_State*)(pIOP->UserData);
	lua_pushboolean(L,true);
	lua_newtable(L);
	lua_pushstring(L,"return_date");
	lua_pushinteger(L,query.returndate());
	lua_settable(L,-3);
	lua_pushstring(L,"secu_name");
	lua_pushstring(L,query.secuname().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"code");
	lua_pushstring(L,query.code().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"direction");
	lua_pushstring(L,query.direction().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"order_vol");
	lua_pushinteger(L,query.ordervol());
	lua_settable(L,-3);
	lua_pushstring(L,"order_price");
	lua_pushinteger(L,query.orderprice());
	lua_settable(L,-3);
	lua_pushstring(L,"average_price");
	lua_pushinteger(L,query.averageprice());
	lua_settable(L,-3);
	lua_pushstring(L,"trade_vol");
	lua_pushinteger(L,query.tradevol());
	lua_settable(L,-3);
	lua_pushstring(L,"cancel_vol");
	lua_pushinteger(L,query.cancelvol());
	lua_settable(L,-3);
	lua_pushstring(L,"flag");
	lua_pushstring(L,query.flag().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"add_date_time");
	lua_pushstring(L,query.adddatetime().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"acid");
	lua_pushinteger(L,query.acid());
	lua_settable(L,-3);
	lua_pushstring(L,"oid");
	lua_pushinteger(L,query.oid());
	lua_settable(L,-3);
	lua_resume(L,2);
}


int LuaClass::shell_query_capital(lua_State *pState)
{
	CCHANDLE hVirtualCloudClient;
	DWORD nSend,nRecv,nSucc,nFail;

	nSend=nRecv=nSucc=nFail=0;

	
	lua_pushlightuserdata(pState, (void*)hvcClient);
	lua_gettable(pState, LUA_REGISTRYINDEX);
	hVirtualCloudClient=(void*)lua_touserdata(pState,-1);

	/*set arguements of postIO*/
	int FuncID=13250;
	int Location=3;
	int Sync=2;
	char DriverName[]="CloudServerB";
	char DeviceName[]="CloudServerB";
	unsigned int Object=0;
	int MajorCmd=4;
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
	queryCapitalRequest *data=new queryCapitalRequest;
	queryCapitalRequest_call *req=data->add_requests();
	req->set_accountid(-1);
	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=pState;
	/*post the request and wait for callback */
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_Query_capital, usrdata ,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(pState,0);
}

void LuaClass::CallBack_Query_capital(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{
	queryCapitalResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);
	queryCapitalResponse_result result=response.responses(0);
	queryCapitalResponse_result_capital capital=result.capitals(0);
	lua_State *L=(lua_State*)(pIOP->UserData);
	lua_pushboolean(L,true);
	lua_newtable(L);
	lua_pushstring(L,"id");
	lua_pushinteger(L,capital.id());
	lua_settable(L,-3);
	lua_pushstring(L,"exchange_id");
	lua_pushinteger(L,capital.exchangeid());
	lua_settable(L,-3);
	lua_pushstring(L,"current_time");
	lua_pushinteger(L,capital.currencytype());
	lua_settable(L,-3);
	lua_pushstring(L,"amount");
	lua_pushinteger(L,capital.amounts());
	lua_settable(L,-3);
	lua_pushstring(L,"free_amount");
	lua_pushinteger(L,capital.freeamounts());
	lua_settable(L,-3);
	lua_pushstring(L,"frozen_amount");
	lua_pushinteger(L,capital.frozenamount());
	lua_settable(L,-3);
	lua_resume(L,2);
}

int LuaClass::LuaF_history_data_test(lua_State *pState)
{

	CCHANDLE hVirtualCloudClient;
	DWORD nSend,nRecv,nSucc,nFail;

	nSend=nRecv=nSucc=nFail=0;

	
	lua_pushlightuserdata(pState, (void*)hstrClient);
	lua_gettable(pState, LUA_REGISTRYINDEX);
	hVirtualCloudClient=(void*)lua_touserdata(pState,-1);

	/*set arguements of postIO*/
	int FuncID=102;
	int Location=3;
	int Sync=2;
	char DriverName[]="";
	char DeviceName[]="";
	unsigned int Object=0;
	int MajorCmd=115;
	int MinorCmd=1;
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
	HistoryDataRequest *data=new HistoryDataRequest;
	data->set_timestamp(0);
	data->set_handle(0);
	HistoryDataRequest_HistoryDataInfo *HistoryDataInfo=data->add_datainfo();
	HistoryDataInfo->set_contract("IF1302");
	HistoryDataInfo->set_startdate(20130124);
	HistoryDataInfo->set_starttime(134000);
	HistoryDataInfo->set_enddate(20130124);
	HistoryDataInfo->set_endtime(143000);

	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=pState;
	/*post the request and wait for callback */
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_history_data_test, usrdata ,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(pState,0);
}

void LuaClass::CallBack_history_data_test(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{
	HistoryDataResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);
	HistoryDataResponse_MarketDataSeries MarketDataSeries=response.dataseries(0);
	CThostFtdcDepthMarketDataFieldStruct data=MarketDataSeries.data(0);
	
	lua_State *L=(lua_State*)(pIOP->UserData);
	lua_pushboolean(L,true);
	lua_newtable(L);
	lua_pushstring(L,"open_price");
	lua_pushnumber(L,data.openprice());
	lua_settable(L,-3);
	lua_pushstring(L,"askprice1");
	lua_pushnumber(L,data.askprice1());
	lua_settable(L,-3);
	lua_resume(L,2);
}


int LuaClass::LuaF_history_data(lua_State *pState)
{

	CCHANDLE hVirtualCloudClient;
	DWORD nSend,nRecv,nSucc,nFail;

	nSend=nRecv=nSucc=nFail=0;

	
	lua_pushlightuserdata(pState, (void*)hstrClient);
	lua_gettable(pState, LUA_REGISTRYINDEX);
	hVirtualCloudClient=(void*)lua_touserdata(pState,-1);

	//set arguements of postIO
	int FuncID=102;
	int Location=3;
	int Sync=2;
	char DriverName[]="";
	char DeviceName[]="";
	unsigned int Object=0;
	int MajorCmd=115;
	int MinorCmd=1;
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

	//fill in the request data 
	HistoryDataRequest *data=new HistoryDataRequest;
	data->set_timestamp(0);
	data->set_handle(0);
	HistoryDataRequest_HistoryDataInfo *HistoryDataInfo=data->add_datainfo();

#ifdef HISTORY_PAPA_ON
	HistoryDataInfo->set_contract(lua_tostring(pState,1));
	HistoryDataInfo->set_startdate(lua_tointeger(pState,2));
	HistoryDataInfo->set_starttime(lua_tointeger(pState,3));
	HistoryDataInfo->set_enddate(lua_tointeger(pState,4));
	HistoryDataInfo->set_endtime(lua_tointeger(pState,5));

#else
	HistoryDataInfo->set_contract("IF1302");
	HistoryDataInfo->set_startdate(20130124);
	HistoryDataInfo->set_starttime(134000);
	HistoryDataInfo->set_enddate(20130124);
	HistoryDataInfo->set_endtime(143000);
#endif
	InBufferLen=data->ByteSize();
	pInBuffer=(unsigned char*)malloc(data->ByteSize());
	data->SerializeWithCachedSizesToArray(pInBuffer);

	lua_State *usrdata=pState;
	//post the request and wait for callback 
	CTime t;
	t=CTime::GetCurrentTime();
	if(!PostIO(hVirtualCloudClient, FuncID, Location, Sync, DriverName, DeviceName, Object, MajorCmd, MinorCmd, pInBuffer, InBufferLen, (PIOCOMP)CallBack_history_data_test, usrdata ,300000))
	{
		printf("%02d%02d%02d: PostIO  Request:%s Error\n",t.GetHour(),t.GetMinute(),t.GetSecond(),pInBuffer);
	}
//	delete data;
	return lua_yield(pState,0);
}

void LuaClass::CallBack_history_data(CCHANDLE pSender, IOPCompleteArgs *pIOP)
{
	HistoryDataResponse response;
	response.ParsePartialFromArray(pIOP->pOutBuffer,pIOP->OutBufferLen);
	HistoryDataResponse_MarketDataSeries MarketDataSeries=response.dataseries(0);
	CThostFtdcDepthMarketDataFieldStruct data=MarketDataSeries.data(0);
	
	lua_State *L=(lua_State*)(pIOP->UserData);
	lua_pushboolean(L,true);
	lua_newtable(L);
	lua_pushstring(L,"tradingday");
	lua_pushstring(L,data.tradingday().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"instrumentid");
	lua_pushstring(L,data.instrumentid().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"exchangeid");
	lua_pushstring(L,data.exchangeid().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"exchangeinstid");
	lua_pushstring(L,data.exchangeinstid().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"lastprice");
	lua_pushnumber(L,data.lastprice());
	lua_settable(L,-3);
	lua_pushstring(L,"presettlementprice");
	lua_pushnumber(L,data.presettlementprice());
	lua_settable(L,-3);
	lua_pushstring(L,"precloseprice");
	lua_pushnumber(L,data.precloseprice());
	lua_settable(L,-3);
	lua_pushstring(L,"preopeninterest");
	lua_pushnumber(L,data.preopeninterest());
	lua_settable(L,-3);
	lua_pushstring(L,"openprice");
	lua_pushnumber(L,data.openprice());
	lua_settable(L,-3);
	lua_pushstring(L,"highestprice");
	lua_pushnumber(L,data.highestprice());
	lua_settable(L,-3);
	lua_pushstring(L,"lowestprice");
	lua_pushnumber(L,data.lowestprice());
	lua_settable(L,-3);
	lua_pushstring(L,"volume");
	lua_pushinteger(L,data.volume());
	lua_settable(L,-3);
	lua_pushstring(L,"turnover");
	lua_pushnumber(L,data.turnover());
	lua_settable(L,-3);
	lua_pushstring(L,"openinterest");
	lua_pushnumber(L,data.openinterest());
	lua_settable(L,-3);
	lua_pushstring(L,"closeprice");
	lua_pushnumber(L,data.closeprice());
	lua_settable(L,-3);
	lua_pushstring(L,"settlementprice");
	lua_pushnumber(L,data.settlementprice());
	lua_settable(L,-3);
	lua_pushstring(L,"upperlimitprice");
	lua_pushnumber(L,data.upperlimitprice());
	lua_settable(L,-3);
	lua_pushstring(L,"lowerlimitprice");
	lua_pushnumber(L,data.lowerlimitprice());
	lua_settable(L,-3);
	lua_pushstring(L,"predelta");
	lua_pushnumber(L,data.predelta());
	lua_settable(L,-3);
	lua_pushstring(L,"currdelta");
	lua_pushnumber(L,data.currdelta());
	lua_settable(L,-3);
	lua_pushstring(L,"updatetime");
	lua_pushstring(L,data.updatetime().c_str());
	lua_settable(L,-3);
	lua_pushstring(L,"updatemillisec");
	lua_pushnumber(L,data.updatemillisec());
	lua_settable(L,-3);
	lua_pushstring(L,"bidprice1");
	lua_pushnumber(L,data.bidprice1());
	lua_settable(L,-3);
	lua_pushstring(L,"bidprice2");
	lua_pushnumber(L,data.bidprice2());
	lua_settable(L,-3);
	lua_pushstring(L,"bidprice3");
	lua_pushnumber(L,data.bidprice3());
	lua_settable(L,-3);
	lua_pushstring(L,"bidprice4");
	lua_pushnumber(L,data.bidprice4());
	lua_settable(L,-3);
	lua_pushstring(L,"bidprice5");
	lua_pushnumber(L,data.bidprice5());
	lua_settable(L,-3);
	lua_pushstring(L,"askprice1");
	lua_pushnumber(L,data.askprice1());
	lua_settable(L,-3);
	lua_pushstring(L,"askprice2");
	lua_pushnumber(L,data.askprice2());
	lua_settable(L,-3);
	lua_pushstring(L,"askprice3");
	lua_pushnumber(L,data.askprice3());
	lua_settable(L,-3);
	lua_pushstring(L,"askprice4");
	lua_pushnumber(L,data.askprice4());
	lua_settable(L,-3);
	lua_pushstring(L,"askprice5");
	lua_pushnumber(L,data.askprice5());
	lua_settable(L,-3);
	lua_pushstring(L,"bidvolume1");
	lua_pushinteger(L,data.bidvolume1());
	lua_settable(L,-3);
	lua_pushstring(L,"bidvolume2");
	lua_pushinteger(L,data.bidvolume2());
	lua_settable(L,-3);
	lua_pushstring(L,"bidvolume3");
	lua_pushinteger(L,data.bidvolume3());
	lua_settable(L,-3);
	lua_pushstring(L,"bidvolume4");
	lua_pushinteger(L,data.bidvolume4());
	lua_settable(L,-3);
	lua_pushstring(L,"bidvolume5");
	lua_pushinteger(L,data.bidvolume5());
	lua_settable(L,-3);
	lua_pushstring(L,"askvolume1");
	lua_pushinteger(L,data.askvolume1());
	lua_settable(L,-3);
	lua_pushstring(L,"askvolume2");
	lua_pushinteger(L,data.askvolume2());
	lua_settable(L,-3);
	lua_pushstring(L,"askvolume3");
	lua_pushinteger(L,data.askvolume3());
	lua_settable(L,-3);
	lua_pushstring(L,"askvolume4");
	lua_pushinteger(L,data.askvolume4());
	lua_settable(L,-3);
	lua_pushstring(L,"askvolume5");
	lua_pushinteger(L,data.askvolume5());
	lua_settable(L,-3);
	lua_pushstring(L,"averageprice");
	lua_pushnumber(L,data.averageprice());
	lua_settable(L,-3);

	lua_resume(L,2);
}
