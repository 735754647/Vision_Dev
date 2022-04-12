#include "StdAfx.h"
#include "CameraApi.h"
#include "Dev_MV.h"
//指令内存中存储的数目
#define  ORDER_SAVE_MAX    500 



bool CDevMV::init()
{
	return true;
}

CDevMV::CDevMV(void)
{
	m_bIsAdd=false;

	//指令监控

	m_HVDevOrderInfo.SetOrderSize(ORDER_SAVE_MAX);

	memset(tempTimeIn,0,sizeof(long)*500);
	memset(tempTimeOut,0,sizeof(long)*500);
}

CDevMV::~CDevMV(void)
{

}


//监控记录
void CDevMV::GetOrder(std::vector<CString>& orderList)
{
	orderList=m_HVDevOrderInfo.GetInfoOrderly();
}

void CDevMV::WriteOrder(CString order)
{
	m_HVDevOrderInfo.WriterOrder(order);
}


