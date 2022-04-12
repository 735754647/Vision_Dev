#include "StdAfx.h"

#include "DevHIKUser.h"
//#include "./HMIMsg.h"
//#include "HMIMsg.h"
#include "MvCameraControl.h"


//����ʼ��

bool CDevHIKUser::m_bInit=CDevHIKUser::Init();

bool CDevHIKUser::Init()
{
	return true;
}
/*ˮƽ��תͼ��*/
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
	//ͼƬ���������������            
	MV_SAVE_IMAGE_PARAM_EX stParam;

	//Դ����                 
	stParam.pData         = pData;              //ԭʼͼ������
	stParam.nDataLen      = pFrameInfo->nFrameLen;    //ԭʼͼ�����ݳ���
	stParam.enPixelType   = pFrameInfo->enPixelType;  //ԭʼͼ�����ݵ����ظ�ʽ
	stParam.nWidth        = pFrameInfo->nWidth;       //ͼ���
	stParam.nHeight       = pFrameInfo->nHeight;      //ͼ��� 
	stParam.nJpgQuality   = 70;						  //JPEGͼƬ��������  

	//Ŀ������
	stParam.enImageType   = MV_Image_Jpeg;            //��Ҫ�����ͼ�����ͣ�ת����JPEG��ʽ
	stParam.nBufferSize   = 1920*1080*3;             //�洢�ڵ�Ĵ�С
	unsigned char* pImage = (unsigned char*)malloc(1920*1080*3);
	stParam.pImageBuffer  = pImage;                   //������ݻ����������ת��֮���ͼƬ����         

	int nRet = MV_CC_SaveImageEx(&stParam);
	if(MV_OK != nRet)
	{
		return;
	}

	//��ת��֮��ͼƬ���ݱ�����ļ�
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
//ץͼ�߳�
/*ͼ��ץȡ�ص�����*/
//void __stdcall ImageCallBack(unsigned char * pData, MV_FRAME_OUT_INFO* pFrameInfo, void* pUser)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	if(pFrameInfo)
//	{
//		CDevHIKUser *pThis = (CDevHIKUser*)pUser;
//		//��Ҫˮƽ��תͼ��ȡ��ע��
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
		//��Ҫˮƽ��תͼ��ȡ��ע��
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
//���ݻص�
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
		//dfTim =1000*dfMinus / dfFreq;  //����ʱ��
		//CString strTemp;
		//strTemp.Format(_T("����ʱ������->�յ�ͼ��%d ms"),dfTim);
		
		SetConnectedFlag(true);
		scvVedioData((BYTE*)Data.pDataBuffer,
			Data.nImgWidth,
			Data.nImgHeight,
			Data.nBitCount,false);

		//m_TriggerTimePtEnd=GetClock();
		//dfMinus=m_TriggerTimePtEnd-m_TriggerTimePt;
		//if(dfMinus<0)
		//	dfMinus+=0xffffffffffffffff; 
		//dfTim =1000*dfMinus / dfFreq;  //����ʱ��
		//CString strTemp2;
		//strTemp2.Format(_T("\r\n����ʱ������->�͸�SCV��%d ms"),dfTim);
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

	//����
	m_Gain=1;

	//�ع�
	m_Exposure=4;

	//����
	m_Brightness=32;

	//�Աȶ�
	m_Contrast=100;

	m_FPS=155;

	//m_Grabber = NULL;
	m_hCamera = NULL;

	m_Timer.resize(10);

	m_TriggerTimePt=0;
	m_TriggerTimePtEnd=0;
}
//****************��ʱ��******************
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
		info.Format(_T("������ʱ��ID��(%d)�ķ�Χ����"),TimerID);
		AfxMessageBox(info,MB_TOPMOST);
		return ;
	}
	if(!IsTimerEnd(TimerID))
	{
        CString info;
		info.Format(_T("������ʱ��ID��(%d)+plc_IsTimerEndû���ȴȥplc_initTimer��ʼ��"),TimerID);
		AfxMessageBox(info,MB_TOPMOST);
		ASSERT(0);
	}

	ThreadTimerLock(); //�߳���
	m_Timer[TimerID].TimerStart=GetClock();
	m_Timer[TimerID].Time=bTime;
	ThreadTimerUnlock(); //�߳���
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
		info.Format(_T("������ʱ��ID��(%d)�ķ�Χ����"),TimerID);
		AfxMessageBox(info,MB_TOPMOST);
		return false;
	}

	ThreadTimerLock(); //�߳���
	m_Timer[TimerID].TimerEnd=GetClock();
	dfMinus=m_Timer[TimerID].TimerEnd-m_Timer[TimerID].TimerStart;
	if(dfMinus<0)
		dfMinus+=0xffffffffffffffff; 
	dfTim =1000*dfMinus / dfFreq; 

	bool Retn=false;
	if (dfTim>=m_Timer[TimerID].Time) //��������һ�����ڵ���
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

	ThreadTimerUnlock(); //�߳���
	return Retn;
}

