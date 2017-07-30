/**@file
*@brief 定义了一个Node类.
*@author luoaling
*@date 2017-7-29
*
*在DBC文件中节点部分定义了所有参与节点的名称,在本节中定义的名称在本节中必须是唯一的.
*
*/
#pragma once
#include <string>
#include <vector>

using namespace std;
/**
*@class 
*@biref Node类较为简单，只有一个存储了string类型 node_name 的vector容器变量.
*
*在该类中利用AddNodeName方法添加节点的node_name,以及NodeName方法获取node_name.
*
*/
class Node {

public:

	/**AddNodeName方法用于vector容器的赋值,而NodeName方法则是用于得到该容器.*/
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
