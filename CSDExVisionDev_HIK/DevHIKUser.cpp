#include "StdAfx.h"

#include "DevHIKUser.h"
//#include "./HMIMsg.h"
//#include "HMIMsg.h"
#include "MvCameraControl.h"


//设表初始化

bool CDevHIKUser::m_bInit=CDevHIKUser::Init();

bool CDevHIKUser::Init()
{
	return true;
}
/*水平翻转图像*/
void FlipH(unsigned char *pData,unsigned char *pDstData,int H,int W)
{
	memset(pDstData,0,sizeof(unsigned char)*H*W);
	for(int i=0;i<H;i++)
	{
		for(int j=0;j<W;j++)
		{
			pDstData[i*W+j] = pData[i*W+W-j-1];
		}
	}

}
void SaveImageHik(unsigned char * pData,MV_FRAME_OUT_INFO* pFrameInfo)
{
	//图片数据输入输出参数            
	MV_SAVE_IMAGE_PARAM_EX stParam;

	//源数据                 
	stParam.pData         = pData;              //原始图像数据
	stParam.nDataLen      = pFrameInfo->nFrameLen;    //原始图像数据长度
	stParam.enPixelType   = pFrameInfo->enPixelType;  //原始图像数据的像素格式
	stParam.nWidth        = pFrameInfo->nWidth;       //图像宽
	stParam.nHeight       = pFrameInfo->nHeight;      //图像高 
	stParam.nJpgQuality   = 70;						  //JPEG图片编码质量  

	//目标数据
	stParam.enImageType   = MV_Image_Jpeg;            //需要保存的图像类型，转换成JPEG格式
	stParam.nBufferSize   = 1920*1080*3;             //存储节点的大小
	unsigned char* pImage = (unsigned char*)malloc(1920*1080*3);
	stParam.pImageBuffer  = pImage;                   //输出数据缓冲区，存放转换之后的图片数据         

	int nRet = MV_CC_SaveImageEx(&stParam);
	if(MV_OK != nRet)
	{
		return;
	}

	//将转换之后图片数据保存成文件
	FILE* fp = fopen("image.bmp", "wb");
	fwrite(pImage, 1, stParam.nImageLen, fp);
	fclose(fp);
	free(pImage);
}

void RGB2BGR(unsigned char *src, unsigned char *dst, int width, int height)
{
	memset(dst,0,sizeof(unsigned char)*width*height*3);
	unsigned char temp=0;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			//dst[i*width*3+j]=src[i*width*3+j+2];
			//dst[i*width*3+j+1]=src[i*width*3+j+1];
			//dst[i*width*3+j+2]=src[i*width*3+j];
			temp = *src;
			*src = *(src+2);
			*(src+2) = temp;
			src += 3;
		}
	}
}
//抓图线程
/*图像抓取回调函数*/
//void __stdcall ImageCallBack(unsigned char * pData, MV_FRAME_OUT_INFO* pFrameInfo, void* pUser)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	if(pFrameInfo)
//	{
//		CDevHIKUser *pThis = (CDevHIKUser*)pUser;
//		//需要水平翻转图像，取消注释
//		unsigned char *pDstData  =(unsigned char *) malloc(sizeof(unsigned char)*pFrameInfo->nHeight*pFrameInfo->nWidth*3);
//		ImageData tempData;
//		//FlipH(pData,pDstData,pFrameInfo->nHeight,pFrameInfo->nWidth);
//		if(pFrameInfo->enPixelType == PixelType_Gvsp_RGB8_Packed||pFrameInfo->enPixelType == PixelType_Gvsp_BGR8_Packed)
//		{
//			RGB2BGR(pData,pDstData,pFrameInfo->nWidth,pFrameInfo->nHeight);
//			tempData.pDataBuffer=pData;
//			tempData.nBitCount=3;
//		}
//		else
//		{
//			tempData.pDataBuffer = pData/*pDstData*/;
//			tempData.nBitCount=1;
//		}
//		tempData.nImgHeight = pFrameInfo->nHeight;
//		tempData.nImgWidth = pFrameInfo->nWidth;
//		pThis->frameReady(tempData);
//		free(pDstData);
//	}
//
//}
void __stdcall ImageCallBack(unsigned char * pData, MV_FRAME_OUT_INFO* pFrameInfo, void* pUser)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (pFrameInfo)
	{
		
		CDevHIKUser *pThis = (CDevHIKUser*)pUser;
		//需要水平翻转图像，取消注释
		//unsigned char *pDstData  =(unsigned char *) malloc(sizeof(unsigned char)*pFrameInfo->nHeight*pFrameInfo->nWidth);
		ImageData tempData;
		//FlipH(pData,pDstData,pFrameInfo->nHeight,pFrameInfo->nWidth);
		tempData.pDataBuffer = pData/*pDstData*/;
		tempData.nImgHeight = pFrameInfo->nHeight;
		tempData.nImgWidth = pFrameInfo->nWidth;
		tempData.nBitCount=1;
		pThis->frameReady(tempData);
		//free(pDstData);

	}

}
//数据回调
void CDevHIKUser::frameReady(ImageData Data)
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

