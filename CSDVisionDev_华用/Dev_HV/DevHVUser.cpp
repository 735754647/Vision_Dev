#include "StdAfx.h"

#if SCVDEV_USE_HV

#include "DevHVUser.h"
#include "../../../AutoCSD_include/AutoCSD/SMCVStruct.h"
#include "../../../AutoCSD_include/AutoCSD/HMIMsg.h"

//�豸���ʼ��
std::vector<DevHV2SCVMap> CDevHVUser::m_MapHVList;
bool CDevHVUser::m_bInit=CDevHVUser::Init();
bool CDevHVUser::Init()
{
	m_MapHVList.clear();
	return true;
}
//�ص��ַ�
int CDevHVUser::DevHVCallBack(pHVGigE_Img_i pCommuParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	for (unsigned long i=0;i<m_MapHVList.size();i++)
	{
		if (m_MapHVList[i].nDevId==pCommuParam->nDevId)
		{		
			m_MapHVList[i].pObj->frameReady(pCommuParam,m_MapHVList[i].pObj);
		}
	}

	return 0;
}

CDevHVUser::CDevHVUser(void)
{
	m_pSCVDevice=NULL;
	m_DeviceID=0;
	m_vdDeviceName="";
	m_bIsDevOpened=false;
	m_bIsDevConnected=true;
	m_bIsTriggerROIMode=false;
	m_bIsTriggerROISetted=false;

	m_Width=640;
	m_Height=480;

	//����
	m_Gain=4;

	//�ع�
	m_Exposure=4;

	//����
	m_Brightness=32;

	//�Աȶ�
	m_Contrast=32;

	m_FPS=30;

	m_TriggerTimePt=0;
	m_TriggerTimePtEnd=0;

	m_bIsTriggerMode=false;
}

CDevHVUser::~CDevHVUser(void)
{
}

//****************��ʱ��******************
LONGLONG CDevHVUser::GetClock()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	LONGLONG time=0;
	LARGE_INTEGER  litmp; 
	LONGLONG       QPart1;
	QueryPerformanceCounter(&litmp); 
	QPart1 = litmp.QuadPart; 
	time = (LONGLONG)(QPart1); 
	return time;
}
//���������ͼ������
void CDevHVUser::scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI)
{
   m_pSCVDevice->scvDev_VedioData(pData,width,height,bitCount,bROI);
}
void CDevHVUser::frameReady(pHVGigE_Img_i pCommuParam,CDevHVUser* pObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString strTem;
	if (pCommuParam->pDataBuffer!=NULL)
	{
		SetConnectedFlag(true);

		if (m_bIsTriggerROIMode)
		{
			//pCommuParam->nBitCount == 1 ʱ�������һ��ROI
			if(pCommuParam->nBitCount == 1)					
			{
				scvVedioData((BYTE*)pCommuParam->pDataBuffer,
					pCommuParam->nImgWidth,
					pCommuParam->nImgHeight,
					1,true);

				strTem.Format(_T("ROI��1֡ͼ���յ���%d,��%d"),pCommuParam->nImgWidth,pCommuParam->nImgHeight);
				WriteOrder(strTem);
			}

			if(pCommuParam->nBitCount == 2)					
			{
				scvVedioData((BYTE*)pCommuParam->pDataBuffer,
					pCommuParam->nImgWidth,
					pCommuParam->nImgHeight,
					1,false);

				strTem.Format(_T("ROI��2֡ͼ���յ���%d,��%d"),pCommuParam->nImgWidth,pCommuParam->nImgHeight);
				WriteOrder(strTem);
			}
		} 
		else //��ROIģʽ
		{
			//LARGE_INTEGER  litmp; 
			//LONGLONG         dfMinus, dfFreq, dfTim; 
			//QueryPerformanceFrequency(&litmp); 
			//dfFreq = litmp.QuadPart; 
			//m_TriggerTimePtEnd=GetClock();
			//dfMinus=m_TriggerTimePtEnd-m_TriggerTimePt;
			//if(dfMinus<0)
			//	dfMinus+=0xffffffffffffffff; 
			//dfTim =1000*dfMinus / dfFreq;  //����ʱ��
			//CString strTemp;
			//strTemp.Format(_T("����ʱ������->�յ�ͼ��%d ms"),dfTim);

			scvVedioData((BYTE*)pCommuParam->pDataBuffer,
				pCommuParam->nImgWidth,
				pCommuParam->nImgHeight,
				pCommuParam->nBitCount,false);

			strTem.Format(_T("��1֡ͼ���յ���%d,��%d"),pCommuParam->nImgWidth,pCommuParam->nImgHeight);
			WriteOrder(strTem);

			//m_TriggerTimePtEnd=GetClock();
			//dfMinus=m_TriggerTimePtEnd-m_TriggerTimePt;
			//if(dfMinus<0)
			//	dfMinus+=0xffffffffffffffff; 
			//dfTim =1000*dfMinus / dfFreq;  //����ʱ��
			//CString strTemp2;
			//strTemp2.Format(_T("\r\n����ʱ������->�͸�SCV��%d ms"),dfTim);
			//HMIMsgBoxCenter(strTemp+strTemp2,HMI_MSG_OK);
		}
	} 
	else
	{
		SetConnectedFlag(false);
		SetOpenedFlag(false);
	}
}
void CDevHVUser::SetConnectedFlag(bool flag)
{
	Lock();
	m_bIsDevConnected=flag;
	UnLock();
}
bool CDevHVUser::GetConnectedFlag()
{
	bool flag=false;

	Lock();
	flag=m_bIsDevConnected;
	UnLock();

	return flag;
}

