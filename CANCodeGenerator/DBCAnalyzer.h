#pragma once
#include "MessageAnalyzer.h"
#include "SignalAnalyzer.h"
#include "AttributeAnalyzer.h"
#include "NodeAnalyzer.h"
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

	void AddNode(Node const & _nodes) {
		m_nodes.push_back(_nodes);
	}
	std::vector<Node> & Nodes(void) {
		return m_nodes;
	}
	std::vector<Node> const & Nodes(void) const {
		return m_nodes;
	}

private:

	std::vector<Message> m_messages; 
	std::vector<Attribute> m_attributes;
	std::vector<Node> m_nodes;
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
	//bool NodeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	uint8_t ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size);
};

//split模板函数的实现
template <typename A, typename B>
A split(const B& s, const B& delim)
{
	A result;
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
