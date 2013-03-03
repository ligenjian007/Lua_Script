#pragma once

#if defined( BUILD_DLL )
    #define CCAPI __declspec(dllexport)
#else
    #define CCAPI __declspec(dllimport)
#endif

typedef void * CCHANDLE;
struct tagIOPCompleteArgs;
typedef struct tagIOPCompleteArgs IOPCompleteArgs;

enum IOState { IO_STATE_NONE = -1, IO_STATE_SUCCESS = 0, IO_STATE_ERROR = 1, IO_STATE_IO_PENDING = 2, IO_STATE_CANCELED = 3 };
enum ZipAlgorithm { ZIP_ALGORITHM_NONE = 0, ZIP_ALGORITHM_BZ2 = 1, ZIP_ALGORITHM_ZLIB = 2 };
typedef void (WINAPI *PIOCOMP)(CCHANDLE pSender, IOPCompleteArgs *pIOP);
typedef void (WINAPI *PIOCOMPEX)(CCHANDLE pSender, IOPCompleteArgs *pIOP,void *&pInBuffer,int &InBufferLen);

#define NAME_LENGTH 30
#define UID_LEN DWORD

#pragma pack(4)
struct tagIOPCompleteArgs
{
	unsigned int Object;
	int MajorCmd;
	int MinorCmd;
	IOState StateCode;
	unsigned int ErrorCode;
	unsigned char *pInBuffer;
	unsigned int InBufferLen;
	unsigned char *pOutBuffer;
	unsigned int OutBufferLen;
	unsigned char *pErrorInfo;
	unsigned int ErrorInfoLen;
	void *UserData;
};

typedef struct tagDeviceRegistration
{
	int nFuncID;			//功能号
	int nLocation;			//位置 0-Any 1-Local 2-Remote 3-CloudServer
	int nSync;				//同异步 0-Any 1-Sync 2-Async
	char szDriverName[NAME_LENGTH];	//驱动名/CloundServer名
	char szDeviceName[NAME_LENGTH];	//设备名
	bool operator ==(const tagDeviceRegistration &rhs) const {return nFuncID==rhs.nFuncID&&nLocation==rhs.nLocation&&nSync==rhs.nSync&&strcmp(szDriverName,rhs.szDriverName)==0&&strcmp(szDeviceName,rhs.szDeviceName)==0;};
	bool operator < (const tagDeviceRegistration &rhs) const
	{
		if(nFuncID<rhs.nFuncID)return true;
		else if(nFuncID==rhs.nFuncID&&nLocation<rhs.nLocation)return true;
		else if(nFuncID==rhs.nFuncID&&nLocation==rhs.nLocation&&nSync<rhs.nSync)return true;
		else if(nFuncID==rhs.nFuncID&&nLocation==rhs.nLocation&&nSync==rhs.nSync&&strcmp(szDriverName,rhs.szDriverName)<0)return true;
		else if(nFuncID==rhs.nFuncID&&nLocation==rhs.nLocation&&nSync==rhs.nSync&&strcmp(szDriverName,rhs.szDriverName)==0&&strcmp(szDeviceName,rhs.szDeviceName)<0)return true;
		else return false;
	}
} DeviceRegistration;

typedef struct tagRequestHead
{
	char szVersion[NAME_LENGTH];	//VC版本
	UID_LEN dwUID;
	UID_LEN dwCSUID;
	DeviceRegistration ReqDev;
	int MajorCmd;
	int MinorCmd;
	int nTimeOut;					//超时
	char szUsername[NAME_LENGTH];	//用户名
	char szPassword[NAME_LENGTH];	//密码
	DWORD RequestQueueHandle;
	int StateCode;					//状态代码（用于Response）
	int ErrorCode;					//错误代码（用于Response）
	unsigned char szErrorInfo[NAME_LENGTH*2];//错误信息（用于Response）
	int ErrorInfoLen;				//错误信息长度（用于Response）
	bool operator ==(const tagRequestHead &rhs){return dwUID==rhs.dwUID&&dwCSUID==rhs.dwCSUID&&ReqDev==rhs.ReqDev;};
	tagRequestHead()
	{
		ZeroMemory(szVersion,NAME_LENGTH);
		dwUID=0;
		dwCSUID=0;
		ZeroMemory(&ReqDev,sizeof(DeviceRegistration));
		MajorCmd=0;
		MinorCmd=0;
		nTimeOut=0;
		ZeroMemory(szUsername,NAME_LENGTH);
		ZeroMemory(szPassword,NAME_LENGTH);
		RequestQueueHandle=0;
		StateCode=0;
		ErrorCode=0;
		ZeroMemory(szErrorInfo,NAME_LENGTH*2);
		ErrorInfoLen=0;
	}
} RequestHead;

