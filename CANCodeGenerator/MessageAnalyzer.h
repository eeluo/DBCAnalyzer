/**@file
*@brief ������һ��Message��.
*@author luoaling
*@date 2017-7-25
*
*��Ϣ���ֶ����˼�Ⱥ������֡�������Լ����ǵ����Ժ���֡�ϴ�����ź�.
*
*/
#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "SignalAnalyzer.h"

/**
*@class
*@biref message���־���CAN-ID,CAN-ID��DBC�ļ��б�����Ψһ��.
*
*message�а�����message_id,message_name,message_size��transmitter��Щ����,
*ͬʱ��������signal����,��������һ��signal���͵�vector����,signal���ֻ�
*����һ�ļ�"SignalAnalyzer.h"�ж���.
*
*@note ���ͽڵ�����ڽڵ㲿�ֵĽڵ�����node_name�����ж���,���messageû�з��ͽڵ�,
*transmitter���ַ����������ó�"Vector__XXX".
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
	std::string         m_message_name;///< ����Ϣ����message_name������Ψһ��
	std::string			m_msg_transmitter;///< transmitterָ���˷��ͽڵ������
	uint32_t            m_msg_id;
	uint8_t             m_msg_size;///< message_sizeָ������Ϣ���ֽڴ�С
	std::vector<Signal> m_signals;///< signal�����г���������Ϣ�ϵ������ź�,��������Ϣ�����ֶ��е�λ�ü�������
};

