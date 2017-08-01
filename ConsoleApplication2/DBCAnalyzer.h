#pragma once

#include "Message.h"
#include "Comment.h"
#include "AttributeValue.h"
#include "SignalValue.h"

class DBCFileDescriptor {
public:
	// 
	void AddMessage(Message const & _msg) {
		m_messages.push_back(_msg);
	}
	std::vector<Message> & Messages(void) {
		return m_messages;
	}

	std::vector<Message> const & Messages(void) const {
		return m_messages;
	}
	///search for  signal's receiver,the second parameter will contain these class
	uint32_t SignalReceiversSearch(const std::string & srs, std::vector<Signal> & vs);
	uint32_t SignalReceiversSearch(const std::string & srs, bool output = false, std::ostream & os = std::cout);
	uint32_t MessageIdSearch(uint32_t id, bool output = false, std::ostream & os = std::cout);
	uint32_t MessageIdSearch(uint32_t id, std::vector<Message> & vc);

	void AddComment(const Comment & _cmt)
	{
		m_comments.push_back(_cmt);
	}
	std::vector<Comment> & Comments(){ return m_comments; }
	const std::vector<Comment> & Comments() const { return m_comments; }

	///search for comment's message id,the second parameter will contain these class
	uint32_t CommentMessageIdSearch(uint32_t id, bool output = false, std::ostream & os = std::cout);
	uint32_t CommentMessageIdSearch(uint32_t id, std::vector<Comment> & vc);

	void AddAttributeValue(const AttributeValue & _atv)
	{
		m_attributevalues.push_back(_atv);
	}
	std::vector<AttributeValue> & AttributeValues(){ return m_attributevalues; }
	const std::vector<AttributeValue> & AttributeValues() const { return m_attributevalues; }

	///search for attribute_value's object type,the second parameter will contain these class
	uint32_t ObjectTypeSearch(AttributeValue::_ObjectType ot, bool output = false, std::ostream & os = std::cout);
	uint32_t ObjectTypeSearch(AttributeValue::_ObjectType ot, std::vector<AttributeValue> & va);

	void AddSignalValue(const SignalValue & _sv)
	{
		m_signalvalues.push_back(_sv);
	}
	std::vector<SignalValue> & SignalValues(){ return m_signalvalues; }
	const std::vector<SignalValue> & SignalValues() const { return m_signalvalues; }

	uint32_t SignalValueMessageIdSearch(uint32_t id, bool output = false, std::ostream & os = std::cout);
	uint32_t SignalValueMessageIdSearch(uint32_t id, std::vector<SignalValue> & vs);

	///output
	void PrintMessages(std::ostream & os);
	void PrintComments(std::ostream & os);
	void PrintAttributeValues(std::ostream & os);
	void PrintSignalValues(std::ostream & os);
	void PrintDescriptor(std::ostream & os);
private:

	std::vector<Message> m_messages;

	std::vector<Comment> m_comments;
	std::vector<AttributeValue> m_attributevalues;
	std::vector<SignalValue> m_signalvalues;
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


private:
	void AnalyzerDBCByLines(std::vector<std::string> const & _lines, DBCFileDescriptor & _file_descriptor);

	bool MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);

	bool CommentRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	bool AttributeValueRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);
	bool SignalValueRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor);

	bool SignalRecognizer(std::string const & _line, Message & _msg);

	uint8_t ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size);
};