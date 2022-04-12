#include "StdAfx.h"

#include "DevMVUser.h"
#include "../../../AutoCSD_include/AutoCSD/HMIMsg.h"
#include "CameraApi.h"
#include "CameraGrabber.h"
#include "CameraImage.h"

//����ʼ��

bool CDevMVUser::m_bInit=CDevMVUser::Init();

bool CDevMVUser::Init()
{
	return true;
}

//ץͼ�߳�
/*ͼ��ץȡ�ص�����*/
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

//���ݻص�
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

	//����
	m_Gain=1;

	//�ع�
	m_Exposure=4;

	//����
	m_Brightness=32;

	//�Աȶ�
	m_Contrast=100;

	m_FPS=155;

	m_Grabber = NULL;
	m_hCamera = NULL;

	m_Timer.resize(10);

	m_TriggerTimePt=0;
	m_TriggerTimePtEnd=0;
}
//****************��ʱ��******************
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

//���������ͼ������
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
//��SPLCDev�豸�Ľӿ�
void CDevMVUser::scvDevInterface(SCVDevStream *pSCVDevice)
{
    m_pSCVDevice=pSCVDevice;
}
//���ñ����������
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
//���ñ������ID
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
//��ʼ���豸�ؼ���
long CDevMVUser::scvInitVedioLibrary()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//�˳��豸�ؼ���
long CDevMVUser::scvExitVedioLibrary()
{
    long myRetn=SMCV_RETN_SUCCESS;
    
	return myRetn;
}

//��ʱ�̶���640X480,�����Ҫ�Զ���ֱ��ʣ� ����Ҫ�ṩROI����ʼ��ַ���ꡣ���п�͸���Ϣ���ǲ����� ����������ʱ������
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

	//�ر�
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
	//��ø��������������
	CameraGetCapability(m_hCamera,&m_sCameraInfo);//����������������

	//����ISPģ�����ͼ��Ϊ8bit�Ҷȸ�ʽ�� Ĭ����BGR24��ʽ�����Ҫ��߾��ȿ�̬��������������Ϊ16ibt�ҶȻ���48bit��ɫģʽ��
	//��ͬ�������ʽ�������m_pFrameBuffer��Ҫ���벻ͬ��С�Ļ������� 
	CameraSetIspOutFormat(m_hCamera,CAMERA_MEDIA_TYPE_MONO8);
	m_bMonoSensor = m_sCameraInfo.sIspCapacity.bMonoSensor; 

	SetConnectedFlag(true);
	SetOpenedFlag(true);

	return myRetn;
}

long CDevMVUser::scvCloseDevice()
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

//�����������SDK�ڲ��Դ��������ܣ�����5�����Զ���6���������ⲿ�ٵ��á�
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

//�����������SDK�ڲ��Դ��������ܣ��Զ��ģ������ⲿ�ٵ��á�
long CDevMVUser::scvOpenCamWhenLostEx()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//����
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

//֡��
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

//�������ӵ�ͼ�����ȿ���ͨ��٤���Աȶȣ�������ع������⣬Brightness��Ҫ��Ӧ��һ��?�����õ�Ӧ���Ƕ�Ӧ٤��
long CDevMVUser::scvSetBrightness(double bright)
{
	m_Brightness = (long)bright;

	int gamma = (int)bright;
	
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
		
	//�����٤���� CameraSetGamma(m_hCamera,gamma); gamm Ĭ��ֵΪ100����ʾ����ǿҲ������������100Ϊ����������100�䰵
	
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
	//�����٤���� CameraGetGamma(m_hCamera,&gamma);

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
		
	bright = gamma;
	
	return myRetn;
}

//�Աȶ�
long CDevMVUser::scvSetContrast(double contrast)
{
	m_Contrast = (long)contrast;
	
	int c = (int )contrast;
	
	long myRetn=SMCV_RETN_SUCCESS;

	
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
		
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	
	//ע�⣬������������Աȶ�Ĭ����100����ʾ����ǿҲ������������100�����Աȶȣ�����100��ǿ�Աȶȣ���ΧΪ0��200.
	CameraSetContrast(m_hCamera,c);

	return myRetn;
}
long CDevMVUser::scvGetContrast(double &contrast)
{
	long myRetn=SMCV_RETN_SUCCESS;
	int c;

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
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	
	CameraGetContrast(m_hCamera,&c);
	
	contrast = (double)c;

	return myRetn;
}

