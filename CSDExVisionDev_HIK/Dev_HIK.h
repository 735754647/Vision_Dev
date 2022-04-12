#pragma once
 /*******************************************************************************
**
** �ļ�����CDevHIK.h
**
** �����ߣ�xyc_01
**
** ����ʱ�䣺2015.1.16
**
** �����£�2015.1.16
** 
** �汾�� ver 1.00.00
** 
** ģ����Ҫ���ܣ�
       ��װ�����������Ҫʵ�֣�

	   1, ����������ֳ�ʼ��

	   2������ص�����

	   3��ͼ��ת

	   4��֡�ʣ����棬���ŵ����úͻ�ȡ���������

	   5���������أ�ʵʱ��ʾ

	   ��

**
**  ģ���ʹ�ã�
       1��ʹ��ǰ�߳�ʼ����
	   
**
**
    ��ʷ��¼

*******************************************************************************/

#if !defined(_DEV_API_HIK_SMCVVEDIO_H_)
#define _DEV_API_HIK_SMCVVEDIO_H_

#include "./DeviceOrderInfo.h"
#include "afxmt.h"

class CDevHIK
{
public:
	CDevHIK(void);
	~CDevHIK(void);


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