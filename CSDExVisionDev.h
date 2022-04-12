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
	//��SPLCDev�豸�Ľӿ�
	virtual void scvDevInterface(SCVDevStream *pSCVDevice)=0;

	//���ñ����������
	virtual long scvSetDeviceName(CString strName)=0;
	virtual long scvGetDeviceName(CString& strName)=0;

	//���ñ������ID
	virtual long scvSetDeviceID(int devID)=0;
	virtual long scvGetDeviceID(int& devID)=0;

	//��ʼ���豸�ؼ���
	virtual long scvInitVedioLibrary()=0;

	//�˳��豸�ؼ���
	virtual long scvExitVedioLibrary()=0;

	//�����
	virtual long scvOpenCamDevice()=0;

	//��͸�
	virtual long scvSetCamImageSize(unsigned long width,unsigned long height)=0;

	//�ر����
	virtual long scvCloseDevice()=0;

	//����֮�����´�
	virtual long scvOpenCamWhenLost()=0;

public:
	//֡��
	virtual long scvSetFPS(double FPS)=0;
	virtual long scvGetFPS(double &fps)=0;

	//����
	virtual long scvSetBrightness(double bright)=0;
	virtual long scvGetBrightness(double &bright)=0;

	//�Աȶ�
	virtual long scvSetContrast(double contrast)=0;
	virtual long scvGetContrast(double &contrast)=0;

	//����
	virtual long scvGetExposureParm(double& exposure)=0;
	virtual long scvGetMaxExposureParm(double& exposure)=0;
	virtual long scvGetMinExposureParm(double& exposure)=0;
	virtual long scvSetExposureParm(long val)=0;

	//����
	virtual long scvGetGainParm(double& gain)=0;
	virtual long scvGetMaxGainParm(double& gain)=0;
	virtual long scvGetMinGainParm(double& gain)=0;
	virtual long scvSetGain(long val)=0;

	//��Ƶ������
	virtual long scvIsLive(bool &isLive)=0;
	virtual long scvStartVedioLive()=0;
	virtual long scvStopVedioLive()=0;

	//����,����Ӳ��
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

	//�豸�Ƿ�����
	virtual long scvIsConnected(bool &isConnect)=0;

	virtual bool scvSetCamDisConnected()=0;

	

	//��ʱ���ý���
	virtual long scvTimer()=0;

	//��ȡ�豸�ĵ��ȼ�¼
	virtual long scvGetDeviceOrder(std::vector<CString>& orderList)=0;

	//д���豸��¼
	virtual long scvWriteDeviceOrder(CString orderList)=0;
};

//����ӿ�
extern "C" __declspec(dllexport) HRESULT CreateVisionDev(CSDExVisionDev ** pp_MotionDev);
typedef HRESULT (*TCreateVisionDev)(CSDExVisionDev **pp_MotionDev);

#endif //_INCLUDE_AUTOCSDExVisionDev_INTERFECE_H_