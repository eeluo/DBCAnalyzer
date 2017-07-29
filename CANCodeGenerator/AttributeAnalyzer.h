#pragma once
#include <string>
#include <vector>
#include <cstdint>

class Attribute {

public:
	/*enum OBJ_TYPE {
		_,
		BU_,
		BO_,
		SG_,
		EV_
	};*/
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

	//OBJ_TYPE m_obj_type;
	std::string m_obj_type;
	std::string m_att_name;
	std::string m_att_def_val;
	std::vector<std::string> m_val_type;
	VALUE_TYPE m_value_type;

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


