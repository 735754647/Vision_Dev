#pragma once

#if SCVDEV_USE_HV //

#include "../../../AutoCSD_include/AutoCSD/SMCVStruct.h"
#include "Dev_HV.h"
#include <vector>


class CDevHVUser;

//定义关联的结构体
struct DevHV2SCVMap
{
	int nDevId;//当前设备索引号   
	CDevHVUser* pObj;  //当前的对象
};
typedef struct CvRect
{
	int x;
	int y;
	int width;
	int height;
}
CvRect;

class CDevHVUser:public CDevHV
{
public:
	CDevHVUser(void);
	~CDevHVUser(void);
	//---------------------------------------------------------
	//
	//-----------------------回调函数，从相机获取图像数据------
	//
	//---------------------------------------------------------
public:
	//读到相机的图像数据
	virtual void scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI);

	//---------------------------------------------------------
	//
	//-----------------------相机初始化------
	//
	//---------------------------------------------------------
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
	long scvOpenCamWhenLostEx();

	//---------------------------------------------------------
	//
	//-----------------------设置和获取相机的属性------
	//
	//---------------------------------------------------------
public:
	//快照
	long scvSetSnapMode(bool bMode);
	long scvGetSnapMode(bool &mode);

	//帧率
	long scvSetFPS(double bFPS);
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

	//视屏流转置
	long scvsetFlipH();
	long scvsetFlipV();

	//视频流开关
	long scvIsLive(bool &isLive);
	long scvStartVedioLive();
	long scvStopVedioLive();

	//触发,关联硬件
	long scvSetTriggerMode(bool trigger);
	long scvIsTriggerMode(bool &trigger);
	long scvSetTriggerROIMode(bool bROI);
	long scvIsTriggerROIMode(bool &bROI);
	long scvTrigger();
    long scvTriggerWithROI(CvRect rRectROI);

	//设备是否连接
	long scvIsConnected(bool &isConnect);

	//获得当前设备的数目
	long scvGetAvailableDevices(unsigned long &num);

	//获得当前设备的数目
	long scvGetAvailableDevices(std::vector<unsigned long>& dev);

	//获取设备的调度记录
	long scvGetDevOrder(std::vector<CString>& orderList);

	//写入设备记录
	long scvWriteDeviceOrder(CString orderList);

	//设备回调处理
private:
	void frameReady(pHVGigE_Img_i pCommuParam,CDevHVUser* pObj);
	static int CALLBACK DevHVCallBack(pHVGigE_Img_i pCommuParam);

    void Lock();
	void UnLock();

	void SetConnectedFlag(bool flag);
	bool GetConnectedFlag();

	void SetOpenedFlag(bool flag);
	bool GetOpenedFlag();

	//获取时钟基准
	LONGLONG GetClock();
private:
	bool m_bIsDevOpened;

	SCVDevStream * m_pSCVDevice;

	//相机名称
	std::string m_vdDeviceName;

	LONGLONG m_TriggerTimePt;
	LONGLONG m_TriggerTimePtEnd;

	//相机ID
	int m_DeviceID;

	//宽和高
	int m_Width;
	int m_Height;

	//相机是否连接
	bool m_bIsDevConnected;

	//是否是ROI模式
	bool m_bIsTriggerROIMode;

	//已经设置过ROI
	bool m_bIsTriggerROISetted;

	//是否触发模式
	bool m_bIsTriggerMode;

	//增益
	long m_Gain;

	//曝光
	long m_Exposure;

	//亮度
	long m_Brightness;

	//对比度
	long m_Contrast;

	//获取帧率
	long m_FPS;

	//对象表
	static bool  m_bInit;
	static bool  Init();
	static std::vector<DevHV2SCVMap>  m_MapHVList;
	CCriticalSection m_CCriticalSection;
};

#endif  //SCVDEV_USE_HV