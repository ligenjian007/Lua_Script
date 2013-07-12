#include "stdafx.h"
#include "MdSpi.h"
#include "TraderSpi.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
using namespace std;

#pragma warning(disable : 4996)

// USER_API参数
extern CThostFtdcMdApi* pMdUserApi;
extern CTraderSpi* pTraderUserSpi;

// 配置参数
extern char MdFRONT_ADDR[];		
extern TThostFtdcBrokerIDType	BROKER_ID;
extern TThostFtdcInvestorIDType INVESTOR_ID;
extern TThostFtdcPasswordType	PASSWORD;
extern char* ppInstrumentID[];	
extern int iInstrumentID;

extern char INSTRUMENT_ID[];				// 合约代码
extern TThostFtdcPriceType	LIMIT_PRICE;	// 价格
extern TThostFtdcDirectionType	DIRECTION;	// 买卖方向
extern TThostFtdcOffsetFlagType OpenOrClose;// 开平仓
// 会话参数
extern TThostFtdcFrontIDType	FRONT_ID;	//前置编号
extern TThostFtdcSessionIDType	SESSION_ID;	//会话编号
extern TThostFtdcOrderRefType	ORDER_REF;	//报单引用
extern int iNextOrderRef;

// 请求编号
extern int iRequestID;

//强平指令
bool Force = false;

extern CRITICAL_SECTION lockStatusQueue;
extern CRITICAL_SECTION lockInfoQueue;

typedef struct tagStatus
{
	TThostFtdcInstrumentIDType InstrumentID;
	char TraderStatus;//0表示未报单，1表示已报单但为开仓，2表示已开仓，3表示已报单但未平仓，4表示周期结束
	double Price;//成交价
	TThostFtdcDirectionType	Direction;
}StatusQueue;
extern vector<StatusQueue> vectStatusQueue;

typedef struct tagInfo
{
	TThostFtdcInstrumentIDType InstrumentID;
	double LastPrice;
	double AskPrice1;
	double BidPrice1;
	double PreClosePrice;
	double OpenPrice;
	double HighestPrice;
	double LowestPrice;
	int Volume;
	double Turnover;
}InfoQueue;
extern vector<InfoQueue> vectInfoQueue;

void CMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
						int nRequestID, bool bIsLast)
{
	cerr << "--->>> "<< __FUNCTION__ << endl;
	IsErrorRspInfo(pRspInfo);
}

void CMdSpi::OnFrontDisconnected(int nReason)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> Reason = " << nReason << endl;
}

void CMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void CMdSpi::OnFrontConnected()
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	///用户登录请求
	ReqUserLogin();
}

void CMdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.UserID, INVESTOR_ID);
	strcpy(req.Password, PASSWORD);
	int iResult = pMdUserApi->ReqUserLogin(&req, ++iRequestID);
	cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
							CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		cerr << "--->>> 获取当前交易日 = " << pMdUserApi->GetTradingDay() << endl;
		// 请求订阅行情
		SubscribeMarketData();	
	}
}

void CMdSpi::SubscribeMarketData()
{
	int iResult = pMdUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}

void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}

void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	InfoQueue midInfoQueue;
	strcpy(midInfoQueue.InstrumentID,pDepthMarketData->InstrumentID);
	midInfoQueue.LastPrice = pDepthMarketData->LastPrice;
	midInfoQueue.AskPrice1 = pDepthMarketData->AskPrice1;
	midInfoQueue.BidPrice1 = pDepthMarketData->BidPrice1;
	midInfoQueue.PreClosePrice = pDepthMarketData->PreClosePrice;
	midInfoQueue.OpenPrice = pDepthMarketData->OpenPrice;
	midInfoQueue.HighestPrice = pDepthMarketData->HighestPrice;
	midInfoQueue.LowestPrice = pDepthMarketData->LowestPrice;
	midInfoQueue.Volume = pDepthMarketData->Volume;
	midInfoQueue.Turnover = pDepthMarketData->Turnover;

	EnterCriticalSection(&lockInfoQueue);
	for (vector<InfoQueue>::iterator iter=vectInfoQueue.begin();iter!=vectInfoQueue.end();iter++)
	{
		if (strcmp(iter->InstrumentID,midInfoQueue.InstrumentID) == 0)
		{
			vectInfoQueue.erase(iter);
			break;
		}
	}
	vectInfoQueue.push_back(midInfoQueue);
	LeaveCriticalSection(&lockInfoQueue);

	cerr << __FUNCTION__ << endl;
}

bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}