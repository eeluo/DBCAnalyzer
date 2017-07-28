#pragma once
#include "MessageAnalyzer.h"
#include "SignalAnalyzer.h"
#include "AttributeAnalyzer.h"
#include <string>
#include <vector>
#include <cstdint>

class DBCFileDescriptor {
public:
	void AddMessage(Message const & _msg) {
		m_messages.push_back(_msg);
	}
	std::vector<Message> & Messages(void) {
		return m_messages;
	}
	std::vector<Message> const & Messages(void) const {
		return m_messages;
	}

	void AddAttribute(Attribute const & _attribute) {
		m_attributes.push_back(_attribute);
	}
	std::vector<Attribute> & Attributes(void) {
		return m_attributes;
	}
	std::vector<Attribute> const & Attributes(void) const {
		return m_attributes;
	}

private:

	std::vector<Message> m_messages; 
	std::vector<Attribute> m_attributes;
};


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

	uint8_t ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size);
};

