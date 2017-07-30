/**@file
*@brief ������һ��DBCFileDescriptor��.
*@author luoaling
*/
#pragma once
#include "MessageAnalyzer.h"
#include "SignalAnalyzer.h"
#include "AttributeAnalyzer.h"
#include "NodeAnalyzer.h"
#include <string>
#include <vector>
#include <cstdint>

/**
*@class
*@biref DBCFileDescriptor��������Ӹ������͵������ͻ�ȡ����.
*
*��Ҫ����DBC�ļ���ĳ�����֣��ͱ�����DBCFileDescriptor����
*�����ý������ֶ�Ӧ���͵�����,�ͻ�ȡ�������ķ���
*
*/

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

	std::vector<Message> m_messages;///< messages����������message���ֺ�signal����
	std::vector<Attribute> m_attributes;///< attributes����������attribute����
	std::vector<Node> m_nodes;///< nodes����������node����
};