void CDevHVUser::SetOpenedFlag(bool flag)
{
	Lock();
	m_bIsDevOpened=flag;
	UnLock();
}
bool CDevHVUser::GetOpenedFlag()
{
	bool flag=false;

	Lock();
	flag=m_bIsDevOpened;
	UnLock();

	return flag;
}
//��SPLCDev�豸�Ľӿ�
void CDevHVUser::scvDevInterface(SCVDevStream *pSCVDevice)
{
    m_pSCVDevice=pSCVDevice;
}
//���ñ����������
long CDevHVUser::scvSetDeviceName(CString strName)
{
	long myRetn=SMCV_RETN_SUCCESS;

#if SCVDEV_USE_HV  //��������豸

	CStringW strw = strName;
	CStringA stra(strw.GetBuffer(0));
	strw.ReleaseBuffer();
	m_vdDeviceName=stra.GetBuffer(0);
	stra.ReleaseBuffer();

#endif //SCVDEV_USE_IMGSOURCE

	return myRetn;
}
long CDevHVUser::scvGetDeviceName(CString& strName)
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}
//���ñ������ID
long CDevHVUser::scvSetDeviceID(int devID)
{
	long myRetn=SMCV_RETN_SUCCESS;

#if SCVDEV_USE_HV  //��������豸

	m_DeviceID=devID;

#endif //SCVDEV_USE_HV

	return myRetn;
}
long CDevHVUser::scvGetDeviceID(int& devID)
{
	long myRetn=SMCV_RETN_SUCCESS;

#if SCVDEV_USE_HV  //��������豸

    devID=m_DeviceID;

#endif //SCVDEV_USE_HV

	return myRetn;
}
//��ʼ���豸�ؼ���
long CDevHVUser::scvInitVedioLibrary()
{
	long myRetn=SMCV_RETN_SUCCESS;
	
	return myRetn;
}

