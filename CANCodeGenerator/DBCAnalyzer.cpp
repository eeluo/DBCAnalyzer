/**@file
*@brief DBCAnalyzer类中函数的具体实现
*@author luoaling
*/
#include "DBCAnalyzer.h"
#include "DBCFileDescriptor.h"
#include <regex>
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>

DBCAnalyzer::DBCAnalyzer()
{
}

DBCAnalyzer::~DBCAnalyzer()
{
}

/**
*@brief Analyze方法用于分析读取DBC文件
*@author liyiwen
*
*Analyze方法首先读取DBC文件，并将读取的文件内容在容器内存成字符串，
*之后调用AnalyzerDBCByLines方法来分析读取之后生成的字符串是否符合
*DBC文件各个部分的标准格式规范，符合则形成相应的文件描述符
*
*@param[in] _file_name _file_name是要读取的dbc文件名.
*@return 返回DBCFileDescriptor类对象file_descriptor.
*/
DBCFileDescriptor DBCAnalyzer::Analyze(std::string const & _file_name)
{
	DBCFileDescriptor file_descriptor;
		
	std::ifstream in_file(_file_name);
	std::vector<std::string> file_lines;
	std::string line;
	while (std::getline(in_file, line)) {
		file_lines.push_back(line);
	}
	AnalyzerDBCByLines(file_lines, file_descriptor);

	return std::move(file_descriptor);
}

/**
*@brief AnalyzerDBCByLines方法按行分析字符串是否符合规范，符合则形成相应的文件描述符
*@author liyiwen
*
*每分析独立的一部分，就需要在AnalyzerDBCByLines函数添加相应的代码，
*由于message和signal部分二者之间不是独立的，所以较为复杂
*
*@param[in] _lines,_file_descriptor _lines是生成的字符串的某行,_file_descriptor是形成的相应的文件描述符
*/
void DBCAnalyzer::AnalyzerDBCByLines(std::vector<std::string> const & _lines, DBCFileDescriptor & _file_descriptor)
{
	for (auto iter = _lines.begin(); iter != _lines.end(); ++iter) {
		if (MessageRecognizer(*iter, _file_descriptor))
		{
			auto & msg = _file_descriptor.Messages().back();
			++iter;
			while (iter != _lines.end() && SignalRecognizer(*iter, msg)) {
				++iter;
			}
			--iter;
		}
		AttributeRecognizer(*iter, _file_descriptor);
		NodeRecognizer(*iter, _file_descriptor);
	}
}

/**
*@brief MessageRecognizer方法判断message部分的字符串是否符合规范
*@author luoaling
*
*MessageRecognizer方法采用正则表达式来检查message的字符串，以此达到检验目的，
*正则匹配字符串较为简单，同时利用正则匹配的默认分组顺序，给相应的
*Message类对象进行赋值，最后添加存储Message类型的容器
*
*@param[in] _lines,_file_descriptor _lines是字符串中message部分的某行,_file_descriptor是形成的相应的文件描述符
*@return 返回一个布尔值，说明字符串是否符合规范，符合则形成相应的文件描述符
*/
bool DBCAnalyzer::MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
{
	// message = BO_ message_id message_name ':' message_size transmitter{ signal };
	//message_id = unsigned_integer , message_name = C_identifier
	//message_size = unsigned_integer , transmitter = node_name | 'Vector__XXX'
	std::regex message_definition(R"(BO_\s+(\d+)\s+([a-zA-Z_](\w*))\s*:\s*(\d+)\s+((\w+)|Vector__XXX))");
	std::smatch m;
	if (!std::regex_match(_line, m, message_definition)) {
		return false;
	}

	Message msg;
	msg.SetMsgID(std::stol(m[1].str()));
	msg.SetMessageName(m[2].str());
	msg.SetMsgSize(std::stoi(m[4].str()));
	msg.SetMessageTransmitter(m[5].str());

	_file_descriptor.AddMessage(msg);

	return true;
}

