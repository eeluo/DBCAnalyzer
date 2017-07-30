/**@file
*@brief 定义了一个Message类.
*@author luoaling
*@date 2017-7-25
*
*消息部分定义了集群中所有帧的名称以及它们的属性和在帧上传输的信号.
*
*/
#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "SignalAnalyzer.h"

/**
*@class
*@biref message部分就是CAN-ID,CAN-ID在DBC文件中必须是唯一的.
*
*message中包含了message_id,message_name,message_size和transmitter这些变量,
*同时还包含了signal部分,即定义了一个signal类型的vector容器,signal部分会
*在另一文件"SignalAnalyzer.h"中定义.
*
*@note 发送节点必须在节点部分的节点名称node_name集合中定义,如果message没有发送节点,
*transmitter的字符串必须设置成"Vector__XXX".
*
*/

class Message {

public:

	std::string const & Name() const { return m_message_name; }
	void SetMessageName(std::string const & _name) {
		m_message_name = _name;
	}

	std::string const & Transmitter() const { return m_msg_transmitter; }
	void SetMessageTransmitter(std::string const & _transmitter) {
		m_msg_transmitter = _transmitter;
	}

	uint32_t ID(void) const { return m_msg_id; }
	void SetMsgID(uint32_t _msg_id) { m_msg_id = _msg_id; }

	uint8_t GetSize(void) const { return m_msg_size; }
	void SetMsgSize(uint8_t _msg_size) { m_msg_size = _msg_size; }

	void AddSignal(Signal const & _signal) {
		m_signals.push_back(_signal);
	}

	std::vector<Signal> & Signals(void) {
		return m_signals;
	}
	std::vector<Signal> const & Signals(void) const {
		return m_signals;
	}

private:
	std::string         m_message_name;///< 在消息集中message_name必须是唯一的
	std::string			m_msg_transmitter;///< transmitter指定了发送节点的名称
	uint32_t            m_msg_id;
	uint8_t             m_msg_size;///< message_size指定了消息的字节大小
	std::vector<Signal> m_signals;///< signal部分列出放置在消息上的所有信号,它们在消息数据字段中的位置及其属性
};

