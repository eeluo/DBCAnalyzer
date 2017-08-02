#include "stdafx.h"
#include "NodeAnalyzer.h"

std::ostream & operator<<(std::ostream & os, const Node & node)
{
	os << "Node names are: ";
	for (auto iter = node.NodeName().begin(); iter < node.NodeName().end(); iter++)
	{
		os << *iter << ' ';
	}
	return os;
}