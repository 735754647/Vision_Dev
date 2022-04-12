
#include "StdAfx.h"
#include "DeviceOrderInfo.h"

CDeviceOrderInfo::CDeviceOrderInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	m_pOrderMutix=NULL;
	m_bIsEnableRecordOrder=true;
	m_nCurentOrderIndex=0;
	m_strOrder.clear();
}
CDeviceOrderInfo::~CDeviceOrderInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
}

//多线程标记
void CDeviceOrderInfo::SetCritiaclSection(CCriticalSection* pSection)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	m_pOrderMutix=pSection;

}
//设置信息容量大小
void  CDeviceOrderInfo::SetOrderSize(unsigned long size)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Lock();
	}

	m_strOrder.clear();
	m_strOrder.resize(size);

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Unlock();
	}
}

//获取指定位置的信息
CString CDeviceOrderInfo::GetOrderInfo(unsigned long index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	CString strTemp=_T("");
	if (index>=m_strOrder.size())
	{
		AfxMessageBox(_T("获取指令信息超范围！"));
		return strTemp;
	}

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Lock();
	}

	strTemp=m_strOrder[index];

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Unlock();
	}

	return strTemp;
}
//获取指令信息存取进行重新排序的结果
CString1D CDeviceOrderInfo::GetInfoOrderly()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Lock();
	}
	CString1D strTemp1D;
	unsigned long nSize=m_strOrder.size();
	strTemp1D.resize(nSize);

	for (int i=0;i<nSize;i++)
	{
		CString strTemp;
		long tempIndex=0;
		if (i<m_nCurentOrderIndex)
		{
			tempIndex=i+nSize-m_nCurentOrderIndex;
		} 
		else
		{
			tempIndex=i-m_nCurentOrderIndex;
		}
		strTemp=GetOrderInfo(i);

		ASSERT(tempIndex>=0);
		ASSERT(tempIndex<nSize);
		strTemp1D[tempIndex]=strTemp;
	}

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Unlock();
	}

	return strTemp1D;
}
//写入指令内存
void CDeviceOrderInfo::WriterOrder(CString order)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	/*if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Lock();
	}
	unsigned long nSize=m_strOrder.size();
	if(m_bIsEnableRecordOrder)
	{
		if (m_nCurentOrderIndex>=nSize)
		{
			m_nCurentOrderIndex=0;
		}
		//ASSERT(m_nCurentOrderIndex<nSize);
		//ASSERT(m_nCurentOrderIndex>=0);

		//int nSizeIndexOut=order.GetLength();
		//bool lineFlag=false;
		//CString strSub;
		//int indexStart=0;
		//bool Oderstr1=false;
		//bool Oderstr2=false;
		//for(int i=0;i<nSizeIndexOut;i++)
		//{
		//	strSub=order.Mid(i,1);
		//	if(strSub==_T("+"))
		//	{
		//		indexStart=i+1;
		//		Oderstr1=true;
		//	}
		//	else if(strSub==_T(")"))
		//	{
		//		Oderstr2=true;
		//		strSub=order.Mid(indexStart,i+1-indexStart);
		//		break;
		//	}
		//}
		//if (!Oderstr1||!Oderstr1) //+和）都没有
		//{
		//	strSub=order;
		//}

		//CString strSub2;
		//int reOrderCount=0;
		//CString strTemp;
		//Oderstr1=false;
		//Oderstr2=false;
		//if(m_nCurentOrderIndex>1)
		//{
		//	nSizeIndexOut=m_strOrder[m_nCurentOrderIndex-1].GetLength();
		//	lineFlag=false;
		//	for(int i=0;i<nSizeIndexOut;i++)
		//	{
		//		strSub2=m_strOrder[m_nCurentOrderIndex-1].Mid(i,1);
		//		if(strSub2==_T("+"))
		//		{
		//			indexStart=i+1;
		//			Oderstr1=true;
		//		}
		//		else if(strSub2==_T(")"))
		//		{
		//			Oderstr2=true;
		//			strSub2=m_strOrder[m_nCurentOrderIndex-1].Mid(indexStart,i+1-indexStart);
		//			break;
		//		}
		//	}
		//	if (!Oderstr1||!Oderstr1) //+和）都没有
		//	{
		//		strSub2=m_strOrder[m_nCurentOrderIndex-1];
		//	}

		//	reOrderCount=0;
		//	strTemp=m_strOrder[m_nCurentOrderIndex-1].Left(2);
		//	CString strReal;
		//	CString strReOrder;
		//	int redoIndex=1;
		//	if(strTemp==_T("re"))
		//	{
		//		int nSizeIndex=m_strOrder[m_nCurentOrderIndex-1].GetLength();
		//		for(int i=0;i<nSizeIndex;i++)
		//		{
		//			strReal=m_strOrder[m_nCurentOrderIndex-1].Mid(i,1);
		//			if(strReal==_T("-"))
		//			{
		//				lineFlag=true;
		//				break;
		//			}
		//			redoIndex++;
		//		}

		//		strReal=m_strOrder[m_nCurentOrderIndex-1].Mid(redoIndex,nSizeIndex-redoIndex);
		//		strReOrder=m_strOrder[m_nCurentOrderIndex-1].Mid(2,redoIndex-1-2);
		//		reOrderCount=_tstoi(strReOrder);
		//	}
		//}
		//if(strSub2==strSub)
		//{
		//	reOrderCount++;
		//	strTemp.Format(_T("re%d-"),reOrderCount);
		//	m_nCurentOrderIndex--;
		//	m_strOrder[m_nCurentOrderIndex]=strTemp+order;
		//	m_nCurentOrderIndex++;
		//}
		//else
		{
			m_strOrder[m_nCurentOrderIndex]=order;
		    m_nCurentOrderIndex++;
		}
	}
	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Unlock();
	}*/
}
//清除指令内存
void CDeviceOrderInfo::ClearOrder(unsigned long size)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	SetOrderSize(size);
	m_nCurentOrderIndex=0;
}
//设置当前的记录使能
void CDeviceOrderInfo::EnableRecordOrder(bool bEable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Lock();
	}

	m_bIsEnableRecordOrder=bEable;

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Unlock();
	}
}

