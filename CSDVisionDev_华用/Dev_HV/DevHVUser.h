#pragma once

#if SCVDEV_USE_HV //

#include "../../../AutoCSD_include/AutoCSD/SMCVStruct.h"
#include "Dev_HV.h"
#include <vector>


class CDevHVUser;

//��������Ľṹ��
struct DevHV2SCVMap
{
	int nDevId;//��ǰ�豸������   
	CDevHVUser* pObj;  //��ǰ�Ķ���
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
	//-----------------------�ص��������������ȡͼ������------
	//
	//---------------------------------------------------------
public:
	//���������ͼ������
	virtual void scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI);

	//---------------------------------------------------------
	//
	//-----------------------�����ʼ��------
	//
	//---------------------------------------------------------
public:
	//��SPLCDev�豸�Ľӿ�
	void scvDevInterface(SCVDevStream *pSCVDevice);

	//���ñ����������
	long scvSetDeviceName(CString strName);
	long scvGetDeviceName(CString& strName);

	//���ñ������ID
	long scvSetDeviceID(int devID);
	long scvGetDeviceID(int& devID);

	//��ʼ���豸�ؼ���
	long scvInitVedioLibrary();

	//�˳��豸�ؼ���
	long scvExitVedioLibrary();

	//�����
	long scvOpenCamDevice();

	//��͸�
	long scvSetCamImageSize(unsigned long width,unsigned long height);

	//�ر����
	long scvCloseDevice();

	//����֮�����´�
	long scvOpenCamWhenLost();
	long scvOpenCamWhenLostEx();

	//---------------------------------------------------------
	//
	//-----------------------���úͻ�ȡ���������------
	//
	//---------------------------------------------------------
public:
	//����
	long scvSetSnapMode(bool bMode);
	long scvGetSnapMode(bool &mode);

	//֡��
	long scvSetFPS(double bFPS);
	long scvGetFPS(double &fps);

	//����
	long scvSetBrightness(double bright);
	long scvGetBrightness(double &bright);

	//�Աȶ�
	long scvSetContrast(double contrast);
	long scvGetContrast(double &contrast);

	//����
	long scvGetExposureParm(double& exposure);
	long scvGetMaxExposureParm(double& exposure);
	long scvGetMinExposureParm(double& exposure);
	long scvSetExposureParm(long val);

	//����
	long scvGetGainParm(double& gain);
	long scvGetMaxGainParm(double& gain);
	long scvGetMinGainParm(double& gain);
	long scvSetGain(long val);

	//������ת��
	long scvsetFlipH();
	long scvsetFlipV();

	//��Ƶ������
	long scvIsLive(bool &isLive);
	long scvStartVedioLive();
	long scvStopVedioLive();

	//����,����Ӳ��
	long scvSetTriggerMode(bool trigger);
	long scvIsTriggerMode(bool &trigger);
	long scvSetTriggerROIMode(bool bROI);
	long scvIsTriggerROIMode(bool &bROI);
	long scvTrigger();
    long scvTriggerWithROI(CvRect rRectROI);

	//�豸�Ƿ�����
	long scvIsConnected(bool &isConnect);

	//��õ�ǰ�豸����Ŀ
	long scvGetAvailableDevices(unsigned long &num);

	//��õ�ǰ�豸����Ŀ
	long scvGetAvailableDevices(std::vector<unsigned long>& dev);

	//��ȡ�豸�ĵ��ȼ�¼
	long scvGetDevOrder(std::vector<CString>& orderList);

	//д���豸��¼
	long scvWriteDeviceOrder(CString orderList);

	//�豸�ص�����
private:
	void frameReady(pHVGigE_Img_i pCommuParam,CDevHVUser* pObj);
	static int CALLBACK DevHVCallBack(pHVGigE_Img_i pCommuParam);

    void Lock();
	void UnLock();

	void SetConnectedFlag(bool flag);
	bool GetConnectedFlag();

	void SetOpenedFlag(bool flag);
	bool GetOpenedFlag();

	//��ȡʱ�ӻ�׼
	LONGLONG GetClock();
private:
	bool m_bIsDevOpened;

	SCVDevStream * m_pSCVDevice;

	//�������
	std::string m_vdDeviceName;

	LONGLONG m_TriggerTimePt;
	LONGLONG m_TriggerTimePtEnd;

	//���ID
	int m_DeviceID;

	//��͸�
	int m_Width;
	int m_Height;

	//����Ƿ�����
	bool m_bIsDevConnected;

	//�Ƿ���ROIģʽ
	bool m_bIsTriggerROIMode;

	//�Ѿ����ù�ROI
	bool m_bIsTriggerROISetted;

	//�Ƿ񴥷�ģʽ
	bool m_bIsTriggerMode;

	//����
	long m_Gain;

	//�ع�
	long m_Exposure;

	//����
	long m_Brightness;

	//�Աȶ�
	long m_Contrast;

	//��ȡ֡��
	long m_FPS;

	//�����
	static bool  m_bInit;
	static bool  Init();
	static std::vector<DevHV2SCVMap>  m_MapHVList;
	CCriticalSection m_CCriticalSection;
};

#endif  //SCVDEV_USE_HV