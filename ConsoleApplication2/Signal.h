#pragma once

#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <string>
#include <vector>
#include <cstdint>

/** "def
*  first std::string,second: char,third: a container of string
*  for example:
*  SPILT("hello world I am Cpp", ' ', any_container)--->
*  "hello" "world" "I" "am" "Cpp"
*/
#define SPILT(_Str,_C,_Container)									\
	do{																\
		std::string _S(_Str);										\
		for (auto _Iter = _S.begin(), _Flag = _S.begin();; _Iter++)	\
		{			                   								\
			if (_S.end() == _Iter)									\
			{														\
				_Container.push_back(std::string(_Flag, _Iter));	\
				break;												\
			}														\
			if (_C == *_Iter)										\
			{														\
				_Container.push_back(std::string(_Flag, _Iter));	\
				_Flag = _Iter;										\
				while(_C == *_Iter)									\
				{													\
					_Flag++;										\
					_Iter++;										\
					if (_Iter == _S.end())							\
						break;										\
				}													\
			}														\
			if (_Iter == _S.end())									\
				break;												\
		}															\
	} while (0)

/**
*@brief string�ַ����ķָ�splitģ�庯��.
*@author luoaling
*@date 2017-7-26
*
*split��������ͨ������string�ַ����ͷָ���,����ͬʱ������ַָ����,
*�ָ���֮��Ҳ����Ҫ���,����һ���洢�˷ָ��������ַ���������.
*
*@param[in] s,delim sΪҪ�ָ���ַ���,delimΪ�ָ���.
*@return ����һ���洢�����ַ�����result����.
*@note split�����޷�ͬʱ�������ָ���
*�ܴ���:123,456 789;
*���ܴ���:123,.456 789;
*/
template <typename A, typename B>
A split(const B& s, const B& delim)
{
	A result;
	std::string::size_type pos1, pos2;
	pos2 = s.find_first_of(delim);///< pos2�����ҵ����ַָ��������е��׸�λ��
	pos1 = 0;///< pos1��ʼ��Ϊ�ַ���s�ĵ�һ���ַ���λ��
	while (std::string::npos != pos2)///< �Ƿ��ҵ��ָ���
	{
		result.push_back(s.substr(pos1, pos2 - pos1));
		///�ƶ�pos1��pos2��λ��
		pos1 = pos2 + 1;
		pos2 = s.find_first_of(delim, pos1);
	}
	if (pos1 != s.length()) {
		result.push_back(s.substr(pos1));
	}
	return result;
}
//deal with signal
class Signal {
public:
	void SetFactor(double factor)
	{
		m_factor = factor;
	}
	double Factor() const { return m_factor; }

	void SetOffset(double offset)
	{
		m_offset = offset;
	}
	double Offset() const { return m_offset; }

	void SetMinimum(double minimum)
	{
		m_minimum = minimum;
	}
	double Minimum() const { return m_minimum; }

	void SetMaximum(double maximum)
	{
		m_maximum = maximum;
	}
	double Maximum() const { return m_maximum; }

	void SetUnit(const std::string & unit)
	{
		m_unit = unit;
	}
	const std::string & Unit() const { return m_unit; }

	void SetReceivers(const std::vector<std::string> & receivers)
	{
		m_receivers = receivers;
	}
	const std::vector<std::string> & Receivers() const { return m_receivers; }

	std::vector<std::string>::size_type NumberOfReceivers() const { return m_receivers.size(); }

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

private:
	std::string m_signal_name;//<signal name
	uint8_t	m_start_bit;//<start bit
	uint8_t	m_signal_size;//<signal size
	bool	m_is_big_endian;//<whether big endian
	bool	m_is_unsigned;//<whether unsigned

	double	m_factor;//<factor
	double	m_offset;//<offset
	double	m_minimum;//<minmum
	double	m_maximum;//<maximum
	std::string	m_unit;//<uint
	std::vector<std::string> m_receivers;//<receivers
};

std::ostream & operator<<(std::ostream & os, const Signal & signal);

#endif