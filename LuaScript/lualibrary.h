#ifndef __LUALIBRARY__H__
#define __LUALIBRARY__H__

#include "interface.h"

extern "C"  
{  
    #include "lua.h"  
    #include "lauxlib.h"  
    #include "lualib.h"  
}  

typedef struct tagRequestQueue
{
	IOPCompleteArgs * pIOP;
	RequestInfo ReqInfo;
	BYTE * pInBuffer;
	int InBufferLen;
	int nCounter;
} RequestQueue;


#endif __LUALIBRARY__H__