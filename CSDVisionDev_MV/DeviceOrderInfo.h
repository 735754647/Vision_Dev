#pragma once
 /*******************************************************************************
**
** �ļ�����DeviceOrderInfo.h
**
** �����ߣ�xyc_01
**
** ����ʱ�䣺2014.10.27
**
** �����£�2014.10.27
** 
** ˵������Ӳ���豸���·�ָ����м�أ������������ļ�,
** 
** ģ����Ҫ���ܣ�
       1, ��װ��ع��̣��ṩ��صĺ���
	   
**
**  ģ���ʹ�ã�

       1��ֱ��ʹ��
��ʷ��¼��
	   1����ָ���ڴ�,2014.11.11�����컪
*******************************************************************************/
#if !defined (_SMCV_INCLIDE_VISIONODERINFO_H)
#define _SMCV_INCLIDE_VISIONODERINFO_H

#include "afxmt.h"
#include <vector>

using namespace std;
//1ά��Ϣ��
typedef std::vector<CString> CString1D;

//����ָ����Ϣ
class CDeviceOrderInfo
{
public:
	CDeviceOrderInfo(void);
	~CDeviceOrderInfo(void);

public:
	//���̱߳��
	void SetCritiaclSection(CCriticalSection* pSection);

	//������Ϣ������С
	void SetOrderSize(unsigned long size);

	//д��ָ���ڴ�
	void WriterOrder(CString order);
	
	//���ָ���ڴ�
	void ClearOrder(unsigned long size);

	//���õ�ǰ�ļ�¼ʹ��
	void EnableRecordOrder(bool bEable);

	//��ǰ�Ƿ�ʹ�ܼ�¼��״̬
	bool IsCurentRecordOrderAble();

	//��ȡָ��λ�õ���Ϣ
	CString GetOrderInfo(unsigned long index);

	//��ȡָ����Ϣ��ȡ������������Ľ��
	CString1D GetInfoOrderly();

	//��ȡ��ǰ��������
	unsigned long GetCurentIndex();

	//��ȡ��¼����
	unsigned long GetOrderSize();

	//��ȡ��׼ʱ��
	LONGLONG GetPCClock();

	//��ȡ��ͬ��ͬ��ָ���·�ʱ����
	LONGLONG GetTimeOrderBetweenLast(LONGLONG &timein,LONGLONG &timeout);

private:
	bool             m_bIsEnableRecordOrder;  //�Ƿ����ָ����Ϣ
	CString1D        m_strOrder;              //ָ����Ϣ�洢��
	unsigned long    m_nCurentOrderIndex;     //����ָ���λ��
	CCriticalSection* m_pOrderMutix;            //���߳�ͬ�����
};

#endif //_SMCV_INCLIDE_VISIONODERINFO_H