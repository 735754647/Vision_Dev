#include "StdAfx.h"

#include "DevDHUser.h"


//����ʼ��

bool CDevDHUser::m_bInit=CDevDHUser::Init();

bool CDevDHUser::Init()
{
	return true;
}

//ץͼ�߳�
/*ͼ��ץȡ�ص�����*/

void CDevDHUser::ImageCallBack(const Dahua::GenICam::CFrame & frame)
{
	if(frame.valid())
	{
		ImageData tempData;
		tempData.pDataBuffer = (void*)frame.getImage();
		tempData.nImgHeight = frame.getImageHeight();
		tempData.nImgWidth = frame.getImageWidth();
		tempData.nBitCount = 1;
		this->frameReady(tempData);
	}
}
//���ݻص�
void CDevDHUser::frameReady(ImageData Data)
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

CDevDHUser::CDevDHUser(void)
{
	m_pSCVDevice=NULL;
	m_DeviceID = -1;
	m_vdDeviceName="";
	m_bIsDevOpened=false;
	m_bIsDevConnected=true;
	m_bIsLive = false;
	m_bIsTriggerMode = false;
	m_Width=640;
	m_Height=480;

	//����
	m_Gain=1;

	//�ع�
	m_Exposure=4;

	//����
	m_Brightness=32;

	//�Աȶ�
	m_Contrast=100;

	m_FPS=300;

	m_Timer.resize(10);

	m_TriggerTimePt=0;
	m_TriggerTimePtEnd=0;
}
//****************��ʱ��******************
LONGLONG CDevDHUser::GetClock()
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

void CDevDHUser::InitTimer(unsigned long TimerID,unsigned long bTime) 
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
void CDevDHUser::ThreadTimerLock()
{
	m_CCriticalTimerSection.Lock();
}
void CDevDHUser::ThreadTimerUnlock()
{
	m_CCriticalTimerSection.Unlock();
}
bool CDevDHUser::IsTimerEnd(unsigned long TimerID) 
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

CDevDHUser::~CDevDHUser(void)
{

}

//���������ͼ������
void CDevDHUser::scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI)
{
   m_pSCVDevice->scvDev_VedioData(pData,width,height,bitCount,bROI);
}


void CDevDHUser::SetConnectedFlag(bool flag)
{
	Lock();
	m_bIsDevConnected=flag;
	UnLock();
}

bool CDevDHUser::GetConnectedFlag()
{
	bool flag=false;

	Lock();
	flag=m_bIsDevConnected;
	UnLock();

	return flag;
}

void CDevDHUser::SetOpenedFlag(bool flag)
{
	Lock();
	m_bIsDevOpened=flag;
	UnLock();
}
bool CDevDHUser::GetOpenedFlag()
{
	bool flag=false;

	Lock();
	flag=m_bIsDevOpened;
	UnLock();

	return flag;
}
//��SPLCDev�豸�Ľӿ�
void CDevDHUser::scvDevInterface(SCVDevStream *pSCVDevice)
{
    m_pSCVDevice=pSCVDevice;
}
//���ñ����������
long CDevDHUser::scvSetDeviceName(CString strName)
{
	long myRetn=SMCV_RETN_SUCCESS;

	CStringW strw = strName;
	CStringA stra(strw.GetBuffer(0));
	strw.ReleaseBuffer();
	m_vdDeviceName=stra.GetBuffer(0);
	stra.ReleaseBuffer();

	return myRetn;
}
long CDevDHUser::scvGetDeviceName(CString& strName)
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}
//���ñ������ID
long CDevDHUser::scvSetDeviceID(int devID)
{
	long myRetn=SMCV_RETN_SUCCESS;

	m_DeviceID=devID;

	return myRetn;
}
long CDevDHUser::scvGetDeviceID(int& devID)
{
	long myRetn=SMCV_RETN_SUCCESS;

    devID=m_DeviceID;

	return myRetn;
}
//��ʼ���豸�ؼ���
long CDevDHUser::scvInitVedioLibrary()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//�˳��豸�ؼ���
long CDevDHUser::scvExitVedioLibrary()
{
    long myRetn=SMCV_RETN_SUCCESS;
    
	return myRetn;
}

