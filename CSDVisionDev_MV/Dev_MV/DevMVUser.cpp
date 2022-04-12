#include "StdAfx.h"

#include "DevMVUser.h"
#include "../../../AutoCSD_include/AutoCSD/HMIMsg.h"
#include "CameraApi.h"
#include "CameraGrabber.h"
#include "CameraImage.h"

//设表初始化

bool CDevMVUser::m_bInit=CDevMVUser::Init();

bool CDevMVUser::Init()
{
	return true;
}

//抓图线程
/*图像抓取回调函数*/
int __stdcall FrameListenerEntry(void* Grabber, int Phase, BYTE *pFrameBuffer, tSdkFrameHead* pFrameHead, void* Context)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (Phase == 1)
	{
		CDevMVUser *pThis = (CDevMVUser*)Context;
		ImageData temData;
		temData.pDataBuffer=pFrameBuffer;
		temData.nImgWidth=pFrameHead->iWidth;
		temData.nImgHeight=pFrameHead->iHeight;
		temData.nBitCount=1;
		pThis->frameReady(temData);

		return 1;
	}
}

//数据回调
void CDevMVUser::frameReady(ImageData Data)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString strTem;
	if (Data.pDataBuffer!=NULL)
	{
		//m_TriggerTimePtEnd=GetClock();
		//LARGE_INTEGER  litmp; 
		//LONGLONG         dfMinus, dfFreq, dfTim; 
		//QueryPerformanceFrequency(&litmp); 
		//dfFreq = litmp.QuadPart; 
		//dfMinus=m_TriggerTimePtEnd-m_TriggerTimePt;
		//if(dfMinus<0)
		//	dfMinus+=0xffffffffffffffff; 
		//dfTim =1000*dfMinus / dfFreq;  //拍照时间
		//CString strTemp;
		//strTemp.Format(_T("拍照时间软触发->收到图像：%d ms"),dfTim);
		
		SetConnectedFlag(true);
		scvVedioData((BYTE*)Data.pDataBuffer,
			Data.nImgWidth,
			Data.nImgHeight,
			Data.nBitCount,false);

		//m_TriggerTimePtEnd=GetClock();
		//dfMinus=m_TriggerTimePtEnd-m_TriggerTimePt;
		//if(dfMinus<0)
		//	dfMinus+=0xffffffffffffffff; 
		//dfTim =1000*dfMinus / dfFreq;  //拍照时间
		//CString strTemp2;
		//strTemp2.Format(_T("\r\n拍照时间软触发->送给SCV：%d ms"),dfTim);
		//HMIMsgBoxCenter(strTemp+strTemp2,HMI_MSG_OK);
	} 
	else
	{
		SetConnectedFlag(false);
		SetOpenedFlag(false);
	}
}

CDevMVUser::CDevMVUser(void)
{
	m_pSCVDevice=NULL;
	m_DeviceID = -1;
	m_vdDeviceName="";
	m_bIsDevOpened=false;
	m_bIsDevConnected=true;

	m_Width=640;

	m_hCamera=NULL;
	m_Height=480;

	//增益
	m_Gain=1;

	//曝光
	m_Exposure=4;

	//亮度
	m_Brightness=32;

	//对比度
	m_Contrast=100;

	m_FPS=155;

	m_Grabber = NULL;
	m_hCamera = NULL;

	m_Timer.resize(10);

	m_TriggerTimePt=0;
	m_TriggerTimePtEnd=0;
}
//****************定时器******************
LONGLONG CDevMVUser::GetClock()
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

