// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "DBCAnalyzer.h"

#include <regex>
#include <fstream>

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
	for (auto iter = _lines.begin(); iter != _lines.end(); ++iter)
	{
		if (MessageRecognizer(*iter, _file_descriptor))///Recognizer message
		{
			auto & msg = _file_descriptor.Messages().back();
			++iter;
			while (iter != _lines.end() && SignalRecognizer(*iter, msg))///Recognizer signal(from message)
			{
				++iter;
			}
			--iter;
		}
		else if (CommentRecognizer(*iter, _file_descriptor))///Recognizer comment
		{
			;///do nothing
		}
		else if (AttributeValueRecognizer(*iter, _file_descriptor))///Recognizer attribute value
		{
			;///do nothing
		}
		else if (SignalValueRecognizer(*iter, _file_descriptor))///Recognizer siganl value
		{
			;///do nothing
		}
	}
}

/**
*  signal_value = value_descriptions_for_signal
*  value_descriptions_for_signal = 'VAL_' message_id signal_name { value_description } ';';
*  @param a line of string
*  @param class file_description
*  @return match or not match
*/
bool DBCAnalyzer::SignalValueRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
{
	std::smatch m;
	if (!std::regex_match(_line, m, std::regex(R"(VAL_\s+(\d+)\s+(\w+)\s+([\s\w"]+);)")))
	{
		return false;
	}
	SignalValue sv;
	sv.SetMessageId(std::stoul(m[1].str()));
	sv.SetSignalName(m[2].str());

	///Set value_description
	std::vector<uint32_t> vi;
	std::vector<std::string> vs;
	split_number_and_string(m[3].str(), vi, vs);
	for (auto i = 0u; i < vi.size(); i++)
	{
		sv.AddValueDescription(vi[i], vs[i]);
	}

	_file_descriptor.AddSignalValue(sv);
	return true;
}

/**
*  attribute_values = { attribute_value_for_object };
*  attribute_value_for_object = 'BA_' attribute_name
*  (attribute_value |
*  'BU_' node_name attribute_value |
*  'BO_' message_id attribute_value |
*  'SG_' message_id signal_name attribute_value |
*  'EV_' env_var_name attribute_value)
*  @param a line of string
*  @param class file_description
*  @return match or not match
*/
bool DBCAnalyzer::AttributeValueRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
{
	std::smatch m;

	///read attribute_value and set attribute_name
	if (!std::regex_match(_line, m, std::regex(R"(BA_\s+(\"[-\w]*\")\s+(.*))")))
	{
		return false;
	}
	AttributeValue atv;
	atv.SetName(m[1].str());

	///deal with last attribute_value,which have five object_types
	std::string back_str(m[2].str());
	if (std::regex_match(back_str, m, std::regex(R"((\d+\.*\d*)\s*;.*)")))///only attribute_value
	{
		atv.SetValue(std::stod(m[1].str()));
		atv.SetObjectType(AttributeValue::_);
		_file_descriptor.AddAttributeValue(atv);
		return true;
	}
	else if (std::regex_match(back_str, m, std::regex(R"(BU_\s+(\w+)\s+(\d+\.*\d*)\s*;.*)")))///'BU_' node_name attribute_value
	{
		atv.SetNodeName(m[1].str());
		atv.SetValue(std::stod(m[2].str()));
		atv.SetObjectType(AttributeValue::BU_);
		_file_descriptor.AddAttributeValue(atv);
		return true;
	}
	else if (std::regex_match(back_str, m, std::regex(R"(BO_\s+(\d+)\s+(\d+\.*\d*)\s*;.*)")))///'BO_' message_id attribute_value
	{
		atv.SetMessageId(std::stoul(m[1].str()));
		atv.SetValue(std::stod(m[2].str()));
		atv.SetObjectType(AttributeValue::BO_);
		_file_descriptor.AddAttributeValue(atv);
		return true;
	}
	else if (std::regex_match(back_str, m, std::regex(R"(SG_\s+(\d+)\s+(\w+)\s+(\d+\.*\d*)\s*;.*)")))///'SG_' message_id signal_name attribute_value
	{
		atv.SetMessageId(std::stol(m[1].str()));
		atv.SetSignalName(m[2].str());
		atv.SetValue(std::stod(m[3].str()));
		atv.SetObjectType(AttributeValue::SG_);
		_file_descriptor.AddAttributeValue(atv);
		return true;
	}
	else if (std::regex_match(back_str, m, std::regex(R"(EV_\s+(\w+)\s+(\d+\.*\d*)\s*;.*)")))///'EV_' env_var_name attribute_value
	{
		atv.SetEnvVarName(m[1].str());
		atv.SetValue(std::stod(m[2].str()));
		atv.SetObjectType(AttributeValue::EV_);
		_file_descriptor.AddAttributeValue(atv);
		return true;
	}
	else
	{
		return false;
	}
}