CDevHIKUser::CDevHIKUser(void)
{
	m_pSCVDevice=NULL;
	m_DeviceID = -1;
	m_vdDeviceName="";
	m_bIsDevOpened=false;
	m_bIsDevConnected=true;
	m_bIsLive = false;
	m_bIsTriggerMode = 0;
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

	//m_Grabber = NULL;
	m_hCamera = NULL;

	m_Timer.resize(10);

	m_TriggerTimePt=0;
	m_TriggerTimePtEnd=0;
}
//****************定时器******************
LONGLONG CDevHIKUser::GetClock()
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

void CDevHIKUser::InitTimer(unsigned long TimerID,unsigned long bTime) 
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
void CDevHIKUser::ThreadTimerLock()
{
	m_CCriticalTimerSection.Lock();
}
void CDevHIKUser::ThreadTimerUnlock()
{
	m_CCriticalTimerSection.Unlock();
}
bool CDevHIKUser::IsTimerEnd(unsigned long TimerID) 
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

CDevHIKUser::~CDevHIKUser(void)
{

}

//读到相机的图像数据
void CDevHIKUser::scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI)
{
   m_pSCVDevice->scvDev_VedioData(pData,width,height,bitCount,bROI);
}


void CDevHIKUser::SetConnectedFlag(bool flag)
{
	Lock();
	m_bIsDevConnected=flag;
	UnLock();
}

bool CDevHIKUser::GetConnectedFlag()
{
	bool flag=false;

	Lock();
	flag=m_bIsDevConnected;
	UnLock();

	return flag;
}

void CDevHIKUser::SetOpenedFlag(bool flag)
{
	Lock();
	m_bIsDevOpened=flag;
	UnLock();
}
bool CDevHIKUser::GetOpenedFlag()
{
	bool flag=false;

	Lock();
	flag=m_bIsDevOpened;
	UnLock();

	return flag;
}
//和SPLCDev设备的接口
void CDevHIKUser::scvDevInterface(SCVDevStream *pSCVDevice)
{
    m_pSCVDevice=pSCVDevice;
}
//设置本相机的名称
long CDevHIKUser::scvSetDeviceName(CString strName)
{
	long myRetn=SMCV_RETN_SUCCESS;

	CStringW strw = strName;
	CStringA stra(strw.GetBuffer(0));
	strw.ReleaseBuffer();
	m_vdDeviceName=stra.GetBuffer(0);
	stra.ReleaseBuffer();

	return myRetn;
}
long CDevHIKUser::scvGetDeviceName(CString& strName)
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}
//设置本相机的ID
long CDevHIKUser::scvSetDeviceID(int devID)
{
	long myRetn=SMCV_RETN_SUCCESS;

	m_DeviceID=devID;

	return myRetn;
}
long CDevHIKUser::scvGetDeviceID(int& devID)
{
	long myRetn=SMCV_RETN_SUCCESS;

    devID=m_DeviceID;

	return myRetn;
}
//初始化设备控件库
long CDevHIKUser::scvInitVedioLibrary()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//退出设备控件库
long CDevHIKUser::scvExitVedioLibrary()
{
    long myRetn=SMCV_RETN_SUCCESS;
    
	return myRetn;
}

