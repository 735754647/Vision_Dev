#if !defined(_DEV_HV_LIB_Include_H_)
#define _DEV_HV_LIB_Include_H_

#define  VSI_KMB_NET   1//�Ƿ�ǧ����

#pragma comment(lib,"../../../lib/Release/AutoCSD.lib") 

//���廪��������ļ�·��
#ifdef _DEBUG // 
#pragma comment(lib,"../../../lib/Dug/Dev_CAM_HV_Lib/HVGigE_WP.lib") //
#endif //_DEBUG

#ifndef _DEBUG    //
#pragma comment(lib,"../../../lib/Release/Dev_CAM_HV_Lib/HVGigE_WP.lib") //
#endif

#endif  //(_DEV_HV_LIB_Include_H_)