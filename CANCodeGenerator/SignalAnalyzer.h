/**@file
*@brief ������һ��Signal��.
*@author luoaling
*@date 2017-7-26
*/
#pragma once

#ifndef _SIGNALANALYZER_H_
#define _SIGNALANALYZER_H_

#include <string>
#include <vector>
#include <cstdint>

/**
*@class
*@biref signal�����г���������Ϣ�ϵ������ź�,��������Ϣ�����ֶ��е�λ�ü�������.
*
*signal�а�����signal_name,start_bit,signal_size,byte_order,value_type,(factor,offset)
*[minimum|maximum ] ,unit��receiver��.
*
*@note ���սڵ�����ڽڵ㲿�ֵĽڵ�����node_name�����ж���,���signalû�н��սڵ�,
*receiver���ַ����������ó�"Vector__XXX".
*
*/

class Signal {
public:
	void SetName(std::string const _name) {
		m_signal_name = _name;
	}
	std::string const & Name(void) const { return m_signal_name; }

	void SetBitInfo(uint8_t _start, uint8_t _size) {
		m_start_bit = _start;
		m_signal_size = _size;
	}
	uint8_t StartBit(void) const { return m_start_bit; }
	uint8_t SignalSize(void) const { return m_signal_size; }

	bool IsBigEndian(void) const { return m_is_big_endian; }
	void SetIsBigEndian(bool _is_big_endian) {
		m_is_big_endian = _is_big_endian;
	}
	void SetIsUnsigned(bool _is_unsigned) {
		m_is_unsigned = _is_unsigned;
	}
	bool IsUnsigned(void) const { return m_is_unsigned; }

	double GetFactor(void) const { return m_factor; };
	void SetFactor(double _factor)  { m_factor = _factor;}

	double GetOffset(void) const { return m_offset; }
	void SetOffset(double _offset) { m_offset = _offset; }

	double GetMinimum(void) const { return m_minimum; }
	void SetMinimum(double _minimum) { m_minimum = _minimum; }

	double GetMaximum(void) const { return m_maximum; }
	void SetMaximum(double _maximum) { m_maximum = _maximum; }

	void SetUnit(std::string const _unit) {
		m_unit = _unit;
	}
	std::string const & Unit(void) const { return m_unit; }

	/**SetReceiver��Receiver����Ϊ�����ʱ������DBC�ļ��Աȣ���������*/
	void SetReceiver(std::string const _receiver) {
		m_receiver = _receiver;
	}
	std::string const & Receiver(void) const { return m_receiver; }

	void AddRece_unit(std::vector<std::string> const & _rece_unit) {
		m_rece_unit = _rece_unit;
	}
	std::vector<std::string> & Rece_unit(void) {
		return m_rece_unit;

	}
	std::vector<std::string> const & Rece_unit(void) const {
		return m_rece_unit;
	}
	/**GetByteOrder��SetByteOrder��GetValueType��SetValueType����ͬ��������*/
	uint8_t GetByteOrder(void) const { return m_byte_order; }
	void SetByteOrder(uint8_t _byte_order) { m_byte_order = _byte_order; }
	std::string const &GetValueType (void) const { return m_value_type; }
	void SetValueType(std:: string const _value_type) { m_value_type = _value_type; }


private:
	std::string m_signal_name;///< �˴������signal_name���ڵ�����Ϣ���źű�����Ψһ��
	uint8_t m_start_bit;///< start_bitֵָ���ź���֡�����ݶ��ڵ�λ��,�����䷶ΧΪ 0 ~ 8*message_size - 1
	uint8_t m_signal_size;///< signal_sizeָ���źŵı��ش�С
	bool    m_is_big_endian;///< byte_order = '0' | '1',����źŵ��ֽ�˳��Ϊ Motorola,�� 1=little endian, 0=big endian
	uint8_t m_byte_order;///< ����Ϊ�����ʱ������DBC�ļ��Աȣ���������
	bool    m_is_unsigned;///< value_type�������ź����޷���,value_type = '+' | '-' , (* +=unsigned, -=signed *)
	std::string m_value_type;///< ����Ϊ�����ʱ������DBC�ļ��Աȣ���������
	/**factor��offset����������ת������,���źŵ�ԭʼֵת��Ϊ�źŵ�����ֵ*/
	double	m_factor;
	double	m_offset;
	/**minimum��maximum�������źŵ�����ֵ����Ч��Χ*/
	double	m_minimum;
	double	m_maximum;
	std::string m_unit;
	std::string m_receiver;///< receiverָ���˽��սڵ������,�˴���m_receiver�а����˶�����սڵ�����ƣ�����Ϊ�����ʱ������DBC�ļ��Աȣ���������
	std::vector<std::string> m_rece_unit;///< ����m_rece_unit���ڴ洢receiver�еĶ�����սڵ�����ƽ��зָ��ĸ������սڵ�����
};
#endif // !_SIGNALANALYZER_H_