//�˳��豸�ؼ���
long CDevHVUser::scvExitVedioLibrary()
{
    long myRetn=SMCV_RETN_SUCCESS;
	m_MapHVList.clear(); //Ҫ�����2016-5-24 �˳���ʱ����
	m_ObjMnger1D.clear();
	return myRetn;
}
long CDevHVUser::scvSetCamImageSize(unsigned long width,unsigned long height)
{
	long myRetn=SMCV_RETN_SUCCESS;
	m_Width=width;
	m_Height=height;
	return myRetn;
}
long CDevHVUser::scvOpenCamDevice()
{
	long myRetn=SMCV_RETN_SUCCESS;
	USER_CALLBACK_PROC pCallBack=&CDevHVUser::DevHVCallBack;

	HRESULT retval=0;
	CString strTemp;
 
	API_HV_CloseDevice(m_DeviceID);
    retval=API_HV_OpenDevice(m_DeviceID);
	if (S_OK!=retval)
	{
		/*strTemp.Format(_T("�����ʧ��API_HV_OpenDevice��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);*/
		SetConnectedFlag(false);
		SetOpenedFlag(false);
		return SMCV_RETN_FAILIURE;
	}
	retval=API_HV_DevCapInit(m_DeviceID);

#if !VSI_KMB_NET //��ǧ����
    retval=API_HV_SetPacketSize(1,m_DeviceID);
#endif 
	
	if (S_OK!=retval) 
	{
		/*strTemp.Format(_T("�����ʧ��API_HV_DevCapInit��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);*/
		SetConnectedFlag(false);
		SetOpenedFlag(false);
		return SMCV_RETN_FAILIURE;
	}
	API_HV_SetCallBack(pCallBack,m_DeviceID);
    API_HV_SetROI(0,0,m_Width,m_Height,m_DeviceID);
	DevHV2SCVMap temSCVMap;  //ѹ�����
	temSCVMap.nDevId=m_DeviceID;
	temSCVMap.pObj=this;
	m_MapHVList.push_back(temSCVMap);

	HVGigE_Video_i temImgSize;
	temImgSize.nStart_X=0;
	temImgSize.nStart_Y=0;
	temImgSize.nVideoWidth=m_Width;
	temImgSize.nVideoHeight=m_Height;
	m_bIsTriggerROIMode=false;
	m_bIsTriggerROISetted=false;
	retval=API_HV_SetResolution(temImgSize,m_DeviceID);
	if (S_OK!=retval)
	{
		/*strTemp.Format(_T("�����ʧ��API_HV_SetResolution��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);*/
		SetConnectedFlag(false);
		SetOpenedFlag(false);
		return SMCV_RETN_FAILIURE;
	}
	SetConnectedFlag(true);
	SetOpenedFlag(true);

	return myRetn;
}

