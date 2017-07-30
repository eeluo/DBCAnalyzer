/**@file
*@brief ������һ��Node��.
*@author luoaling
*@date 2017-7-29
*
*��DBC�ļ��нڵ㲿�ֶ��������в���ڵ������,�ڱ����ж���������ڱ����б�����Ψһ��.
*
*/
#pragma once
#include <string>
#include <vector>

using namespace std;
/**
*@class 
*@biref Node���Ϊ�򵥣�ֻ��һ���洢��string���� node_name ��vector��������.
*
*�ڸ���������AddNodeName������ӽڵ��node_name,�Լ�NodeName������ȡnode_name.
*
*/
class Node {

public:

	/**AddNodeName��������vector�����ĸ�ֵ,��NodeName�����������ڵõ�������.*/
	void AddNodeName(std::vector<std::string> const & _node_name) {
		m_node_name = _node_name;
	}
	std::vector<std::string> & NodeName(void) {
		return m_node_name;

	}
	std::vector<std::string> const & NodeName(void) const {
		return m_node_name;
	}

private:
	vector<string> m_node_name;
};
