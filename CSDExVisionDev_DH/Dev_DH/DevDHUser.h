#pragma once

#include "../CSDExVisionDev_DH.h"

#include "Dev_DH.h"

#include <vector>

#include "Include/GenICam/System.h"
#include "Include/GenICam/Camera.h"
#include "Include/Infra/PrintLog.h"
//#include "StreamRetrieve.h"
#include "Include/Memory/SharedPtr.h"

#include "Dev_DH_Lib.h"

using namespace Dahua;
using namespace GenICam;

class CDevDHUser;

//定义关联的结构体
struct DevDH2SCVMap
{
	int nDevId;//当前设备索引号   
	CDevDHUser* pObj;  //当前的对象
};

typedef struct _ImageData
{	
	void*    pDataBuffer;           //当前数据缓冲区的地址
	int      nImgWidth;				//每帧数据图像的宽度
	int      nImgHeight;			//每帧数据图像的高度
	int      nBitCount;				//每个像素所占的字节数
	int      nDevId;				//当前设备索引号       //***********
}ImageData, *pImageData;

class CDevDHUser:public CDevDH
{
public:
	CDevDHUser(void);
	~CDevDHUser(void);

public:
	//读到相机的图像数据
	virtual void scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI);

	//相机初始化
public:
	//初始化设备的接口
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

	//定时进入
	void scvTimer();

	//设置和获取相机的属性
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

	//快门 单位0.1ms
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
	long scvSetTriggerMode(int trigger);
	long scvIsTriggerMode(int &trigger);
	long scvTrigger();

	//设备是否连接
	long scvIsConnected(bool &isConnect);

	//获得当前设备的数目
	long scvGetAvailableDevices(unsigned long &num);

	//获取设备的调度记录
	long scvGetDevOrder(std::vector<CString>& orderList);

	//数据回调
	void frameReady(ImageData Data);

	void ImageCallBack(const Dahua::GenICam::CFrame & frame);

	//设备多线程互锁
private:
    void Lock();
	void UnLock();

	void SetConnectedFlag(bool flag);
	bool GetConnectedFlag();

	void SetOpenedFlag(bool flag);
	bool GetOpenedFlag();


	//获取时钟基准
	LONGLONG GetClock();

	//初始化定时器
	void InitTimer(unsigned long TimerID,unsigned long bTime); 

	//判断定时器是否结束
	bool IsTimerEnd(unsigned long TimerID);

	void ThreadTimerLock();
	void ThreadTimerUnlock();

	//内部变量
private:
	bool m_bIsDevOpened;//相机打开标志
	bool m_bIsLive;//正在采集标志位
	int m_bIsTriggerMode;//触发模式标志位
	CCriticalSection m_CCriticalTimerSection;
	//定时器
	typedef struct tagVisionTimer 
	{
		LONGLONG TimerStart;
		LONGLONG TimerEnd;
		double Time;

	}VisionTimer ;
	vector<VisionTimer >    m_Timer;

	//相机名称
	std::string m_vdDeviceName;

	//相机ID
	int m_DeviceID;
	
	LONGLONG m_TriggerTimePt;
	LONGLONG m_TriggerTimePtEnd;
	
	//宽和高
	int m_Width;
	int m_Height;

	//相机是否连接
	bool m_bIsDevConnected;

	//增益
	double m_Gain;
	double m_MaxGain;
	double m_MinGain;

	//曝光
	long m_Exposure;

	//亮度
	long m_Brightness;

	//对比度
	long m_Contrast;

	//获取帧率
	long m_FPS;

	//对象表s
	static bool  m_bInit;
	static bool  Init();

public:
	BOOL           	 		m_bMonoSensor;//为TRUE时表示该相机为黑白相机
	BOOL            		m_bExit;//用来通知图像抓取线程结束
	//指针
	SCVDevStream *			m_pSCVDevice;

	//相机句柄
	ICameraPtr				cameraPtr;
	IStreamSourcePtr		streamPtr;
	IAcquisitionControlPtr  sptrAcquisitionCtl;
	IImageFormatControlPtr  sptrImageFormatCtrl;
	
	CCriticalSection m_CCriticalSection;
};
