#include "StdAfx.h"
#include "Dev_DH.h"
//指令内存中存储的数目
#define  ORDER_SAVE_MAX    500 



bool CDevDH::init()
{
	return true;
}

CDevDH::CDevDH(void)
{
	m_bIsAdd=false;

	//指令监控

	m_HVDevOrderInfo.SetOrderSize(ORDER_SAVE_MAX);

	memset(tempTimeIn,0,sizeof(long)*500);
	memset(tempTimeOut,0,sizeof(long)*500);
}

CDevDH::~CDevDH(void)
{

}


//监控记录
void CDevDH::GetOrder(std::vector<CString>& orderList)
{
	orderList=m_HVDevOrderInfo.GetInfoOrderly();
}

void CDevDH::WriteOrder(CString order)
{
	m_HVDevOrderInfo.WriterOrder(order);
}


