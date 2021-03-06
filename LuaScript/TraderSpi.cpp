#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include "TraderSpi.h"
#include "LuaShell.h"

#pragma warning(disable : 4996)

// USER_API参数
extern CThostFtdcTraderApi* pTraderUserApi;

// 配置参数
extern char TraderFRONT_ADDR[];	// 交易前置地址
extern char BROKER_ID[];		// 经纪公司代码
extern char INVESTOR_ID[];		// 投资者代码
extern char PASSWORD[];			// 用户密码
extern char INSTRUMENT_ID[];	// 合约代码
extern TThostFtdcPriceType	LIMIT_PRICE;	// 价格
extern TThostFtdcDirectionType	DIRECTION;	// 买卖方向
extern TThostFtdcOffsetFlagType OpenOrClose;

// 会话参数
extern TThostFtdcFrontIDType	FRONT_ID;	//前置编号
extern TThostFtdcSessionIDType	SESSION_ID;	//会话编号
extern TThostFtdcOrderRefType	ORDER_REF;	//报单引用
extern int iNextOrderRef;

extern char* ppInstrumentID[];	
extern int iInstrumentID;

// 请求编号
extern int iRequestID;

extern CRITICAL_SECTION lockStatusQueue;
extern CRITICAL_SECTION lockInfoQueue;
extern CRITICAL_SECTION lockOrderQueue;


extern vector<StatusQueue> vectStatusQueue;

typedef struct tagOrder
{
	TThostFtdcInstrumentIDType INSTRUMENT_ID;								// 合约代码
	TThostFtdcDirectionType	DIRECTION;										// 买卖方向
	TThostFtdcPriceType	LIMIT_PRICE;										// 价格
	TThostFtdcOffsetFlagType OpenOrClose;									// 开平仓
	TThostFtdcOrderRefType	ORDER_REF;										//报单引用
}OrderQueue;
extern vector<OrderQueue> vectOrderQueue;

extern double BuyPrice;
extern double SellPrice;

void CTraderSpi::OnFrontConnected()
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	///用户登录请求
	ReqUserLogin();
}

void CTraderSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.UserID, INVESTOR_ID);
	strcpy(req.Password, PASSWORD);

	int iResult = pTraderUserApi->ReqUserLogin(&req, ++iRequestID);
	cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
								CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		// 保存会话参数
		FRONT_ID = pRspUserLogin->FrontID;
		SESSION_ID = pRspUserLogin->SessionID;
		iNextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
		iNextOrderRef++;
		sprintf(ORDER_REF, "%d", iNextOrderRef);
		///获取当前交易日
		cerr << "--->>> 获取当前交易日 = " << pTraderUserApi->GetTradingDay() << endl;
		///投资者结算结果确认
		ReqSettlementInfoConfirm();

	}
}

void CTraderSpi::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.InvestorID, INVESTOR_ID);
	int iResult = pTraderUserApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
	cerr << "--->>> 投资者结算结果确认: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///请求查询合约
		//ReqQryInstrument();
	}
}

void CTraderSpi::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InstrumentID, INSTRUMENT_ID);
	int iResult = pTraderUserApi->ReqQryInstrument(&req, ++iRequestID);
	cerr << "--->>> 请求查询合约: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///请求查询合约
		//ReqQryTradingAccount();
	}
}

void CTraderSpi::ReqQryTradingAccount()
{
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.InvestorID, INVESTOR_ID);
	int iResult = pTraderUserApi->ReqQryTradingAccount(&req, ++iRequestID);
	cerr << "--->>> 请求查询资金账户: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///请求查询投资者持仓
		//ReqQryInvestorPosition();
	}
}

void CTraderSpi::ReqQryInvestorPosition()
{
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, BROKER_ID);
	strcpy(req.InvestorID, INVESTOR_ID);
	strcpy(req.InstrumentID, INSTRUMENT_ID);
	int iResult = pTraderUserApi->ReqQryInvestorPosition(&req, ++iRequestID);
	cerr << "--->>> 请求查询投资者持仓: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///报单录入请求
		//ReqOrderInsert();
	}
}