/**
*  comments = {comment} ;
*  comment = 'CM_' (char_string |
*  'BU_' node_name char_string |
*  'BO_' message_id char_string |
*  'SG_' message_id signal_name char_string |
*  'EV_' env_var_name char_string)
*  ';'
*  But in this file,it only has "'CM_' 'SG_' message_id signal_name char_string ';'"
*  @param a line of string
*  @param class file_description
*  @return match or not match
*/
bool DBCAnalyzer::CommentRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
{
	std::regex comment_definition(R"(CM_\s+SG_\s+(\d+)\s+(\w+)\s+(\"[ \w+]+\")\s*;.*)");
	std::smatch m;
	if (!std::regex_match(_line, m, comment_definition))
	{
		return false;
	}
	Comment cmt;
	cmt.SetMessageId(std::stoul(m[1].str()));
	cmt.SetSignalName(m[2].str());
	cmt.SetCharString(m[3].str());
	_file_descriptor.AddComment(cmt);
	return true;
}

/**
*  message = BO_ message_id message_name ':' message_size transmitter{ signal };
*  @param a line of string
*  @param class file_description
*  @return match or not match
*/
bool DBCAnalyzer::MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
{
	std::regex message_definition(R"(BO_\s+(\d+)\s+(\w+)\s*:\s+(\w+)\s+(\w+).*)");
	std::smatch m;
	if (!std::regex_match(_line, m, message_definition))
	{
		return false;
	}
	Message msg;
	msg.SetMessageName(m[2].str());
	msg.SetMsgID(std::stoul(m[1].str()));

	msg.SetMsgSize(std::stoul(m[3].str()));
	msg.SetMsgtransmitter(m[4].str());

	_file_descriptor.AddMessage(msg);
	return true;
}

