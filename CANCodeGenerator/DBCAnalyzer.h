#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "MessageAnalyzer.h"
#include "SignalAnalyzer.h"

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

private:

	std::vector<Message> m_messages; 
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

	uint8_t ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size);
};