void CTraderSpi::ReqOrderInsert()
{
	OrderQueue midOrderQueue;
	EnterCriticalSection(&lockOrderQueue);
	midOrderQueue = vectOrderQueue[0];
	for (vector<OrderQueue>::iterator iter=vectOrderQueue.begin();iter!=vectOrderQueue.end();iter++)
	{
		vectOrderQueue.erase(iter);
		break;
	}
	LeaveCriticalSection(&lockOrderQueue);

	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, BROKER_ID);
	///投资者代码
	strcpy(req.InvestorID, INVESTOR_ID);
	///合约代码
	strcpy(req.InstrumentID, midOrderQueue.INSTRUMENT_ID);
	///报单引用
	strcpy(req.OrderRef, midOrderQueue.ORDER_REF);
	///用户代码
	//	TThostFtdcUserIDType	UserID;
	///报单价格条件: 限价
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
	///买卖方向: 
	req.Direction = midOrderQueue.DIRECTION;
	///组合开平标志: 开仓/平仓
	req.CombOffsetFlag[0] = midOrderQueue.OpenOrClose;
	///组合投机套保标志
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	///价格
	req.LimitPrice = midOrderQueue.LIMIT_PRICE;
	///数量: 1
	req.VolumeTotalOriginal = 1;
	///有效期类型: 当日有效
	req.TimeCondition = THOST_FTDC_TC_GFD;
	///GTD日期
	//	TThostFtdcDateType	GTDDate;
	///成交量类型: 任何数量
	req.VolumeCondition = THOST_FTDC_VC_AV;
	///最小成交量: 1
	req.MinVolume = 1;
	///触发条件: 立即
	req.ContingentCondition = THOST_FTDC_CC_Immediately;
	///止损价
	//	TThostFtdcPriceType	StopPrice;
	///强平原因: 非强平
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///自动挂起标志: 否
	req.IsAutoSuspend = 0;
	///业务单元
	//	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	//	TThostFtdcRequestIDType	RequestID;
	///用户强评标志: 否
	req.UserForceClose = 0;

	int iResult = pTraderUserApi->ReqOrderInsert(&req, ++iRequestID);
	cerr << "--->>> 报单录入请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void CTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	IsErrorRspInfo(pRspInfo);
}

void CTraderSpi::ReqOrderAction(CThostFtdcOrderField *pOrder)
{
	static bool ORDER_ACTION_SENT = false;		//是否发送了报单
	if (ORDER_ACTION_SENT)
		return;

	CThostFtdcInputOrderActionField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, pOrder->BrokerID);
	///投资者代码
	strcpy(req.InvestorID, pOrder->InvestorID);
	///报单操作引用
	//	TThostFtdcOrderActionRefType	OrderActionRef;
	///报单引用
	strcpy(req.OrderRef, pOrder->OrderRef);
	///请求编号
	//	TThostFtdcRequestIDType	RequestID;
	///前置编号
	req.FrontID = FRONT_ID;
	///会话编号
	req.SessionID = SESSION_ID;
	///交易所代码
	//	TThostFtdcExchangeIDType	ExchangeID;
	///报单编号
	//	TThostFtdcOrderSysIDType	OrderSysID;
	///操作标志
	req.ActionFlag = THOST_FTDC_AF_Delete;
	///价格
	//	TThostFtdcPriceType	LimitPrice;
	///数量变化
	//	TThostFtdcVolumeType	VolumeChange;
	///用户代码
	//	TThostFtdcUserIDType	UserID;
	///合约代码
	strcpy(req.InstrumentID, pOrder->InstrumentID);

	int iResult = pTraderUserApi->ReqOrderAction(&req, ++iRequestID);
	cerr << "--->>> 报单操作请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
	ORDER_ACTION_SENT = true;
}

void CTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	IsErrorRspInfo(pRspInfo);
}

///报单通知
void CTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	cerr << "--->>> " << __FUNCTION__  << endl;
	if (IsMyOrder(pOrder))
	{
		if (IsTradingOrder(pOrder))
		{
			//撤单要求
			//ReqOrderAction(pOrder);
		}
		else if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)
			cout << "--->>> 撤单成功" << endl;
	}
}

///成交通知
void CTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	if (pTrade->OffsetFlag == THOST_FTDC_OF_Open)
	{
		if (pTrade->Direction == THOST_FTDC_D_Buy)
		{
			BuyPrice = pTrade->Price;
		}
		else if (pTrade->Direction == THOST_FTDC_D_Sell)
		{
			SellPrice = pTrade->Price;
		}
		LuaClass::LuaF_future_entrust_callback1(pTrade->SequenceNo,pTrade->OffsetFlag,pTrade->Direction,pTrade->InstrumentID,pTrade->Volume,pTrade->Price,BROKER_ID,pTrade->OrderRef,pTrade->TradeDate,pTrade->TradeTime);
	}
	else if (pTrade->OffsetFlag == THOST_FTDC_OF_CloseToday)
	{
		if (pTrade->Direction == THOST_FTDC_D_Buy)
		{
			BuyPrice = 0;
		}
		else if (pTrade->Direction == THOST_FTDC_D_Sell)
		{
			SellPrice = 0;
		}
		LuaClass::LuaF_future_entrust_callback2(pTrade->SequenceNo,pTrade->OffsetFlag,pTrade->Direction,pTrade->InstrumentID,pTrade->Volume,pTrade->Price,BROKER_ID,pTrade->OrderRef,pTrade->TradeDate,pTrade->TradeTime);
	}

	cerr << "--->>> " << __FUNCTION__  << endl;
}

void CTraderSpi:: OnFrontDisconnected(int nReason)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> Reason = " << nReason << endl;
}

void CTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void CTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	IsErrorRspInfo(pRspInfo);
}

bool CTraderSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}

bool CTraderSpi::IsMyOrder(CThostFtdcOrderField *pOrder)
{
	return ((pOrder->FrontID == FRONT_ID) &&
		(pOrder->SessionID == SESSION_ID) &&
		(strcmp(pOrder->OrderRef, ORDER_REF) == 0));
}

bool CTraderSpi::IsTradingOrder(CThostFtdcOrderField *pOrder)
{
	return ((pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_AllTraded));
}
