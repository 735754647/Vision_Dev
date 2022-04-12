#pragma once
 /*******************************************************************************
**
** �ļ�����CDevHV.h
**
** �����ߣ�����
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

#if !defined(_DEV_API_HV_SMCVVEDIO_H_)
#define _DEV_API_HV_SMCVVEDIO_H_

#if SCVDEV_USE_HV

#include "Dev_HV_inlcude/HVGigE_WP.h"
#include "../DeviceOrderInfo.h"
#include "afxmt.h"

class CDevHV
{
public:
	CDevHV(void);
	~CDevHV(void);

	/******************************************************************************
	* Function:	API_HV_EnumerateDevice
	* Description: �豸ö��
	* Format:
	*     HRESULT API_HV_EnumerateDevice(pHVGigE_Dev_i * pDev, int * nDevCount) ;
	* Params:
	*     pHVGigE_Dev_i * pDev: ��ȡ���豸��Ϣ
	*     int * nDevCount: ��ȡ�豸����
	* Return: 
	*     API_HV_SUCCESS: �ɹ�;   API_HV_NO_SUCH_DEVICE: δ�ҵ�
	******************************************************************************/
	HRESULT  API_HV_EnumerateDevice(pHVGigE_Dev_i * pDev, int * nDevCount);

	/******************************************************************************
	* Function:	API_HV_OpenDevice
	* Description: ���豸
	* Format:
	*     HRESULT API_HV_OpenDevice(int nDevId) ;
	* Params:
	*     int nId: �豸����
	* Return: 
	*     API_HV_SUCCESS: �ɹ�;   API_HV_NO_SUCH_DEVICE: δ�ҵ�
	******************************************************************************/
	HRESULT  API_HV_OpenDevice(int nDevId);

	/******************************************************************************
	* Function:	API_HV_DevCapInit
	* Description: �豸��׽��ʼ��
	* Format:
	*     HRESULT API_HV_DevCapInit(int nDevId, LPCSTR lpFileName = NULL) ;
	* Params:
	*     int nDevId
	*	  LPCSTR lpFileName: �����ļ�����·������Ϊ��ʱ��Ĭ��Ϊ��ǰĿ¼��
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT  API_HV_DevCapInit(int nDevId, LPCSTR lpFileName = NULL);

	/******************************************************************************
	* Function:	API_HV_DevCapRelease
	* Description: ��Դ�ͷ�
	* Format:
	*     HRESULT API_HV_DevCapRelease(int nDevId) ;
	* Params:
	*     void
	* Return: 
	*     void
	******************************************************************************/
	void     API_HV_DevCapRelease(int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetCallBack
	* Description: ���ûص�����
	* Format:
	*     HRESULT API_HV_SetCallBack(USER_CALLBACK_PROC pCallBack,int nDevId) ;
	* Params:
	*     USER_CALLBACK_PROC pCallBack: �ص�������ַ
	* Return: 
	*     void
	******************************************************************************/
	void     API_HV_SetCallBack(USER_CALLBACK_PROC pCallBack,int nDevId);

	/******************************************************************************
	* Function:	API_HV_StartCapture
	* Description: ��ʼͼ�񲶻�
	* Format:
	*     HRESULT API_HV_StartCapture(int nDevId) ;
	* Params:
	*     void
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT  API_HV_StartCapture(int nDevId);

	/******************************************************************************
	* Function:	API_HV_SuspendCapture
	* Description: ����/�ָ� Data Thread �� Show Thread.
	* Format:
	*     HRESULT API_HV_SuspendCapture(BOOL bSuspend,int nDevId);
	* Params:
	*     BOOL bSuspend: 1 for capture and show suspend; 0 for capture and show resume;
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT  API_HV_SuspendCapture(BOOL bSuspend,int nDevId);


	/******************************************************************************
	* Function:	API_HV_StopCapture
	* Description: ֹͣͼ�񲶻�
	* Format:
	*     HRESULT API_HV_StopCapture(int nDevId) ;
	* Params:
	*     void
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT  API_HV_StopCapture(int nDevId);

	/******************************************************************************
	* Function:	API_HV_ShowControlPage
	* Description: �򿪿������ԶԻ���
	* Format:
	*     HRESULT API_HV_ShowControlPage(int nDevId) ;
	* Params:
	*     void
	* Return: 
	*     �����ַ���
	******************************************************************************/
	HRESULT  API_HV_ShowControlPage(int nDevId);

	/******************************************************************************
	* Function:	API_HV_ShowRWPage
	* Description: �򿪶�/д�Ĵ����Ի���
	* Format:
	*     HRESULT API_HV_ShowRWPage(int nDevId) ;
	* Params:
	*     void
	* Return: 
	*     �����ַ���
	******************************************************************************/
	HRESULT  API_HV_ShowRWPage(int nDevId);

	HRESULT  API_HV_ShowSnapshotPage(int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetFrameRate
	* Description: ��ȡ֡��
	* Format:
	*     HRESULT API_HV_GetFrameRate(double & nRate, int nDevId) ;
	* Params:
	*     double & nRate: ֡��
	* Return: 
	*     �����ַ���
	******************************************************************************/
	HRESULT  API_HV_GetFrameRate(double & nRate, int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetTestInfo
	* Description: ��ȡ���Բ���
	* Format:
	*     HRESULT API_HV_GetTestInfo(int & nImgCount,int & nPacketMissing, int nDevId) ;
	* Params:
	*     int & nImgCount: ͼ����֡��
	*	  int & nPacketMissing�� ��������
	* Return: 
	*     �����ַ���
	******************************************************************************/
	HRESULT  API_HV_GetTestInfo(int & nImgCount,int & nPacketMissing,int &nFrameMissing, int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetParamInfo
	* Description: ��ȡ������Ϣ
	* Format:
	*     HRESULT API_HV_GetParamInfo(int nType, PVOID* ppParamInfoStruct,int nDevId) ;
	* Params:
	*     int nType: ���ȡ��Ϣ�����ͣ�VIDEO_INFO��
	*     PVOID* ppParamInfoStruct: ��ȡ�Ĳ�����Ϣ
	* Return: 
	*     �����ַ���
	******************************************************************************/
	HRESULT  API_HV_GetParamInfo(int nType, PVOID* ppParamInfoStruct,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetFrameBuffer
	* Description: ��ȡһ֡ͼ������
	* Format:
	*     HRESULT API_HV_GetFrameBuffer(long & lBufSize, LPBYTE * pBuf, int & nFrmWidth, int & nFrmHeight, int nDevId) ;
	* Params:
	*     long & lBufSize: ͼ�񻺴��С
	*     LPBYTE * pBuf: ͼ�񻺴�����
	*     int nFrmWidth: ͼ���
	*     int nFrmHeight: ͼ���
	* Return: 
	*     �����ַ���
	******************************************************************************/
	HRESULT  API_HV_GetFrameBuffer(long & lBufSize, LPBYTE * pBuf, int & nFrmWidth, int & nFrmHeight, int nDevId);


	/******************************************************************************
	* Function:	API_HV_SaveImg
	* Description: ����һ֡ͼ��Ϊ.bmp�ļ�
	* Format:
	*     HRESULT API_HV_SaveImg(LPBYTE pBuffer, LPCSTR lpFileName, const int nFrmWidth,
	*						  const int nFrmHeight, const long lBufferSize, int nDevId)
	* Params:
	*     LPBYTE pBuffer: ͼ������Bufferָ��
	*     LPCTSTR lpFileName: ��Ҫ�����bmp�ļ���
	*     int nFrmWidth: ͼ���
	*     int nFrmHeight: ͼ���
	*	  long lBufferSize: ͼ������Buffer�Ĵ�С
	* Return: 
	*     ����ʱ�����ش����ַ��������򣬷�����ȷ�ִ�
	******************************************************************************/
	HRESULT  API_HV_SaveImg(LPBYTE pBuffer, LPCSTR lpFileName, const int nFrmWidth,
												const int nFrmHeight, const long lBufSize, int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetErrorString
	* Description: ��ȡ�����ַ���
	* Format:
	*     HRESULT API_HV_GetErrorString(LONG lError) ;
	* Params:
	*     LONG lError: ����״̬
	* Return: 
	*     �����ַ���
	******************************************************************************/
	CHAR*    API_HV_GetErrorString(LONG lError);


	/******************************************************************************
	* Function:	API_HV_SetPreviewSnapMode()
	* Description: ����Ϊ����Ԥ��(contionus)ģʽ
	* Format:
	*     HRESULT API_HV_SetPreviewSnapMode(int nPreview, int nSnapMode)
	* Params:
	*		nPreview: 1 for preview mode; 
	*				  0 for snapshot mode;
	*		nSnapshot: snapshot mode, selected from 0 to 2, for both outer and inner
	*				  trigger source.     
	*
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/

	HRESULT  API_HV_SetPreviewSnapMode(int nPreview, int nSnapMode,int nDevId);



	/******************************************************************************
	* Function:	API_HV_GetPreviewSnapMode()
	* Description: �õ���ǰΪPreview��Snapshot
	* Format:
	*     HRESULT API_HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapStae,int nDevId)
	* Params:
	*		nPreview: 1 for preview mode; 0 for snapshot mode;
	*		nSnapshot: snapshot mode, selected from 0 to 2;  
	*		pPreSnapState:In\OUT; 
	*					  pPreSnapState.nPreview = 1, pPreSnapState.nSnapMode=0, for preview;  
	*					  pPreSnapState.nPreview = 0, pPreSnapState.nSnapMode=0-2, for snapshot of outer trigger source;
	*
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/

	HRESULT  API_HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapState,int nDevId);

	/******************************************************************************
	* Function:	void API_HV_GetMaxResolution()
	* Description: ��ȡCIS���ֱ��ʵĿ���
	* Format:
	*     HRESULT  API_HV_GetMaxXResolution(int& nMaxWidth, int& nMaxHeight,int nDevId)
	* Params:
	*     nMaxWidth:  IN/OUT; Width for CIS max resolution;
	*     nMaxHeight: IN/OUT; Height for CIS max resolution;
	* Return: 
	*     void
	******************************************************************************/

	HRESULT  API_HV_GetMaxResolution(int& nMaxWidth, int& nMaxHeight,int nDevId);

	//========================== Image Mirror Control ======================================

	/******************************************************************************
	* Function:	API_HV_SetImageMirror()
	* Description: ����ͼ��ľ����������ַ�ʽ��ˮƽ����ֱ��ˮƽ��ֱ��
	* Format:
	*     API_HV_SetImageMirror(int nMirror,int nDevId)
	* Params:
	*	  int nMirror�� ����ͼ��ľ����������ַ�ʽ��ˮƽ����ֱ��ˮƽ��ֱ��
	*					RowMirror=1; ColumnMirror=2; both=3;
	* Return:
	*     API_HV_SUCCESS:�ɹ���
	*     API_HV_REASONLESS_PARAMETER:����������Χ��
	*     API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_SetImageMirror(int nMirror,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetImageMirror()
	* Description: �õ�ͼ��ľ���ʽ��ˮƽ����ֱ��ˮƽ��ֱ��
	* Format:
	*     API_HV_GetImageMirror(int* pnMirror,int nDevId)
	* Params:
	*	  int* pnMirror: ���ص�ǰ�ľ���ʽ�������������ַ�ʽ��ˮƽ����ֱ��ˮƽ��ֱ��
	*					RowMirror=1; ColumnMirror=2; both=3;
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_GetImageMirror(int* pnMirror,int nDevId);

	//========================= Image Resolution Control ===========================================

	/******************************************************************************
	* Function:	API_HV_GetResolution
	* Description: ��ȡ��Ƶ�ķֱ���
	* Format:
	*     HRESULT API_HV_GetResolution(HVGigE_Video_i* psResolution,int nDevId)
	* Params:
	*	  HVGigE_Video_i* psResolution: ͼ��ķֱ���(sResolution)�ķ���ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetResolution(HVGigE_Video_i* psResolution,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetResolution
	* Description: ������Ƶ�ķֱ���
	* Format:
	*      HRESULT API_HV_SetResolution(HVGigE_Video_i sResolution, int nDevId)
	* Params:
	*	  HVGigE_Video_i sResolution��ͼ��ķֱ���(sResolution)
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_SetResolution(HVGigE_Video_i sResolution,int nDevId);

	//========================= Image Color Control ===========================================
	/******************************************************************************
	* Function:	API_HV_GetImageColorStat()
	* Description: �õ�ͼ��Ĳ�ɫ/�Ҷ�״̬
	* Format:
	*     API_HV_GetImageColorStat(BOOL* pbColor,int nDevId)
	* Params:
	*	  BOOL* pbColor�� ����ͼ��Ĳ�ɫ/�Ҷ�״̬
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_GetImageColorStat(BOOL* pbColor,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetImageColorStat()
	* Description: ����ͼ��Ĳ�ɫ/�Ҷ�״̬
	* Format:
	*     API_HV_SetImageColorStat(BOOL bColor, int nDevId)
	* Params:
	*	  BOOL bColor�� ����ͼ��Ĳ�ɫ/�Ҷ�״̬
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_SetImageColorStat(BOOL bColor, int nDevId);

	//========================= Image Gamma Control ===========================================

	/******************************************************************************
	* Function:	API_HV_GetImageGammaStat()
	* Description: �õ�ͼ���Gamma״̬
	* Format:
	*     API_HV_GetImageGammaStat(BOOL* pbGamma,int nDevId)
	* Params:
	*	  BOOL* pbColor�� ����ͼ���Gamma״̬
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_GetImageGammaStat(BOOL* pbGamma,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetImageGammaStat()
	* Description: ����ͼ���Gamma״̬
	* Format:
	*     API_HV_SetImageGammaStat(BOOL bGamma, int nDevId)
	* Params:
	*	  BOOL bColor�� ����ͼ��Gamma״̬
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_SetImageGammaStat(BOOL bGamma, int nDevId);

	//========================= Black Level Control ===========================================

	/******************************************************************************
	* Function:	API_HV_GetBlackLevelInfo
	* Description: ��ȡBlackLevel������Ϣ
	* Format:
	*     HRESULT API_HV_GetBlackLevelInfo( HVGigE_Control_i* psBlackLevel,int nDevId)
	* Params:
	*	   HVGigE_Control_i* psBlackLevel: ����sBlackLevel�Ĳ���ֵ��
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetBlackLevelInfo( HVGigE_Control_i* psBlackLevel,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetBlackLevelInfo
	* Description: ����BlackLevel������Ϣ
	* Format:
	*     HRESULT API_HV_SetParamInfo(HVGigE_Control_i sBlackLevel,int nDevId)
	* Params:
	*	  HVGigE_Control_i sBlackLevel: ��Ҫ���õ�BlackLevel�Ĳ���
	* Return:
	*      none
	*    
	******************************************************************************/

	HRESULT  API_HV_SetBlackLevelInfo(HVGigE_Control_i sBlackLevel,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetBlackLevelEnable
	* Description: ����BlackLevel.bEnable��ֵ
	* Format:
	*     HRESULT API_HV_SetBlackLevelEnable(BOOL bbEnable,int nDevId)
	* Params:
	*	  BOOL bEnable: ��Ҫ���õ�BlackLevel.bEnable��ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
	******************************************************************************/

	HRESULT  API_HV_SetBlackLevelEnable(BOOL bEnable,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetBlackLevelEnable
	* Description: ��ȡBlackLevel.bEnable������Ϣ
	* Format:
	*     HRESULT API_HV_GetBlackLevelEnable(BOOL* pbEnable,int nDevId)
	* Params:
	*	  BOOL* pbEnable: BlackLevel.bEnable��ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
	******************************************************************************/

	HRESULT  API_HV_GetBlackLevelEnable(BOOL* pbEnable,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetBlackLevelAuto
	* Description: ����BlackLevel.bAuto��ֵ
	* Format:
	*     HRESULT API_HV_SetBlackLevelAuto(BOOL bAuto,int nDevId)
	* Params:
	*	  BOOL bAuto: ��Ҫ���õ�sBlackLevel.bAuto��ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
	******************************************************************************/

	HRESULT  API_HV_SetBlackLevelAuto(BOOL bAuto,int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetBlackLevelAuto
	* Description: ��ȡBlackLevel.bAuto��ֵ
	* Format:
	*     HRESULT  API_HV_GetBlackLevelAuto(BOOL* pbAuto,int nDevId)
	* Params:
	*	  BOOL* pbAuto: BlackLevel.bAuto�ķ���ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
	******************************************************************************/


	HRESULT  API_HV_GetBlackLevelAuto(BOOL* pbAuto,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetBlackLevelRange
	* Description: ����sBlackLevel.sRange��ֵ
	* Format:
	*     HRESULT API_HV_SetBlackLevelRange(HVGigE_Range_i sRange,int nDevId)
	* Params:
	*	  HVGigE_Range_i sRange��BlackLevel����Чȡֵ��Χ
	* Return:
	*      API_HV_INVALID_PARAM:��Ч�Ĳ�����Χ��
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
	******************************************************************************/

	HRESULT  API_HV_SetBlackLevelRange(HVGigE_Range_i sRange,int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetBlackLevelRange
	* Description: ��ȡBlackLevel��ȡֵ��Χ
	* Format:
	*     HRESULT  API_HV_GetBlackLevelRange(HVGigE_Range_i* psRange,int nDevId)
	* Params:
	*	  HVGigE_Range_i* psRange: BlackLevel����Чȡֵ��Χ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_GetBlackLevelRange(HVGigE_Range_i* psRange,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetBlackLevelValue
	* Description: ����sBlackLevel.nValueArr[]��ֵ,���������ı�sBlackLevel.nValueArr[1:4]��
	* Format:
	*     HRESULT API_HV_SetBlackLevelValue(int* pnValue,int nDevId)
	* Params:
	*	  int* pnValue: ��Ҫ���õ�BlackLevel.nValue[]��ֵ
	* Return:
	*      API_HV_INVALID_PARAM:��Ч�Ĳ�����Χ��
	*	   API_HV_SUCCESS: �ɹ�����sBlackLevel.nValueArr[1:4]��ֵ
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	*
	* NOTE: just set the Black Value from sBlackLevel.nValueArr[1] to sBlackLevel.nValueArr[4],
	*       Have done NOTHING to sBlackLevel.nValueArr[0]��
	*    
	******************************************************************************/

	HRESULT  API_HV_SetBlackLevelValue(int* pnValue,int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetBlackLevelValue
	* Description: ��ȡBlackLevel.nValue��ֵ
	* Format:
	*     HRESULT API_HV_GetBlackLevelValue(int* pnValueArr,int nDevId)
	* Params:
	*	  int* pnValueArr: ����sBlackLevel.nValueArr[0:5]��ֵ(BlackLevel.nValueArr[0:5])
	* Return:
	*	  API_HV_SUCCESS:�����ɹ�
	*     API_HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
	*    
	******************************************************************************/

	HRESULT  API_HV_GetBlackLevelValue(int* pnValueArr,int nDevId);


	//========================== Gain Control =========================================================

	/******************************************************************************
	* Function:	API_HV_GetGainInfo
	* Description: ��ȡGain�Ĳ�����Ϣ
	* Format:
	*     HRESULT API_HV_GetGainInfo(HVGigE_Control_i* psGain,int nDevId)
	* Params:
	*     HVGigE_Control_i* psGain: Gain�ķ���ֵ
	* Return:
	*	  API_HV_SUCCESS:�����ɹ�
	*     API_HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
	******************************************************************************/

	HRESULT  API_HV_GetGainInfo(HVGigE_Control_i* psGain,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetGainInfo
	* Description: ����Gain������Ϣ
	* Format:
	*     HRESULT API_HV_SetGainInfo(HVGigE_Control_i sGain,int nDevId)
	* Params:
	*	  HVGigE_Control_i sGain: ��Ҫ���õ�Gain�Ĳ���
	* Return:
	*      HRESULT hResult: ״̬����
	*    
	******************************************************************************/

	HRESULT  API_HV_SetGainInfo(HVGigE_Control_i sGain,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetGainEnable
	* Description: ����sGain.bEnable��ֵ
	* Format:
	*     HRESULT API_HV_SetGainEnable(BOOL bEnable,int nDevId)
	* Params:
	*	  bEnable: ��Ҫ���õ�sGain.bEnable��ֵ
	* Return:
	*	  API_HV_SUCCESS:�����ɹ�
	*     API_HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
	******************************************************************************/

	HRESULT  API_HV_SetGainEnable(BOOL bEnable,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetGainEnable
	* Description: ��ȡsGain.bEnable��ֵ
	* Format:
	*     HRESULT API_HV_GetGainEnable(BOOL* pbEnable,int nDevId)
	* Params:
	*	  BOOL* bEnable�����ص�sGain.bEnable��ֵ
	* Return:
	*	  API_HV_SUCCESS:�����ɹ�
	*     API_HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
	******************************************************************************/

	HRESULT  API_HV_GetGainEnable(BOOL* pbEnable,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetGainAuto
	* Description: ����sGain.bAuto��ֵ
	* Format:
	*     HRESULT API_HV_SetGainAuto(BOOL bAuto,int nDevId)
	* Params:
	*	  BOOL bAuto: ��Ҫ���õ�sGain.bAuto��ֵ
	* Return:
	*	  API_HV_SUCCESS:�����ɹ�
	*     API_HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
	******************************************************************************/

	HRESULT  API_HV_SetGainAuto(BOOL bAuto,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetGainAuto
	* Description: ��ȡsGain.bAuto��ֵ
	* Format:
	*     HRESULT API_HV_GetGainAuto(BOOL* pbAuto,int nDevId)
	* Params:
	*	  BOOL* pbAuto������sGain.bAuto��ֵ
	* Return:
	*	  API_HV_SUCCESS:�����ɹ�
	*     API_HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
	******************************************************************************/

	HRESULT  API_HV_GetGainAuto(BOOL* pbAuto,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetGainRange
	* Description: ����sGain.sRange��ֵ
	* Format:
	*     HRESULT API_HV_SetGainRange(HVGigE_Range_i sRange,int nDevId)
	* Params:
	*     HVGigE_Range_i sRange: Gain����Чȡֵ��Χ
	* Return:
	*      API_HV_INVALID_PARAM:��Ч�Ĳ�����Χ��
	*	   API_HV_SUCCESS: �ɹ���
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetGainRange(HVGigE_Range_i sRange,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetGainRange
	* Description: ��ȡsGain.sRange��ֵ
	* Format:
	*     HRESULT API_HV_GetGainRange(HVGigE_Range_i* psRange,int nDevId)
	* Params:
	*	  HVGigE_Range_i* psRange��sGain.sRange�ķ���ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ���
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_GetGainRange(HVGigE_Range_i* psRange,int nDevId);



	/******************************************************************************
	* Function:	API_HV_SetGainValue
	* Description: ����sGain.nValue[0:4]��ֵ
	* Format:
	*     HRESULT API_HV_SetGainValue(int* pnValueArr,int nDevId)
	* Params:
	*	  int* pValueArr: sGain.valueArr[0:4]��ֵ
	* Return:
	*      API_HV_INVALID_PARAM:��Ч�Ĳ�����Χ��
	*	   API_HV_SUCCESS: �ɹ�����Gain��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	* 
	* NOTE: set gain value from sGain.nValue[0] to sGain.nValue[4].   
	******************************************************************************/

	HRESULT  API_HV_SetGainValue(int* pValueArr,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetGainValue
	* Description: ��ȡsGain.nValue[0:4]��ֵ
	* Format:
	*     HRESULT API_HV_GetGainValue(int* nValue,int nDevId)
	* Params:
	*	  int* nValue������sGain.nValueArr[0:4]�ĵ�ǰֵ��������
	*				   Global Gain��G1 Gain��G2 Gain��R Gain, B Gain;
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Gain��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetGainValue(int* pnValue,int nDevId);

	//======================== Exposure Control ======================================================

	////////////////////////////////////////////////////////////////////////////////////
	//			Exposure�Ĳ����������ȡ
	//
	/******************************************************************************
	* Function:	API_HV_GetExposureInfo
	* Description: ��ȡExposure�Ĳ�����Ϣ
	* Format:
	*     HRESULT API_HV_GetExposureInfo(HVGigE_Control_i* psExposure,int nDevId)
	* Params:
	*	  HVGigE_Control_i* psExposur:����Exposure�����ò���
	* Return:
	*	   API_HV_SUCCESS: �ɹ���
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetExposureInfo(HVGigE_Control_i* psExposure,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetExposureInfo
	* Description: ����Exposure������Ϣ
	* Format:
	*     HRESULT API_HV_SetExposureInfo(HVGigE_Control_i sExposure,int nDevId)
	* Params:
	*	  HVGigE_Control_i sExposure: ��Ҫ���õ�Exposure�Ĳ�����Ϣ
	* Return:
	*	   API_HV_SUCCESS: �ɹ���
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetExposureInfo(HVGigE_Control_i sExposure,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetExposureEnable
	* Description: ����sExposure.bEnable��ֵ
	* Format:
	*     HRESULT API_HV_SetExposureEnable(BOOL bEnable,int nDevId)
	* Params:
	*	  bEnable: ��Ҫ���õ�sExposure.bEnable��ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Gain��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetExposureEnable(BOOL bEnable,int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetExposureEnable
	* Description: ��ȡExposure.bEnable������Ϣ
	* Format:
	*     BOOL API_HV_GetExposureEnable(BOOL* pbEnable,int nDevId)
	* Params:
	*	  BOOL* pbEnable: Exposure.bEnable��״̬
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Gain��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetExposureEnable(BOOL* pbEnable,int nDevId);



	/******************************************************************************
	* Function:	API_HV_SetExposureAuto
	* Description: ����Exposure.bAuto��ֵ
	* Format:
	*     HRESULT API_HV_SetExposureAuto(BOOL bAuto,int nDevId)
	* Params:
	*	  BOOL bAuto: ��Ҫ���õ�sExposure.bAuto��ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ���
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetExposureAuto(BOOL bAuto,int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetExposureAuto
	* Description: ��ȡsExposure.bAuto��ֵ
	* Format:
	*     HRESULT API_HV_GetExposure.bAuto(BOOL* pbAuto,int nDevId)
	* Params:
	*	  BOOL* pbAuto: sExposure.bAuto��ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ���
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetExposureAuto(BOOL* pbAuto,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetExposureRange
	* Description: ����Exposure����Чȡֵ��Χ��sExposure.sRange��ֵ
	* Format:
	*     HRESULT API_HV_SetExposureRange(HVGigE_Range_i sRange,int nDevId)
	* Params:
	*	  HVGigE_Range_i sRange��Exposure����Чȡֵ��Χ��sExposure.sRange��ֵ
	* Return:     
	*      API_HV_INVALID_PARAM: ����������Ч��Χ֮�ڣ�
	*	   API_HV_SUCCESS: �ɹ�����Exposure�ķ�Χ
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetExposureRange(HVGigE_Range_i sRange,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetExposureRange
	* Description: ��ȡExposure����Чȡֵ��Χ,sExposre.sRange��ֵ
	* Format:
	*     HRESULT  API_HV_GetExposureRange(HVGigE_Range_i* psRange,int nDevId)
	* Params:
	*	  HVGigE_Range_i* psRange: Exposure����Чȡֵ��Χ��sExposure.sRange��ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure�ķ�Χ
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_GetExposureRange(HVGigE_Range_i* psRange,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetExposureValue
	* Description: ����Exposure.nValue��ֵ
	* Format:
	*     HRESULT API_HV_SetExposureValue(int nValue,int nDevId)
	* Params:
	*	  nValue: Exposure��ֵ(Exposure.nValue),��λΪ������
	* Return:
	*      API_HV_INVALID_PARAM: ����������Ч��Χ֮�ڣ�
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetExposureValue(int nValue,int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetExposureValue
	* Description: ��ȡExposure.nValue��ֵ
	* Format:
	*     HRESULT API_HV_GetExposureValue(int* pnValue,int nDevId)
	* Params:
	*	  int* pnValue:  Exposure�ĵ�ǰֵ(Exposure.nValue��ֵ)����λΪ����
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetExposureValue(int* pnValue,int nDevId);


	//======================== Snapshot Control ======================================================
	///////////////////////////////////////////////////////////////////////////////////
	//		Snapshot �Ĳ����������ȡ
	//

	/******************************************************************************
	* Function:	API_HV_GetSnapInfo
	* Description: ��ȡExposure�Ĳ�����Ϣ
	* Format:
	*     HRESULT API_HV_GetSnapInfo(HVGigE_SnapControl_i* psSnapControl, int nDevId)
	* Params:
	*	  HVGigE_SnapControl_i* psSnapControl: Snapshot�����ò���
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetSnapInfo(HVGigE_SnapControl_i* psSnapControl, int nDevId);


	/******************************************************************************
	* Function:	API_HV_SetSnapInfo
	* Description: ����Snapshot������Ϣ
	* Format:
	*     HRESULT API_HV_SetSnapInfo(HVGigE_SnapControl_i sSnap, int nDevId)
	* Params:
	*	  HVGigE_SnapControl_i sSnap: ��Ҫ���õ�Snapshot�Ĳ���
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetSnapInfo(HVGigE_SnapControl_i sSnap, int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetSnapDebounceTime()
	* Description: ��������ģʽʱ��ȥ����ʱ��(DebouncerTime)��ʱ�䵥λΪus.
	* Format:
	*     HRESULT API_HV_SetSnapDebounceTime(LONG lDebouncerTime,int nDevId)
	* Params:
	*	 LONG lDebouncerTime: ȥ����ʱ�䣬��λΪus
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetSnapDebounceTime(LONG lDebouncerTime,int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetSnapDebounceTime()
	* Description: ��ȡ����ģʽʱ��ȥ����ʱ��(DebouncerTime)��ʱ�䵥λΪus.
	* Format:
	*     LONG API_HV_GetSnapDebounceTime(LONG *plDebouncerTime,int nDevId)
	* Params:
	*	  LONG lDebouncerTime: ����ȥ����ʱ�䣬��λΪus
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetSnapDebounceTime(LONG *plDebouncerTime,int nDevId);



	/******************************************************************************
	* Function:	API_HV_SetSnapExpTime()
	* Description: ��������ģʽʱ���ع�ʱ��(ExposureTime)��ʱ�䵥λΪus.
	* Format:
	*     API_HV_SetSnapExpTime(LONG lExpTime,int nDevId)
	* Params:
	*	  LONG lExpTime���ع�ʱ�䣬��λΪus
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetSnapExpTime(LONG lExpTime,int nDevId);



	/******************************************************************************
	* Function:	API_HV_GetSnapExpTime()
	* Description: �������ģʽʱ���ع�ʱ��(ExposureTime)��ʱ�䵥λΪus.
	* Format:
	*     LONG API_HV_GetSnapExpTime(LONG* plExpTime,int nDevId) 
	* Params:
	*	 LONG* plExpTime�������ع�ʱ�䣬��λΪ΢��
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetSnapExpTime(LONG* plExpTime,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange)
	* Description: ��������ģʽʱ���ع�ʱ��(ExposureTime)����Чֵ��Χ.ʱ�䵥λΪus.
	* Format:
	*     HResult API_HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange,int nDevId)
	* Params:
	*	 HVGigE_Range_i* psRange�������ع�ʱ����Чֵ�ķ�Χ����λΪ΢��
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId)
	* Description: ��������ģʽʱ������Ƶ�ʵ���Чֵ��Χ.
	* Format:
	*     HResult API_HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId)
	* Params:
	*	 HVGigE_Range_i* psRange����������ģʽʱ������Ƶ�ʵ���Чֵ��Χ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetTrigImgCountRange(HVGigE_Range_i* psRange)
	* Description: ��������ģʽʱ������Ƶ�ʵ���Чֵ��Χ.
	* Format:
	*     HResult API_HV_GetTrigImgCountRange(HVGigE_Range_i* psRange,int nDevId)
	* Params:
	*	 HVGigE_Range_i* psRange����������ģʽʱ������������������Чֵ��Χ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetTrigImgCountRange(HVGigE_Range_i* psRange,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetSnapTrigFreqImgCount()
	* Description: ��������ģʽʱ��������Ƶ���Լ�ÿ�δ��������ͼ������
	* Format:
	*     HRESULT API_HV_SetSnapTrigFreqImgCount(LONG lTrigFreq, LONG lTrigImgCount,int nDevId)
	* Params:
	*	 LONG lTrigFreq: ��������ģʽʱ��(����ƣ��Ĵ���Ƶ�ʡ���λΪÿ���֡����
	*    LONG lTrigImgCount������һ�Σ����������ͼ��֡��
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_SetSnapTrigFreqImgCount(LONG lTrigFreq, LONG lTrigImgCount,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetSnapTrigFreqImgCount()
	* Description: ��������ģʽʱ��������Ƶ���Լ�ÿ�δ��������ͼ������
	* Format:
	*     HRESULT API_HV_GetSnapTrigFreqImgCount(LONG* plTrigFreq, LONG* plTrigImgCount,int nDevId)
	* Params:
	*	 LONG* plTrigFreq: ��������ģʽʱ��(����ƣ��Ĵ���Ƶ�ʡ���λΪÿ���֡����
	*    LONG* plTrigImgCount������һ�Σ����������ͼ��֡��
	* Return:
	*	   API_HV_SUCCESS: �ɹ�����Exposure��ֵ��
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetSnapTrigFreqImgCount(LONG* plTrigFreq, LONG* plTrigImgCount,int nDevId);


	/******************************************************************************
	* Function:	void API_HV_SaveParaToIniFile()
	* Description: ���������浽ini�ļ�
	* Format:
	*     HRESULT API_HV_SaveParaToIniFile(int nDevId)
	* Params:
	*	  none
	* Return: 
	*     void
	******************************************************************************/

	HRESULT  API_HV_SaveParaToIniFile(int nDevId);

	/******************************************************************************
	* Function:	void API_HV_IniCamFromIniFile()
	* Description: ʹ��ini�ļ��еĲ������������
	* Format:
	*     HRESULT API_HV_IniCamFromIniFile(int  nDevId)
	* Params:
	*	  none
	* Return: 
	*     void
	******************************************************************************/

	HRESULT  API_HV_IniCamFromIniFile(int nDevId,LPCSTR lpFileName = NULL);

	/******************************************************************************
	* Function:	API_HV_SetSnapIOMode()
	* Description: ��������ģʽ(snapshot)�£����IO����ģʽ��
	* Format:
	*     HRESULT API_HV_SetSnapIOMode(HVGigE_SnapIO_Mode_i sSnapIOMode)
	* Params:
	*		sSnapIOMode.nInMode:  0 for falling-edge valid trigger; 
	*							  1 for rising-edge valide trigger;
	*							  2 for low-level valid trigger;
	*							  3 for high-level valid trigger;
	*		sSnapIOMode.nOutMode: 0 for low-level output;
	*							  1 for high-level output;  
	*
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/

	HRESULT  API_HV_SetSnapIOMode(HVGigE_SnapIO_Mode_i sSnapIOMode,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetSnapIOMode()
	* Description: ��������ģʽ(snapshot)�£����IO����ģʽ��
	* Format:
	*     HRESULT API_HV_GetSnapIOMode(HVGigE_SnapIO_Mode_i* psSnapIOMode,int nDevId)
	* Params:
	*		psSnapIOMode->nInMode:  0 for falling-edge valid trigger; 
	*								1 for rising-edge valide trigger;
	*								2 for low-level valid trigger;
	*								3 for high-level valid trigger;
	*		psSnapIOMode->nOutMode: 0 for low-level output;
	*								1 for high-level output;  
	*
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/

	HRESULT  API_HV_GetSnapIOMode(HVGigE_SnapIO_Mode_i* psSnapIOMode,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetRawData(HVGigE_Img_i* pRawFrameInfo)
	* Description: ����RawData���ݣ�
	* Format:
	*     HRESULT API_HV_GetRawData(HVGigE_Img_i* pRawFrameInfo,int nDevId)
	* Params:
	*		HVGigE_Img_i* pRawFrameInfo:  RawData ��Ϣ
	*		pRawFrameInfo->nImgHeight: ͼ��ĸ�
	*		pRawFrameInfo->nImgWidth��ͼ��Ŀ�
	*		pRawFrameInfo->nBitCount��ÿ��ͼ��������ռ���ֽ���, ֵΪ1
	*		pRawFrameInfo->pDataBuffer��ָ��RawData ͼ������Buffer��ָ��	
	*
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT  API_HV_GetRawData(HVGigE_Img_i* pRawFrameInfo,int nDevId);


	/*****************************************************************************
	* Function:	API_HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo)
	* Description: ����RGB���ݣ�
	* Format:
	*     HRESULT API_HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo,int nDevId)
	* Params:
	*		HVGigE_Img_i* pRawFrameInfo:  RawData ��Ϣ
	*		pRGBFrameInfo->nImgHeight: ͼ��ĸ�
	*		pRGBFrameInfo->nImgWidth��ͼ��Ŀ�
	*		pRGBFrameInfo->nBitCount��ÿ��ͼ��������ռ���ֽ�����ֵΪ3
	*		pRGBFrameInfo->pDataBuffer��ָ��RGBͼ������Buffer��ָ��	
	*
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT  API_HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo,int nDevId);


	/******************************************************************************
	* Function:	API_HV_SnapSWTrigger()
	* Description: Snapshotģʽʱ������ sw Trigger(�������)����Ӧ����
	* Format:
	*     void API_HV_SnapSWTrigger()
	* Params:
	*     void
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	*     API_HV_UNSUCCESS: ʧ��
	******************************************************************************/
	HRESULT 	API_HV_SnapSWTrigger(int nDevId);

	/******************************************************************************
	* Function:	API_HV_CloseDevice
	* Description: �ر�������ͷ���Դ
	* Format:
	*     HRESULT API_HV_CloseDevice(int nDevId) ;
	* Params:
	*     void
	* Return: 
	*     void
	******************************************************************************/
	void  API_HV_CloseDevice(int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetROI
	* Description: ������Ƶ��ROI(Region of Interest)
	* Format:
	*      HRESULT API_HV_SetROI(int Original_x, int Original_y,
	*						int nImgWidth, int nImgHeight,int nDevId)
	* Params:
	*	  int Oringination_x: ROI����ʼ��x����
	*	  int Oringination_y: ROI����ʼ��y����
	*     int nImgWidth: ROI�Ŀ��
	*     int nImgHeight: ROI�ĸ߶�
	*     int nDevId: �豸������
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_SetROI(int Original_x, int Original_y, 
											  int nImgWidth, int nImgHeight,int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetROI
	* Description: ��ȡ��Ƶ��ROI(Region of Interest)
	* Format:
	*      HRESULT API_HV_GetROI(int Original_x, int Original_y,
	*						int nImgWidth, int nImgHeight,int nDevId)
	* Params:
	*	  int nStart_x: ��ȡROI����ʼ��x����
	*	  int nStart_y: ��ȡROI����ʼ��y����
	*     int nImgWidth: ��ȡROI�Ŀ��
	*     int nImgHeight: ��ȡROI�ĸ߶�
	*     int nDevId: �豸������
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT  API_HV_GetROI(int &nStart_x, int &nStart_y, 
											  int &nImgWidth, int &nImgHeight,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetResolutionMode
	* Description: ���÷ֱ���ģʽ
	* Format:
	*     HRESULT API_HV_SetResolutionMode(HVGige_Resolution Res_Mode, int nDevId) ;
	* Params:
	*     HVGige_Resolution Res_Mode �ֱ���ģʽ
	*	  int nDevId  �豸������
	* Return: 
	*     API_HV_SUCCESS  �ɹ�
	******************************************************************************/
	HRESULT  API_HV_SetResolutionMode(HVGige_Resolution Res_Mode, int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetPacketSize
	* Description: ����sGain.nValue[0:4]��ֵ
	* Format:
	*     HRESULT API_HV_SetPacketSize(int nPacketSize,int nDevId)
	* Params:
	*	   int nPacketSize   ���ð���С
	*	   int nDevId   �豸����
	* Return:
	*      API_HV_DEVICE_CONNECT_TIMEOUT:���ӳ�ʱ��
	*	   API_HV_SUCCESS: �ɹ����ð���С��   
	******************************************************************************/

	HRESULT  API_HV_SetPacketSize(int nPacketSize,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetGrrMode_ExpFlash()
	* Description: ����Drrģʽ�µ��ع�ʱ����������������ӳ�ʱ��
	* Format:
	*     HRESULT API_HV_SetGrrMode_ExpFlash(long lExposureTime, long lFlashDelayTime, int nDevId)
	* Params:
	*     long lExposureTime : Grr ģʽ�µ��ع�ʱ�� ����λus��
	*     long lFlashDelayTime �� ����������ʱʱ�䣨��λus��
	*	  int nDevId : ���������
	* Return: 
	*     API_HV_SUCCESS: �ɹ�   API_HV_UNSUCCESS�����ɹ���û������Grrģʽ
	******************************************************************************/

	HRESULT  API_HV_SetGrrMode_ExpFlash(long lExposureTime, long lFlashDelayTime, int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetImageChannel
	* Description: ��ȡͼ���ͨ������Ϊ1����3
	* Format:
	*     HRESULT API_HV_GetImageChannel(int& nChannel,int nDevId)
	* Params:
	*	  int& nBitCount: ͼ��ͨ�����ķ���ֵ
	* Return:
	*	   API_HV_SUCCESS: �ɹ�
	*      API_HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/

	HRESULT  API_HV_GetImageChannel(int& nChannel,int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetImageDataType
	* Description: ������������ͼ���ʽ
	* Format:
	*     HRESULT API_HV_SetImageDataMode(int nDevId) ;
	* Params:
	*     void
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/

	HRESULT  API_HV_SetImageDataType(int nDevId, int nImgDataType);


	/******************************************************************************
	* Function:	API_HV_GetCameraType()
	* Description: �õ���ǰ����ͺ�(Camera Type),�磺HV130GM��
	* Format:
	*     int API_HV_GetCameraType(int nDevId)
	* Params:
	*     int nDevId  �豸����
	* Return: 
	*     �ɹ�������Camera Type�����򷵻�0
	******************************************************************************/
	CAMERA_TYPE  API_HV_GetCameraType(int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetBrightnessFactor()
	* Description: �����������
	* Format:
	*     API_HV_SetBrightnessFactor(float Brightness, int nDevId)
	* Params:
	*	  float Brightness		����        ��Ч��Χ(-1,1]  
	*     int nDevId  �豸����
	* Return: 
	*     �ɹ���return API_HV_SUCCESS; ������ֵ������Χ��Ĭ��Ϊ-0.94��1
	******************************************************************************/
	HRESULT  API_HV_SetBrightnessFactor(float Brightness, int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetBrightnessFactor()
	* Description: ��ȡ��ǰ�������ֵ
	* Format:
	*     API_HV_GetBrightnessFactor(float &Brightness, int nDevId)
	* Params:
	*	  float &Brightness		����        ��Ч��Χ(-1,1]  
	*     int nDevId  �豸����
	* Return: 
	*     �ɹ���return API_HV_SUCCESS; 
	******************************************************************************/
	HRESULT  API_HV_GetBrightnessFactor(float &Brightness, int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetContrastFactor()
	* Description: ��������Աȶ�
	* Format:
	*     API_HV_SetContrastFactor(float Constrast, int nDevId)
	* Params:
	*	  float Constrast       �Աȶ�		��Ч��Χ(-1,1]
	*     int nDevId  �豸����
	* Return: 
	*     �ɹ���return API_HV_SUCCESS; ������ֵ������Χ��Ĭ��Ϊ-0.94��1
	******************************************************************************/
	HRESULT  API_HV_SetContrastFactor(float Constrast, int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetContrastFactor()
	* Description: ��������Աȶ�
	* Format:
	*     API_HV_GetContrastFactor(float &Constrast, int nDevId)
	* Params:
	*	  float Constrast       �Աȶ�		��Ч��Χ(-1,1]
	*     int nDevId  �豸����
	* Return: 
	*     �ɹ���return API_HV_SUCCESS; ������ֵ������Χ��Ĭ��Ϊ-0.94��1
	******************************************************************************/
	HRESULT  API_HV_GetContrastFactor(float &Constrast, int nDevId);

	/******************************************************************************
	* Function:	API_HV_AKeyWhiteBalance()
	* Description: һ����ƽ��
	* Format:
	*     API_HV_AKeyWhiteBalance(int nDevId)
	* Params:
	*     int nDevId  �豸����
	* Return: 
	*     �ɹ���return API_HV_SUCCESS; ע��ֻ��Բ�ɫ���
	******************************************************************************/
	HRESULT  API_HV_AKeyWhiteBalance(int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetUserDefNum()
	* Description: �����û��Զ������к�
	* Format:
	*     HRESULT API_HV_SetUserDefNum(LPSTR lpSeriesNum,int nDevId)
	* Params:
	*     LPCSTR lpSeriesNum : �����û��Զ������к�
	*	  int nDevId : ���������
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT  API_HV_SetUserDefNum(LPSTR lpSeriesNum, int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetUserDefNum()
	* Description: ��ȡ�û��Զ������к�
	* Format:
	*     HRESULT API_HV_GetUserDefNum(LPSTR lpSeriesNum,int nDevId)
	* Params:
	*     LPCSTR lpSeriesNum : �����û��趨���к�
	*	  int nDevId : ���������
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT  API_HV_GetUserDefNum(LPSTR lpSeriesNum, int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetGPIOMode(int nMode, int nDevId)
	* Description: ѡ��GPIO�������
	* Format:
	*     HRESULT  API_HV_SetGPIOMode(int nMode, int nDevId)
	* Params:
	*     int nValue   0Ϊ��������ģʽ��1ΪPC�������ģʽ
	*     int nDevId   ���������
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	*     API_HV_UNSUCCESS: ʧ��
	*     API_HV_INVALID_PARAM: ��Ч����
	******************************************************************************/
	HRESULT 	API_HV_SetGPIOMode(int nMode, int nDevId);

	/******************************************************************************
	* Function:	API_HV_SetGPIOValue(bool bValue, int nDevId)
	* Description: ѡ��GPIO�������
	* Format:
	*     HRESULT  API_HV_SetGPIOValue(bool bValue, int nDevId)
	* Params:
	*     bool bValue   FalseΪ�Ͽ���TrueΪ��ͨ����API_HV_GPIOMode ѡΪ����ƣ�ֵΪ0��ģʽʱ���ú�����Ч
	*     int nDevId   ���������
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	*     API_HV_UNSUCCESS: ʧ��
	******************************************************************************/
	HRESULT 	API_HV_SetGPIOValue(bool bValue, int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetTriggerCount()
	* Description: ��ȡ��������
	* Format:
	*     HRESULT  API_HV_GetTriggerCount(int &nTrigCount, bool bReset, int nDevId)
	* Params:
	*     int &nTrigCount   ���ش�������ֵ������������Ӳ��������
	*     bool bReset    ΪTrueʱ�����ü�����
	*     int nDevId   ���������
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/
	HRESULT 	API_HV_GetTriggerCount(int &nTrigCount, bool bReset, int nDevId);

	/******************************************************************************
	* Function:	API_HV_GetMaxFrameRate()
	* Description: ��ȡ��ǰ����ܹ���������֡��
	* Format:
	*     HRESULT  API_HV_GetMaxFrameRate(int &nMaxFrameRate, int nDevId)
	* Params:
	*     int &nMaxFrameRate			��ȡ��ǰ������֡��
	*     int nDevId					���������
	* Return: 
	*     API_HV_SUCCESS:					�ɹ�
	*     API_HV_FEATURE_NOT_SUPPORT		��֧�ָ�����
	*	  API_HV_SEND_PACKET_FAIL			�������ݰ�ʧ��
	******************************************************************************/
	HRESULT 	API_HV_GetMaxFrameRate(int &nMaxFrameRate, int nDevId);


	/******************************************************************************
	* Function:	API_HV_GetFatorySeriesNum()
	* Description: ��ȡ����������к�
	* Format:
	*     HRESULT API_HV_GetFatorySeriesNum(LPSTR lpSeriesNum,int nDevId)
	* Params:
	*     LPCSTR lpSeriesNum : �����û��趨���к�
	*	  int nDevId : ���������
	* Return: 
	*     API_HV_SUCCESS: �ɹ�
	******************************************************************************/

	HRESULT  API_HV_GetFatorySeriesNum(LPSTR lpSeriesNum, int nDevId);

	/******************************************************************************
	* Function:	HV_SetSpecialROI
	* Description: ������Ƶ��ROI(Region of Interest)
	* Format:
	*      HRESULT HV_SetSpecialROI(int Offset_x1, int Offset_y1, int nWidth1, int nHeight1,
	*								int Offset_x2, int Offset_y2, int nWidth2, int nHeight2,int nDevId)
	* Params:
	*	  int Offset_x1: ��һ��ROI����ʼ��x����
	*	  int Offset_y1: ��һ��ROI����ʼ��y����
	*     int nWidth1: ��һ��ROI�Ŀ��
	*     int nHeight1: ��һ��ROI�ĸ߶�
	*	  int Offset_x2: �ڶ���ROI����ʼ��x����
	*	  int Offset_y2: �ڶ���ROI����ʼ��y����
	*     int nWidth2: �ڶ���ROI�Ŀ��
	*     int nHeight2: �ڶ���ROI�ĸ߶�
	*     int nDevId: �豸������
	* Return:
	*	   HV_SUCCESS: �ɹ�
	*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
	******************************************************************************/
	HRESULT API_HV_SetSpecialROI(int Offset_x1, int Offset_y1, int nWidth1, int nHeight1,
		int Offset_x2, int Offset_y2, int nWidth2, int nHeight2,int nDevId);

	//��ؼ�¼
	void GetOrder(std::vector<CString>& orderList);
	void WriteOrder(CString order);

protected:
	void APIDev_Lock();
	void APIDev_Unlock();

	CCriticalSection m_CCriticalSection;

public:
	bool m_bIsAdd;
    CDeviceOrderInfo    m_HVDevOrderInfo;                      //��������Ϣ�洢
	LONGLONG tempTimeIn[500];
	LONGLONG tempTimeOut[500];

public:
	static bool g_init;
	static bool init();
	static std::vector<CDevHV*> m_ObjMnger1D;
};

#endif //SCVDEV_USE_HV

#endif //_DEV_API_HV_SMCVVEDIO_H_