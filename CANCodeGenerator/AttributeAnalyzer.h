/**@file
*@brief ������һ��Attribute��.
*@author luoaling
*@date 2017-7-27
*/
#pragma once
#include <string>
#include <vector>
#include <cstdint>

/**
*@class
*@biref �û�����������������ӳ�DBC�ļ����������.
*
*Attribute��ֻ�������Զ��岿�֣�û�а�������ֵ�������������֣�
*1.attribute_definition�����ְ���object_type attribute_name attribute_value_type������
*2.attribute_default��ֻ����attribute_name attribute_value������
*
*/

class Attribute {

public:
	///  ö��VALUE_TYPE�洢attribute_value_type�ĵ�һ����
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

	std::string m_obj_type;///< m_obj_type ֻ���� '' | 'BU_' | 'BO_' | 'SG_' | 'EV_'�е�һ��
	std::string m_att_name;///< m_att_name�����Ǵ�˫���ŵ�C����ʶ��
	std::string m_att_def_val;///< m_att_def_val ֻ����unsigned_integer | signed_integer | double |char_string�е�һ��
	std::vector<std::string> m_val_type;///< ���ڴ洢attribute_value_type���ַָ��ĸ����ַ���
	VALUE_TYPE m_value_type;///< ö�ٱ�������

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


