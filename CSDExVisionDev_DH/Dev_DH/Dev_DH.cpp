#include "StdAfx.h"
#include "Dev_DH.h"
//ָ���ڴ��д洢����Ŀ
#define  ORDER_SAVE_MAX    500 



bool CDevDH::init()
{
	return true;
}

CDevDH::CDevDH(void)
{
	m_bIsAdd=false;

	//ָ����

	m_HVDevOrderInfo.SetOrderSize(ORDER_SAVE_MAX);

	memset(tempTimeIn,0,sizeof(long)*500);
	memset(tempTimeOut,0,sizeof(long)*500);
}

CDevDH::~CDevDH(void)
{

}


//��ؼ�¼
void CDevDH::GetOrder(std::vector<CString>& orderList)
{
	orderList=m_HVDevOrderInfo.GetInfoOrderly();
}

void CDevDH::WriteOrder(CString order)
{
	m_HVDevOrderInfo.WriterOrder(order);
}