/**
*  signal = 'SG_' signal_name multiplexer_indicator ':' start_bit '|'
*  signal_size '@' byte_order value_type '(' factor ',' offset ')'
*  '[' minimum '|' maximum ']' unit receiver{ ',' receiver };
*  @param a line of string
*  @param class file_description
*  @return match or not match
*/
bool DBCAnalyzer::SignalRecognizer(std::string const & _line, Message & _msg)
{
	std::regex signal_definition(R"(\s*SG_\s+(\w+)\s+:\s+(\d+)\|(\d+)@(\d)(\+|-)\s+\((\d+\.*\d*),(\d+\.*\d*)\)\s+\[(\d+\.*\d*)\|(\d+\.*\d*)\]\s+(\"\w*\")\s+(\S+).*)");
	std::smatch m;
	if (!std::regex_match(_line, m, signal_definition)) {
		return false;
	}

	Signal signal;
	signal.SetName(m[1].str());
	/**1 - little endian (Intel)
	 * 0 - big endian (Motorola)
	 * @attention : this is different from DBC-File-Format-Documentation.pdf
	 *              chapter 8.1 Signal Definition
	 *              But matches the real behavior of CANdb++
	 */
	signal.SetIsBigEndian(m[4].str() == "0");//0 or 1?

	signal.SetIsUnsigned(m[5].str() == "+");

	uint8_t start_bit = static_cast<uint8_t>(std::stoul(m[2].str()));   // Attention! start_bit should be : LSB position
	uint8_t signal_size = static_cast<uint8_t>(std::stoul(m[3].str()));
	if (signal.IsBigEndian()) {
		start_bit = ChangMotorolaOrderMSBT2LSB(start_bit, signal_size);
	}
	signal.SetBitInfo(start_bit, signal_size);

	signal.SetFactor(std::stod(m[6].str()));
	signal.SetOffset(std::stod(m[7].str()));
	signal.SetMinimum(std::stod(m[8].str()));
	signal.SetMaximum(std::stod(m[9].str()));
	signal.SetUnit(m[10].str());

	//Set receivers
	std::vector<std::string> vs;
	SPILT(m[11].str(), ',', vs);
	signal.SetReceivers(vs);
	
	_msg.AddSignal(signal);

	return true;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return 
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
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return void
*/
void DBCFileDescriptor::PrintMessages(std::ostream & os)
{
	for (auto iter = Messages().begin(); iter < Messages().end(); iter++)
	{
		os << *iter << '\n';
	}
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return void
*/
void DBCFileDescriptor::PrintComments(std::ostream & os)
{
	for (auto iter_comment = Comments().begin(); iter_comment < Comments().end(); iter_comment++)
	{
		os << *iter_comment << '\n';
	}
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return void
*/
void DBCFileDescriptor::PrintAttributeValues(std::ostream & os)
{
	for (auto iter_attribute_value = AttributeValues().begin(); iter_attribute_value < AttributeValues().end(); iter_attribute_value++)
	{
		os << *iter_attribute_value<<'\n';
	}
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return void
*/
void DBCFileDescriptor::PrintSignalValues(std::ostream & os)
{
	for (auto iter_signal_value = SignalValues().begin(); iter_signal_value < SignalValues().end(); iter_signal_value++)
	{
		os << *iter_signal_value << '\n';
	}
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return void
*/
void DBCFileDescriptor::PrintDescriptor(std::ostream & os)
{
	PrintMessages(os);
	PrintComments(os);
	PrintAttributeValues(os);
	PrintSignalValues(os);
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::ObjectTypeSearch(AttributeValue::_ObjectType ot, std::vector<AttributeValue> & va)
{
	uint32_t num = 0;
	for (auto iter = m_attributevalues.begin(); iter < m_attributevalues.end(); iter++)
	{
		if (iter->ObjectType() == ot)
		{
			num++;
			va.push_back(*iter);
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::ObjectTypeSearch(AttributeValue::_ObjectType ot)
{
	uint32_t num = 0;
	for (auto iter = m_attributevalues.begin(); iter < m_attributevalues.end(); iter++)
	{
		if (iter->ObjectType() == ot)
		{
			num++;
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::SignalReceiversSearch(const std::string & srs,std::vector<Signal> & vs)
{
	int num = 0;
	for (auto iter_message = Messages().begin(); iter_message < Messages().end(); iter_message++)
	{
		for (auto iter_signal = iter_message->Signals().begin(); iter_signal < iter_message->Signals().end(); iter_signal++)
		{
			for (auto iter_receiver = iter_signal->Receivers().begin(); iter_receiver < iter_signal->Receivers().end(); iter_receiver++)
			{
				if (*iter_receiver == srs)
				{
					num++;
					vs.push_back(*iter_signal);
					break;
				}
			}
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::SignalReceiversSearch(const std::string & srs)
{
	int num = 0;
	for (auto iter_message = Messages().begin(); iter_message < Messages().end(); iter_message++)
	{
		for (auto iter_signal = iter_message->Signals().begin(); iter_signal < iter_message->Signals().end(); iter_signal++)
		{
			for (auto iter_receiver = iter_signal->Receivers().begin(); iter_receiver < iter_signal->Receivers().end(); iter_receiver++)
			{
				if (*iter_receiver == srs)
				{
					num++;
					break;
				}
			}
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::MessageIdSearch(uint32_t id)
{
	uint32_t num = 0;
	for (auto iter = Messages().begin(); iter < Messages().end(); iter++)
	{
		if (iter->ID() == id)
		{
			num++;
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::MessageIdSearch(uint32_t id, std::vector<Message> & vc)
{
	uint32_t num = 0;
	for (auto iter = Messages().begin(); iter < Messages().end(); iter++)
	{
		if (iter->ID() == id)
		{
			num++;
			vc.push_back(*iter);
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::CommentMessageIdSearch(uint32_t id)
{
	uint32_t num = 0;
	for (auto iter = Comments().begin(); iter < Comments().end(); iter++)
	{
		if (iter->MessageId() == id)
		{
			num++;
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::CommentMessageIdSearch(uint32_t id, std::vector<Comment> & vc)
{
	uint32_t num = 0;
	for (auto iter = Comments().begin(); iter < Comments().end(); iter++)
	{
		if (iter->MessageId() == id)
		{
			num++;
			vc.push_back(*iter);
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::SignalValueMessageIdSearch(uint32_t id)
{
	uint32_t num = 0;
	for (auto iter = SignalValues().begin(); iter < SignalValues().end(); iter++)
	{
		if (iter->MessageId() == id)
		{
			num++;
		}
	}
	return num;
}

/**
* 简要的函数说明文字
*  @param 参数1说明
*  @param 参数2说明
*  @return The number of signalvalues which have the id.
*/
uint32_t DBCFileDescriptor::SignalValueMessageIdSearch(uint32_t id, std::vector<SignalValue> & vs)
{
	uint32_t num = 0;
	for (auto iter = SignalValues().begin(); iter < SignalValues().end(); iter++)
	{
		if (iter->MessageId() == id)
		{
			num++;
			vs.push_back(*iter);
		}
	}
	return num;
}