/**
*@brief SignalRecognizer方法判断signal部分的字符串是否符合规范
*@author luoaling
*
*SignalRecognizer方法采用正则表达式来检查signal的字符串，以此达到检验目的，
*正则匹配字符串较为简单，同时利用正则匹配的默认分组顺序，给相应的
*Signal类对象进行赋值，最后添加存储Signal类型的容器
*
*@param[in] _lines,_msg _lines是DBC文件中signal部分的某行,_msg用于添加signal类型的容器
*@return 返回一个布尔值，说明字符串是否符合规范，符合则形成相应的文件描述符
*/
bool DBCAnalyzer::SignalRecognizer(std::string const & _line, Message & _msg)
{
	//signal = 'SG_' signal_name multiplexer_indicator ':' start_bit '|'
	//	signal_size '@' byte_order value_type '(' factor ',' offset ')'
	//	'[' minimum '|' maximum ']' unit receiver{ ',' receiver };

	//signal_name = C_identifier , start_bit = unsigned_integer ,signal_size = unsigned_integer
	//byte_order = '0' | '1' ,value_type = '+' | '-' , factor = double (factor!=0) , offset = double
	//minimum = double , maximum = double , unit = char_string , receiver = node_name | 'Vector__XXX'
	std::regex signal_definition(R"(\s*SG_\s+([a-zA-Z_](\w*))\s+:\s+([-]?\d+)\|(\d+)@([0-1])(\+|-)\s+\((([-]?[1-9]\d*)(\.\d+)?|(0\.[1-9]\d*)|(0\.\d*[1-9])),([-]?\d+(\.\d+)?)\)\s+\[([-]?\d+(\.\d+)?)\|([-]?\d+(\.\d+)?)\]\s+\"([^"]*)\"\s+((\w+)(,\w+)*|Vector__XXX))");
	std::smatch m;
	if (!std::regex_match(_line, m, signal_definition)) {
		return false;
	}

	uint8_t message_size = _msg.GetSize();//获得相应的message部分的message_size
	uint8_t start_bit = atoi(m[3].str().c_str());   // Attention! start_bit should be : LSB position.
	//start_bit值的范围为 0 ~ 8*message_size - 1，超过这个范围是违反DBC规范的
	if (start_bit > 8 * message_size - 1 || start_bit <0) {
		return false;
	}
	uint8_t signal_size = static_cast<uint8_t>(std::stoul(m[4].str())); //强制类型转换

	Signal signal;
	signal.SetName(m[1].str());

	// 1 - little endian (Intel)
    // 0 - big endian (Motorola)
	// @attention : this is different from DBC-File-Format-Documentation.pdf
	//              chapter 8.1 Signal Definition
	//              But matches the real behavior of CANdb++
	
	signal.SetIsBigEndian(m[5].str() == "0");
	
	if (signal.IsBigEndian()) {
		start_bit = ChangMotorolaOrderMSBT2LSB(start_bit, signal_size);
	}

	signal.SetBitInfo(start_bit, signal_size);
	signal.SetIsUnsigned(m[6].str() == "+");
	signal.SetFactor(std::stof(m[7].str()));
	signal.SetOffset(std::stof(m[12].str()));
	signal.SetMinimum(std::stof(m[14].str()));
	signal.SetMaximum(std::stof(m[16].str()));
	signal.SetUnit(m[18].str());
	signal.SetReceiver(m[19].str());

	signal.SetByteOrder(std::stoi(m[5].str()));
	signal.SetValueType(m[6].str());

	std::string delim = ",";// 以分隔符 , 分隔字符串	
	signal.AddRece_unit(split<std::vector<std::string>>(m[19].str(), delim));
	_msg.AddSignal(signal);

	return true;
}

/**
*@brief ChangMotorolaOrderMSBT2LSB按照signal的Motorola字节顺序，对start_bit数值进行转换
*@author liyiwen
*@param[in] start_bit,signal_size start_bit是signal的开始位置,signal_size是signal的比特大小
*@return 返回一个转换后的符合LSB的start_bit数值
*/
uint8_t DBCAnalyzer::ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size) {
	while (--signal_size) {
		if (0 == (start_bit % 8)) {
			start_bit += 15;
		}
		else {
			start_bit--;
		}
	}
	return start_bit;
}

