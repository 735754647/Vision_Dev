#include "StdAfx.h"
#include "CSDExVisionDev_MV.h"
#include "Dev_MV/DevMVUser.h"

HRESULT CreateVisionDev(CSDExVisionDev ** pp_obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pp_obj = new CSDExVisionDev_MV;
	return TRUE;
}


CSDExVisionDev_MV::CSDExVisionDev_MV(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_CSDExVisionDev_MV=NULL;
}

CSDExVisionDev_MV::~CSDExVisionDev_MV(void)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
}

//和SPLCDev设备的接口
void CSDExVisionDev_MV::scvDevInterface(SCVDevStream *pSCVDevice)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_MV!=NULL)
	{
		((CDevMVUser*)m_CSDExVisionDev_MV)->scvDevInterface(pSCVDevice);
	}
}

//设置本相机的名称
long CSDExVisionDev_MV::scvSetDeviceName(CString strName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetDeviceName(strName);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetDeviceName(CString& strName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetDeviceName(strName);
	}
	return retval;
}

//设置本相机的ID
long CSDExVisionDev_MV::scvSetDeviceID(int devID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetDeviceID(devID);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetDeviceID(int& devID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetDeviceID(devID);
	}
	return retval;
}

//初始化设备控件库
long CSDExVisionDev_MV::scvInitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_CSDExVisionDev_MV=new CDevMVUser;
	return SMCV_RETN_SUCCESS;
}

//退出设备控件库
long CSDExVisionDev_MV::scvExitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_MV!=NULL)
	{
		delete (CDevMVUser*)m_CSDExVisionDev_MV;
	}
	return SMCV_RETN_SUCCESS;
}

//打开相机
long CSDExVisionDev_MV::scvOpenCamDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvOpenCamDevice();
	}
	return retval;
}

//宽和高
long CSDExVisionDev_MV::scvSetCamImageSize(unsigned long width,unsigned long height)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetCamImageSize(width,height);
	}
	return retval;
}

//关闭相机
long CSDExVisionDev_MV::scvCloseDevice()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvCloseDevice();
	}
	return retval;
}

//掉线之后重新打开
long CSDExVisionDev_MV::scvOpenCamWhenLost()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvOpenCamWhenLost();
	}
	return retval;
}

//帧率
long CSDExVisionDev_MV::scvSetFPS(double FPS)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetFPS(FPS);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetFPS(double &fps)
{
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetFPS(fps);
	}
	return retval;
}

//亮度
long CSDExVisionDev_MV::scvSetBrightness(double bright)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetBrightness(bright);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetBrightness(double &bright)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetBrightness(bright);
	}
	return retval;
}

//对比度
long CSDExVisionDev_MV::scvSetContrast(double contrast)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetContrast(contrast);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetContrast(double &contrast)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetContrast(contrast);
	}
	return retval;
}

//快门
long CSDExVisionDev_MV::scvGetExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetMaxExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetMaxExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetMinExposureParm(double& exposure)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetMinExposureParm(exposure);
	}
	return retval;
}
long CSDExVisionDev_MV::scvSetExposureParm(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetExposureParm(val);
	}
	return retval;
}

//增益
long CSDExVisionDev_MV::scvGetGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetExposureParm(gain);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetMaxGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetMaxGainParm(gain);
	}
	return retval;
}
long CSDExVisionDev_MV::scvGetMinGainParm(double& gain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetMinGainParm(gain);
	}
	return retval;
}
long CSDExVisionDev_MV::scvSetGain(long val)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetGain(val);
	}
	return retval;
}

//视频流开关
long CSDExVisionDev_MV::scvIsLive(bool &isLive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvIsLive(isLive);
	}
	return retval;
}
long CSDExVisionDev_MV::scvStartVedioLive()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvStartVedioLive();
	}
	return retval;
}
long CSDExVisionDev_MV::scvStopVedioLive()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvStopVedioLive();
	}
	return retval;
}

//触发,关联硬件
long CSDExVisionDev_MV::scvSetTriggerMode(int trigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetTriggerMode(trigger);
	}
	return retval;
}
long CSDExVisionDev_MV::scvIsTriggerMode(int &trigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvIsTriggerMode(trigger);
	}
	return retval;
}
//定时进入
long CSDExVisionDev_MV::scvTimer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (m_CSDExVisionDev_MV!=NULL)
	{
		((CDevMVUser*)m_CSDExVisionDev_MV)->scvTimer();
	}

	return 0;
}
long CSDExVisionDev_MV::scvTrigger()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvTrigger();
	}
	return retval;
}

//设备是否连接
long CSDExVisionDev_MV::scvIsConnected(bool &isConnect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvIsConnected(isConnect);
	}
	return retval;
}
bool CSDExVisionDev_MV::scvSetCamDisConnected()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvSetDisConnected();
	}
	return retval;
}
//获取设备的调度记录
long CSDExVisionDev_MV::scvGetDeviceOrder(std::vector<CString>& orderList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		//retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvGetDevOrder(isConnect);
	}
	return 0;
}

//写入设备记录
long CSDExVisionDev_MV::scvWriteDeviceOrder(CString orderList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	long retval=SMCV_RETN_SUCCESS;
	if (m_CSDExVisionDev_MV!=NULL)
	{
		//retval=((CDevMVUser*)m_CSDExVisionDev_MV)->scvWriteDeviceOrder(isConnect);
	}
	return 0;
}