//暂时固定成640X480,如果需要自定义分辨率， 还需要提供ROI的起始地址坐标。光有宽和高信息还是不够。 所以这里暂时不处理。
long CDevHIKUser::scvSetCamImageSize(unsigned long width,unsigned long height)
{
	long myRetn=SMCV_RETN_SUCCESS;
	m_Width=width;
	m_Height=height;
	return myRetn;
}

long CDevHIKUser::scvOpenCamDevice()
{
	int nRet1 = MV_CC_CloseDevice(m_hCamera);
	if (MV_OK != nRet1)
	{
		//printf("MV_CC_CloseDevice fail! nRet [%x]\n", nRet1);
		//return -1;
	}

	// 9.销毁句柄
	nRet1 = MV_CC_DestroyHandle(m_hCamera);
	if (MV_OK != nRet1)
	{
		//printf("MV_CC_DestroyHandle fail! nRet [%x]\n", nRet1);
		//return -1;
	}
	long myRetn=SMCV_RETN_SUCCESS;

	unsigned int nTLaysType = MV_GIGE_DEVICE|MV_USB_DEVICE;

	//1 枚举设备
	MV_CC_DEVICE_INFO_LIST m_stDeviceList = {0};
	int nRet = MV_CC_EnumDevices(nTLaysType,&m_stDeviceList);
	if(MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	
	int Index = -1;
	if(m_stDeviceList.nDeviceNum > 0)
	{
		for (int i = 0; i < m_stDeviceList.nDeviceNum; ++i)
		{
			if(strcmp(m_vdDeviceName.c_str(),
				(const char*)m_stDeviceList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.chUserDefinedName) == 0||
				strcmp(m_vdDeviceName.c_str(),
				(const char*)m_stDeviceList.pDeviceInfo[i]->SpecialInfo.stUsb3VInfo.chUserDefinedName) == 0)
			{
				Index = i;
				break;
			}
		}
	}
	else//枚举设备数为0，打开失败
	{
		return SMCV_RETN_FAILIURE;
	}

	if(Index < 0)//没有找到相机
	{
		return SMCV_RETN_FAILIURE;
	}
	//2 生成操作句柄
	//memset(&m_sDeviceInfo,0,sizeof(MV_CC_DEVICE_INFO));
	memcpy(&m_sDeviceInfo,m_stDeviceList.pDeviceInfo[Index],sizeof(MV_CC_DEVICE_INFO));
	nRet = MV_CC_CreateHandle(&m_hCamera,&m_sDeviceInfo);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}

	//3 注册回调函数
	nRet = MV_CC_RegisterImageCallBack(m_hCamera,ImageCallBack,this);
	if(MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}

	//4 打开设备
	unsigned int nAccessMode = MV_ACCESS_Exclusive;
	unsigned short nSwitchOverKey = 0;
	TRY 
	{
		nRet = MV_CC_OpenDevice(m_hCamera, nAccessMode, nSwitchOverKey);
	}
	CATCH (CMemoryException, e)
	{
		AfxMessageBox(_T("打开相机失败！"));
		return SMCV_RETN_FAILIURE;
	}
	END_CATCH
	if(nRet != MV_OK)
	{
		AfxMessageBox(_T("打开相机失败！"));
		return SMCV_RETN_FAILIURE;
	}
	//
	unsigned int nVal = 0;
	//unsigned int nVal1= 0;
	MVCC_INTVALUE nVal1;
	
	MV_CC_GetIntValue(m_hCamera, "Width", &nVal1);
	if (nVal1.nCurValue==1280)
	{
		
		nVal = MV_CC_SetIntValue(m_hCamera, "Width", 640);
		nVal = MV_CC_SetIntValue(m_hCamera, "Height", 480);
		Sleep(100);
		nVal = MV_CC_SetIntValue(m_hCamera, "OffsetX", 320);
		nVal = MV_CC_SetIntValue(m_hCamera, "OffsetY", 272);
		
		/*unsigned int enValue = PixelType_Gvsp_Mono8;
		nRet = MV_CC_SetPixelFormat(m_hCamera, enValue);*/
	}
	/*nVal=MV_CC_SetIntValue(m_hCamera, "Width", 640);
	nVal=MV_CC_SetIntValue(m_hCamera, "Height", 480);*/

	
	if (MV_OK != nRet)
	{

	}
	//5 设置采集模式
	
	nRet = MV_CC_SetTriggerMode(m_hCamera,1);
	if(nRet != MV_OK)
	{
		return SMCV_RETN_FAILIURE;
	}
	//scvSetTriggerMode(true);
	//设置触发源
	nRet = MV_CC_SetTriggerSource(m_hCamera,MV_TRIGGER_SOURCE_SOFTWARE);
	if(nRet != MV_OK)
	{
		return SMCV_RETN_FAILIURE;
	}
	
	//6 设置相图像像素格式
	//unsigned int enValue = PixelType_Gvsp_Mono8;
	//unsigned int enValue = PixelType_Gvsp_RGB8_Packed;
	//nRet = MV_CC_SetPixelFormat(m_hCamera,enValue);
	//if(nRet != MV_OK)
	//{
	//	return SMCV_RETN_FAILIURE;
	//}
	unsigned int enMode = MV_GAMMA_SELECTOR_USER; //设置Gamma类型为USER
	nRet = MV_CC_SetGammaSelector(m_hCamera, enMode);
	if(nRet != MV_OK)
	{
		return SMCV_RETN_FAILIURE;
	}

	m_bMonoSensor = true;

	SetConnectedFlag(true);
	SetOpenedFlag(true);

	return myRetn;
}