//��ʱ�̶���640X480,�����Ҫ�Զ���ֱ��ʣ� ����Ҫ�ṩROI����ʼ��ַ���ꡣ���п�͸���Ϣ���ǲ����� ����������ʱ������
long CDevDHUser::scvSetCamImageSize(unsigned long width,unsigned long height)
{
	long myRetn=SMCV_RETN_SUCCESS;
	m_Width=width;
	m_Height=height;
	return myRetn;
}

long CDevDHUser::scvOpenCamDevice()
{
	long myRetn=SMCV_RETN_SUCCESS;

	//1.ö���豸
	//<ICameraPtr> vCameraPtrList;
	Infra::TVector<ICameraPtr> vCameraPtrList;
	bool ret = CSystem::getInstance().discovery(vCameraPtrList);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	int Index = -1;
	if(vCameraPtrList.size()>0)
	{
		//Index = -2;
		for(int i=0;i<vCameraPtrList.size();++i)
		{
			cameraPtr = vCameraPtrList[i];
			const char *cameraName = cameraPtr->getName();
			if(strcmp(m_vdDeviceName.c_str(),cameraPtr->getName()) == 0)
			{
				Index = i;
				break;
			}
		}
	}
	else
	{
		return SMCV_RETN_FAILIURE;
	}

	if(Index == -1)
	{
		return SMCV_RETN_FAILIURE;
	}

	cameraPtr = vCameraPtrList[Index];

	//2 �������
	ret = cameraPtr->connect();
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	//3 ����AcquisitionControl����
	sptrAcquisitionCtl = CSystem::getInstance().createAcquisitionControl(cameraPtr);
	if(sptrAcquisitionCtl == NULL)
	{
		return SMCV_RETN_FAILIURE;
	}

	//4 ��������
	//���ô���ԴΪ����
	CEnumNode enumNode = sptrAcquisitionCtl->triggerSource();
	ret = enumNode.setValueBySymbol("Software");
	if (!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	//���ô�����
	enumNode = sptrAcquisitionCtl->triggerSelector();
	ret = enumNode.setValueBySymbol("FrameStart");
	if (!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	//���ô���ģʽ
	enumNode = sptrAcquisitionCtl->triggerMode();
	ret = enumNode.setValueBySymbol("On");
	if (!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	//5 ����������
	streamPtr = CSystem::getInstance().createStreamSource(cameraPtr);
	if(streamPtr == NULL)
	{
		return SMCV_RETN_FAILIURE;
	}
	//6 ע��ص�����
	ret = streamPtr->attachGrabbing(GenICam::IStreamSource::Proc(&CDevDHUser::ImageCallBack,this));

	//7 ������ͼ�����ظ�ʽ
	sptrImageFormatCtrl = CSystem::getInstance().createImageFormatControl(cameraPtr);
	enumNode = sptrImageFormatCtrl->pixelFormat();
	ret = enumNode.setValueBySymbol("Mono8");
	
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	
	m_bMonoSensor = true;

	SetConnectedFlag(true);
	SetOpenedFlag(true);
	return myRetn;
}

long CDevDHUser::scvCloseDevice()
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
	bool ret;
	
	//ֹͣ�ɼ�
	if(streamPtr->isGrabbing())
	{
		ret = streamPtr->stopGrabbing();
		if(!ret)
		{
			return SMCV_RETN_FAILIURE;
		}
		m_bIsLive = false;
	}

	CEnumNode enumNode = sptrAcquisitionCtl->triggerSource();
	enumNode = sptrAcquisitionCtl->triggerMode();
	ret = enumNode.setValueBySymbol("Off");
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	ret = streamPtr->startGrabbing();
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	ret = streamPtr->stopGrabbing();
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	if(cameraPtr->isConnected())
		ret = cameraPtr->disConnect();

	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	SetOpenedFlag(false);
	return myRetn;
}
//
long CDevDHUser::scvOpenCamWhenLost()
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
long CDevDHUser::scvOpenCamWhenLostEx()
{
	long myRetn=SMCV_RETN_SUCCESS;

	return myRetn;
}

//����
long CDevDHUser::scvSetSnapMode(bool bMode)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}
long CDevDHUser::scvGetSnapMode(bool &mode)
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	return myRetn;
}

