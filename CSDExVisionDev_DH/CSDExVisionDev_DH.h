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
	//���������ͼ������
	void scvVedioData(BYTE* pData,unsigned long width,unsigned long height,unsigned long bitCount,unsigned long bROI);

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

public:
	//֡��
	long scvSetFPS(double FPS);
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

	//��Ƶ������
	long scvIsLive(bool &isLive);
	long scvStartVedioLive();
	long scvStopVedioLive();

	//����,����Ӳ��
	long scvSetTriggerMode(int trigger);
	long scvIsTriggerMode(int &trigger);
	long scvTrigger();

	//��ʱ����
	long scvTimer();

	//�豸�Ƿ�����
	long scvIsConnected(bool &isConnect);

	//��ȡ�豸�ĵ��ȼ�¼
	long scvGetDeviceOrder(std::vector<CString>& orderList);

	//д���豸��¼
	long scvWriteDeviceOrder(CString orderList);
private:
	LPVOID m_CSDExVisionDev_DH;
};

#endif //_INCLUDE_AUTOCSDExVisionDev_DH_INTERFECE_H_