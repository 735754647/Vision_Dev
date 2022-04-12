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

//和SPLCDev设备的接口
void CSDExVisionDev_HV::scvDevInterface(SCVDevStream *pSCVDevice)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	if (m_CSDExVisionDev_HV!=NULL)
	{
		((CDevHVUser*)m_CSDExVisionDev_HV)->scvDevInterface(pSCVDevice);
	}
}

//设置本相机的名称
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

//设置本相机的ID
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

//初始化设备控件库
long CSDExVisionDev_HV::scvInitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	m_CSDExVisionDev_HV=new CDevHVUser;
	return SMCV_RETN_SUCCESS;
}

//退出设备控件库
long CSDExVisionDev_HV::scvExitVedioLibrary()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	if (m_CSDExVisionDev_HV!=NULL)
	{
		delete (CDevHVUser*)m_CSDExVisionDev_HV;
	}
	return SMCV_RETN_SUCCESS;
}

//打开相机
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

//宽和高
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

//关闭相机
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

//掉线之后重新打开
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

//帧率
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

//亮度
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

//对比度
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

//快门
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

//增益
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

//视频流开关
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

//触发,关联硬件
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

//设备是否连接
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
//定时进入
long CSDExVisionDev_HV::scvTimer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	return 0;
}

//获取设备的调度记录
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

//写入设备记录
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