//֡��
long CDevDHUser::scvSetFPS(double bFPS)
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
	CDoubleNode m_cFrameRateNode = sptrAcquisitionCtl->acquisitionFrameRate();
	double fMax, fMin;
	m_cFrameRateNode.getMaxVal(fMax);
	m_cFrameRateNode.getMinVal(fMin);
	if(bFPS>fMax || bFPS<fMin)
	{
		return SMCV_RETN_FAILIURE;
	}
	bool ret = m_cFrameRateNode.setValue(bFPS);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_FPS = bFPS;
	return myRetn;
}
long CDevDHUser::scvGetFPS(double &fps)
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
	double tempFrameRate = 0;
	CDoubleNode m_cFrameRateNode = sptrAcquisitionCtl->acquisitionFrameRate();
	bool ret = m_cFrameRateNode.getValue(tempFrameRate);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	fps = tempFrameRate;
	return myRetn;

}

//ͼ��������Ϣ
long CDevDHUser::scvSetBrightness(double bright)
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
	IISPControlPtr ptrISPCtlr = CSystem::getInstance().createISPControl(cameraPtr);
	CIntNode m_cBrightnessNode = ptrISPCtlr->brightness();
	int64_t nMax, nMin;
	m_cBrightnessNode.getMaxVal(nMax);
	m_cBrightnessNode.getMinVal(nMin);
	int64_t tempBrightness = nMin + (nMax - nMin) / 100 * bright;
	bool ret = m_cBrightnessNode.setValue(tempBrightness);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_Brightness = (long)bright;
	return myRetn;
}
long CDevDHUser::scvGetBrightness(double &bright)
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
	int64_t tempBrightness;
	IISPControlPtr ptrISPCtlr = CSystem::getInstance().createISPControl(cameraPtr);
	CIntNode m_cBrightnessNode = ptrISPCtlr->brightness();
	bool ret = m_cBrightnessNode.getValue(tempBrightness);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	int64_t nMax, nMin;
	m_cBrightnessNode.getMaxVal(nMax);
	m_cBrightnessNode.getMinVal(nMin);
	bright = (double)100.0*tempBrightness/(nMax-nMin);
	//bright = (double)tempBrightness;
	m_Brightness = bright;
	return myRetn;
}

//�Աȶ�
long CDevDHUser::scvSetContrast(double contrast)
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
			(tempTimeIn[6],tempTimeOut[6]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvSetContrast(%f)"),timeBetween,contrast);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------

	IISPControlPtr ptrISPCtlr = CSystem::getInstance().createISPControl(cameraPtr);
	CIntNode m_cContrastNode = ptrISPCtlr->contrast();

	int64_t nMax, nMin;
	m_cContrastNode.getMaxVal(nMax);
	m_cContrastNode.getMinVal(nMin);
	int64_t tempContrast = nMin + (nMax - nMin) / 100 * contrast;
	bool ret = m_cContrastNode.setValue(tempContrast);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_Contrast = (long)contrast;
	return myRetn;
}
long CDevDHUser::scvGetContrast(double &contrast)
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
			(tempTimeIn[7],tempTimeOut[7]);
		CString strOrder;
		strOrder.Format(_T("-%d-scvGetContrast(%f)"),timeBetween,contrast);
		m_HVDevOrderInfo.WriterOrder(strOrder);
	}
	//----------------
	int64_t c;
	IISPControlPtr ptrISPCtlr = CSystem::getInstance().createISPControl(cameraPtr);
	CIntNode m_cContrastNode = ptrISPCtlr->contrast();
	bool ret = m_cContrastNode.getValue(c);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	int64_t nMax, nMin;
	m_cContrastNode.getMaxVal(nMax);
	m_cContrastNode.getMinVal(nMin);
	contrast = 100.0 * c / (nMax - nMin);
	//contrast = (double)c;
	m_Contrast = (long)contrast;
	return myRetn;
}

//����
long CDevDHUser::scvGetExposureParm(double& exposure)
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
	double tempExposure;
	CDoubleNode m_cExposureNode = sptrAcquisitionCtl->exposureTime();
	bool ret = m_cExposureNode.getValue(tempExposure);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	exposure = tempExposure/100.0;
	m_Exposure = tempExposure;
	return myRetn;
}
long CDevDHUser::scvGetMaxExposureParm(double& exposure)
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
	double tempExposure;
	CDoubleNode m_cExposureNode = sptrAcquisitionCtl->exposureTime();
	bool ret = m_cExposureNode.getMaxVal(tempExposure);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	exposure = tempExposure/100.0;
	return myRetn;
}
long CDevDHUser::scvGetMinExposureParm(double& exposure)
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
	double tempExposure;
	CDoubleNode m_cExposureNode = sptrAcquisitionCtl->exposureTime();
	bool ret = m_cExposureNode.getMinVal(tempExposure);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	exposure = tempExposure/100.0;
	
	return myRetn;
}