CDevHIKUser::~CDevHIKUser(void)
{

}

//���������ͼ������
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
//��SPLCDev�豸�Ľӿ�
void CDevHIKUser::scvDevInterface(SCVDevStream *pSCVDevice)
{
    m_pSCVDevice=pSCVDevice;
}
//���ñ����������
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
//���ñ������ID
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
//��ʼ���豸�ؼ���
long CDevHIKUser::scvInitVedioLibrary()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//�˳��豸�ؼ���
long CDevHIKUser::scvExitVedioLibrary()
{
    long myRetn=SMCV_RETN_SUCCESS;
    
	return myRetn;
}

//��ʱ�̶���640X480,�����Ҫ�Զ���ֱ��ʣ� ����Ҫ�ṩROI����ʼ��ַ���ꡣ���п�͸���Ϣ���ǲ����� ����������ʱ������
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

	// 9.���پ��
	nRet1 = MV_CC_DestroyHandle(m_hCamera);
	if (MV_OK != nRet1)
	{
		//printf("MV_CC_DestroyHandle fail! nRet [%x]\n", nRet1);
		//return -1;
	}
	long myRetn=SMCV_RETN_SUCCESS;

	unsigned int nTLaysType = MV_GIGE_DEVICE|MV_USB_DEVICE;

	//1 ö���豸
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
	else//ö���豸��Ϊ0����ʧ��
	{
		return SMCV_RETN_FAILIURE;
	}

	if(Index < 0)//û���ҵ����
	{
		return SMCV_RETN_FAILIURE;
	}
	//2 ���ɲ������
	//memset(&m_sDeviceInfo,0,sizeof(MV_CC_DEVICE_INFO));
	memcpy(&m_sDeviceInfo,m_stDeviceList.pDeviceInfo[Index],sizeof(MV_CC_DEVICE_INFO));
	nRet = MV_CC_CreateHandle(&m_hCamera,&m_sDeviceInfo);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}

	//3 ע��ص�����
	nRet = MV_CC_RegisterImageCallBack(m_hCamera,ImageCallBack,this);
	if(MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}

	//4 ���豸
	unsigned int nAccessMode = MV_ACCESS_Exclusive;
	unsigned short nSwitchOverKey = 0;
	TRY 
	{
		nRet = MV_CC_OpenDevice(m_hCamera, nAccessMode, nSwitchOverKey);
	}
	CATCH (CMemoryException, e)
	{
		AfxMessageBox(_T("�����ʧ�ܣ�"));
		return SMCV_RETN_FAILIURE;
	}
	END_CATCH
	if(nRet != MV_OK)
	{
		AfxMessageBox(_T("�����ʧ�ܣ�"));
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
	//5 ���òɼ�ģʽ
	
	nRet = MV_CC_SetTriggerMode(m_hCamera,1);
	if(nRet != MV_OK)
	{
		return SMCV_RETN_FAILIURE;
	}
	//scvSetTriggerMode(true);
	//���ô���Դ
	nRet = MV_CC_SetTriggerSource(m_hCamera,MV_TRIGGER_SOURCE_SOFTWARE);
	if(nRet != MV_OK)
	{
		return SMCV_RETN_FAILIURE;
	}
	
	//6 ������ͼ�����ظ�ʽ
	//unsigned int enValue = PixelType_Gvsp_Mono8;
	//unsigned int enValue = PixelType_Gvsp_RGB8_Packed;
	//nRet = MV_CC_SetPixelFormat(m_hCamera,enValue);
	//if(nRet != MV_OK)
	//{
	//	return SMCV_RETN_FAILIURE;
	//}
	unsigned int enMode = MV_GAMMA_SELECTOR_USER; //����Gamma����ΪUSER
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

	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[2],tempTimeOut[2]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvCloseDevice()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	
	//����ʼ�����
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
//�����������SDKû���Զ��������ܣ���ȷ���Ƿ����
//�����������SDK�ڲ��Դ��������ܣ�����5�����Զ���6���������ⲿ�ٵ��á�
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

//�����������SDK�ڲ��Դ��������ܣ��Զ��ģ������ⲿ�ٵ��á�
long CDevHIKUser::scvOpenCamWhenLostEx()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//����
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

//֡��
long CDevHIKUser::scvSetFPS(double bFPS)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

//ͼ��������Ϣ
long CDevHIKUser::scvSetBrightness(double bright)
{
	long myRetn=SMCV_RETN_SUCCESS;
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
//#define MV_E_HANDLE             0x80000000  ///< �������Ч�ľ��
//#define MV_E_SUPPORT            0x80000001  ///< ��֧�ֵĹ���
//#define MV_E_BUFOVER            0x80000002  ///< ��������
//#define MV_E_CALLORDER          0x80000003  ///< ��������˳�����
//#define MV_E_PARAMETER          0x80000004  ///< ����Ĳ���
//#define MV_E_RESOURCE           0x80000006  ///< ��Դ����ʧ��
//#define MV_E_NODATA             0x80000007  ///< ������
//#define MV_E_PRECONDITION       0x80000008  ///< ǰ���������󣬻����л����ѷ����仯
//#define MV_E_VERSION            0x80000009  ///< �汾��ƥ��
//#define MV_E_NOENOUGH_BUF       0x8000000A  ///< ������ڴ�ռ䲻��
//#define MV_E_ABNORMAL_IMAGE     0x8000000B  ///< �쳣ͼ�񣬿����Ƕ�������ͼ������
//#define MV_E_UNKNOW             0x800000FF  ///< δ֪�Ĵ���
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
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

//�Աȶ�.�����������û�жԱȶ����û�ȡSDK
long CDevHIKUser::scvSetContrast(double contrast)
{
	m_Contrast = (long)contrast;
	
	int c = (int )contrast;
	
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

//����
long CDevHIKUser::scvGetExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;

	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
	//---------ָ����
	//if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
	//{
	//	LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
	//		(tempTimeIn[11],tempTimeOut[11]);
	//	CString strOrder;
	//	strOrder.Format(_T("-%d-scvSetExposureParm(%d)"),timeBetween,val);
	//	m_HVDevOrderInfo.WriterOrder(strOrder);
	//}
	//----------------
	unsigned int nRet=MV_CC_SetFloatValue(m_hCamera, "ExposureTime", val*100);
	//unsigned int nRet= MV_CC_SetExposureTime(m_hCamera, val*100);//val��λΪ100us��
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	} 
	return myRetn;
}

//����
long CDevHIKUser::scvGetGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

	
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

//���������ʽ
long CDevHIKUser::scvSetImageFormat(long channels)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

//��ȡ�����ʽ
long CDevHIKUser::scvGetImageFormat(long& _format)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

//������ת��
long CDevHIKUser::scvsetFlipH()
{
	long myRetn=SMCV_RETN_SUCCESS;
	
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
//��ʱ����
void CDevHIKUser::scvTimer()
{
	/*BYTE sn[32];
	CameraSdkStatus retval=CameraReadSN(m_hCamera,sn, 0);
	if (CAMERA_STATUS_SUCCESS!=retval)
	{
		SetConnectedFlag(false);
	}*/
}
//��Ƶ������
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
	//��ʼ�ɼ�
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

	//ֹͣ�ɼ�
	unsigned int nRet = MV_CC_StopGrabbing(m_hCamera);
	if (MV_OK != nRet)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_bIsLive = false;
	return myRetn;
}

//����,����Ӳ��
long CDevHIKUser::scvSetTriggerMode(int trigger)
{
	long myRetn=SMCV_RETN_SUCCESS;

	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
//	unsigned int nRet = MV_CC_SetTriggerMode(m_hCamera, (trigger)?1:0);//1��ʾ�򿪴���ģʽ��0��ʾ�رմ���ģʽ
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
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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
	trigger=m_bIsTriggerMode;	//@zz ����Ӳ������û�ö�ȡ������������Ǳ���ֵ	17.08.16
	//trigger = (struEnumValue.nCurValue == 1? true:false);	

	return myRetn;
}

//����һ�Ρ���ȷ������Ǵ�������ģʽ��CameraSetTriggerMode(m_hCamera,1);��������Ϊ����
long CDevHIKUser::scvTrigger()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		SetConnectedFlag(false);
		return SMCV_RETN_NOINIT;
	}
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
	{
		LONGLONG timeBetween=m_HVDevOrderInfo.GetTimeOrderBetweenLast 
			(tempTimeIn[20],tempTimeOut[20]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvTrigger()"),timeBetween);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}

	if (m_bIsTriggerMode!=3)
	{
		//����
		unsigned int nRet = MV_CC_TriggerSoftwareExecute(m_hCamera);
		if (MV_OK != nRet)
		{
			return SMCV_RETN_FAILIURE;
		}
	}

	m_TriggerTimePt=GetClock();
	return myRetn;
}

//�豸�Ƿ�����
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


//��õ�ǰ�豸����Ŀ
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

//��ȡ�豸�ĵ��ȼ�¼
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
