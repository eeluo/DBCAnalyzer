#include "DBCAnalyzer.h"

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
	}

	/*for (auto iter = _lines.begin(); iter != _lines.end(); ++iter) {
		if (AttributeRecognizer(*iter, _file_descriptor)) {
			auto & att = _file_descriptor.Attributes().back();
		}
	}*/
}

//split模板函数的实现
//template <typename A, typename B>
//A split(const B& s, const B& delim, A result)
//{
//	std::string::size_type pos1, pos2;
//	pos2 = s.find(delim);
//	pos1 = 0;
//	while (std::string::npos != pos2)
//	{
//		result.push_back(s.substr(pos1, pos2 - pos1));
//
//		pos1 = pos2 + delim.size();
//		pos2 = s.find(delim, pos1);
//	}
//	if (pos1 != s.length()) {
//		result.push_back(s.substr(pos1));
//	}
//		
//	return result;
//}

template <typename A, typename B>
A split(const B& s, const B& delim, A result)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find_first_of(delim);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		result.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + 1;
		pos2 = s.find_first_of(delim, pos1);
	}
	if (pos1 != s.length()) {
		result.push_back(s.substr(pos1));
	}

	return result;
}

uint8_t message_size = 8;

bool DBCAnalyzer::MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
{
	// message = BO_ message_id message_name ':' message_size transmitter{ signal };
	//std::regex message_definition(R"(BO_\s+(\d+)\s+(\w+)\s*:.*)");
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


bool DBCAnalyzer::SignalRecognizer(std::string const & _line, Message & _msg)
{
	//signal = 'SG_' signal_name multiplexer_indicator ':' start_bit '|'
	//	signal_size '@' byte_order value_type '(' factor ',' offset ')'
	//	'[' minimum '|' maximum ']' unit receiver{ ',' receiver };
	//std::regex signal_definition(R"(\s*SG_\s+(\w+)\s+:\s+(\d+)\|(\d+)@(\d)(\+|-).*)");
	//std::regex signal_definition(R"(\s*SG_\s+([a-zA-Z_](\w*))\s+:\s+([-]?\d+)\|(\d+)@([0-1])(\+|-)\s+\((([-]?[1-9]\d*)(\.\d+)?|(0\.[1-9]\d*)|(0\.\d*[1-9])),[-]?\d+(\.\d+)?\)\s+\[[-]?\d+(\.\d+)?\|[-]?\d+(\.\d+)?\]\s+\"[^"]*\"\s+((\w+)(,\w+)*|Vector__XXX))");
	std::regex signal_definition(R"(\s*SG_\s+([a-zA-Z_](\w*))\s+:\s+([-]?\d+)\|(\d+)@([0-1])(\+|-)\s+\((([-]?[1-9]\d*)(\.\d+)?|(0\.[1-9]\d*)|(0\.\d*[1-9])),([-]?\d+(\.\d+)?)\)\s+\[([-]?\d+(\.\d+)?)\|([-]?\d+(\.\d+)?)\]\s+\"([^"]*)\"\s+((\w+)(,\w+)*|Vector__XXX))");
	std::smatch m;
	if (!std::regex_match(_line, m, signal_definition)) {
		return false;
	}

	message_size = _msg.GetSize();
	uint8_t start_bit = atoi(m[3].str().c_str());   // Attention! start_bit should be : LSB position.
	if (start_bit > 8 * message_size - 1 || start_bit <0) {
		return false;
	}

	uint8_t signal_size = static_cast<uint8_t>(std::stoul(m[4].str())); 

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
	std::string delim = ",";	
	std::vector<std::string> rece_none;
	signal.AddRece_unit(split(m[19].str(), delim, rece_none));
	//signal.AddRece_unit(split1<std::vector<std::string>>(m[19].str(), delim));
	_msg.AddSignal(signal);

	return true;
}

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

bool DBCAnalyzer::AttributeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor) {
	// attribute_definition = 'BA_DEF_' object_type attribute_name attribute_value_type ';';
	//object_type = '' | 'BU_' | 'BO_' | 'SG_' | 'EV_' ;
	//attribute_name = '"' C_identifier '"' ;
	//attribute_value_type = 'INT' signed_integer signed_integer |
	//'HEX' signed_integer signed_integer |
	//'FLOAT' double double |
	//'STRING' |
	//'ENUM'[char_string{ ',' char_string }]
	std::regex raw_definition(R"(BA_DEF_\s+(BU_|BO_|SG_|EV_|\s?)\s+(\"([^"]*[a-zA-Z_](\w*))\")(.*);)");
	std::regex int_definition(R"(INT\s+([-]?\d+)\s+([-]?\d+))");
	std::regex hex_definition(R"(HEX\s+([-]?\d+)\s+([-]?\d+))");
	std::regex float_definition(R"(FLOAT\s+([-]?\d+(\.\d+)?)\s+([-]?\d+(\.\d+)?))");
	std::regex string_definition(R"(STRING)");
	std::regex enum_definition(R"(ENUM\s+(\"([^"]*[a-zA-Z_](\w*))\")(,\"([^"]*[a-zA-Z_](\w*))\")*)");
	std::smatch m0,m1;
	if (!std::regex_match(_line,m0,raw_definition)) { return false; }
	//std::cout << m0[5].str();
	bool enum_int = std::regex_match(m0[5].str(), int_definition);
	bool enum_hex = std::regex_match(m0[5].str(), hex_definition);
	bool enum_float = std::regex_match(m0[5].str(), float_definition);
	bool enum_str = std::regex_match(m0[5].str(), string_definition);
	bool enum_enum = std::regex_match(m0[5].str(), enum_definition);

	if (!enum_int) {}
	else if (!enum_hex) {}
	else if (!enum_float) {}
	else if (!enum_str) {}
	else if (!enum_enum) {}
	else { return false; }
	
	Attribute att;
	att.SetObjType(m0[1].str());
	att.SetAttributeName(m0[2].str());

	if (enum_str) {
		std::vector<std::string> vec_str;
		vec_str.push_back("STRING");
		att.AddValueType(vec_str);
	}
	//std::cout << m0[1].str() << "  " << m0[2].str() << std::endl;
	//if (enum_int || enum_hex || enum_float || enum_enum) {
		std::string delim = ", ";
		std::vector<std::string> rece_none;
		att.AddValueType(split(m0[5].str(), delim, rece_none));
	//}
	/*if(enum_str){
		std::vector<std::string> vec_str;
		vec_str.push_back(m0[5].str());
		att.AddValueType(vec_str);
	}*/

	_file_descriptor.AddAttribute(att);

	return true;
}