//����
long CDevMVUser::scvGetExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;


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
	
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	
	double t;
	
	CameraGetExposureTime(m_hCamera,&t);//t�ĵ�λ��΢�룬���緵�� 2.234��ʾ�ع�ʱ����2.234��΢�� 

	exposure=t*0.01;//��ȷ���Ƿ�Ҫ���㵥λ��

	return myRetn;
}
long CDevMVUser::scvGetMaxExposureParm(double& exposure)
{
	long myRetn=SMCV_RETN_SUCCESS;

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

	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

	double exp = (double)val*100;//val�ĵ�λ��ʲô��exp��λ��΢�룬����Ҫ���㣬ע�⡣
	
	CameraSetExposureTime(m_hCamera,exp);
	 
	return myRetn;
}

//����
long CDevMVUser::scvGetGainParm(double& gain)
{
	long myRetn=SMCV_RETN_SUCCESS;

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
	
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	
	int g=0;
	
    CameraGetAnalogGain(m_hCamera,&g);//����õ���g��Ҫ���Բ���ֵ���ǷŴ�ı����ˡ�

	
	gain = m_sCameraInfo.sExposeDesc.fAnalogGainStep * (double)g;//�Ŵ���
		
	return myRetn;
}
long CDevMVUser::scvGetMaxGainParm(double& gain)
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


	gain=( (double) m_sCameraInfo.sExposeDesc.uiAnalogGainMax) *  m_sCameraInfo.sExposeDesc.fAnalogGainStep;//����

	return myRetn;
}

long CDevMVUser::scvGetMinGainParm(double& gain)
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
	
	gain=( (double) m_sCameraInfo.sExposeDesc.uiAnalogGainMin) *  m_sCameraInfo.sExposeDesc.fAnalogGainStep;//����

	return myRetn;
}

long CDevMVUser::scvSetGain(long val)
{
	m_Gain=val;

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

	int step;
	step = (int)(((double)val )/ m_sCameraInfo.sExposeDesc.fAnalogGainStep);
	
	CameraSetAnalogGain(m_hCamera,step);
	
	return myRetn;
}

//������ת��
long CDevMVUser::scvsetFlipH()
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

	CameraSetMirror(m_hCamera, 0, TRUE);//FALSE��ʾȡ��ˮƽ��ת��TRUEΪʹ�ܡ�
	
	return myRetn;
}
long CDevMVUser::scvsetFlipV()
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

	CameraSetMirror(m_hCamera, 1, TRUE);//FALSE��ʾȡ����ֱ��ת��TRUEΪʹ�ܡ�
	

	return myRetn;
}
//��ʱ����
void CDevMVUser::scvTimer()
{
	/*BYTE sn[32];
	CameraSdkStatus retval=CameraReadSN(m_hCamera,sn, 0);
	if (CAMERA_STATUS_SUCCESS!=retval)
	{
		SetConnectedFlag(false);
	}*/
}
//��Ƶ������
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

//����,����Ӳ��
long CDevMVUser::scvSetTriggerMode(int trigger)
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
//<<<<<<< .mine	
//=======>>>>>>> .theirs	//CameraSetTriggerMode(m_hCamera,trigger? 1:0);// 0��ʾ����ģʽ ��1��ʾ������2��ʾӲ����
	CameraSetTriggerMode(m_hCamera,trigger);// 0��ʾ����ģʽ ��1��ʾ������2��ʾӲ����

	unsigned int nRet;
	//CameraSetTriggerMode(m_hCamera,trigger? 1:0);// 0��ʾ����ģʽ ��1��ʾ������2��ʾӲ����
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

	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	int mode;
	
	CameraGetTriggerMode(m_hCamera,&mode);// 0��ʾ����ģʽ ��1��ʾ������2��ʾӲ����

	trigger = (mode == 0? false:true);
		
	return myRetn;
}

//����һ�Ρ���ȷ������Ǵ�������ģʽ��CameraSetTriggerMode(m_hCamera,1);��������Ϊ����
long CDevMVUser::scvTrigger()
{
	long myRetn=SMCV_RETN_SUCCESS;

	
	//---------ָ����
	if(m_HVDevOrderInfo.IsCurentRecordOrderAble())  //��ش���
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

//�豸�Ƿ�����
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

//��õ�ǰ�豸����Ŀ
long CDevMVUser::scvGetAvailableDevices(unsigned long &num)
{
	long myRetn=SMCV_RETN_SUCCESS;
	int counts = 0;
	
	counts = CameraEnumerateDeviceEx();

	num = (int) counts;
	
	return myRetn;
}

//��ȡ�豸�ĵ��ȼ�¼
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
