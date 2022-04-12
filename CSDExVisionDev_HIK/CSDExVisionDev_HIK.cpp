#include "StdAfx.h"
#include "CSDExVisionDev_HIK.h"
#include "DevHIKUser.h"

HRESULT CreateVisionDev(CSDExVisionDev ** pp_obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pp_obj = new CSDExVisionDev_HIK;
	return TRUE;
}


CSDExVisionDev_HIK::CSDExVisionDev_HIK(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_CSDExVisionDev_HIK=NULL;
}

CSDExVisionDev_HIK::~CSDExVisionDev_HIK(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
}

//和SPLCDev设备的接口
void CSDExVisionDev_HIK::scvDevInterface(SCVDevStream *pSCVDevice)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvDevInterface(pSCVDevice);
	}
}

//设置本相机的名称
long CSDExVisionDev_HIK::scvSetDeviceName(CString strName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetDeviceName(strName);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetDeviceName(CString& strName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetDeviceName(strName);
	}
	return retval;
}

//设置本相机的ID
long CSDExVisionDev_HIK::scvSetDeviceID(int devID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetDeviceID(devID);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetDeviceID(int& devID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetDeviceID(devID);
	}
	return retval;
}

//初始化设备控件库
long CSDExVisionDev_HIK::scvInitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_CSDExVisionDev_HIK=new CDevHIKUser;
	return SMCV_RETN_SUCCESS;
}

//退出设备控件库
long CSDExVisionDev_HIK::scvExitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		delete (CDevHIKUser*)m_CSDExVisionDev_HIK;
	}
	return SMCV_RETN_SUCCESS;
}

//打开相机
long CSDExVisionDev_HIK::scvOpenCamDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvOpenCamDevice();
	}
	return retval;
}

//宽和高
long CSDExVisionDev_HIK::scvSetCamImageSize(unsigned long width,unsigned long height)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetCamImageSize(width,height);
	}
	return retval;
}

//关闭相机
long CSDExVisionDev_HIK::scvCloseDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvCloseDevice();
	}
	return retval;
}

//掉线之后重新打开
long CSDExVisionDev_HIK::scvOpenCamWhenLost()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvOpenCamWhenLost();
	}
	return retval;
}

//帧率
long CSDExVisionDev_HIK::scvSetFPS(double FPS)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetFPS(FPS);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetFPS(double &fps)
{
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetFPS(fps);
	}
	return retval;
}

//亮度
long CSDExVisionDev_HIK::scvSetBrightness(double bright)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetBrightness(bright);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetBrightness(double &bright)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetBrightness(bright);
	}
	return retval;
}

//对比度
long CSDExVisionDev_HIK::scvSetContrast(double contrast)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetContrast(contrast);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetContrast(double &contrast)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetContrast(contrast);
	}
	return retval;
}

//快门
long CSDExVisionDev_HIK::scvGetExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetMaxExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetMaxExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetMinExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetMinExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvSetExposureParm(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetExposureParm(val);
	}
	return retval;
}

//增益
long CSDExVisionDev_HIK::scvGetGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetExposureParm(gain);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetMaxGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetMaxGainParm(gain);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvGetMinGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetMinGainParm(gain);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvSetGain(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetGain(val);
	}
	return retval;
}

//视频流开关
long CSDExVisionDev_HIK::scvIsLive(bool &isLive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvIsLive(isLive);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvStartVedioLive()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvStartVedioLive();
	}
	return retval;
}
long CSDExVisionDev_HIK::scvStopVedioLive()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvStopVedioLive();
	}
	return retval;
}

//触发,关联硬件
long CSDExVisionDev_HIK::scvSetTriggerMode(int trigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetTriggerMode(trigger);
	}
	return retval;
}
long CSDExVisionDev_HIK::scvIsTriggerMode(int &trigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvIsTriggerMode(trigger);
	}
	return retval;
}
//定时进入
long CSDExVisionDev_HIK::scvTimer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvTimer();
	}
	return 0;
}
long CSDExVisionDev_HIK::scvTrigger()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvTrigger();
	}
	return retval;
}

//设备是否连接
long CSDExVisionDev_HIK::scvIsConnected(bool &isConnect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvIsConnected(isConnect);
	}
	return retval;
}
bool CSDExVisionDev_HIK::scvSetCamDisConnected()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetDisConnected(false);
	}
	return retval;
}

//获取设备的调度记录
long CSDExVisionDev_HIK::scvGetDeviceOrder(std::vector<CString>& orderList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		//retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetDevOrder(orderList);
	}
	return 0;
}

//写入设备记录
long CSDExVisionDev_HIK::scvWriteDeviceOrder(CString orderList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		//retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvWriteDeviceOrder(orderList);
	}
	return 0;
}

long CSDExVisionDev_HIK::scvSetImageFormat( long _format )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvSetImageFormat(_format);
	}
	return retval;
}

long CSDExVisionDev_HIK::scvGetImageFormat( long& _format )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_HIK!=NULL)
	{
		retval=((CDevHIKUser*)m_CSDExVisionDev_HIK)->scvGetImageFormat(_format);
	}
	return retval;
}