long CDevHIKUser::scvCloseDevice()
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
	if (m_hCamera)
	{
		//Uninit the camera
		unsigned int nRet = MV_CC_CloseDevice(m_hCamera);
		if (MV_OK != nRet)
		{
			return SMCV_RETN_FAILIURE;
		}
		nRet = MV_CC_DestroyHandle(m_hCamera);
		if (MV_OK != nRet)
		{
			return SMCV_RETN_FAILIURE;
		}
		m_bIsLive = false;
		m_bIsDevOpened = false;
	}
	SetOpenedFlag(false);
	return myRetn;
}
//海康威视相机SDK没有自动重连功能，不确定是否可用
//迈德威视相机SDK内部自带重连功能，掉线5秒内自动重6连，无需外部再调用。
long CDevHIKUser::scvOpenCamWhenLost()
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
long CDevHIKUser::scvOpenCamWhenLostEx()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//快照
long CDevHIKUser::scvSetSnapMode(bool bMode)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}
long CDevHIKUser::scvGetSnapMode(bool &mode)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}

//帧率
long CDevHIKUser::scvSetFPS(double bFPS)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[4],tempTimeOut[4]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetFPS(%f)"),timeBetween,bFPS);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	unsigned int nRet = MV_CC_SetFrameRate(m_hCamera, bFPS);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_FPS = bFPS;
	return myRetn;
}
long CDevHIKUser::scvGetFPS(double &fps)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[4],tempTimeOut[4]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvGetFPS(%f)"),timeBetween,fps);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	MVCC_FLOATVALUE struFloatValue = {0}; 
	unsigned int nRet = MV_CC_GetFrameRate(m_hCamera, &struFloatValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	fps = struFloatValue.fCurValue;

	return myRetn;

}