void CDevMVUser::InitTimer(unsigned long TimerID,unsigned long bTime) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	unsigned long nTimerSize=m_Timer.size();

	if (TimerID<0||TimerID>=nTimerSize)
	{
		CString info;
		info.Format(_T("索引定时器ID号(%d)的范围不对"),TimerID);
		AfxMessageBox(info,MB_TOPMOST);
		return ;
	}
	if(!IsTimerEnd(TimerID))
	{
        CString info;
		info.Format(_T("索引定时器ID号(%d)+plc_IsTimerEnd没完成却去plc_initTimer初始化"),TimerID);
		AfxMessageBox(info,MB_TOPMOST);
		ASSERT(0);
	}

	ThreadTimerLock(); //线程锁
	m_Timer[TimerID].TimerStart=GetClock();
	m_Timer[TimerID].Time=bTime;
	ThreadTimerUnlock(); //线程锁
}
void CDevMVUser::ThreadTimerLock()
{
	m_CCriticalTimerSection.Lock();
}
void CDevMVUser::ThreadTimerUnlock()
{
	m_CCriticalTimerSection.Unlock();
}
bool CDevMVUser::IsTimerEnd(unsigned long TimerID) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	LARGE_INTEGER  litmp; 
	LONGLONG         dfMinus, dfFreq, dfTim; 
	QueryPerformanceFrequency(&litmp); 
	dfFreq = litmp.QuadPart; 

	unsigned long nTimerSize=m_Timer.size();

	if (TimerID<0||TimerID>=nTimerSize)
	{
		CString info;
		info.Format(_T("索引定时器ID号(%d)的范围不对"),TimerID);
		AfxMessageBox(info,MB_TOPMOST);
		return false;
	}

	ThreadTimerLock(); //线程锁
	m_Timer[TimerID].TimerEnd=GetClock();
	dfMinus=m_Timer[TimerID].TimerEnd-m_Timer[TimerID].TimerStart;
	if(dfMinus<0)
		dfMinus+=0xffffffffffffffff; 
	dfTim =1000*dfMinus / dfFreq; 

	bool Retn=false;
	if (dfTim>=m_Timer[TimerID].Time) //必须是下一个周期到来
	{
		m_Timer[TimerID].TimerStart=0;
		m_Timer[TimerID].TimerEnd=0;
		m_Timer[TimerID].Time=0;
		Retn=true;
	}
	else
	{
		Retn=false;
	}

	ThreadTimerUnlock(); //线程锁
	return Retn;
}

CDevMVUser::~CDevMVUser(void)
{
	if (m_Grabber != 0)
	{
		//Uninit the camera
		CameraGrabber_Destroy(m_Grabber);
		m_Grabber = 0;
		m_hCamera = 0;
	}
}

//读到相机的图像数据
void CDevMVUser::scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI)
{
   m_pSCVDevice->scvDev_VedioData(pData,width,height,bitCount,bROI);
}


void CDevMVUser::SetConnectedFlag(bool flag)
{
	Lock();
	m_bIsDevConnected=flag;
	UnLock();
}

bool CDevMVUser::GetConnectedFlag()
{
	bool flag=false;

	Lock();
	flag=m_bIsDevConnected;
	UnLock();

	return flag;
}

void CDevMVUser::SetOpenedFlag(bool flag)
{
	Lock();
	m_bIsDevOpened=flag;
	UnLock();
}
bool CDevMVUser::GetOpenedFlag()
{
	bool flag=false;

	Lock();
	flag=m_bIsDevOpened;
	UnLock();

	return flag;
}
//和SPLCDev设备的接口
void CDevMVUser::scvDevInterface(SCVDevStream *pSCVDevice)
{
    m_pSCVDevice=pSCVDevice;
}
//设置本相机的名称
long CDevMVUser::scvSetDeviceName(CString strName)
{
	long myRetn=SMCV_RETN_SUCCESS;

	CStringW strw = strName;
	CStringA stra(strw.GetBuffer(0));
	strw.ReleaseBuffer();
	m_vdDeviceName=stra.GetBuffer(0);
	stra.ReleaseBuffer();

	return myRetn;
}
long CDevMVUser::scvGetDeviceName(CString& strName)
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}
//设置本相机的ID
long CDevMVUser::scvSetDeviceID(int devID)
{
	long myRetn=SMCV_RETN_SUCCESS;

	m_DeviceID=devID;

	return myRetn;
}
long CDevMVUser::scvGetDeviceID(int& devID)
{
	long myRetn=SMCV_RETN_SUCCESS;

    devID=m_DeviceID;

	return myRetn;
}
//初始化设备控件库
long CDevMVUser::scvInitVedioLibrary()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//退出设备控件库
long CDevMVUser::scvExitVedioLibrary()
{
    long myRetn=SMCV_RETN_SUCCESS;
    
	return myRetn;
}

//暂时固定成640X480,如果需要自定义分辨率， 还需要提供ROI的起始地址坐标。光有宽和高信息还是不够。 所以这里暂时不处理。
long CDevMVUser::scvSetCamImageSize(unsigned long width,unsigned long height)
{
	long myRetn=SMCV_RETN_SUCCESS;
	m_Width=width;
	m_Height=height;
	return myRetn;
}

