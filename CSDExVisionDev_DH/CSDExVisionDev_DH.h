#ifndef _INCLUDE_AUTOCSDExVisionDev_DH_INTERFECE_H_
#define _INCLUDE_AUTOCSDExVisionDev_DH_INTERFECE_H_

#include "../../AutoCSD_include/AutoCSD/SMCVStruct.h"
#include "../CSDExVisionDev.h"

class CSDExVisionDev_DH:
	public CSDExVisionDev
{
public:
	CSDExVisionDev_DH(void);
	~CSDExVisionDev_DH(void);

public:
	//读到相机的图像数据
	void scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI);

public:
	//和SPLCDev设备的接口
	void scvDevInterface(SCVDevStream *pSCVDevice);

	//设置本相机的名称
	long scvSetDeviceName(CString strName);
	long scvGetDeviceName(CString& strName);

	//设置本相机的ID
	long scvSetDeviceID(int devID);
	long scvGetDeviceID(int& devID);

	//初始化设备控件库
	long scvInitVedioLibrary();

	//退出设备控件库
	long scvExitVedioLibrary();

	//打开相机
	long scvOpenCamDevice();

	//宽和高
	long scvSetCamImageSize(unsigned long width,unsigned long height);

	//关闭相机
	long scvCloseDevice();

	//掉线之后重新打开
	long scvOpenCamWhenLost();

public:
	//帧率
	long scvSetFPS(double FPS);
	long scvGetFPS(double &fps);

	//亮度
	long scvSetBrightness(double bright);
	long scvGetBrightness(double &bright);

	//对比度
	long scvSetContrast(double contrast);
	long scvGetContrast(double &contrast);

	//快门
	long scvGetExposureParm(double& exposure);
	long scvGetMaxExposureParm(double& exposure);
	long scvGetMinExposureParm(double& exposure);
	long scvSetExposureParm(long val);

	//增益
	long scvGetGainParm(double& gain);
	long scvGetMaxGainParm(double& gain);
	long scvGetMinGainParm(double& gain);
	long scvSetGain(long val);

	//视频流开关
	long scvIsLive(bool &isLive);
	long scvStartVedioLive();
	long scvStopVedioLive();

	//触发,关联硬件
	long scvSetTriggerMode(int trigger);
	long scvIsTriggerMode(int &trigger);
	long scvTrigger();

	//定时进入
	long scvTimer();

	//设备是否连接
	long scvIsConnected(bool &isConnect);

	//获取设备的调度记录
	long scvGetDeviceOrder(std::vector<CString>& orderList);

	//写入设备记录
	long scvWriteDeviceOrder(CString orderList);
private:
	LPVOID m_CSDExVisionDev_DH;
};

#endif //_INCLUDE_AUTOCSDExVisionDev_DH_INTERFECE_H_