//图像亮度信息
long CDevHIKUser::scvSetBrightness(double bright)
{
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
	MVCC_INTVALUE struIntValue = {0};
	//struIntValue.nCurValue=bright/100*16;
	//unsigned int temBright=bright/100*15;
	unsigned int temBright = bright;
	 int nRet = MV_CC_SetBrightness(m_hCamera, (unsigned int)temBright);
	//unsigned int nRet=MV_CC_SetFloatValue(m_hCamera, ("Brightness"), (unsigned int)temBright);
//#define MV_E_HANDLE             0x80000000  ///< 错误或无效的句柄
//#define MV_E_SUPPORT            0x80000001  ///< 不支持的功能
//#define MV_E_BUFOVER            0x80000002  ///< 缓存已满
//#define MV_E_CALLORDER          0x80000003  ///< 函数调用顺序错误
//#define MV_E_PARAMETER          0x80000004  ///< 错误的参数
//#define MV_E_RESOURCE           0x80000006  ///< 资源申请失败
//#define MV_E_NODATA             0x80000007  ///< 无数据
//#define MV_E_PRECONDITION       0x80000008  ///< 前置条件有误，或运行环境已发生变化
//#define MV_E_VERSION            0x80000009  ///< 版本不匹配
//#define MV_E_NOENOUGH_BUF       0x8000000A  ///< 传入的内存空间不足
//#define MV_E_ABNORMAL_IMAGE     0x8000000B  ///< 异常图像，可能是丢包导致图像不完整
//#define MV_E_UNKNOW             0x800000FF  ///< 未知的错误
	 int a=0;
	 switch(nRet)
	 {
	 case MV_E_HANDLE:
		 a=0;
		 break;
	 case MV_E_SUPPORT:
		 a=0;
		 break;
	 case MV_E_BUFOVER:
		 a=0;
		 break;
	 case MV_E_CALLORDER:
		 a=0;
		 break;
	 case MV_E_PARAMETER:
		 a=0;
		 break;
	 case MV_E_RESOURCE:
		 a=0;
		 break;
	 case MV_E_NODATA:
		 a=0;
		 break;
	 case MV_E_PRECONDITION:
		 a=0;
		 break;
	 case MV_E_VERSION:
		 a=0;
		 break;
	 case MV_E_NOENOUGH_BUF:
		 a=0;
		 break;
	 case MV_E_ABNORMAL_IMAGE:
		 a=0;
		 break;
	 case MV_E_UNKNOW:
		 a=0;
		 break;
	 default:
		 a=0;
		 break;
	 }
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_Brightness = (long)bright;
	return myRetn;
}
long CDevHIKUser::scvGetBrightness(double &bright)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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
	MVCC_INTVALUE struIntValue = {0};

	unsigned int nRet = MV_CC_GetBrightness(m_hCamera, &struIntValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	bright = struIntValue.nCurValue/16*100;

	return myRetn;
}

