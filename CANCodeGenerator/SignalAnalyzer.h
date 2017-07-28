#pragma once
#include <string>
#include <vector>
#include <cstdint>

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

	double GetFactor() { return m_factor; };
	void SetFactor(double _factor)  { m_factor = _factor;}

	double GetOffset() { return m_offset; }
	void SetOffset(double _offset) { m_offset = _offset; }

	double GetMinimum() { return m_minimum; }
	void SetMinimum(double _minimum) { m_minimum = _minimum; }

	double GetMaximum() { return m_maximum; }
	void SetMaximum(double _maximum) { m_maximum = _maximum; }

	void SetUnit(std::string const _unit) {
		m_unit = _unit;
	}
	std::string const & Unit(void) const { return m_unit; }

	void SetReceiver(std::string const _receiver) {
		m_receiver = _receiver;
	}
	std::string const & Receiver(void) const { return m_receiver; }

	void AddRece_unit(std::vector<std::string> const & _rece_unit) {
		m_rece_unit = _rece_unit;
		//m_rece_unit.push_back(_rece_unit);
	}
	std::vector<std::string> & Rece_unit(void) {
		return m_rece_unit;

	}
	std::vector<std::string> const & Rece_unit(void) const {
		return m_rece_unit;
	}

	uint8_t GetByteOrder(void) const { return m_byte_order; }
	void SetByteOrder(uint8_t _byte_order) { m_byte_order = _byte_order; }
	std::string const &GetValueType (void) const { return m_value_type; }
	void SetValueType(std:: string const _value_type) { m_value_type = _value_type; }

	/*bool SignalRecognizer(std::string const & _line, Message & _msg);
	uint8_t ChangMotorolaOrderMSBT2LSB(uint8_t start_bit, uint8_t signal_size);*/

private:
	std::string m_signal_name;
	uint8_t m_start_bit;
	uint8_t m_signal_size;
	bool    m_is_big_endian;
	uint8_t m_byte_order;
	bool    m_is_unsigned;
	std::string m_value_type;
	double	m_factor;
	double	m_offset;
	double	m_minimum;
	double	m_maximum;
	std::string m_unit;
	std::string m_receiver;
	std::vector<std::string> m_rece_unit;
};

