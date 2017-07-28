//#include "AttributeAnalyzer.h"
//#include <vector>
//#include "DBCAnalyzer.h"
//#include <regex>
//#include <fstream>
//#include <string>
//#include <iostream>
//#include <stdlib.h>



//bool Message::MessageRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor)
//{
//	//attribute_definition = 'BA_DEF_' object_type attribute_name attribute_value_type ';';
//	//object_type = '' | 'BU_' | 'BO_' | 'SG_' | 'EV_' ;
//	//attribute_name = '"' C_identifier '"' ;
//	//attribute_value_type = 'INT' signed_integer signed_integer |
//							//'HEX' signed_integer signed_integer |
//							//'FLOAT' double double |
//							//'STRING' |
//							//'ENUM'[char_string{ ',' char_string }]
//	std::regex message_definition(R"(BO_\s+(\d+)\s+([a-zA-Z_](\w*))\s*:\s*(\d+)\s+((\w+)|Vector__XXX))");
//	std::smatch m;
//	if (!std::regex_match(_line, m, message_definition)) {
//		return false;
//	}
//
//	Message msg;
//	msg.SetMsgID(std::stol(m[1].str()));
//	msg.SetMessageName(m[2].str());
//	msg.SetMsgSize(std::stoi(m[4].str()));
//	msg.SetMessageTransmitter(m[5].str());
//
//	_file_descriptor.AddMessage(msg);
//
//	return true;
//}
//bool DBCAnalyzer::AttributeRecognizer(std::string const & _line, DBCFileDescriptor & _file_descriptor) {
//	// attribute_definition = 'BA_DEF_' object_type attribute_name attribute_value_type ';';
//	//object_type = '' | 'BU_' | 'BO_' | 'SG_' | 'EV_' ;
//	//attribute_name = '"' C_identifier '"' ;
//	//attribute_value_type = 'INT' signed_integer signed_integer |
//								//'HEX' signed_integer signed_integer |
//								//'FLOAT' double double |
//								//'STRING' |
//								//'ENUM'[char_string{ ',' char_string }]
//	std::regex attribute_definition(R"()");
//	std::smatch m;
//	if (!std::regex_match(_line, m, attribute_definition)) {
//		return false;
//	}
//
//	Attribute att;
//
//
//	_file_descriptor.AddAttribute(att);
//
//	return true;
//
//}