long CDevMVUser::scvOpenCamDevice()
{
	long myRetn=SMCV_RETN_SUCCESS;

	CameraSdkStatus status;

	//关闭
	scvCloseDevice();

	tSdkCameraDevInfo DevInfo[8];
	int nDev = ARRAYSIZE(DevInfo);
	CameraEnumerateDevice(DevInfo, &nDev);
	int Index = -1;
	for (int i = 0; i < nDev; ++i)
	{
		if (strcmp(m_vdDeviceName.c_str(), (char const*)DevInfo[i].acFriendlyName) == 0)
		{
			Index = i;
			break;
		}
	}
	if (Index < 0)
		return SMCV_RETN_FAILIURE;
	CameraSdkStatus retStatus=CameraGrabber_Create(&m_Grabber, &DevInfo[Index]);
	if ( retStatus != CAMERA_STATUS_SUCCESS)
		return SMCV_RETN_FAILIURE;
	m_DeviceID=Index;
	retStatus=CameraGrabber_GetCameraHandle(m_Grabber, &m_hCamera);
	
	retStatus=CameraGrabber_SetFrameListener(m_Grabber, FrameListenerEntry, this);

	scvSetTriggerMode(true);
	CameraSetMirror(m_hCamera,0,TRUE);
	CameraSetAeState(m_hCamera, FALSE);
	//获得该相机的特性描述
	CameraGetCapability(m_hCamera,&m_sCameraInfo);//获得相机的特性描述

	//设置ISP模块输出图像为8bit灰度格式。 默认是BGR24格式，如果要求高精度宽动态分析，可以设置为16ibt灰度或者48bit彩色模式。
	//不同的输出格式，后面的m_pFrameBuffer需要申请不同大小的缓冲区。 
	CameraSetIspOutFormat(m_hCamera,CAMERA_MEDIA_TYPE_MONO8);
	m_bMonoSensor = m_sCameraInfo.sIspCapacity.bMonoSensor; 

	SetConnectedFlag(true);
	SetOpenedFlag(true);

	return myRetn;
}

long CDevMVUser::scvCloseDevice()
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[2],tempTimeOut[2]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvCloseDevice()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	//反初始化相机
	if (m_Grabber != 0)
	{
		//Uninit the camera
		CameraGrabber_Destroy(m_Grabber);
		m_Grabber = 0;
		m_hCamera = 0;
	}
	
	SetOpenedFlag(false);
	
	return myRetn;
}

//迈德威视相机SDK内部自带重连功能，掉线5秒内自动重6连，无需外部再调用。
long CDevMVUser::scvOpenCamWhenLost()
{
	long myRetn=SMCV_RETN_SUCCESS;

	if (GetOpenedFlag())
	{
		return SMCV_RETN_SUCCESS;
	}
	scvOpenCamDevice();
	scvStartVedioLive();
	return myRetn;
}

//迈德威视相机SDK内部自带重连功能，自动的，无需外部再调用。
long CDevMVUser::scvOpenCamWhenLostEx()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//快照
long CDevMVUser::scvSetSnapMode(bool bMode)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}
long CDevMVUser::scvGetSnapMode(bool &mode)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}

//帧率
long CDevMVUser::scvSetFPS(double bFPS)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}
long CDevMVUser::scvGetFPS(double &fps)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	fps = 155;

	return myRetn;

}

//迈德威视的图像亮度可以通过伽马，对比度，增益和曝光来调解，Brightness需要对应哪一个?看华用的应该是对应伽马，
long CDevMVUser::scvSetBrightness(double bright)
{
	m_Brightness = (long)bright;

	int gamma = (int)bright;
	
	long myRetn=SMCV_RETN_SUCCESS;


	//---------指令监控
		if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
		{
			LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
				(tempTimeIn[4],tempTimeOut[4]);
			CString strOrder;
			strOrder.Format(_T("-%d-scvSetBrightness(%f)"),timeBetween,bright);
			m_HVDevOrderInfo.WriterOrder(strOrder);
		}
		//----------------
		
	//如果是伽马，用 CameraSetGamma(m_hCamera,gamma); gamm 默认值为100，表示不增强也不减弱。低于100为变亮，高于100变暗
	
	return myRetn;
}
long CDevMVUser::scvGetBrightness(double &bright)
{
	long myRetn=SMCV_RETN_SUCCESS;
	int gamma = 100;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//如果是伽马，用 CameraGetGamma(m_hCamera,&gamma);

	//---------指令监控
		if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
		{
			LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
				(tempTimeIn[5],tempTimeOut[5]);
			CString strOrder;
			strOrder.Format(_T("-%d-scvGetBrightness(%f)"),timeBetween,bright);
			m_HVDevOrderInfo.WriterOrder(strOrder);
		}
		//----------------
		
	bright = gamma;
	
	return myRetn;
}

