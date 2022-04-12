#include "StdAfx.h"
#include "CSDExVisionDev_HV.h"
#include "Dev_HV/DevHVUser.h"


HRESULT CreateVisionDev(CSDExVisionDev ** pp_obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	*pp_obj = new CSDExVisionDev_HV;
	return TRUE;
}

CSDExVisionDev_HV::CSDExVisionDev_HV(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	m_CSDExVisionDev_HV=NULL;
}

CSDExVisionDev_HV::~CSDExVisionDev_HV(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
}

//��SPLCDev�豸�Ľӿ�
void CSDExVisionDev_HV::scvDevInterface(SCVDevStream *pSCVDevice)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	if (m_CSDExVisionDev_HV!=NULL)
	{
		((CDevHVUser*)m_CSDExVisionDev_HV)->scvDevInterface(pSCVDevice);
	}
}

//���ñ����������
long CSDExVisionDev_HV::scvSetDeviceName(CString strName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetDeviceName(strName);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetDeviceName(CString& strName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetDeviceName(strName);
	}
	return retval;
}

//���ñ������ID
long CSDExVisionDev_HV::scvSetDeviceID(int devID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetDeviceID(devID);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetDeviceID(int& devID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetDeviceID(devID);
	}
	return retval;
}

//��ʼ���豸�ؼ���
long CSDExVisionDev_HV::scvInitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	m_CSDExVisionDev_HV=new CDevHVUser;
	return SMCV_RETN_SUCCESS;
}

//�˳��豸�ؼ���
long CSDExVisionDev_HV::scvExitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	if (m_CSDExVisionDev_HV!=NULL)
	{
		delete (CDevHVUser*)m_CSDExVisionDev_HV;
	}
	return SMCV_RETN_SUCCESS;
}

//�����
long CSDExVisionDev_HV::scvOpenCamDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvOpenCamDevice();
	}
	return retval;
}

//��͸�
long CSDExVisionDev_HV::scvSetCamImageSize(unsigned long width,unsigned long height)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetCamImageSize(width,height);
	}
	return retval;
}

//�ر����
long CSDExVisionDev_HV::scvCloseDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvCloseDevice();
	}
	return retval;
}

//����֮�����´�
long CSDExVisionDev_HV::scvOpenCamWhenLost()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvOpenCamWhenLost();
	}
	return retval;
}

//֡��
long CSDExVisionDev_HV::scvSetFPS(double FPS)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetFPS(FPS);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetFPS(double &fps)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetFPS(fps);
	}
	return retval;
}

//����
long CSDExVisionDev_HV::scvSetBrightness(double bright)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetBrightness(bright);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetBrightness(double &bright)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetBrightness(bright);
	}
	return retval;
}

//�Աȶ�
long CSDExVisionDev_HV::scvSetContrast(double contrast)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetContrast(contrast);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetContrast(double &contrast)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetContrast(contrast);
	}
	return retval;
}

//����
long CSDExVisionDev_HV::scvGetExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetMaxExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetMaxExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetMinExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetMinExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_HV::scvSetExposureParm(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetExposureParm(val);
	}
	return retval;
}

//����
long CSDExVisionDev_HV::scvGetGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetExposureParm(gain);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetMaxGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetMaxGainParm(gain);
	}
	return retval;
}
long CSDExVisionDev_HV::scvGetMinGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetMinGainParm(gain);
	}
	return retval;
}
long CSDExVisionDev_HV::scvSetGain(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetGain(val);
	}
	return retval;
}

//��Ƶ������
long CSDExVisionDev_HV::scvIsLive(bool &isLive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvIsLive(isLive);
	}
	return retval;
}
long CSDExVisionDev_HV::scvStartVedioLive()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvStartVedioLive();
	}
	return retval;
}
long CSDExVisionDev_HV::scvStopVedioLive()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvStopVedioLive();
	}
	return retval;
}

//����,����Ӳ��
long CSDExVisionDev_HV::scvSetTriggerMode(bool trigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvSetTriggerMode(trigger);
	}
	return retval;
}
long CSDExVisionDev_HV::scvIsTriggerMode(bool &trigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvIsTriggerMode(trigger);
	}
	return retval;
}
long CSDExVisionDev_HV::scvTrigger()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvTrigger();
	}
	return retval;
}

//�豸�Ƿ�����
long CSDExVisionDev_HV::scvIsConnected(bool &isConnect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvIsConnected(isConnect);
	}
	return retval;
}
//��ʱ����
long CSDExVisionDev_HV::scvTimer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	return 0;
}

//��ȡ�豸�ĵ��ȼ�¼
long CSDExVisionDev_HV::scvGetDeviceOrder(std::vector<CString>& orderList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvGetDevOrder(orderList);
	}
	return 0;
}

//д���豸��¼
long CSDExVisionDev_HV::scvWriteDeviceOrder(CString orderList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HV!=NULL)
	{
		//retval=((CDevHVUser*)m_CSDExVisionDev_HV)->scvWriteDeviceOrder(orderList);
	}
	return 0;
}