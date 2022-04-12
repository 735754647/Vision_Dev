#include "StdAfx.h"

#if  SCVDEV_USE_HV

#include "Dev_HV.h"

//指令内存中存储的数目
#define  ORDER_SAVE_MAX    500 

std::vector<CDevHV*> CDevHV::m_ObjMnger1D;
bool g_init=CDevHV::init();
bool CDevHV::init()
{
	m_ObjMnger1D.clear();
	return true;
}

CDevHV::CDevHV(void)
{
	m_bIsAdd=false;

	//指令监控
	m_HVDevOrderInfo.SetCritiaclSection(&m_CCriticalSection);
	m_HVDevOrderInfo.SetOrderSize(ORDER_SAVE_MAX);

	memset(tempTimeIn,0,sizeof(long)*500);
	memset(tempTimeOut,0,sizeof(long)*500);
}

CDevHV::~CDevHV(void)
{
}

HRESULT  CDevHV::API_HV_EnumerateDevice(pHVGigE_Dev_i * pDev, int * nDevCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[0],tempTimeOut[0]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_EnumerateDevice()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

    HRESULT retval=S_OK;

	APIDev_Lock();
	HRESULT retv=HV_EnumerateDevice(pDev,nDevCount);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_OpenDevice(int nDevId)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[1],tempTimeOut[1]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_OpenDevice(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	int temSize=m_ObjMnger1D.size();
	bool temRes=false;
	for (int i=0;i<temSize;i++)
	{
		if (m_ObjMnger1D[i]==this)
		{
			temRes=true;
		}
	}
	if (!temRes)
	{
		m_ObjMnger1D.push_back(this);
	}

	HRESULT retval=S_OK;
	
	APIDev_Lock();
	HRESULT retv=HV_OpenDevice(nDevId);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}
	return retval;
}
HRESULT  CDevHV::API_HV_DevCapInit(int nDevId, LPCSTR lpFileName /*= NULL*/)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[2],tempTimeOut[2]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_DevCapInit(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();
	HRESULT retv=HV_DevCapInit(nDevId,lpFileName);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
void  CDevHV::API_HV_DevCapRelease(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[3],tempTimeOut[3]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_DevCapRelease(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	APIDev_Lock();
	HV_DevCapRelease(nDevId);
	APIDev_Unlock();
}
void  CDevHV::   API_HV_SetCallBack(USER_CALLBACK_PROC pCallBack,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[4],tempTimeOut[4]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetCallBack(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	APIDev_Lock();
	HV_SetCallBack(pCallBack,nDevId);
	APIDev_Unlock();
}
HRESULT  CDevHV::API_HV_StartCapture(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[4],tempTimeOut[4]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_StartCapture(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();
	HRESULT retv=HV_StartCapture(nDevId);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SuspendCapture(BOOL bSuspend,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[5],tempTimeOut[5]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SuspendCapture(%d,%d)"),timeBetween,bSuspend,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();
	HRESULT retv=HV_SuspendCapture(bSuspend,nDevId);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_StopCapture(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[5],tempTimeOut[5]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_StopCapture(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();
	HRESULT retv=HV_StopCapture(nDevId);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_ShowControlPage(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[6],tempTimeOut[6]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_ShowControlPage(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_ShowControlPage(nDevId);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_ShowRWPage(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[7],tempTimeOut[7]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_ShowRWPage(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_ShowRWPage(nDevId);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_ShowSnapshotPage(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[8],tempTimeOut[8]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_ShowSnapshotPage(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_ShowSnapshotPage(nDevId);
	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetFrameRate(double & nRate, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[9],tempTimeOut[9]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetFrameRate(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetFrameRate(nRate,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetTestInfo(int & nImgCount,int & nPacketMissing,int &nFrameMissing, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[10],tempTimeOut[10]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetTestInfo(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetTestInfo(nImgCount,nImgCount,nFrameMissing,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetParamInfo(int nType, PVOID* ppParamInfoStruct,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[11],tempTimeOut[11]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetParamInfo(%d,%d)"),timeBetween,nType,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetParamInfo(nType,ppParamInfoStruct,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetFrameBuffer(long & lBufSize, LPBYTE * pBuf, int & nFrmWidth, int & nFrmHeight, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[12],tempTimeOut[12]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetFrameBuffer(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetFrameBuffer(lBufSize,pBuf,nFrmWidth,nFrmHeight,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SaveImg(LPBYTE pBuffer, LPCSTR lpFileName, const int nFrmWidth,
						const int nFrmHeight, const long lBufSize, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[13],tempTimeOut[13]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SaveImg(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SaveImg(pBuffer,lpFileName,nFrmWidth,nFrmHeight,lBufSize,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
CHAR*  CDevHV::API_HV_GetErrorString(LONG lError)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[14],tempTimeOut[14]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetErrorString()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	CHAR* retval=NULL;
	APIDev_Lock();
	retval=HV_GetErrorString(lError);
	APIDev_Unlock();
	return retval;
}

HRESULT  CDevHV::API_HV_SetPreviewSnapMode(int nPreview, int nSnapMode,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[15],tempTimeOut[15]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetPreviewSnapMode(%d,%d,%d)"),timeBetween,nPreview, nSnapMode,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetPreviewSnapMode(nPreview,nSnapMode,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

 	return retval;
}

HRESULT  CDevHV::API_HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapState,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[16],tempTimeOut[16]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetPreviewSnapMode(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetPreviewSnapMode(psPreSnapState,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetMaxResolution(int& nMaxWidth, int& nMaxHeight,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[17],tempTimeOut[17]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetPreviewSnapMode(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetMaxResolution(nMaxWidth,nMaxHeight,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetImageMirror(int nMirror,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[18],tempTimeOut[18]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetImageMirror(%d,%d)"),timeBetween,nMirror,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetImageMirror(nMirror,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetImageMirror(int* pnMirror,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[19],tempTimeOut[19]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetImageMirror(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetImageMirror(pnMirror,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetResolution(HVGigE_Video_i* psResolution,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[20],tempTimeOut[20]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetResolution(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetResolution(psResolution,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetResolution(HVGigE_Video_i sResolution,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[21],tempTimeOut[21]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetResolution(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetResolution(sResolution,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetImageColorStat(BOOL* pbColor,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[22],tempTimeOut[22]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetImageColorStat(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetImageColorStat(pbColor,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetImageColorStat(BOOL bColor, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[23],tempTimeOut[23]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetImageColorStat(%d,%d)"),timeBetween,bColor,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetImageColorStat(bColor,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetImageGammaStat(BOOL* pbGamma,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[24],tempTimeOut[24]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetImageGammaStat(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetImageGammaStat(pbGamma,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetImageGammaStat(BOOL bGamma, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast
			(tempTimeIn[25],tempTimeOut[25]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetImageGammaStat((%d，%d)"),timeBetween,bGamma,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetImageGammaStat(bGamma,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetBlackLevelInfo( HVGigE_Control_i* psBlackLevel,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[26],tempTimeOut[26]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetBlackLevelInfo(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetBlackLevelInfo(psBlackLevel,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetBlackLevelInfo(HVGigE_Control_i sBlackLevel,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[27],tempTimeOut[27]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetBlackLevelInfo(sBlackLevel.bEnable:%d,sBlackLevel.bAuto:%d,%d)"),timeBetween,
			(int)sBlackLevel.bEnable,
			(int)sBlackLevel.bAuto,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetBlackLevelInfo(sBlackLevel,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetBlackLevelEnable(BOOL bEnable,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[28],tempTimeOut[28]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetBlackLevelEnable(%d,%d)"),timeBetween,(int)bEnable,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetBlackLevelEnable(bEnable,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetBlackLevelEnable(BOOL* pbEnable,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[29],tempTimeOut[29]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetBlackLevelEnable(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetBlackLevelEnable(pbEnable,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetBlackLevelAuto(BOOL bAuto,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[30],tempTimeOut[30]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetBlackLevelAuto(%d,%d)"),timeBetween,(int)bAuto,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetBlackLevelAuto(bAuto,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}


HRESULT  CDevHV::API_HV_GetBlackLevelAuto(BOOL* pbAuto,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[31],tempTimeOut[31]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetBlackLevelAuto(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetBlackLevelAuto(pbAuto,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetBlackLevelRange(HVGigE_Range_i sRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[32],tempTimeOut[32]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetBlackLevelRange(sRange.nMax:%d,sRange.nMin:%d,%d)"),timeBetween,
			sRange.nMax,
			sRange.nMin,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetBlackLevelRange(sRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetBlackLevelRange(HVGigE_Range_i* psRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[33],tempTimeOut[33]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetBlackLevelRange(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetBlackLevelRange(psRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetBlackLevelValue(int* pnValue,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[34],tempTimeOut[34]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetBlackLevelValue(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetBlackLevelValue(pnValue,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetBlackLevelValue(int* pnValueArr,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[35],tempTimeOut[35]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetBlackLevelValue(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetBlackLevelValue(pnValueArr,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetGainInfo(HVGigE_Control_i* psGain,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[36],tempTimeOut[36]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetGainInfo(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetGainInfo(psGain,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetGainInfo(HVGigE_Control_i sGain,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[37],tempTimeOut[37]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetGainInfo(sGain.bEnable:%d,sGain.bAuto:%d,%d)"),timeBetween,
			(int)sGain.bEnable,
			(int)sGain.bAuto,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetGainInfo(sGain,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetGainEnable(BOOL bEnable,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[38],tempTimeOut[38]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetGainEnable(%d,%d)"),timeBetween,(int)bEnable,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetGainEnable(bEnable,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetGainEnable(BOOL* pbEnable,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[39],tempTimeOut[39]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetGainEnable(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetGainEnable(pbEnable,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetGainAuto(BOOL bAuto,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[40],tempTimeOut[40]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetGainAuto(%d,%d)"),timeBetween,bAuto,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetGainAuto(bAuto,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetGainAuto(BOOL* pbAuto,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[41],tempTimeOut[41]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetGainAuto(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetGainAuto(pbAuto,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetGainRange(HVGigE_Range_i sRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[42],tempTimeOut[42]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetGainRange(sRange.nMax:%d,sRange.nMin:%d,%d)"),timeBetween,
			sRange.nMax,
			sRange.nMin,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetGainRange(sRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetGainRange(HVGigE_Range_i* psRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[43],tempTimeOut[43]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetGainRange(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetGainRange(psRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetGainValue(int* pValueArr,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[44],tempTimeOut[44]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetGainValue(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetGainValue(pValueArr,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetGainValue(int* pnValue,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[45],tempTimeOut[45]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetGainValue(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetGainValue(pnValue,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetExposureInfo(HVGigE_Control_i* psExposure,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[46],tempTimeOut[46]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetExposureInfo(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetExposureInfo(psExposure,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetExposureInfo(HVGigE_Control_i sExposure,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[47],tempTimeOut[47]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetExposureInfo(sExposure.bEnable:%d,sExposure.bAuto:%d,%d)"),timeBetween,
			(int)sExposure.bEnable,
			(int)sExposure.bAuto,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetExposureInfo(sExposure,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetExposureEnable(BOOL bEnable,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[48],tempTimeOut[48]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetExposureEnable(%d,%d)"),timeBetween,(int)bEnable,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetExposureEnable(bEnable,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetExposureEnable(BOOL* pbEnable,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[49],tempTimeOut[49]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetExposureEnable(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetExposureEnable(pbEnable,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetExposureAuto(BOOL bAuto,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[50],tempTimeOut[50]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetExposureAuto(%d,%d)"),timeBetween,(int)bAuto,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetExposureAuto(bAuto,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetExposureAuto(BOOL* pbAuto,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[51],tempTimeOut[51]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetExposureAuto(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetExposureAuto(pbAuto,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetExposureRange(HVGigE_Range_i sRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[52],tempTimeOut[52]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetExposureRange(sRange.nMax:%d,sRange.nMin:%d,%d)"),timeBetween,
			sRange.nMax,
			sRange.nMin,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetExposureRange(sRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetExposureRange(HVGigE_Range_i* psRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[53],tempTimeOut[53]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetExposureRange(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetExposureRange(psRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetExposureValue(int nValue,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[54],tempTimeOut[54]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetExposureValue(%d,%d)"),timeBetween,nValue,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetExposureValue(nValue,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetExposureValue(int* pnValue,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[55],tempTimeOut[55]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetExposureValue(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetExposureValue(pnValue,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetSnapInfo(HVGigE_SnapControl_i* psSnapControl, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[56],tempTimeOut[56]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetSnapInfo(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetSnapInfo(psSnapControl,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetSnapInfo(HVGigE_SnapControl_i sSnap, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[57],tempTimeOut[57]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetSnapInfo(sSnap.lDebouncerTime:%d,sSnap.lExpTime:%d,sSnap.lTrigFreq:%d,sSnap.lTrigImgCount:%d,%d)")
			,timeBetween,
			sSnap.lDebouncerTime,
			sSnap.lExpTime,
			sSnap.lTrigFreq,
			sSnap.lTrigImgCount,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetSnapInfo(sSnap,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetSnapDebounceTime(LONG lDebouncerTime,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[58],tempTimeOut[58]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetSnapDebounceTime(%d,%d)"),timeBetween,lDebouncerTime,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetSnapDebounceTime(lDebouncerTime,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetSnapDebounceTime(LONG *plDebouncerTime,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[59],tempTimeOut[59]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetSnapDebounceTime(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetSnapDebounceTime(plDebouncerTime,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetSnapExpTime(LONG lExpTime,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[60],tempTimeOut[60]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetSnapExpTime(%d,%d)"),timeBetween,lExpTime,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SetSnapExpTime(lExpTime,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetSnapExpTime(LONG* plExpTime,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[61],tempTimeOut[61]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetSnapExpTime(%d)"),timeBetween,nDevId);
		//m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetSnapExpTime(plExpTime,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[62],tempTimeOut[62]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetSnapExpTimeRange(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetSnapExpTimeRange(psRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[63],tempTimeOut[63]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetTrigFreqRange(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetTrigFreqRange(psRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetTrigImgCountRange(HVGigE_Range_i* psRange,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[64],tempTimeOut[64]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetTrigImgCountRange(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_GetTrigImgCountRange(psRange,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

 HRESULT  CDevHV::API_HV_SetSnapTrigFreqImgCount(LONG lTrigFreq, LONG lTrigImgCount,int nDevId)
 {
	 //---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[65],tempTimeOut[65]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetSnapTrigFreqImgCount(%d,%d,%d)"),timeBetween,
			lTrigFreq,
			lTrigImgCount,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	 HRESULT retval=S_OK;
	 APIDev_Lock();
	 HRESULT retv=HV_SetSnapTrigFreqImgCount(lTrigFreq,lTrigImgCount,nDevId);
	 APIDev_Unlock();
	 if (HV_SUCCESS!=retv)
	 {
		 retval=S_FALSE;
	 }

	 return retval;
 }
HRESULT  CDevHV::API_HV_GetSnapTrigFreqImgCount(LONG* plTrigFreq, LONG* plTrigImgCount,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[66],tempTimeOut[66]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetSnapTrigFreqImgCount(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	 APIDev_Lock();
	HRESULT retv=HV_GetSnapTrigFreqImgCount(plTrigFreq,plTrigImgCount,nDevId);
	APIDev_Unlock();
	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SaveParaToIniFile(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[67],tempTimeOut[67]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SaveParaToIniFile(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_SaveParaToIniFile(nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_IniCamFromIniFile(int nDevId,LPCSTR lpFileName)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[68],tempTimeOut[68]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_IniCamFromIniFile(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	HRESULT retval=S_OK;
	APIDev_Lock();
	HRESULT retv=HV_IniCamFromIniFile(nDevId,lpFileName);

	APIDev_Unlock();


	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetSnapIOMode(HVGigE_SnapIO_Mode_i sSnapIOMode,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[69],tempTimeOut[69]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetSnapIOMode(sSnapIOMode.nInMode:%d,sSnapIOMode.nOutMode:%d,%d)"),
			timeBetween,
            sSnapIOMode.nInMode,
			sSnapIOMode.nOutMode,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();
	HRESULT retv=HV_SetSnapIOMode(sSnapIOMode,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetSnapIOMode(HVGigE_SnapIO_Mode_i* psSnapIOMode,int nDevId)
{
    //---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[70],tempTimeOut[70]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetSnapIOMode(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();
	
	HRESULT retv=HV_GetSnapIOMode(psSnapIOMode,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetRawData(HVGigE_Img_i* pRawFrameInfo,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[71],tempTimeOut[71]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetRawData(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetRawData(pRawFrameInfo,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[72],tempTimeOut[72]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetRGBData(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetRGBData(pRGBFrameInfo,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT CDevHV::API_HV_SnapSWTrigger(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[73],tempTimeOut[73]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SnapSWTrigger(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HRESULT retval=S_OK;

	APIDev_Lock();
	HRESULT retv=HV_SnapSWTrigger(nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
void  CDevHV::API_HV_CloseDevice(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[74],tempTimeOut[74]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_CloseDevice(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	APIDev_Lock();
	HV_CloseDevice(nDevId);
	APIDev_Unlock();
}
HRESULT  CDevHV::API_HV_SetROI(int Original_x, int Original_y, 
					   int nImgWidth, int nImgHeight,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[75],tempTimeOut[75]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetROI(%d,%d,%d,%d,%d)"),timeBetween,
			Original_x,
			Original_y,
			nImgWidth,
            nImgHeight,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetROI(Original_x,Original_y,nImgWidth,nImgHeight,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetROI(int &nStart_x, int &nStart_y, 
					   int &nImgWidth, int &nImgHeight,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[76],tempTimeOut[76]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetROI(%d,%d,%d,%d,%d)"),timeBetween,
			nStart_x,
			nStart_y,
			nImgWidth,
            nImgHeight,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetROI(nStart_x,nStart_y,nImgWidth,nImgHeight,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetResolutionMode(HVGige_Resolution Res_Mode, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[77],tempTimeOut[77]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetResolutionMode(%d,%d)"),timeBetween,Res_Mode,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetResolutionMode(Res_Mode,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetPacketSize(int nPacketSize,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[78],tempTimeOut[78]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetPacketSize(%d,%d)"),timeBetween,nPacketSize,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetPacketSize(nPacketSize,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetGrrMode_ExpFlash(long lExposureTime, long lFlashDelayTime, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[79],tempTimeOut[79]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetGrrMode_ExpFlash(%d,%d,%d)"),timeBetween,
			lExposureTime,
			lFlashDelayTime,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetGrrMode_ExpFlash(lExposureTime,lFlashDelayTime,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetImageChannel(int& nChannel,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[80],tempTimeOut[80]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetImageChannel(%d,%d)"),timeBetween,nChannel,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetImageChannel(nChannel,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_SetImageDataType(int nDevId, int nImgDataType)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[81],tempTimeOut[81]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetImageDataType(%d,%d)"),timeBetween,nDevId,nImgDataType);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetImageDataType(nDevId,nImgDataType);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
CAMERA_TYPE  CDevHV::API_HV_GetCameraType(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[82],tempTimeOut[82]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetCameraType(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	CAMERA_TYPE retval=NOTYPE;

	APIDev_Lock();

	HRESULT retv=HV_GetCameraType(nDevId);

	APIDev_Unlock();

	return retval;
}
HRESULT  CDevHV::API_HV_SetBrightnessFactor(float Brightness, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[83],tempTimeOut[83]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetBrightnessFactor(%3.3f,%d)"),timeBetween,Brightness,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetBrightnessFactor(Brightness,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetBrightnessFactor(float &Brightness, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[84],tempTimeOut[84]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetBrightnessFactor(%3.3f,%d)"),timeBetween,Brightness,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetBrightnessFactor(Brightness,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetContrastFactor(float Constrast, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[85],tempTimeOut[85]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetContrastFactor(%3.3f,%d)"),timeBetween,Constrast,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetContrastFactor(Constrast,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetContrastFactor(float &Constrast, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[86],tempTimeOut[86]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetContrastFactor(%3.3f,%d)"),timeBetween,Constrast,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetContrastFactor(Constrast,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_AKeyWhiteBalance(int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[87],tempTimeOut[87]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_AKeyWhiteBalance(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_AKeyWhiteBalance(nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_SetUserDefNum(LPSTR lpSeriesNum, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[88],tempTimeOut[88]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetUserDefNum(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetUserDefNum(lpSeriesNum,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT  CDevHV::API_HV_GetUserDefNum(LPSTR lpSeriesNum, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[89],tempTimeOut[89]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetUserDefNum(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetUserDefNum(lpSeriesNum,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT 	CDevHV::API_HV_SetGPIOMode(int nMode, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[90],tempTimeOut[90]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetGPIOMode(%d,%d)"),timeBetween,nMode,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetGPIOMode(nMode,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT 	CDevHV::API_HV_SetGPIOValue(bool bValue, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[91],tempTimeOut[91]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetGPIOValue(%d,%d)"),timeBetween,(int)bValue,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_SetGPIOValue(bValue,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT 	CDevHV::API_HV_GetTriggerCount(int &nTrigCount, bool bReset, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[92],tempTimeOut[92]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetTriggerCount(%d,%d,%d)"),timeBetween,nTrigCount,
			(int)bReset,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetTriggerCount(nTrigCount,bReset,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT 	CDevHV::API_HV_GetMaxFrameRate(int &nMaxFrameRate, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[93],tempTimeOut[93]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetMaxFrameRate(%d,%d)"),timeBetween,nMaxFrameRate,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetMaxFrameRate(nMaxFrameRate,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

HRESULT  CDevHV::API_HV_GetFatorySeriesNum(LPSTR lpSeriesNum, int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[94],tempTimeOut[94]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_GetFatorySeriesNum(%d)"),timeBetween,nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;

	APIDev_Lock();

	HRESULT retv=HV_GetFatorySeriesNum(lpSeriesNum,nDevId);

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}
HRESULT CDevHV::API_HV_SetSpecialROI(int Offset_x1, int Offset_y1, int nWidth1, int nHeight1,
							 int Offset_x2, int Offset_y2, int nWidth2, int nHeight2,int nDevId)
{
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		long timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[95],tempTimeOut[95]);
		CString strOrder;
		strOrder.Format(_T("-%d-API_HV_SetSpecialROI(%d,%d,%d,%d,%d,%d,%d,%d,%d)"),
			timeBetween,
			Offset_x1,
			Offset_y1,
			nWidth1,
			nHeight1,
			Offset_x2,
			Offset_y2,
			nWidth2,
			nHeight2,
			nDevId);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	HRESULT retval=S_OK;
	HRESULT retv=0;
	APIDev_Lock();

	/*retv=HV_SetSpecialROI(Offset_x1,Offset_y1,nWidth1,
		nHeight1,Offset_x2,Offset_y2,nWidth2,nHeight2,nDevId);*/

	APIDev_Unlock();

	if (HV_SUCCESS!=retv)
	{
		retval=S_FALSE;
	}

	return retval;
}

//监控记录
void CDevHV::GetOrder(std::vector<CString>& orderList)
{
	orderList=m_HVDevOrderInfo.GetInfoOrderly();
}
void CDevHV::WriteOrder(CString order)
{
	m_HVDevOrderInfo.WriterOrder(order);
}
void CDevHV::APIDev_Lock()
{
    m_CCriticalSection.Lock();

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		m_HVDevOrderInfo.WriterOrder(_T("APIDev_Lock()"));
	}
	//----------------
}
void CDevHV::APIDev_Unlock()
{
    m_CCriticalSection.Unlock();

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		m_HVDevOrderInfo.WriterOrder(_T("APIDev_Unlock()"));
	}
	//----------------
}

#endif //SCVDEV_USE_HV