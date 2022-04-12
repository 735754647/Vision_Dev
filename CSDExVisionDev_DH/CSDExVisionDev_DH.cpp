#include "StdAfx.h"
#include "CSDExVisionDev_DH.h"
#include "Dev_DH/DevDHUser.h"

HRESULT CreateVisionDev(CSDExVisionDev ** pp_obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pp_obj = new CSDExVisionDev_DH;
	return TRUE;
}


CSDExVisionDev_DH::CSDExVisionDev_DH(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_CSDExVisionDev_DH=NULL;
}

CSDExVisionDev_DH::~CSDExVisionDev_DH(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
}

//��SPLCDev�豸�Ľӿ�
void CSDExVisionDev_DH::scvDevInterface(SCVDevStream *pSCVDevice)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_DH!=NULL)
	{
		((CDevDHUser*)m_CSDExVisionDev_DH)->scvDevInterface(pSCVDevice);
	}
}

//���ñ����������
long CSDExVisionDev_DH::scvSetDeviceName(CString strName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetDeviceName(strName);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetDeviceName(CString& strName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetDeviceName(strName);
	}
	return retval;
}

//���ñ������ID
long CSDExVisionDev_DH::scvSetDeviceID(int devID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetDeviceID(devID);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetDeviceID(int& devID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetDeviceID(devID);
	}
	return retval;
}

//��ʼ���豸�ؼ���
long CSDExVisionDev_DH::scvInitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_CSDExVisionDev_DH=new CDevDHUser;
	return SMCV_RETN_SUCCESS;
}

//�˳��豸�ؼ���
long CSDExVisionDev_DH::scvExitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_DH!=NULL)
	{
		delete (CDevDHUser*)m_CSDExVisionDev_DH;
	}
	return SMCV_RETN_SUCCESS;
}

//�����
long CSDExVisionDev_DH::scvOpenCamDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvOpenCamDevice();
	}
	return retval;
}

//��͸�
long CSDExVisionDev_DH::scvSetCamImageSize(unsigned long width,unsigned long height)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetCamImageSize(width,height);
	}
	return retval;
}

//�ر����
long CSDExVisionDev_DH::scvCloseDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvCloseDevice();
	}
	return retval;
}

//����֮�����´�
long CSDExVisionDev_DH::scvOpenCamWhenLost()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvOpenCamWhenLost();
	}
	return retval;
}

//֡��
long CSDExVisionDev_DH::scvSetFPS(double FPS)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetFPS(FPS);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetFPS(double &fps)
{
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetFPS(fps);
	}
	return retval;
}

//����
long CSDExVisionDev_DH::scvSetBrightness(double bright)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetBrightness(bright);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetBrightness(double &bright)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetBrightness(bright);
	}
	return retval;
}

//�Աȶ�
long CSDExVisionDev_DH::scvSetContrast(double contrast)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetContrast(contrast);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetContrast(double &contrast)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetContrast(contrast);
	}
	return retval;
}

//����
long CSDExVisionDev_DH::scvGetExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetMaxExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetMaxExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetMinExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetMinExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_DH::scvSetExposureParm(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetExposureParm(val);
	}
	return retval;
}

//����
long CSDExVisionDev_DH::scvGetGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetExposureParm(gain);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetMaxGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetMaxGainParm(gain);
	}
	return retval;
}
long CSDExVisionDev_DH::scvGetMinGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetMinGainParm(gain);
	}
	return retval;
}
long CSDExVisionDev_DH::scvSetGain(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetGain(val);
	}
	return retval;
}

//��Ƶ������
long CSDExVisionDev_DH::scvIsLive(bool &isLive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvIsLive(isLive);
	}
	return retval;
}
long CSDExVisionDev_DH::scvStartVedioLive()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvStartVedioLive();
	}
	return retval;
}
long CSDExVisionDev_DH::scvStopVedioLive()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvStopVedioLive();
	}
	return retval;
}

//����,����Ӳ��
long CSDExVisionDev_DH::scvSetTriggerMode(int trigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvSetTriggerMode(trigger);
	}
	return retval;
}
long CSDExVisionDev_DH::scvIsTriggerMode(int &trigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvIsTriggerMode(trigger);
	}
	return retval;
}
//��ʱ����
long CSDExVisionDev_DH::scvTimer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_DH!=NULL)
	{
		((CDevDHUser*)m_CSDExVisionDev_DH)->scvTimer();
	}

	return 0;
}
long CSDExVisionDev_DH::scvTrigger()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvTrigger();
	}
	return retval;
}

//�豸�Ƿ�����
long CSDExVisionDev_DH::scvIsConnected(bool &isConnect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvIsConnected(isConnect);
	}
	return retval;
}

//��ȡ�豸�ĵ��ȼ�¼
long CSDExVisionDev_DH::scvGetDeviceOrder(std::vector<CString>& orderList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		//retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvGetDevOrder(orderList);
	}
	return 0;
}

//д���豸��¼
long CSDExVisionDev_DH::scvWriteDeviceOrder(CString orderList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_DH!=NULL)
	{
		//retval=((CDevDHUser*)m_CSDExVisionDev_DH)->scvWriteDeviceOrder(orderList);
	}
	return 0;
}