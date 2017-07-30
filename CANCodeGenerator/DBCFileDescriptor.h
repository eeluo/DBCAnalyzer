/**@file
*@brief 定义了一个DBCFileDescriptor类.
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
*@biref DBCFileDescriptor类用于添加各种类型的容器和获取容器.
*
*当要解析DBC文件的某个部分，就必须在DBCFileDescriptor类中
*添加与该解析部分对应类型的容器,和获取该容器的方法
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

	std::vector<Message> m_messages;///< messages容器包含了message部分和signal部分
	std::vector<Attribute> m_attributes;///< attributes容器包含了attribute部分
	std::vector<Node> m_nodes;///< nodes容器包含了node部分
};
