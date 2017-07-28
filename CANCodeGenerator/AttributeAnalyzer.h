#pragma once
#include <string>
#include <vector>
#include <cstdint>

class Attribute {

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
		//m_rece_unit.push_back(_rece_unit);
	}
	std::vector<std::string> & ValueType(void) {
		return m_val_type;
	}
	std::vector<std::string> const & ValueType(void) const {
		return m_val_type;
	}


private:

	std::string m_obj_type;
	std::string m_att_name;
	std::vector<std::string> m_val_type;

};
