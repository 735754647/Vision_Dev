#pragma once

#include "./CSDExVisionDev_HIK.h"

#include "Dev_HIK.h"

#include <vector>

#include "MvCameraControl.h"
#include "Dev_HIK_Lib.h"


class CDevHIKUser;

//��������Ľṹ��
struct DevHIK2SCVMap
{
	int nDevId;//��ǰ�豸������   
	CDevHIKUser* pObj;  //��ǰ�Ķ���
};

typedef struct _ImageData
{	
	void*    pDataBuffer;           //��ǰ���ݻ������ĵ�ַ
	int      nImgWidth;				//ÿ֡����ͼ��Ŀ��
	int      nImgHeight;			//ÿ֡����ͼ��ĸ߶�
	int      nBitCount;				//ÿ��������ռ���ֽ���
	int      nDevId;				//��ǰ�豸������       //***********
}ImageData, *pImageData;

class CDevHIKUser:public CDevHIK
{
public:
	CDevHIKUser(void);
	~CDevHIKUser(void);

public:
	//���������ͼ������
	virtual void scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI);

	//�����ʼ��
public:
	//��ʼ���豸�Ľӿ�
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

	//��ʱ����
	void scvTimer();

	//���úͻ�ȡ���������
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

	//���� ��λ0.1ms
	long scvGetExposureParm(double& exposure);
	long scvGetMaxExposureParm(double& exposure);
	long scvGetMinExposureParm(double& exposure);
	long scvSetExposureParm(long val);

	//����
	long scvGetGainParm(double& gain);
	long scvGetMaxGainParm(double& gain);
	long scvGetMinGainParm(double& gain);
	long scvSetGain(long val);

	//ͼ���ʽ
	long scvSetImageFormat(long channels);
	long scvGetImageFormat(long& _format);

	//������ת��
	long scvsetFlipH();
	long scvsetFlipV();

	//��Ƶ������
	long scvIsLive(bool &isLive);
	long scvStartVedioLive();
	long scvStopVedioLive();

	//����,����Ӳ��
	long scvSetTriggerMode(int trigger);
	long scvIsTriggerMode(int &trigger);
	long scvTrigger();

	//�豸�Ƿ�����
	long scvIsConnected(bool &isConnect);

	//�豸�Ƿ�����
	bool scvSetDisConnected(bool isConnect);

	//��õ�ǰ�豸����Ŀ
	long scvGetAvailableDevices(unsigned long &num);

	//��ȡ�豸�ĵ��ȼ�¼
	long scvGetDevOrder(std::vector<CString>& orderList);

	//���ݻص�
	void frameReady(ImageData Data);

	//�豸���̻߳���
private:
    void Lock();
	void UnLock();

	void SetConnectedFlag(bool flag);
	bool GetConnectedFlag();

	void SetOpenedFlag(bool flag);
	bool GetOpenedFlag();


	//��ȡʱ�ӻ�׼
	LONGLONG GetClock();

	//��ʼ����ʱ��
	void InitTimer(unsigned long TimerID,unsigned long bTime); 

	//�ж϶�ʱ���Ƿ����
	bool IsTimerEnd(unsigned long TimerID);

	void ThreadTimerLock();
	void ThreadTimerUnlock();

	//�ڲ�����
private:
	bool m_bIsDevOpened;//����򿪱�־
	bool m_bIsLive;//���ڲɼ���־λ
	int m_bIsTriggerMode;//����ģʽ��־λ
	CCriticalSection m_CCriticalTimerSection;
	//��ʱ��
	typedef struct tagVisionTimer 
	{
		LONGLONG TimerStart;
		LONGLONG TimerEnd;
		double Time;

	}VisionTimer ;
	vector<VisionTimer >    m_Timer;

	//�������
	std::string m_vdDeviceName;

	//���ID
	int m_DeviceID;
	
	LONGLONG m_TriggerTimePt;
	LONGLONG m_TriggerTimePtEnd;
	
	//��͸�
	int m_Width;
	int m_Height;

	//����Ƿ�����
	bool m_bIsDevConnected;

	//����
	double m_Gain;
	double m_MaxGain;
	double m_MinGain;

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

public:
	BOOL           	 		m_bMonoSensor;//ΪTRUEʱ��ʾ�����Ϊ�ڰ����
	BOOL            		m_bExit;//����֪ͨͼ��ץȡ�߳̽���
	MV_CC_DEVICE_INFO       m_sDeviceInfo;
	//ָ��
	SCVDevStream *			m_pSCVDevice;

	//������
	void *m_hCamera;
	//void *m_Grabber;
	
	CCriticalSection m_CCriticalSection;
};
