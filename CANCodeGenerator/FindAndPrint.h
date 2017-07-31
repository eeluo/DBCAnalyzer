/**@file
*@brief ������һ��FindAndPrint��.
*@author luoaling
*@date 2017-7-31
*/
#pragma once
#include "DBCAnalyzer.h"
#include "DBCFileDescriptor.h"
#include "SignalAnalyzer.h"
#include "MessageAnalyzer.h"
#include "AttributeAnalyzer.h"
#include "NodeAnalyzer.h"
#include <iostream>
#include <vector>
#include <string>

/**
*@class
*@biref FindAndPrint����Ҫ����ʵ�ֲ��Һʹ�ӡ�������.
*
*��ӡ�����Ҫ�������ȡ֮�����ɵ�DBC�ļ����ַ������Է�����DBCԭ�ļ����жԱȣ�
*�ٴμ���ȡ�ļ��Ƿ����Ȼ��������DBC�ļ���ĳ���ֵĽ����ض����ң��������ƣ�
*���ֱȽ������������
*
*/

class FindAndPrint {

public:
	FindAndPrint();
	~FindAndPrint();

public:
	/**@brief ͨ�����ڲ���message_name��signal_name*/
	void FindMessageAndSignalNameByNodeName(void);
	/**@brief ͨ�����ڲ���message_name*/
	void FindMessageNameByTransmitter(const string &str);
	/**@brief ͨ�����ڲ���signal_name*/
	void FindSignalsNameByReceiver(const string &str);
	/**@brief ͨ�����ڲ���attribute_name*/
	void FindAttributeNameByValueType(void);
	/**@brief ͨ�����ڲ�����ֵ��Χ��ϵ���ַ���*/
	void FindMaxAndMinValueByValueType(void);
	/**@brief ͨ�����ڲ���attribute_name����ֵ��Χ��ϵ���ַ���*/
	void FindAttributeNameAndValueRangeByValueType(void);
	/**@brief ��ӡ����ڵ�node���ֵ�����*/
	void PrintNodes(void);
	/**@brief ��ӡ���ֻ��message���ֵ�����*/
	void PrintMessage(void);
	/**@brief ��ӡ���message���ֺ�signal���ֵ�����*/
	void PrintMessages(void);
	/**@brief ��ӡ���attribute definitions���ֵ�����*/
	void PrintAttribute(void);
};