//对比度.海康威视相机没有对比度设置获取SDK
long CDevHIKUser::scvSetContrast(double contrast)
{
	m_Contrast = (long)contrast;
	
	int c = (int )contrast;
	
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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
	MVCC_FLOATVALUE struFloatValue = {0}; 

	unsigned int nRet = MV_CC_GetGamma(m_hCamera, &struFloatValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	//nRet=MV_CC_SetFloatValue(m_hCamera, "Gamma ", contrast/100.0*4);
	nRet = MV_CC_SetGamma(m_hCamera, contrast/100.0*4);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	return myRetn;
}
long CDevHIKUser::scvGetContrast(double &contrast)
{
	long myRetn=SMCV_RETN_SUCCESS;
	int c;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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
	MVCC_FLOATVALUE struFloatValue = {0}; 
	unsigned int nRet = MV_CC_GetGamma(m_hCamera, &struFloatValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	contrast = struFloatValue.fCurValue/4*100.0;
	return myRetn;
}

//快门
long CDevHIKUser::scvGetExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;

	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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
	MVCC_FLOATVALUE struFloatValue = {0}; 
	unsigned int nRet = MV_CC_GetExposureTime(m_hCamera, &struFloatValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	exposure = struFloatValue.fCurValue*0.01;

	return myRetn;
}
long CDevHIKUser::scvGetMaxExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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
	MVCC_INTVALUE struIntValue = {0};
	unsigned int nRet = MV_CC_GetAutoExposureTimeUpper(m_hCamera, &struIntValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	exposure = struIntValue.nCurValue*0.01;
	return myRetn;
}
long CDevHIKUser::scvGetMinExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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
	MVCC_INTVALUE struIntValue = {0}; 
	unsigned int nRet = MV_CC_GetAutoExposureTimeLower(m_hCamera, &struIntValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	exposure = struIntValue.nCurValue*0.01;
	
	return myRetn;
}



long CDevHIKUser::scvSetExposureParm(long val)
{
	m_Exposure=val;

	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//---------指令监控
	//if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	//{
	//	LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
	//		(tempTimeIn[11],tempTimeOut[11]);
	//	CString strOrder;
	//	strOrder.Format(_T("-%d-scvSetExposureParm(%d)"),timeBetween,val);
	//	m_HVDevOrderInfo.WriterOrder(strOrder);
	//}
	//----------------
	unsigned int nRet=MV_CC_SetFloatValue(m_hCamera, "ExposureTime", val*100);
	//unsigned int nRet= MV_CC_SetExposureTime(m_hCamera, val*100);//val单位为100us。
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	} 
	return myRetn;
}

//增益
long CDevHIKUser::scvGetGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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
	MVCC_FLOATVALUE struFloatValue = {0};

	unsigned int nRet = MV_CC_GetGain(m_hCamera, &struFloatValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	gain = struFloatValue.fCurValue/15*100;

	return myRetn;
}
long CDevHIKUser::scvGetMaxGainParm(double& gain)
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
	MVCC_FLOATVALUE struFloatValue = {0};

	unsigned int nRet = MV_CC_GetGain(m_hCamera, &struFloatValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	gain = struFloatValue.fMax;
	m_MaxGain = struFloatValue.fMax;

	return myRetn;
}

long CDevHIKUser::scvGetMinGainParm(double& gain)
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
	MVCC_FLOATVALUE struFloatValue = {0};

	unsigned int nRet = MV_CC_GetGain(m_hCamera, &struFloatValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	gain = struFloatValue.fMin;
	m_MinGain = struFloatValue.fMin;
	return myRetn;
}

long CDevHIKUser::scvSetGain(long val)
{
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
	if (val>=15)
	{
		val = 14;
		//return myRetn;
	}
	float fValue = (float)val;
	unsigned int nRet=MV_CC_SetFloatValue(m_hCamera, "Gain", fValue);
	//unsigned int nRet = MV_CC_SetGain(m_hCamera, fValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_Gain=fValue;
	return myRetn;
}

//设置相机格式
long CDevHIKUser::scvSetImageFormat(long channels)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[15],tempTimeOut[15]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetImageFormat(%d)"),timeBetween,channels);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	unsigned int enValue = PixelType_Gvsp_Mono8;
	if(channels==3)
	{
		enValue = PixelType_Gvsp_RGB8_Packed;
	}
	unsigned nRet = MV_CC_SetPixelFormat(m_hCamera,enValue);
	if(MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	return myRetn;
}

//获取相机格式
long CDevHIKUser::scvGetImageFormat(long& _format)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[15],tempTimeOut[15]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetImageFormat(%d)"),timeBetween,_format);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	MVCC_ENUMVALUE struEnumValue = {0};
	unsigned nRet = MV_CC_GetPixelFormat(m_hCamera,&struEnumValue);
	if(MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	if(struEnumValue.nCurValue == PixelType_Gvsp_Mono8)
	{
		_format = 1;
	}
	else if(struEnumValue.nCurValue == PixelType_Gvsp_BGR8_Packed)
	{
		_format = 3;
	}
	return myRetn;
}

//视屏流转置
long CDevHIKUser::scvsetFlipH()
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

	
	return myRetn;
}
long CDevHIKUser::scvsetFlipV()
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
	
	return myRetn;
}
//定时进入
void CDevHIKUser::scvTimer()
{
	/*BYTE sn[32];
	CameraSdkStatus retval=CameraReadSN(m_hCamera,sn, 0);
	if (CAMERA_STATUS_SUCCESS!=retval)
	{
		SetConnectedFlag(false);
	}*/
}
//视频流开关
long CDevHIKUser::scvIsLive(bool &isLive)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	if(!m_bIsLive)
	{
		return SMCV_RETN_FAILIURE;
	}
	return myRetn;
}
long CDevHIKUser::scvStartVedioLive()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//开始采集
	unsigned int nRet = MV_CC_StartGrabbing(m_hCamera);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_bIsLive = true;

    return myRetn;
}
long CDevHIKUser::scvStopVedioLive()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	//停止采集
	unsigned int nRet = MV_CC_StopGrabbing(m_hCamera);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_bIsLive = false;
	return myRetn;
}

//触发,关联硬件
long CDevHIKUser::scvSetTriggerMode(int trigger)
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
	
	unsigned int nRet;
