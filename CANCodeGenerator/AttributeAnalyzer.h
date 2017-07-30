/**@file
*@brief 定义了一个Attribute类.
*@author luoaling
*@date 2017-7-27
*/
#pragma once
#include <string>
#include <vector>
#include <cstdint>

/**
*@class
*@biref 用户定义的属性是用来延长DBC文件对象的属性.
*
*Attribute类只包含属性定义部分，没有包含属性值，它包括两部分：
*1.attribute_definition：其又包含object_type attribute_name attribute_value_type三部分
*2.attribute_default：只包含attribute_name attribute_value两部分
*
*/

class Attribute {

public:
	///  枚举VALUE_TYPE存储attribute_value_type的第一部分
	enum VALUE_TYPE {
		INT,
		HEX,
		FLOAT,
		STRING,
		ENUM
	};

public:

	std::string const & ObjType() const { return m_obj_type; }
	void SetObjType(std::string const & _obj_type) {
		m_obj_type = _obj_type;
	}

	std::string const & AttributeName() const { return m_att_name; }
	void SetAttributeName(std::string const & _att_name) {
		m_att_name = _att_name;
	}

	void AddValueType(std::vector<std::string> const & _val_type) {
		m_val_type = _val_type;
	}
	std::vector<std::string> & ValueType(void) {
		return m_val_type;
	}
	std::vector<std::string> const & ValueType(void) const {
		return m_val_type;
	}
	
	VALUE_TYPE GetValueType(void) const  { return m_value_type; }
	void SetValueType(VALUE_TYPE _value_type) {
		m_value_type = _value_type;
	}

	std::string const & DefaultValue() const { return m_att_def_val; }
	void SetDefaultValue(std::string const & _att_def_val) {
		m_att_def_val = _att_def_val;
	}

private:

	std::string m_obj_type;///< m_obj_type 只能是 '' | 'BU_' | 'BO_' | 'SG_' | 'EV_'中的一种
	std::string m_att_name;///< m_att_name必须是带双引号的C风格标识符
	std::string m_att_def_val;///< m_att_def_val 只能是unsigned_integer | signed_integer | double |char_string中的一种
	std::vector<std::string> m_val_type;///< 用于存储attribute_value_type部分分割后的各子字符串
	VALUE_TYPE m_value_type;///< 枚举变量定义

	/*int default_vi, max_vi, min_vi;
	float default_vf, max_vf, min_vf;
	
	int GetDefaultValueInt() {
		if (m_value_type != INT) {
			throw exception("Come on, this is not a int type~~! you can't use this");
		}
		return default_vi;
	}
*/
};