long CDevHVUser::scvCloseDevice()
{
	long myRetn=SMCV_RETN_SUCCESS;

	API_HV_StopCapture(m_DeviceID);
	API_HV_CloseDevice(m_DeviceID);
	SetOpenedFlag(false);
	
	return myRetn;
}
//����֮�����´�
long CDevHVUser::scvOpenCamWhenLost()
{
	long myRetn=SMCV_RETN_SUCCESS;

	if (GetOpenedFlag()&&GetConnectedFlag())
	{
		return SMCV_RETN_SUCCESS;
	}
	scvOpenCamWhenLostEx();
	return myRetn;
}
long CDevHVUser::scvOpenCamWhenLostEx()
{
	long myRetn=SMCV_RETN_SUCCESS;

	HRESULT retval=0;
	USER_CALLBACK_PROC pCallBack=&CDevHVUser::DevHVCallBack;
	CString temStrName;
	temStrName.Format(_T("%d"),m_DeviceID);
#if AUTOCSD_DEBUG
	SPLC temPLC;
	temPLC.plc_WriteLogDebug(temStrName+_T("���scvOpenCamWhenLostEx IN"));
#endif

	API_HV_StopCapture(m_DeviceID);
	Sleep(20);
	API_HV_CloseDevice(m_DeviceID);
	Sleep(20);
	API_HV_DevCapRelease(m_DeviceID);
	Sleep(20);
	retval=API_HV_OpenDevice(m_DeviceID);
	if (S_OK!=retval)
	{
		API_HV_StopCapture(m_DeviceID);
		API_HV_CloseDevice(m_DeviceID);
		SetOpenedFlag(false);
		return SMCV_RETN_FAILIURE;
	}

	DevHV2SCVMap temSCVMap;  //ѹ�����
	temSCVMap.nDevId=m_DeviceID;
	temSCVMap.pObj=this;
	bool temRes=false;
	for (int i=0;i<m_MapHVList.size();i++)
	{
		if (m_DeviceID==m_MapHVList[i].nDevId)
		{
			temRes=true;
		}
	}
	if (!temRes||m_MapHVList.size()<1)
	{
		m_MapHVList.push_back(temSCVMap);
	}

	API_HV_DevCapInit(m_DeviceID);
	Sleep(20);
	API_HV_SetCallBack(pCallBack,m_DeviceID);
	API_HV_SetROI(0,0,m_Width,m_Height,m_DeviceID);
	Sleep(20);
	HVGigE_Video_i temImgSize;
	temImgSize.nStart_X=0;
	temImgSize.nStart_Y=0;
	temImgSize.nVideoWidth=m_Width;
	temImgSize.nVideoHeight=m_Height;
	m_bIsTriggerROIMode=false;
	m_bIsTriggerROISetted=false;
	retval=API_HV_SetResolution(temImgSize,m_DeviceID);
	Sleep(20);
	SetOpenedFlag(true);
	API_HV_SetPreviewSnapMode(0,0,m_DeviceID);
	Sleep(20);
	scvSetFPS(m_FPS);
	scvSetGain(m_Gain);
	scvSetExposureParm(m_Exposure);
	scvSetContrast(m_Contrast);
	scvSetBrightness(m_Brightness);
	Sleep(20);
	API_HV_StartCapture(m_DeviceID);
#if AUTOCSD_DEBUG
	SPLC temPLC1;
	temPLC1.plc_WriteLogDebug(temStrName+_T("���scvOpenCamWhenLostEx �˳�"));
#endif
	return myRetn;
}
//����
long CDevHVUser::scvSetSnapMode(bool bMode)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}
long CDevHVUser::scvGetSnapMode(bool &mode)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}

