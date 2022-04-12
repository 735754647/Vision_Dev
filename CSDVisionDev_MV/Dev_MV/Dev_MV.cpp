#include "StdAfx.h"
#include "CameraApi.h"
#include "Dev_MV.h"
//ָ���ڴ��д洢����Ŀ
#define  ORDER_SAVE_MAX    500 



bool CDevMV::init()
{
	return true;
}

CDevMV::CDevMV(void)
{
	m_bIsAdd=false;

	//ָ����

	m_HVDevOrderInfo.SetOrderSize(ORDER_SAVE_MAX);

	memset(tempTimeIn,0,sizeof(long)*500);
	memset(tempTimeOut,0,sizeof(long)*500);
}

CDevMV::~CDevMV(void)
{

}


//��ؼ�¼
void CDevMV::GetOrder(std::vector<CString>& orderList)
{
	orderList=m_HVDevOrderInfo.GetInfoOrderly();
}

void CDevMV::WriteOrder(CString order)
{
	m_HVDevOrderInfo.WriterOrder(order);
}