long CDevDHUser::scvSetExposureParm(long val)
{
	m_Exposure=val;

	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
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

	CDoubleNode m_cExposureNode = sptrAcquisitionCtl->exposureTime();
	double dMax;
	m_cExposureNode.getMaxVal(dMax);
	if(val*100.0 > dMax)
	{
		return SMCV_RETN_FAILIURE;
	}
	bool ret = m_cExposureNode.setValue((double)val*100.0);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	return myRetn;
}

//����
long CDevDHUser::scvGetGainParm(double& gain)
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
	double tempGain;
	IAnalogControlPtr ptrAnalogCtrl = CSystem::getInstance().createAnalogControl(cameraPtr);
	CDoubleNode m_cGainNode = ptrAnalogCtrl->gainRaw();
	bool ret = m_cGainNode.getValue(tempGain);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	gain = (tempGain-1.0)/5.0*10.0;
	m_Gain = gain;

	return myRetn;
}
long CDevDHUser::scvGetMaxGainParm(double& gain)
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
	double tempGain;
	IAnalogControlPtr ptrAnalogCtrl = CSystem::getInstance().createAnalogControl(cameraPtr);
	CDoubleNode m_cGainNode = ptrAnalogCtrl->gainRaw();
	bool ret = m_cGainNode.getMaxVal(tempGain);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_MaxGain = (tempGain-1.0)/5.0*10.0;
	gain = m_MaxGain;
	return myRetn;
}

long CDevDHUser::scvGetMinGainParm(double& gain)
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
	double tempGain;
	IAnalogControlPtr ptrAnalogCtrl = CSystem::getInstance().createAnalogControl(cameraPtr);
	CDoubleNode m_cGainNode = ptrAnalogCtrl->gainRaw();
	bool ret = m_cGainNode.getMinVal(tempGain);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	gain = (tempGain-1.0)/5.0*10.0;
	m_MinGain = gain;
	return myRetn;
}

long CDevDHUser::scvSetGain(long val)
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
	double tempGain = (double)val/ 10.0 * 5.0+1.0;
	IAnalogControlPtr ptrAnalogCtrl = CSystem::getInstance().createAnalogControl(cameraPtr);
	CDoubleNode m_cGainNode = ptrAnalogCtrl->gainRaw();
	bool ret = m_cGainNode.setValue(tempGain);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_Gain = val;
	return myRetn;
}

//������ת��
long CDevDHUser::scvsetFlipH()
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
	CBoolNode m_cFlipHNode = sptrImageFormatCtrl->reverseX();
	bool ret = m_cFlipHNode.setValue(true);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
		
	return myRetn;
}
long CDevDHUser::scvsetFlipV()
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
	
	CBoolNode m_cFlipHNode = sptrImageFormatCtrl->reverseY();
	bool ret = m_cFlipHNode.setValue(true);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	return myRetn;
}
//��ʱ����
void CDevDHUser::scvTimer()
{
	/*BYTE sn[32];
	CameraSdkStatus retval=CameraReadSN(m_hCamera,sn, 0);
	if (CAMERA_STATUS_SUCCESS!=retval)
	{
		SetConnectedFlag(false);
	}*/
}
//��Ƶ������
long CDevDHUser::scvIsLive(bool &isLive)
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
long CDevDHUser::scvStartVedioLive()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}
	//��ʼ�ɼ�
	bool ret = streamPtr->startGrabbing();
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_bIsLive = true;

    return myRetn;
}
long CDevDHUser::scvStopVedioLive()
{
	long myRetn=SMCV_RETN_SUCCESS;
	if (!GetOpenedFlag())
	{
		return SMCV_RETN_NOINIT;
	}

	//ֹͣ�ɼ�
	bool ret = streamPtr->stopGrabbing();
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	m_bIsLive = false;
	return myRetn;
}