/**
*@brief AttributeRecognizer方法判断attribute definitions部分的字符串是否符合规范
*@author luoaling
*
*AttributeRecognizer方法采用正则表达式来检查attribute definitions的字符串，以此达到检验目的，
*正则匹配字符串较为简单，同时利用正则匹配的默认分组顺序，给相应的
*Attribute类对象进行赋值，最后添加存储Attribute类型的容器
*
*@param[in] _lines,_file_descriptor _lines是字符串中attribute definitions部分的某行,_file_descriptor是形成的相应的文件描述符
*@return 返回一个布尔值，说明字符串是否符合规范，符合则形成相应的文件描述符
*@note Attribute类只包含属性定义部分，没有包含属性值，它包括两部分：
*attribute_definition 和 attribute_default
*/
bool DBCAnalyzer::AttributeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor) {
	//attribute_definitions = { attribute_definition } ;
	// attribute_definition = 'BA_DEF_' object_type attribute_name attribute_value_type ';';
	//object_type = '' | 'BU_' | 'BO_' | 'SG_' | 'EV_' ;
	//attribute_name = '"' C_identifier '"' ;
	//attribute_value_type = 'INT' signed_integer signed_integer |
	//						'HEX' signed_integer signed_integer |
	//						'FLOAT' double double |
	//						'STRING' |
	//						'ENUM'[char_string{ ',' char_string }]

	//attribute_defaults = { attribute_default } ;
	//attribute_default = 'BA_DEF_DEF_' attribute_name attribute_value ';';
	//attribute_value = unsigned_integer | signed_integer | double | char_string;

	//这是attribute_definition部分的正则表达式
	//由于attribute_value_type变量较为复杂，这里将正则表达式分开，以便于对多种情况进行正则匹配
	//匹配除了attribute_value_type部分的字符串的正则表达式
	std::regex raw_definition(R"(BA_DEF_\s(BU_|BO_|SG_|EV_|\s?)\s+(\"([^"]*[a-zA-Z_](\w*))\")\s+(.*);)");
	//分别编写attribute_value_type部分的五种正则表达式
	std::regex int_definition(R"(INT\s+([-]?\d+)\s+([-]?\d+))");
	std::regex hex_definition(R"(HEX\s+([-]?\d+)\s+([-]?\d+))");
	std::regex float_definition(R"(FLOAT\s+([-]?\d+(\.\d+)?)\s+([-]?\d+(\.\d+)?))");
	std::regex string_definition(R"(STRING\s+)");
	std::regex enum_definition(R"(ENUM\s+(\"([^"]*)\")(,\"([^"]*)\")*)");
	//这是attribute_default部分的正则表达式
	std::regex raw_default(R"(BA_DEF_DEF_\s+(\"([^"]*[a-zA-Z_](\w*))\")\s+(\d+|[-]?\d+|[-]?\d+(\.\d+)?|\"([^"]*)\");)");
	std::smatch m0, m1;//m0存储attribute_definition的匹配结果,m1存储attribute_default的匹配结果

	if (!(std::regex_match(_line, m0, raw_definition) || std::regex_match(_line, m1, raw_default))) {
		return false; 
	}
	/*if ((!std::regex_match(_line, m0, raw_definition))&&(!std::regex_match(_line, m1, raw_default)))
	{
		return false;
	}*/
	//分别对attribute_value_type部分的五种情况进行正则匹配
	bool enum_int = std::regex_match(m0[5].str(), int_definition);
	bool enum_hex = std::regex_match(m0[5].str(), hex_definition);
	bool enum_float = std::regex_match(m0[5].str(), float_definition);
	bool enum_str = std::regex_match(m0[5].str(), string_definition);
	bool enum_enum = std::regex_match(m0[5].str(), enum_definition);

	if (!(enum_int | enum_hex | enum_float | enum_str | enum_enum | std::regex_match(_line, m1, raw_default))) {
		return false;
	}
	/*if (!enum_int && !enum_hex && !enum_float && !enum_str && !enum_enum && !std::regex_match(_line, m1, raw_default))
	{
		return false;
	}*/
	
	Attribute att;
	//对attribute_default部分变量赋值
	if (std::regex_match(_line, m1, raw_default)) {
		att.SetAttributeName(m1[1].str());
		att.SetDefaultValue(m1[4].str());
	}
	//对attribute_definition部分变量赋值，同样分五种情况来赋值
	else {
		att.SetObjType(m0[1].str());
		att.SetAttributeName(m0[2].str());
		if (enum_int) {
			att.SetValueType(Attribute::INT);
			std::string delim = ", ";//分隔符有,和空格两个
			att.AddValueType(split<std::vector<std::string>>(m0[5].str(), delim));
		}
		if (enum_hex) {
			att.SetValueType(Attribute::HEX);
			std::string delim = ", ";
			att.AddValueType(split<std::vector<std::string>>(m0[5].str(), delim));
		}
		if (enum_float) {
			att.SetValueType(Attribute::FLOAT);
			std::string delim = ", ";
			att.AddValueType(split<std::vector<std::string>>(m0[5].str(), delim));
		}
		if (enum_enum) {
			att.SetValueType(Attribute::ENUM);
			std::string delim = ", ";
			att.AddValueType(split<std::vector<std::string>>(m0[5].str(), delim));
		}
		if (enum_str) {
			att.SetValueType(Attribute::STRING);
			std::vector<std::string> vec_str;
			vec_str.push_back(m0[5].str());
			att.AddValueType(vec_str);
		}
	}
	_file_descriptor.AddAttribute(att);
	return true;
}

/**
*@brief NodeRecognizer方法判断node部分的字符串是否符合规范
*@author luoaling
*
*NodeRecognizer方法采用正则表达式来检查node的字符串，以此达到检验目的，
*正则匹配字符串较为简单，同时利用正则匹配的默认分组顺序，给相应的
*Node类对象进行赋值，最后添加存储Node类型的容器
*
*@param[in] _lines,_file_descriptor _lines是字符串中node部分的某行,_file_descriptor是形成的相应的文件描述符
*@return 返回一个布尔值，说明字符串是否符合规范，符合则形成相应的文件描述符
*/
bool DBCAnalyzer::NodeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor) {
	//nodes = 'BU_:' {node_name} ;
	//node_name = C_identifier;
	std::regex node_definition(R"(BU_:\s+(([a-zA-Z_]\w*\s*)*))");
	std::smatch m;
	if (!std::regex_match(_line, m, node_definition)) { return false; }

	Node node;
	std::string delim = " ";//以空格作为分隔符分割字符串
	node.AddNodeName(split<std::vector<std::string>>(m[1].str(),delim));

	_file_descriptor.AddNode(node);

	return true;
}