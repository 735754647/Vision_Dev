#pragma once



#if !defined(_DEV_API_DH_SMCVVEDIO_H_)
#define _DEV_API_DH_SMCVVEDIO_H_

#include "../DeviceOrderInfo.h"
#include "afxmt.h"

class CDevDH
{
public:
	CDevDH(void);
	~CDevDH(void);


	//��ؼ�¼
	void GetOrder(std::vector<CString>& orderList);
	void WriteOrder(CString order);

protected:
	


public:
	bool m_bIsAdd;
    CDeviceOrderInfo    m_HVDevOrderInfo;                      //��������Ϣ�洢
	LONGLONG tempTimeIn[500];
	LONGLONG tempTimeOut[500];

public:
	static bool g_init;
	static bool init();
	
};

#endif //_DEV_API_MV_SMCVVEDIO_H_