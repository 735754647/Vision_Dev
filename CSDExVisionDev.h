#ifndef _INCLUDE_AUTOCSDExVisionDev_INTERFECE_H_
#define _INCLUDE_AUTOCSDExVisionDev_INTERFECE_H_

#ifdef AUTOCSDExVisionDev_EXP
#define AUTOCSDExVisionDev_API __declspec(dllexport)
#else
#define AUTOCSDExVisionDev_API __declspec(dllimport)
#endif

#include "../AutoCSD_include/AutoCSD/SMCVStruct.h"

class CSDExVisionDev
{
public:
	//和SPLCDev设备的接口
	virtual void scvDevInterface(SCVDevStream *pSCVDevice)=0;

	//设置本相机的名称
	virtual long scvSetDeviceName(CString strName)=0;
	virtual long scvGetDeviceName(CString& strName)=0;

	//设置本相机的ID
	virtual long scvSetDeviceID(int devID)=0;
	virtual long scvGetDeviceID(int& devID)=0;

	//初始化设备控件库
	virtual long scvInitVedioLibrary()=0;

	//退出设备控件库
	virtual long scvExitVedioLibrary()=0;

	//打开相机
	virtual long scvOpenCamDevice()=0;

	//宽和高
	virtual long scvSetCamImageSize(unsigned long width,unsigned long height)=0;

	//关闭相机
	virtual long scvCloseDevice()=0;

	//掉线之后重新打开
	virtual long scvOpenCamWhenLost()=0;

public:
	//帧率
	virtual long scvSetFPS(double FPS)=0;
	virtual long scvGetFPS(double &fps)=0;

	//亮度
	virtual long scvSetBrightness(double bright)=0;
	virtual long scvGetBrightness(double &bright)=0;

	//对比度
	virtual long scvSetContrast(double contrast)=0;
	virtual long scvGetContrast(double &contrast)=0;

	//快门
	virtual long scvGetExposureParm(double& exposure)=0;
	virtual long scvGetMaxExposureParm(double& exposure)=0;
	virtual long scvGetMinExposureParm(double& exposure)=0;
	virtual long scvSetExposureParm(long val)=0;

	//增益
	virtual long scvGetGainParm(double& gain)=0;
	virtual long scvGetMaxGainParm(double& gain)=0;
	virtual long scvGetMinGainParm(double& gain)=0;
	virtual long scvSetGain(long val)=0;

	//视频流开关
	virtual long scvIsLive(bool &isLive)=0;
	virtual long scvStartVedioLive()=0;
	virtual long scvStopVedioLive()=0;

	//触发,关联硬件
//<<<<<<< .mine	
	//virtual long scvSetTriggerMode(int trigger)=0;
	//virtual long scvIsTriggerMode(int &trigger)=0;
//=======	
	virtual long scvSetTriggerMode(int trigger)=0;

	virtual long scvIsTriggerMode(int &trigger)=0;
//>>>>>>> .theirs	
//||||||| .r12266
//	virtual long scvIsTriggerMode(bool &trigger)=0;
//=======
//	virtual long scvIsTriggerMode(int &trigger)=0;
//>>>>>>> .r12355
	virtual long scvTrigger()=0;

	//设备是否连接
	virtual long scvIsConnected(bool &isConnect)=0;

	virtual bool scvSetCamDisConnected()=0;

	

	//定时调用进入
	virtual long scvTimer()=0;

	//获取设备的调度记录
	virtual long scvGetDeviceOrder(std::vector<CString>& orderList)=0;

	//写入设备记录
	virtual long scvWriteDeviceOrder(CString orderList)=0;
};

//输出接口
extern "C" __declspec(dllexport) HRESULT CreateVisionDev(CSDExVisionDev ** pp_MotionDev);
typedef HRESULT (*TCreateVisionDev)(CSDExVisionDev **pp_MotionDev);

#endif //_INCLUDE_AUTOCSDExVisionDev_INTERFECE_H_