//当前是否使能记录的状态
bool CDeviceOrderInfo::IsCurentRecordOrderAble()
{
	return false;
	//AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	bool tempRetn=false;

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Lock();
	}

	tempRetn=m_bIsEnableRecordOrder;

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Unlock();
	}

	return tempRetn;
}
//获取当前的索引号
unsigned long CDeviceOrderInfo::GetCurentIndex()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	unsigned long tempRetn=0;

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Lock();
	}

	if(m_nCurentOrderIndex>0)
//		tempRetn=m_nCurentOrderIndex-1;
		tempRetn=m_nCurentOrderIndex;

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Unlock();
	}

	return tempRetn;
}
//获取记录个数
unsigned long CDeviceOrderInfo::GetOrderSize()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	unsigned long nSize=0;

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Lock();
	}
	nSize=m_strOrder.size();

	if (m_pOrderMutix!=NULL)
	{
		m_pOrderMutix->Unlock();
	}

	return nSize;
}

//获取基准时间
LONGLONG CDeviceOrderInfo::GetPCClock()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	LONGLONG time=0;
	LARGE_INTEGER  litmp; 
	LONGLONG       QPart1;
	QueryPerformanceCounter(&litmp); 
	QPart1 = litmp.QuadPart; // 获得基准值
	time = (LONGLONG)(QPart1); 
	return time;
}

//获取相同相同轴指令下发时间间隔
LONGLONG CDeviceOrderInfo::GetTimeOrderBetweenLast(LONGLONG &timein,LONGLONG &timeout)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	LARGE_INTEGER  litmp; 
	LONGLONG       dfMinus, dfFreq, dfTim; 
	QueryPerformanceFrequency(&litmp); 
	dfFreq = litmp.QuadPart; // 获得计数器的时钟频率

	timeout=GetPCClock();//获得系统时间
	dfMinus=timeout-timein;
	if(dfMinus<0)
		dfMinus+=0xffffffffffffffff; //溢出判断
	dfTim =1000*dfMinus / dfFreq; // 获得对应的时间值，单位为ms

	timein=GetPCClock();//获得系统时间;

	return dfTim;
}

