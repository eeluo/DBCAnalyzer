/**@file
*@brief 定义了一个FindAndPrint类.
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
*@biref FindAndPrint类主要用于实现查找和打印输出功能.
*
*打印输出主要是输出读取之后生成的DBC文件的字符串，以方便与DBC原文件进行对比，
*再次检查读取文件是否出错；然后可以针对DBC文件的某部分的进行特定查找，比如名称，
*这种比较有意义的属性
*
*/

class FindAndPrint {

public:
	FindAndPrint();
	~FindAndPrint();

public:
	/**@brief 通过用于查找message_name和signal_name*/
	void FindMessageAndSignalNameByNodeName(void);
	/**@brief 通过用于查找message_name*/
	void FindMessageNameByTransmitter(const string &str);
	/**@brief 通过用于查找signal_name*/
	void FindSignalsNameByReceiver(const string &str);
	/**@brief 通过用于查找attribute_name*/
	void FindAttributeNameByValueType(void);
	/**@brief 通过用于查找数值范围或系列字符串*/
	void FindMaxAndMinValueByValueType(void);
	/**@brief 通过用于查找attribute_name和数值范围或系列字符串*/
	void FindAttributeNameAndValueRangeByValueType(void);
	/**@brief 打印输出节点node部分的内容*/
	void PrintNodes(void);
	/**@brief 打印输出只有message部分的内容*/
	void PrintMessage(void);
	/**@brief 打印输出message部分和signal部分的内容*/
	void PrintMessages(void);
	/**@brief 打印输出attribute definitions部分的内容*/
	void PrintAttribute(void);
};
