/**@file
*@brief 定义了一个Signal类.
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
*@biref signal部分列出放置在消息上的所有信号,它们在消息数据字段中的位置及其属性.
*
*signal中包含了signal_name,start_bit,signal_size,byte_order,value_type,(factor,offset)
*[minimum|maximum ] ,unit和receiver等.
*
*@note 接收节点必须在节点部分的节点名称node_name集合中定义,如果signal没有接收节点,
*receiver的字符串必须设置成"Vector__XXX".
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

	/**SetReceiver和Receiver仅是为了输出时容易与DBC文件对比，并无意义*/
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
	/**GetByteOrder、SetByteOrder、GetValueType、SetValueType方法同样无意义*/
	uint8_t GetByteOrder(void) const { return m_byte_order; }
	void SetByteOrder(uint8_t _byte_order) { m_byte_order = _byte_order; }
	std::string const &GetValueType (void) const { return m_value_type; }
	void SetValueType(std:: string const _value_type) { m_value_type = _value_type; }


private:
	std::string m_signal_name;///< 此处定义的signal_name对于单个消息的信号必须是唯一的
	uint8_t m_start_bit;///< start_bit值指定信号在帧的数据段内的位置,而且其范围为 0 ~ 8*message_size - 1
	uint8_t m_signal_size;///< signal_size指定信号的比特大小
	bool    m_is_big_endian;///< byte_order = '0' | '1',如果信号的字节顺序为 Motorola,则 1=little endian, 0=big endian
	uint8_t m_byte_order;///< 仅是为了输出时容易与DBC文件对比，并无意义
	bool    m_is_unsigned;///< value_type定义了信号有无符号,value_type = '+' | '-' , (* +=unsigned, -=signed *)
	std::string m_value_type;///< 仅是为了输出时容易与DBC文件对比，并无意义
	/**factor和offset定义了线性转换规则,将信号的原始值转换为信号的物理值*/
	double	m_factor;
	double	m_offset;
	/**minimum和maximum定义了信号的物理值的有效范围*/
	double	m_minimum;
	double	m_maximum;
	std::string m_unit;
	std::string m_receiver;///< receiver指定了接收节点的名称,此处的m_receiver中包含了多个接收节点的名称，仅是为了输出时容易与DBC文件对比，并无意义
	std::vector<std::string> m_rece_unit;///< 容器m_rece_unit用于存储receiver中的多个接收节点的名称进行分割后的各个接收节点名称
};
#endif // !_SIGNALANALYZER_H_
