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
	}
}
//字符串分割split函数
//std::vector<std::string> split(const std::string& s, const std::string& delim)
//{
//	std::vector<std::string> result;
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
//	if (pos1 != s.length())
//		result.push_back(s.substr(pos1));
//	return result;
//}

//split模板函数的实现
template <typename A, typename B>
A split(const B& s, const B& delim, A result);
template <typename A, typename B>
A split(const B& s, const B& delim, A result)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(delim);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		result.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + delim.size();
		pos2 = s.find(delim, pos1);
	}
	if (pos1 != s.length())
		result.push_back(s.substr(pos1));
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
	//signal.AddRece_unit(split(m[19].str(), ","));
	std::string delim = ",";	
	std::vector<std::string> rece_none;
	//std::vector<std::string> rece_unit;
	//rece_unit = split(m[19].str(), delim, rece_none);
	//signal.AddRece_unit(rece_unit);
	signal.AddRece_unit(split(m[19].str(), delim, rece_none));
	_msg.AddSignal(signal);

	//std::string pattern = ",";
	//std::vector<std::string> m_rece_unit = split(m[19].str(), ",");
	/*for (std::vector<std::string>::size_type i = 0; i != m_rece_unit.size(); ++i)
		std::cout << m_rece_unit[i] << " ";
	std::cout << std::endl;*/
	
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