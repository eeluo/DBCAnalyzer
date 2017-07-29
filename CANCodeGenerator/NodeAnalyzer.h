#pragma once
#include <string>
#include <vector>

using namespace std;

class Node {

public:

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
