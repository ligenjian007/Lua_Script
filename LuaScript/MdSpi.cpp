#include "stdafx.h"
#include "MdSpi.h"
#include "TraderSpi.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
using namespace std;

#pragma warning(disable : 4996)

// USER_API����
extern CThostFtdcMdApi* pMdUserApi;
extern CTraderSpi* pTraderUserSpi;

// ���ò���
extern char MdFRONT_ADDR[];		
extern TThostFtdcBrokerIDType	BROKER_ID;
extern TThostFtdcInvestorIDType INVESTOR_ID;
extern TThostFtdcPasswordType	PASSWORD;
extern char* ppInstrumentID[];	
extern int iInstrumentID;

extern char INSTRUMENT_ID[];				// ��Լ����
extern TThostFtdcPriceType	LIMIT_PRICE;	// �۸�
extern TThostFtdcDirectionType	DIRECTION;	// ��������
extern TThostFtdcOffsetFlagType OpenOrClose;// ��ƽ��
// �Ự����
extern TThostFtdcFrontIDType	FRONT_ID;	//ǰ�ñ��
extern TThostFtdcSessionIDType	SESSION_ID;	//�Ự���
extern TThostFtdcOrderRefType	ORDER_REF;	//��������
extern int iNextOrderRef;

// ������
extern int iRequestID;

//ǿƽָ��
bool Force = false;

extern CRITICAL_SECTION lockStatusQueue;
extern CRITICAL_SECTION lockInfoQueue;

typedef struct tagStatus
{
	TThostFtdcInstrumentIDType InstrumentID;
	char TraderStatus;//0��ʾδ������1��ʾ�ѱ�����Ϊ���֣�2��ʾ�ѿ��֣�3��ʾ�ѱ�����δƽ�֣�4��ʾ���ڽ���
	double Price;//�ɽ���
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
	///�û���¼����
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
	cerr << "--->>> �����û���¼����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
							CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///��ȡ��ǰ������
		cerr << "--->>> ��ȡ��ǰ������ = " << pMdUserApi->GetTradingDay() << endl;
		// ����������
		SubscribeMarketData();	
	}
}

void CMdSpi::SubscribeMarketData()
{
	int iResult = pMdUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> �������鶩������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
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
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}