//֡��
long CDevHVUser::scvSetFPS(double bFPS)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	retval=API_HV_SetSnapTrigFreqImgCount(bFPS,1,m_DeviceID);
	m_FPS=bFPS;
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("����֡��ʧ��API_HV_SetSnapTrigFreqImgCount��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/
    
	return myRetn;
}
long CDevHVUser::scvGetFPS(double &fps)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	retval=API_HV_GetFrameRate(fps,m_DeviceID);
	fps=m_FPS;
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��ȡ֡��ʧ��API_HV_GetFrameRate��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/
	return myRetn;
}
//����
long CDevHVUser::scvSetBrightness(double bright)
{
	m_Brightness=bright;

	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	double temStep=1.94/64;
	float temBright=bright*temStep-0.94;
	HRESULT retval=0;
	CString strTemp;
	retval=API_HV_SetBrightnessFactor(temBright,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��������ʧ��API_HV_SetBrightnessFactor��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	return myRetn;
}
long CDevHVUser::scvGetBrightness(double &bright)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	double temStep=1.94/64;
	float temBright=0;
	HRESULT retval=0;
	CString strTemp;
	retval=API_HV_GetBrightnessFactor(temBright,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��������ʧ��API_HV_GetBrightnessFactor��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	bright=(temBright+0.94)/temStep;

	return myRetn;
}

//�Աȶ�
long CDevHVUser::scvSetContrast(double contrast)
{
	m_Contrast=contrast;

	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	double temStep=1.94/64;
	float temBright=contrast*temStep-0.94;
	HRESULT retval=0;
	CString strTemp;
	retval=API_HV_SetContrastFactor(temBright,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��������ʧ��API_HV_SetContrastFactor��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	return myRetn;
}
long CDevHVUser::scvGetContrast(double &contrast)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	double temStep=1.94/64;
	float temBright=0;
	HRESULT retval=0;
	CString strTemp;
	retval=API_HV_GetContrastFactor(temBright,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��������ʧ��API_HV_GetContrastFactor��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	contrast=(temBright+0.94)/temStep;

	return myRetn;
}
//����
long CDevHVUser::scvGetExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	
	HRESULT retval=0;
	CString strTemp;
	LONG temTime=0;
	retval=API_HV_GetSnapExpTime(&temTime,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��ȡ����ʧ��API_HV_GetSnapExpTime��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	exposure=temTime/100;

	return myRetn;
}
long CDevHVUser::scvGetMaxExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	HVGigE_Range_i temGainInfo;
	retval=API_HV_GetSnapExpTimeRange(&temGainInfo,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��ȡ���Ų���ʧ��API_HV_GetSnapExpTimeRange��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/
	
	exposure=temGainInfo.nMax/100;

	return myRetn;
}
long CDevHVUser::scvGetMinExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	HVGigE_Range_i temGainInfo;
	retval=API_HV_GetSnapExpTimeRange(&temGainInfo,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��ȡ���Ų���ʧ��API_HV_GetSnapExpTimeRange��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/
	
	exposure=temGainInfo.nMin/100;

	return myRetn;
}
long CDevHVUser::scvSetExposureParm(long val)
{
	m_Exposure=val;

	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	val=val*100;
	retval=API_HV_SetSnapExpTime(val,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("���ÿ���ʧ��API_HV_SetSnapExpTime��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/
	return myRetn;
}

//����
long CDevHVUser::scvGetGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	int nGainVal[5];
	retval=API_HV_GetGainValue(nGainVal,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��ȡ����ʧ��API_HV_GetGainValue��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	return myRetn;
}
long CDevHVUser::scvGetMaxGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	HVGigE_Range_i temGainInfo;
	retval=API_HV_GetGainRange(&temGainInfo,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��ȡ�������ʧ��API_HV_GetGainRange��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	gain=temGainInfo.nMax;

	return myRetn;
}
long CDevHVUser::scvGetMinGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	HVGigE_Range_i temGainInfo;
	retval=API_HV_GetGainRange(&temGainInfo,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��ȡ�������ʧ��API_HV_GetGainRange��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	gain=temGainInfo.nMin;

	return myRetn;
}
long CDevHVUser::scvSetGain(long val)
{
	m_Gain=val;

	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;
	int nGainVal[5];
	retval=API_HV_GetGainValue(nGainVal,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��������ʧ��API_HV_GetGainValue��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	nGainVal[0]=val;
	retval=API_HV_SetGainValue(nGainVal,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��������ʧ��API_HV_SetGainValue��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	return myRetn;
}

//������ת��
long CDevHVUser::scvsetFlipH()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}
long CDevHVUser::scvsetFlipV()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}

//��Ƶ������
long CDevHVUser::scvIsLive(bool &isLive)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}
long CDevHVUser::scvStartVedioLive()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;

	retval=API_HV_StartCapture(m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("�����ʧ��API_HV_StartCapture��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	retval=API_HV_SuspendCapture(false,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("�����ʧ��API_HV_SuspendCapture��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/
	

		return myRetn;
}
long CDevHVUser::scvStopVedioLive()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;

	retval=API_HV_StopCapture(m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("�����ʧ��API_HV_StopCapture��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	retval=API_HV_SuspendCapture(true,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("�����ʧ��API_HV_SuspendCapture��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	return myRetn;
}

//����,����Ӳ��
long CDevHVUser::scvSetTriggerMode(bool trigger)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;

	if(m_bIsTriggerMode!=trigger)
	{
		if (trigger)
		{
			retval=API_HV_SetPreviewSnapMode(0,0,m_DeviceID);
		}
		else
		{
			retval=API_HV_SetPreviewSnapMode(1,0,m_DeviceID);
		}
	}
	else
	{
		return SMCV_RETN_SUCCESS;
	}

	m_bIsTriggerMode=trigger;

	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("�������ģʽ����ʧ��API_HV_SetPreviewSnapMode��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	return myRetn;
}
long CDevHVUser::scvIsTriggerMode(bool &trigger)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HVGigE_PreSnap_State_i temState;

	HRESULT retval=0;
	CString strTemp;

	retval=API_HV_GetPreviewSnapMode(&temState,m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("��ȡ����ģʽʧ��API_HV_GetPreviewSnapMode��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	if (temState.nPreview)
	{
		trigger=false;
	}
	else
	{
        trigger=true;
	}

	return myRetn;
}

long CDevHVUser::scvSetTriggerROIMode(bool bROI)
{
	long myRetn=SMCV_RETN_SUCCESS;
	HRESULT retval=0;
	CString strTemp;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	if (!bROI)
	{
		//�κ��޸ķֱ��ʵĲ���һ����ֹͣ�ɼ�
		retval=API_HV_StopCapture(m_DeviceID);
		//retval=API_HV_SuspendCapture(TRUE,m_DeviceID);
		if (S_OK!=retval)
		{
			strTemp.Format(_T("scvSetTriggerROIModeʧ��API_HV_StopCapture��ID��%d"),m_DeviceID);
			AfxMessageBox(strTemp,MB_TOPMOST);
			return SMCV_RETN_FAILIURE;
		}

		//�˳�����ROIģʽ����������ֱ��ʣ��÷ֱ��ʿ�����ROI������ʱ��ROIֻ�����һ����
		retval=API_HV_SetROI(0,0,m_Width,m_Height,m_DeviceID);
		//retval=API_HV_SetSpecialROI(0,0,m_Width,m_Height,0,0,12,12,m_DeviceID);
		if (S_OK!=retval)
		{
			strTemp.Format(_T("scvSetTriggerROIModeʧ��API_HV_SetROI��ID��%d"),m_DeviceID);
			AfxMessageBox(strTemp,MB_TOPMOST);
			return SMCV_RETN_FAILIURE;
		}

		HVGigE_PreSnap_State_i temRetVal;
		retval=API_HV_GetPreviewSnapMode(&temRetVal,m_DeviceID);
		if (S_OK!=retval)
		{
			strTemp.Format(_T("scvSetTriggerROIModeʧ��API_HV_GetPreviewSnapMode��ID��%d"),m_DeviceID);
			AfxMessageBox(strTemp,MB_TOPMOST);
			return SMCV_RETN_FAILIURE;
		}

		//�˳�����ROIģʽ��,ģʽ���
		retval=API_HV_SetPreviewSnapMode(temRetVal.nPreview,temRetVal.nSnapMode,m_DeviceID);
		if (S_OK!=retval)
		{
			strTemp.Format(_T("scvSetTriggerROIModeʧ��API_HV_SetPreviewSnapMode��ID��%d"),m_DeviceID);
			AfxMessageBox(strTemp,MB_TOPMOST);
			return SMCV_RETN_FAILIURE;
		}

		//���ú��Ժ�ʼ�ɼ�
		retval=API_HV_StartCapture(m_DeviceID);
		//retval=API_HV_SuspendCapture(FALSE,m_DeviceID);
		if (S_OK!=retval)
		{
			strTemp.Format(_T("scvSetTriggerROIModeʧ��API_HV_StartCapture��ID��%d"),m_DeviceID);
			AfxMessageBox(strTemp,MB_TOPMOST);
			return SMCV_RETN_FAILIURE;
		}
	}
    m_bIsTriggerROIMode=bROI;
	return myRetn;
}
long CDevHVUser::scvIsTriggerROIMode(bool &bROI)
{
    long myRetn=SMCV_RETN_SUCCESS;

	bROI=m_bIsTriggerROIMode;

	return myRetn;
}
long CDevHVUser::scvTrigger()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;

	//ȫͼ����ģʽ
	if (m_bIsTriggerROIMode)
	{
		scvSetTriggerROIMode(false);
	}

	//����
	m_bIsTriggerROISetted=false;
	retval=API_HV_SnapSWTrigger(m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("����ʧ��API_HV_SnapSWTrigger��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/
	m_TriggerTimePt=GetClock();
	return myRetn;
}
long CDevHVUser::scvTriggerWithROI(CvRect rRectROI)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	HRESULT retval=0;
	CString strTemp;

	//ROI����ģʽ
	if (!m_bIsTriggerROIMode)
	{
		scvSetTriggerROIMode(true);
	}

	if (!m_bIsTriggerROISetted)
	{
		//�κ��޸ķֱ��ʵĲ���һ����ֹͣ�ɼ�
		retval=API_HV_StopCapture(m_DeviceID);
		//retval=API_HV_SuspendCapture(TRUE,m_DeviceID);

		//���������ROIģʽ
		unsigned long temX=rRectROI.x;
		unsigned long temY=rRectROI.y;
		unsigned long temWidth=rRectROI.width;
		unsigned long temHeight=rRectROI.height;

		retval=API_HV_SetSpecialROI(temX,temY,temWidth,temHeight,0,0,m_Width,m_Height,m_DeviceID);

		//����ROIģʽֻ���ڴ���ģʽ�²���Ч�����ҽ�����Ƶ�����ó�10000
		retval=API_HV_SetSnapTrigFreqImgCount(10000,1,m_DeviceID);
		retval=API_HV_SetPreviewSnapMode(0,0,m_DeviceID);

		//���ú��Ժ�ʼ�ɼ�
		retval=API_HV_StartCapture(m_DeviceID);
		//retval=API_HV_SuspendCapture(FALSE,m_DeviceID);

		m_bIsTriggerROISetted=true;
	}

	//����
	retval=API_HV_SnapSWTrigger(m_DeviceID);
	/*if (S_OK!=retval)
	{
		strTemp.Format(_T("����ʧ��API_HV_SnapSWTrigger��ID��%d"),m_DeviceID);
		AfxMessageBox(strTemp,MB_TOPMOST);
		return SMCV_RETN_FAILIURE;
	}*/

	return myRetn;
}
//�豸�Ƿ�����
long CDevHVUser::scvIsConnected(bool &isConnect)
{
	long myRetn=SMCV_RETN_SUCCESS;
    isConnect=GetConnectedFlag();
	return myRetn;
}

//��õ�ǰ�豸����Ŀ
long CDevHVUser::scvGetAvailableDevices(unsigned long &num)
{
	long myRetn=SMCV_RETN_SUCCESS;

	std::vector<unsigned long> temDevs;
	temDevs.clear();
	scvGetAvailableDevices(temDevs);

	num=temDevs.size();

	return myRetn;
}
//��ȡ�豸�ĵ��ȼ�¼
long CDevHVUser::scvGetDevOrder(std::vector<CString>& orderList)
{
    long myRetn=SMCV_RETN_SUCCESS;

	orderList.clear();
	GetOrder(orderList);

	return myRetn;
}
//д���豸��¼
long CDevHVUser::scvWriteDeviceOrder(CString orderList)
{
	long myRetn=SMCV_RETN_SUCCESS;
	WriteOrder(orderList);

	return myRetn;
}
//��õ�ǰ�豸����Ŀ
long CDevHVUser::scvGetAvailableDevices(std::vector<unsigned long>& dev)
{
	long Retn=SMCV_RETN_SUCCESS;

	HRESULT retval=0;
	CString strTemp;
	std::vector<unsigned long> temDevs;
	temDevs.clear();

	pHVGigE_Dev_i temDev;
	int temDevCount=0;
	API_HV_EnumerateDevice(&temDev,&temDevCount);

	for (int i=0;i<temDevCount;i++)
	{
		retval=API_HV_OpenDevice(i);
		if (S_OK==retval)
		{
			temDevs.push_back(i);
			API_HV_CloseDevice(i);
		}
	}
	dev=temDevs;

	return Retn;
}
void CDevHVUser::Lock()
{
   m_CCriticalSection.Lock();
}
void CDevHVUser::UnLock()
{
   m_CCriticalSection.Unlock();
}
#endif //SCVDEV_USE_HV
