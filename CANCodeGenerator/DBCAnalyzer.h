/**@file
*@brief ������һ��DBCAnalyzer���һ��string�ַ����ָ��ģ�庯��.
*@author luoaling
*/
#pragma once

#ifndef _DBCANALYZER_H_
#define _DBCANALYZER_H_

#include "DBCFileDescriptor.h"
#include "MessageAnalyzer.h"
#include "SignalAnalyzer.h"
#include "AttributeAnalyzer.h"
#include "NodeAnalyzer.h"
#include <string>
#include <vector>
#include <cstdint>

/**
*@class
*@biref ����һ��DBC�ļ������һ��DBC���ļ�������.
*
*Analyze�������ڶ�ȡDBC�ļ���*Recognizer���������ж�DBC���ļ�������
*�Ƿ�����<DBC-File-Format-Documentation.pdf> �еĸ�ʽ�淶.
*
*@note ChangMotorolaOrderMSBT2LSB�������ܺ���,
*�����ڱ�������signal�������źŵ��ֽ�˳��ΪMotorola,��DBC�ļ��ĸ�ʽ�淶��һ��.
*/

// @brief input a dbc file, output a DBCFileDescriptor for DBC
//        DBC Ref to : <DBC-File-Format-Documentation.pdf>
//        Analyzer file by Regular Expression.
//
class DBCAnalyzer
{
public:
	DBCAnalyzer();
	~DBCAnalyzer();

public:
	/**������ȡDBC�ļ�*/
	DBCFileDescriptor Analyze(std::string const & _file_name);

//private:
public:
	/**@brief ������������ȡ���DBC�ļ��Ƿ���ϱ�ע�淶,�������γ���Ӧ���ļ�������*/
	void AnalyzerDBCByLines(std::vector<std::string> const & _lines, DBCFileDescriptor & _file_descriptor);
	/**@brief ����message����*/
	bool MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	/**@brief ����signal����*/
	bool SignalRecognizer(std::string const & _line, Message & _msg);
	/**@brief ����attribute����*/
	bool AttributeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	/**@brief ����node����*/
	bool NodeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	/**@brief �ڷ���signal����ʱ��Ҫ�õ�*/
	uint8_t ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size);
};

/**
*@brief string�ַ����ķָ�splitģ�庯��.
*@author luoaling
*@date 2017-7-26
*
*split��������ͨ������string�ַ����ͷָ���,����ͬʱ������ַָ����,
*�ָ���֮��Ҳ����Ҫ���,����һ���洢�˷ָ��������ַ���������.
*
*@param[in] s,delim sΪҪ�ָ���ַ���,delimΪ�ָ���.
*@return ����һ���洢�����ַ�����result����.
*@note split�����޷�ͬʱ�������ָ���
*�ܴ���:123,456 789;
*���ܴ���:123,.456 789;
*/
template <typename A, typename B>
A split(const B& s, const B& delim)
{
	A result;
	std::string::size_type pos1, pos2;
	pos2 = s.find_first_of(delim);///< pos2�����ҵ����ַָ��������е��׸�λ��
	pos1 = 0;///< pos1��ʼ��Ϊ�ַ���s�ĵ�һ���ַ���λ��
	while (std::string::npos != pos2)///< �Ƿ��ҵ��ָ���
	{
		result.push_back(s.substr(pos1, pos2 - pos1));
		///�ƶ�pos1��pos2��λ��
		pos1 = pos2 + 1;
		pos2 = s.find_first_of(delim, pos1);
	}
	if (pos1 != s.length()) {
		result.push_back(s.substr(pos1));
	}
	return result;
}
#endif // !_DBCANALYZER_H_