//	unsigned int nRet = MV_CC_SetTriggerMode(m_hCamera, (trigger)?1:0);//1表示打开触发模式，0表示关闭触发模式
	switch(trigger)
	{
	case 0:
		nRet = MV_CC_SetTriggerMode(m_hCamera,MV_TRIGGER_MODE_ON);
		nRet = MV_CC_SetTriggerSource(m_hCamera,MV_TRIGGER_SOURCE_SOFTWARE);
		break;
	case 1:
		nRet = MV_CC_SetTriggerMode(m_hCamera,MV_TRIGGER_MODE_ON);
		nRet = MV_CC_SetTriggerSource(m_hCamera,MV_TRIGGER_SOURCE_SOFTWARE);
		break;
	case 2:
	//	nRet = MV_CC_SetTriggerMode(m_hCamera,MV_TRIGGER_MODE_ON);
	//	nRet = MV_CC_SetTriggerSource(m_hCamera,MV_TRIGGER_SOURCE_LINE0);
		nRet = MV_CC_SetTriggerMode(m_hCamera,MV_TRIGGER_MODE_OFF);
		break;
	case 3:
		nRet = MV_CC_SetTriggerMode(m_hCamera,MV_TRIGGER_MODE_ON);
		nRet = MV_CC_SetTriggerSource(m_hCamera,MV_TRIGGER_SOURCE_LINE0);
		break;
	}
	 
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	 m_bIsTriggerMode=trigger;


	//m_bIsTriggerMode = (trigger)?true:false;

	return myRetn;
}
long CDevHIKUser::scvIsTriggerMode(int &trigger)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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
	MVCC_ENUMVALUE struEnumValue = {0};
	unsigned int nRet = MV_CC_GetTriggerMode(m_hCamera, &struEnumValue);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	trigger=m_bIsTriggerMode;	//@zz 兼容硬触发，没用读取相机参数，而是变量值	17.08.16
	//trigger = (struEnumValue.nCurValue == 1? true:false);	

	return myRetn;
}

//软触发一次。先确保相机是处于软触发模式。CameraSetTriggerMode(m_hCamera,1);可以设置为软触发
long CDevHIKUser::scvTrigger()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		SetConnectedFlag(false);
		return SMCV_RETN_NOINIT;
	}
	//---------指令监控
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //监控处理
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[20],tempTimeOut[20]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvTrigger()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}

	if (m_bIsTriggerMode!=3)
	{
		//软触发
		unsigned int nRet = MV_CC_TriggerSoftwareExecute(m_hCamera);
		if (MV_OK != nRet)
		{
			return SMCV_RETN_FAILIURE;
		}
	}

	m_TriggerTimePt=GetClock();
	return myRetn;
}

//设备是否连接
long CDevHIKUser::scvIsConnected(bool &isConnect)
{
	long myRetn=SMCV_RETN_SUCCESS;
    isConnect=GetConnectedFlag();
	return myRetn;
}

bool CDevHIKUser::scvSetDisConnected(bool isConnect)
{
	long myRetn=SMCV_RETN_SUCCESS;
	SetConnectedFlag(false);
	SetOpenedFlag(false);
	return myRetn;
}


//获得当前设备的数目
long CDevHIKUser::scvGetAvailableDevices(unsigned long &num)
{
	long myRetn=SMCV_RETN_SUCCESS;

	unsigned int nTLayerType = MV_GIGE_DEVICE | MV_USB_DEVICE;
	MV_CC_DEVICE_INFO_LIST m_stDevList = {0};
	int nRet = MV_CC_EnumDevices(nTLayerType, &m_stDevList);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}

	num = m_stDevList.nDeviceNum;
	return myRetn;
}

//获取设备的调度记录
long CDevHIKUser::scvGetDevOrder(std::vector<CString>& orderList)
{
    long myRetn=SMCV_RETN_SUCCESS;

	orderList.clear();
	GetOrder(orderList);

	return myRetn;
}

void CDevHIKUser::Lock()
{
   m_CCriticalSection.Lock();
}
void CDevHIKUser::UnLock()
{
   m_CCriticalSection.Unlock();
}