typedef struct tagRequestInfo
{
	DWORD nQueueHandle;
	DWORD nRequestID;
	DeviceRegistration ReqDev;
} RequestInfo;

#pragma pack()

CCAPI CCHANDLE CreateVirtualCloudClient(int CoDataConn = 1);			//建立一个CC句柄
CCAPI void CloseVirtualCloudClient(CCHANDLE hVirtualCloudClient);		//与create对应，关闭cc
CCAPI void SetServerAddress(CCHANDLE hVirtualCloudClient, char* ServerAddress);
CCAPI void SetCmdPort(CCHANDLE hVirtualCloudClient, int CmdPort);
CCAPI void SetDataPort(CCHANDLE hVirtualCloudClient, int DataPort);
CCAPI bool Connect(CCHANDLE hVirtualCloudClient);
CCAPI void Disconnect(CCHANDLE hVirtualCloudClient);
CCAPI bool PostIO(CCHANDLE hVirtualCloudClient, int FuncID, int Location, int Sync, char* DriverName, char* DeviceName, unsigned int Object, int MajorCmd, int MinorCmd, unsigned char *pInBuffer, unsigned int InBufferLen, PIOCOMP pNotifier, void *UserData,int TimeOut=3000 ,ZipAlgorithm CompressMode = ZIP_ALGORITHM_NONE); 
// you need free pOutBuffer and pErrorInfo after this call
CCAPI bool StartIO(CCHANDLE hVirtualCloudClient, int FuncID, int Location, int Sync, char* DriverName, char* DeviceName, unsigned int &Object, int MajorCmd, int MinorCmd, unsigned char *pInBuffer, unsigned int InBufferLen, unsigned char* &pOutBuffer,unsigned int &OutBufferLen, unsigned char* &pErrorInfo,unsigned int &ErrorInfoLen, unsigned int &ErrorCode, IOState &StateCode, int TimeOut = 30000, ZipAlgorithm CompressMode = ZIP_ALGORITHM_NONE);
CCAPI void SetUsername(CCHANDLE hVirtualCloudClient, char* Username);
CCAPI void SetPassword(CCHANDLE hVirtualCloudClient, char* Password);
CCAPI void SetVirtualDriverName(CCHANDLE hVirtualCloudClient, char* VirtualDriverName);
CCAPI void SetVirtualDeviceName(CCHANDLE hVirtualCloudClient, char* VirtualDeviceName);
CCAPI void SetVitrualMajorCmd(CCHANDLE hVirtualCloudClient, int VitrualMajorCmd);
CCAPI void SetVitrualMinorCmd(CCHANDLE hVirtualCloudClient, int VitrualMinorCmd);
CCAPI bool Subscribe(CCHANDLE hVirtualCloudClient,CCHANDLE pSender,DWORD &RequestQueueHandle,int FuncID, int Location, int Sync, char* DriverName, char* DeviceName, int MajorCmd,int MinorCmd, int SubscribingMajorCmd,int SubscribingMinorCmd , PIOCOMPEX pNotifier,unsigned char *pInBuffer, unsigned int InBufferLen,unsigned char* &pErrorInfo,unsigned int &ErrorInfoLen, unsigned int &ErrorCode,bool NewHandle=false);
CCAPI bool Unsubscribe(CCHANDLE hVirtualCloudClient,DWORD RequestQueueHandle,int FuncID, int Location, int Sync, char* DriverName, char* DeviceName, int MajorCmd, int MinorCmd, int UnsubscribingMajorCmd,int UnsubscribingMinorCmd, unsigned char* &pErrorInfo,unsigned int &ErrorInfoLen, unsigned int &ErrorCode);
CCAPI void SetReservedSubscribingPackageCount(CCHANDLE hVirtualCloudClient,int ReservedSubscribingPackageCount);