//对比度
long CDevMVUser::scvSetContrast(double contrast)
{
	m_Contrast = (long)contrast;
	
	int c = (int )contrast;
	
	long myRetn=SMCV_RETN_SUCCESS;

	
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[6],tempTimeOut[6]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetContrast(%f)"),timeBetween,contrast);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
		
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	
	//注意，迈德威视相机对比度默认是100，表示不增强也不减弱，低于100减弱对比度，高于100增强对比度，范围为0到200.
	CameraSetContrast(m_hCamera,c);

	return myRetn;
}
long CDevMVUser::scvGetContrast(double &contrast)
{
	long myRetn=SMCV_RETN_SUCCESS;
	int c;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[7],tempTimeOut[7]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvGetContrast(%f)"),timeBetween,contrast);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	
	CameraGetContrast(m_hCamera,&c);
	
	contrast = (double)c;

	return myRetn;
}

//快门
long CDevMVUser::scvGetExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;


	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[8],tempTimeOut[8]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvGetExposureParm(%f)"),timeBetween,exposure);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	
	double t;
	
	CameraGetExposureTime(m_hCamera,&t);//t的单位是微秒，例如返回 2.234表示曝光时间是2.234个微秒 

	exposure=t*0.01;//请确认是否要换算单位。

	return myRetn;
}
long CDevMVUser::scvGetMaxExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[9],tempTimeOut[9]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvGetMaxExposureParm(%f)"),timeBetween,exposure);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

  
	double line_time;
	CameraGetExposureLineTime(m_hCamera, &line_time);

	exposure = line_time*m_sCameraInfo.sExposeDesc.uiExposeTimeMax*0.01;
	

	return myRetn;
}
long CDevMVUser::scvGetMinExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[10],tempTimeOut[10]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvGetMinExposureParm(%f)"),timeBetween,exposure);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}



	double line_time;
	CameraGetExposureLineTime(m_hCamera, &line_time);

	exposure = line_time*m_sCameraInfo.sExposeDesc.uiExposeTimeMin*0.01;
	
	return myRetn;
}



long CDevMVUser::scvSetExposureParm(long val)
{
	m_Exposure=val;

	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[11],tempTimeOut[11]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetExposureParm(%d)"),timeBetween,val);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	double exp = (double)val*100;//val的单位是什么，exp单位是微秒，这里要换算，注意。
	
	CameraSetExposureTime(m_hCamera,exp);
	 
	return myRetn;
}

//增益
long CDevMVUser::scvGetGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[12],tempTimeOut[12]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetExposureParm(%f)"),timeBetween,gain);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	
	int g=0;
	
    CameraGetAnalogGain(m_hCamera,&g);//这里得到的g需要乘以步进值就是放大的倍数了。

	
	gain = m_sCameraInfo.sExposeDesc.fAnalogGainStep * (double)g;//放大倍数
		
	return myRetn;
}
long CDevMVUser::scvGetMaxGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[13],tempTimeOut[13]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvGetMaxGainParm(%f)"),timeBetween,gain);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}


	gain=( (double) m_sCameraInfo.sExposeDesc.uiAnalogGainMax) *  m_sCameraInfo.sExposeDesc.fAnalogGainStep;//倍数

	return myRetn;
}

long CDevMVUser::scvGetMinGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;

	
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[14],tempTimeOut[14]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvGetMinGainParm(%f)"),timeBetween,gain);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	
	gain=( (double) m_sCameraInfo.sExposeDesc.uiAnalogGainMin) *  m_sCameraInfo.sExposeDesc.fAnalogGainStep;//倍数

	return myRetn;
}

long CDevMVUser::scvSetGain(long val)
{
	m_Gain=val;

	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[15],tempTimeOut[15]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetGain(%d)"),timeBetween,val);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	int step;
	step = (int)(((double)val )/ m_sCameraInfo.sExposeDesc.fAnalogGainStep);
	
	CameraSetAnalogGain(m_hCamera,step);
	
	return myRetn;
}