//����,����Ӳ��
long CDevDHUser::scvSetTriggerMode(int trigger)
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
	bool ret = true;
	CEnumNode enumNode = sptrAcquisitionCtl->triggerSource();
	switch(trigger)
	{
	case 0:
		//���ô���ԴΪ����
		enumNode = sptrAcquisitionCtl->triggerSource();
		ret = enumNode.setValueBySymbol("Software");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}

		//���ô�����
		enumNode = sptrAcquisitionCtl->triggerSelector();
		ret = enumNode.setValueBySymbol("FrameStart");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}

		//���ô���ģʽ
		enumNode = sptrAcquisitionCtl->triggerMode();
		ret = enumNode.setValueBySymbol("On");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}
		break;
	case 1:
		//���ô���ԴΪ����
		enumNode = sptrAcquisitionCtl->triggerSource();
		ret = enumNode.setValueBySymbol("Software");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}

		//���ô�����
		enumNode = sptrAcquisitionCtl->triggerSelector();
		ret = enumNode.setValueBySymbol("FrameStart");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}

		//���ô���ģʽ
		enumNode = sptrAcquisitionCtl->triggerMode();
		ret = enumNode.setValueBySymbol("On");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}
		break;
	case 2://ʵʱģʽ
		enumNode = sptrAcquisitionCtl->triggerMode();
		ret = enumNode.setValueBySymbol("Off");
		break;
	case 3://Ӳ����
		//���ô���ԴΪ�ⲿ����
		enumNode = sptrAcquisitionCtl->triggerSource();
		ret = enumNode.setValueBySymbol("Line1");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}

		//���ô�����
		enumNode = sptrAcquisitionCtl->triggerSelector();
		ret = enumNode.setValueBySymbol("FrameStart");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}
		//���ô���ģʽ
		enumNode = sptrAcquisitionCtl->triggerActivation();    
		ret = enumNode.setValueBySymbol("RisingEdge");    
		if (ret != 0)    
		{        
			return SMCV_RETN_FAILIURE; 
		}
		//�����ⴥ��Ϊ�����أ��½���ΪFallingEdge��
		enumNode = sptrAcquisitionCtl->triggerMode();
		ret = enumNode.setValueBySymbol("On");
		if (!ret)
		{
			return SMCV_RETN_FAILIURE;
		}
		break;
	}
	

	m_bIsTriggerMode = trigger;

	return myRetn;
}
long CDevDHUser::scvIsTriggerMode(int &trigger)
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
	Infra::CString trggerModeStr;
	CEnumNode enumNode = sptrAcquisitionCtl->triggerMode();
	bool ret = enumNode.getValueSymbol(trggerModeStr);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	if(strcmp(trggerModeStr.c_str(),"On") == 0)
	{
		trigger = 1;
		
	}
	else if(strcmp(trggerModeStr.c_str(),"Off") == 0)
	{
		trigger = 0;
	}
	else
	{
		myRetn = SMCV_RETN_FAILIURE;
	}
	
	m_bIsTriggerMode = trigger ? true:false;

	return myRetn;
}

//����һ�Ρ���ȷ������Ǵ�������ģʽ��CameraSetTriggerMode(m_hCamera,1);��������Ϊ����
long CDevDHUser::scvTrigger()
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
	//----------------
	//����
	CCmdNode cmdNode = sptrAcquisitionCtl->triggerSoftware();
	bool ret = cmdNode.execute();
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}

	m_TriggerTimePt=GetClock();
	return myRetn;
}

//�豸�Ƿ�����
long CDevDHUser::scvIsConnected(bool &isConnect)
{
	long myRetn=SMCV_RETN_SUCCESS;
    isConnect=GetConnectedFlag();
	return myRetn;
}

//��õ�ǰ�豸����Ŀ
long CDevDHUser::scvGetAvailableDevices(unsigned long &num)
{
	long myRetn=SMCV_RETN_SUCCESS;
	Infra::TVector<ICameraPtr> vCameraList;
	bool ret = CSystem::getInstance().discovery(vCameraList);
	if(!ret)
	{
		return SMCV_RETN_FAILIURE;
	}
	num = vCameraList.size();
	return myRetn;
}

//��ȡ�豸�ĵ��ȼ�¼
long CDevDHUser::scvGetDevOrder(std::vector<CString>& orderList)
{
    long myRetn=SMCV_RETN_SUCCESS;

	orderList.clear();
	GetOrder(orderList);

	return myRetn;
}

void CDevDHUser::Lock()
{
   m_CCriticalSection.Lock();
}
void CDevDHUser::UnLock()
{
   m_CCriticalSection.Unlock();
}
