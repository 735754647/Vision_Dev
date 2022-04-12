#pragma once
 /*******************************************************************************
**
** 文件名：DeviceOrderInfo.h
**
** 创建者：xyc_01
**
** 创建时间：2014.10.27
**
** 最后更新：2014.10.27
** 
** 说明：对硬件设备的下发指令进行监控，函数的声明文件,
** 
** 模块主要功能：
       1, 封装监控过程，提供监控的函数
	   
**
**  模块的使用：

       1，直接使用
历史记录：
	   1，清指令内存,2014.11.11，杨庆华
*******************************************************************************/
#if !defined (_SMCV_INCLIDE_VISIONODERINFO_H)
#define _SMCV_INCLIDE_VISIONODERINFO_H

#include "afxmt.h"
#include <vector>

using namespace std;
//1维信息符
typedef std::vector<CString> CString1D;

//定义指令信息
class CDeviceOrderInfo
{
public:
	CDeviceOrderInfo(void);
	~CDeviceOrderInfo(void);

public:
	//多线程标记
	void SetCritiaclSection(CCriticalSection* pSection);

	//设置信息容量大小
	void SetOrderSize(unsigned long size);

	//写入指令内存
	void WriterOrder(CString order);
	
	//清除指令内存
	void ClearOrder(unsigned long size);

	//设置当前的记录使能
	void EnableRecordOrder(bool bEable);

	//当前是否使能记录的状态
	bool IsCurentRecordOrderAble();

	//获取指定位置的信息
	CString GetOrderInfo(unsigned long index);

	//获取指令信息存取进行重新排序的结果
	CString1D GetInfoOrderly();

	//获取当前的索引号
	unsigned long GetCurentIndex();

	//获取记录个数
	unsigned long GetOrderSize();

	//获取基准时间
	LONGLONG GetPCClock();

	//获取相同相同轴指令下发时间间隔
	LONGLONG GetTimeOrderBetweenLast(LONGLONG &timein,LONGLONG &timeout);

private:
	bool             m_bIsEnableRecordOrder;  //是否更新指令信息
	CString1D        m_strOrder;              //指令信息存储体
	unsigned long    m_nCurentOrderIndex;     //最新指令的位置
	CCriticalSection* m_pOrderMutix;            //多线程同步标记
};

#endif //_SMCV_INCLIDE_VISIONODERINFO_H