//视屏流转置
long CDevMVUser::scvsetFlipH()
{
	long myRetn=SMCV_RETN_SUCCESS;
	
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[16],tempTimeOut[16]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvsetFlipH()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	CameraSetMirror(m_hCamera, 0, TRUE);//FALSE表示取消水平翻转。TRUE为使能。
	
	return myRetn;
}
long CDevMVUser::scvsetFlipV()
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[17],tempTimeOut[17]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvsetFlipV()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	CameraSetMirror(m_hCamera, 1, TRUE);//FALSE表示取消垂直翻转。TRUE为使能。
	

	return myRetn;
}
//定时进入
void CDevMVUser::scvTimer()
{
	/*BYTE sn[32];
	CameraSdkStatus retval=CameraReadSN(m_hCamera,sn, 0);
	if (CAMERA_STATUS_SUCCESS!=retval)
	{
		SetConnectedFlag(false);
	}*/
}
//视频流开关
long CDevMVUser::scvIsLive(bool &isLive)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}
long CDevMVUser::scvStartVedioLive()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	CameraGrabber_StartLive(m_Grabber);
	

    return myRetn;
}
long CDevMVUser::scvStopVedioLive()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	CameraGrabber_StopLive(m_Grabber);
	
	return myRetn;
}

//触发,关联硬件
long CDevMVUser::scvSetTriggerMode(int trigger)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[18],tempTimeOut[18]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetTriggerMode(%d)"),timeBetween,trigger);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
//<<<<<<< .mine	
//=======>>>>>>> .theirs	//CameraSetTriggerMode(m_hCamera,trigger? 1:0);// 0表示连续模式 ，1表示软触发，2表示硬触发
	CameraSetTriggerMode(m_hCamera,trigger);// 0表示连续模式 ，1表示软触发，2表示硬触发

	unsigned int nRet;
	//CameraSetTriggerMode(m_hCamera,trigger? 1:0);// 0表示连续模式 ，1表示软触发，2表示硬触发
	switch(trigger)
	{
	case 0:
		CameraSetTriggerMode(m_hCamera,0);
		break;
	case 1:
		CameraSetTriggerMode(m_hCamera,1);
		break;
	case 2:
		CameraSetTriggerMode(m_hCamera,1);
		break;
	case 3:
		CameraSetTriggerMode(m_hCamera,1);
		break;
	}
	return myRetn;
}
long CDevMVUser::scvIsTriggerMode(int &trigger)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[19],tempTimeOut[19]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvIsTriggerMode()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	int mode;
	
	CameraGetTriggerMode(m_hCamera,&mode);// 0表示连续模式 ，1表示软触发，2表示硬触发

	trigger = (mode == 0? false:true);
		
	return myRetn;
}

//软触发一次。先确保相机是处于软触发模式。CameraSetTriggerMode(m_hCamera,1);可以设置为软触发
long CDevMVUser::scvTrigger()
{
	long myRetn=SMCV_RETN_SUCCESS;

	
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[20],tempTimeOut[20]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvTrigger()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	if (!GetOpenedFlag())
	{
		SetConnectedFlag(false);
		return SMCV_RETN_NOINIT;
	}
	CameraSoftTrigger(m_hCamera);
	m_TriggerTimePt=GetClock();
	return myRetn;
}

//设备是否连接
long CDevMVUser::scvIsConnected(bool &isConnect)
{
	long myRetn=SMCV_RETN_SUCCESS;
    isConnect=GetConnectedFlag();
	return myRetn;
}
bool CDevMVUser::scvSetDisConnected()
{
	long myRetn=SMCV_RETN_SUCCESS;
	SetConnectedFlag(false);
	SetOpenedFlag(false);
	return myRetn;
}

//获得当前设备的数目
long CDevMVUser::scvGetAvailableDevices(unsigned long &num)
{
	long myRetn=SMCV_RETN_SUCCESS;
	int counts = 0;
	
	counts = CameraEnumerateDeviceEx();

	num = (int) counts;
	
	return myRetn;
}

//获取设备的调度记录
long CDevMVUser::scvGetDevOrder(std::vector<CString>& orderList)
{
    long myRetn=SMCV_RETN_SUCCESS;

	orderList.clear();
	GetOrder(orderList);

	return myRetn;
}

void CDevMVUser::Lock()
{
   m_CCriticalSection.Lock();
}
void CDevMVUser::UnLock()
{
   m_CCriticalSection.Unlock();
}
