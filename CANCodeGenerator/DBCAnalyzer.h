/**@file
*@brief 定义了一个DBCAnalyzer类和一个string字符串分割的模板函数.
*@author luoaling
*/
#pragma once
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
*@biref 输入一个DBC文件，输出一个DBC的文件标识符.
*
*Analyze方法用于读取DBC文件，*Recognizer方法用于判断DBC的文件标识符
*是否满足<DBC-File-Format-Documentation.pdf> 中的格式规范.
*
*@note ChangMotorolaOrderMSBT2LSB方法不能忽略,
*是由于本程序在signal部分中信号的字节顺序为Motorola,与DBC文件的格式规范不一致.
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
	DBCFileDescriptor Analyze(std::string const & _file_name);

//private:
public:
	void AnalyzerDBCByLines(std::vector<std::string> const & _lines, DBCFileDescriptor & _file_descriptor);

	bool MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	bool SignalRecognizer(std::string const & _line, Message & _msg);
	bool AttributeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	bool NodeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	uint8_t ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size);
};

/**
*@brief string字符串的分割split模板函数.
*@author luoaling
*@date 2017-7-26
*
*split函数可以通过输入string字符串和分隔符,可以同时输入多种分割符号,
*分隔符之间也不需要间隔,返回一个存储了分割后各个子字符串的容器.
*
*@param[in] s,delim s为要分割的字符串,delim为分隔符.
*@return 返回一个存储了子字符串的result容器.
*@note split函数无法同时处理多个分隔符
*能处理:123,456 789;
*不能处理:123,.456 789;
*/
template <typename A, typename B>
A split(const B& s, const B& delim)
{
	A result;
	std::string::size_type pos1, pos2;
	pos2 = s.find_first_of(delim);///< pos2用于找到出现分隔符集合中的首个位置
	pos1 = 0;///< pos1初始化为字符串s的第一个字符的位置
	while (std::string::npos != pos2)///< 是否找到分隔符
	{
		result.push_back(s.substr(pos1, pos2 - pos1));
		///移动pos1和pos2的位置
		pos1 = pos2 + 1;
		pos2 = s.find_first_of(delim, pos1);
	}
	if (pos1 != s.length()) {
		result.push_back(s.substr(pos1));
	}
	return result;
}
