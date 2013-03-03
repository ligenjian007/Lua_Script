#include "stdafx.h"
#include "lualibrary.h"
#include <vector>

extern vector<RequestQueue> vectRequestQueue;
extern bool bBeginProcess=false;
extern UINT ProcessRequest(LPVOID lpParam);
extern DWORD nRecv,nPreProcess,nAsyProcess,nPostProcess;
extern BOOL _ExitFlag = 0;

extern lua_State *L; 

//int Connect(lua_State *L)