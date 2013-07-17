// LuaScript.cpp : 定义控制台应用程序的入口点。
//
#ifndef __LUA__SCRIPT__H__
#define __LUA__SCRIPT__H__


#include "stdafx.h"
//#include ".\VirtualCloudServer\interface.h"
#include "interface.h"
#include <vector>
#include "HSComm.pb.h"
#include <string>
#include "FutureData.pb.h"
#include ".\ThostTraderApi\ThostFtdcMdApi.h"
#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include "MdSpi.h"
#include <windows.h>
#include "TraderSpi.h"
#include <list>


extern "C"  
{  
    #include "lua.h"  
    #include "lauxlib.h"  
    #include "lualib.h"  
	#include "pluto.h"
}  

using namespace std;
using namespace HSCommPB;
using namespace FutureDataPB;

const int MAX_THREAD_NUM=30;

typedef struct tagStatus
{
	TThostFtdcInstrumentIDType InstrumentID;
	char TraderStatus;//0表示未报单，1表示已报单但为开仓，2表示已开仓，3表示已报单但未平仓，4表示周期结束
	double Price;//成交价
	TThostFtdcDirectionType	Direction;
}StatusQueue;


/*
luaClass is a shell that is responsible for adding new functions and excute lua script
*/

class LuaClass
{
public:
	LuaClass();
	~LuaClass();
	int	Init(string serverAddress="127.0.0.1", int cmdPort=12298, int dataPort=12299);
	int	execute(int port,string filename); //the first parameter is the coroutine to execute the file (second parameter)
	int	executeMain(string filename);
	string executeScript(string script);
	static void* svrAddr;
	static void* usrName;
	static void* hvcClient;
	static void* hstrClient;

private:
	DWORD nSend,nRecv,nSucc,nFail;
	lua_State *pMainShell;
	lua_State *pCoroutines[MAX_THREAD_NUM];
	string serverAddress,userName;
	int cmdPort,dataPort;


/*
the following procedures are intended to execute the shell command
*/
public:
	static int shell_sleep(lua_State *pState);
	static int shell_connect(lua_State *pState);

	static int shell_entrust(lua_State *pState);
	static void CallBack_Entrust(CCHANDLE pSender, IOPCompleteArgs *pIOP);
	static int shell_query_entrust(lua_State *pState);
	static void CallBack_Query_entrust(CCHANDLE pSender, IOPCompleteArgs *pIOP);
	static int shell_query_orders(lua_State *pState);
	static void CallBack_Query_orders(CCHANDLE pSender, IOPCompleteArgs *pIOP);
	static int shell_query_capital(lua_State *pState);
	static void CallBack_Query_capital(CCHANDLE pSender, IOPCompleteArgs *pIOP);
	static int LuaF_history_data_test(lua_State *pState);
	static void CallBack_history_data_test(CCHANDLE pSender, IOPCompleteArgs *pIOP);
	static int LuaF_history_beta(lua_State *pState);
	static void CallBack_history_beta(CCHANDLE pSender, IOPCompleteArgs *pIOP);
	static int LuaF_history_data(lua_State *pState);
	static void CallBack_history_data(CCHANDLE pSender, IOPCompleteArgs *pIOP);
	static int LuaF_future_entrust(lua_State *pState);
	static int LuaF_future_init(lua_State *pState);
	static int luaF_getAskPrice(lua_State *pState);
	static int luaF_getBidPrice(lua_State *pState);
	static int luaF_Trade(lua_State *pState);
	static int luaF_getBuyPrice(lua_State *pState);
	static int luaF_getSellPrice(lua_State *pState);
	static int luaF_breakPoint(lua_State *pState);
	static void LuaF_future_entrust_callback1(TThostFtdcSequenceNoType,TThostFtdcOffsetFlagType,TThostFtdcDirectionType,TThostFtdcInstrumentIDType,TThostFtdcVolumeType,TThostFtdcPriceType,TThostFtdcBrokerIDType,TThostFtdcOrderRefType,TThostFtdcDateType,TThostFtdcTimeType);
	static void LuaF_future_entrust_callback2(TThostFtdcSequenceNoType,TThostFtdcOffsetFlagType,TThostFtdcDirectionType,TThostFtdcInstrumentIDType,TThostFtdcVolumeType,TThostFtdcPriceType,TThostFtdcBrokerIDType,TThostFtdcOrderRefType,TThostFtdcDateType,TThostFtdcTimeType);
	static void LuaF_future_entrust_callback3();
	static int LuaF_future_entrust_para(lua_State *pState);
	static void restart();
	static char result_text[2048];
	static list<string> buf_string_list;

private:
	static void box_userdata(lua_State *pState,char slot_name[20],void* & userdata);
	static void unbox_userdata(lua_State *pState,char slot_name[20],void* & userdata);
	static lua_State *storedState;
	static int times_;
	static int totalTimes_;
	static bool canTerminate_;
};

#endif 