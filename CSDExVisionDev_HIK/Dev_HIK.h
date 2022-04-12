#pragma once
 /*******************************************************************************
**
** 文件名：CDevHIK.h
**
** 创建者：xyc_01
**
** 创建时间：2015.1.16
**
** 最后更新：2015.1.16
** 
** 版本： ver 1.00.00
** 
** 模块主要功能：
       封装华用相机，主要实现：

	   1, 相机按照名字初始化

	   2，相机回调函数

	   3，图像翻转

	   4，帧率，增益，快门等设置和获取相机的属性

	   5，触发开关，实时显示

	   等

**
**  模块的使用：
       1，使用前线初始化库
	   
**
**
    历史记录

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


	//监控记录
	void GetOrder(std::vector<CString>& orderList);
	void WriteOrder(CString order);

protected:
	


public:
	bool m_bIsAdd;
    CDeviceOrderInfo    m_HVDevOrderInfo;                      //整个的信息存储
	LONGLONG tempTimeIn[500];
	LONGLONG tempTimeOut[500];

public:
	static bool g_init;
	static bool init();
	
};

#endif //_DEV_API_MV_SMCVVEDIO_H_