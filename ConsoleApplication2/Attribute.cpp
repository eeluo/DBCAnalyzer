#include "stdafx.h"
#include "AttributeAnalyzer.h"

std::ostream & operator<<(std::ostream & os, const Attribute & atb)
{
	os << "Attribute's object type: " << atb.ObjType()
		<< "\tAttribute's name: " << atb.AttributeName()
		<< "\tAttribute's default value: " << atb.DefaultValue()
		<< "\tAttribute's value type: ";
	for (const auto & str : atb.ValueType())
	{
		os << str << ' ';
	}
	return os;
}