/**@file
*@brief FindAndPrint类中函数的具体实现
*@author luoaling
*@date 2017-7-31 
*/
#include "DBCAnalyzer.h"
#include "DBCFileDescriptor.h"
#include "FindAndPrint.h"
#include <iostream>
#include <vector>
#include <string>

FindAndPrint::FindAndPrint() {

}
FindAndPrint::~FindAndPrint() {

}

/**
*@brief FindMessageAndSignalNameByNodeName方法用于查找message_name和signal_name
*@author luoaling
*
*FindMessageAndSignalNameByNodeName方法确认要查找之后，通过输入
*节点node部分的node_name，调用FindMessageNameByTransmitter方法
*和FindSignalsNameByReceiver方法找到对应的message_name和signal_name，
*并将查找到的结果打印输出
*
*/
void FindAndPrint::FindMessageAndSignalNameByNodeName(void) {
	
	string str;
	cout << "是否要查找节点？ Y:查找，N:不查找 ";
	cin >> str;
	if (cin.get() == 'N') { cout << "退出查找" << endl; return; }
	else {
		cout << "请输入您要查找的节点名称：";
		cin.clear();
		cin >> str;
		FindMessageNameByTransmitter(str);
		FindSignalsNameByReceiver(str);
	}
}

/**
*@brief FindMessageNameByTransmitter方法用于查找message_name
*@author luoaling
*
*FindMessageNameByTransmitter方法可以在FindMessageAndSignalNameByNodeName方法中使用，
*也可以单独用来通过输入发送节点transmitter的名称，找到对应的message_name，并打印输出
*
*@param[in] str str即为发送节点transmitter的名称
*/
void FindAndPrint::FindMessageNameByTransmitter(const string &str) {
	
	
	auto msg = Messages();
	cout << "对于发送节点 \"" << str << " \"" << ", 找到以下的message_name: " << endl;
	for (auto const & _msg : Messages()) {
		if (_msg.Transmitter() == str)
		{
			cout << _msg.Name() << endl;
		}
	}
}

/**
*@brief FindSignalsNameByReceiver方法用于查找signal_name
*@author luoaling
*
*FindSignalsNameByReceiver方法可以在FindMessageAndSignalNameByNodeName方法中使用，
*也可以单独用来通过输入接收节点receiver的名称，找到对应的signal_name，并打印输出
*
*@param[in] str str即为接收节点receiver的名称
*/
void FindAndPrint::FindSignalsNameByReceiver(const string &str) {
	
	Signal sig;
	
	cout << "对于接收节点 \"" << str << " \"" << ", 找到以下的signal_name: " << endl;
	for (auto const & _msg : Messages()) {
		for (auto const & _signal : _msg.Signals()) {
			for (auto const & re_unit : _signal.Rece_unit()) {
				if (re_unit == str)
					cout << _signal.Name() << endl;
			}
		}
	}
}

/**
*@brief FindAttributeNameByValueType方法用于查找attribute_name
*@author luoaling
*
*FindAttributeNameByValueType方法将输入的0~4范围内的整型强制转换成枚举值，
*然后再通过枚举值，找到对应的attribute_name
*
*@note 只能输入0~4范围内的整型，超出这个范围需要重新输入
*/
void FindAndPrint::FindAttributeNameByValueType(void) {
	
	
	cout << "是否要查找属性名称？ Y:查找，N:不查找 ";
	if (cin.get() == 'N') { cout << "退出查找" << endl; return; }
	else {
		cout << "请输入您要查找的属性值 0->INT,1->HEX,2->FOLAT,3->STRING,4->ENUM：";
		int value;
		cin.clear();
		cin >> value;
		while ((value<0) | (value>4)) {
			cin.clear();
			cout << "输入错误，请重新输入：";
			cin >> value;
		}
		Attribute::VALUE_TYPE type = Attribute::VALUE_TYPE(value);
		for (auto const & att : Attributes()) {
			if (type == att.GetValueType()) {
				cout << att.AttributeName() << endl;
			}
		}
	}
}

/**
*@brief FindMaxAndMinValueByValueType方法用于查找数值范围或系列字符串
*@author luoaling
*
*FindMaxAndMinValueByValueType方法将输入的0、1、2、4等整型强制转换成枚举值，
*然后通过0、1、2对应的枚举值，找到数值范围，通过与4对应的枚举值，找到系列字符串，
*并将结果打印输出
*
*@note 只能输入0~4范围内的整型，超出这个范围需要重新输入，
此时输入整型3是错误的，因为STRING无数值、无字符串可以查找
*/
void FindAndPrint::FindMaxAndMinValueByValueType(void) {
	
	
	cout << "STRING类型无法查找，ENUM类型是一系列字符串！" << endl;
	cout << "是否要查找属性的数值范围？ Y:查找，N:不查找 ";
	if (cin.get() == 'N') { cout << "退出查找" << endl; return; }
	else {
		cout << "请输入您要查找的属性值 0->INT,1->HEX,2->FOLAT,4->ENUM：";
		int value;
		cin.clear();
		cin >> value;
		while ((value<0) | (value == 3) | (value>4)) {
			cin.clear();
			if (value == 3) {
				cout << "输入错误！STRING类型没有数值，请重新输入：";
			}
			else {
				cout << "输入错误，请重新输入：";
			}
			cin >> value;
		}
		Attribute::VALUE_TYPE type = Attribute::VALUE_TYPE(value);
		for (auto const & att : Attributes()) {
			if ((type == att.GetValueType()) && (type != Attribute::ENUM)) {
				cout << "min:" << att.ValueType()[1] << "  " << "max:" << att.ValueType()[2] << endl;
			}
			if ((type == att.GetValueType()) && (type == Attribute::ENUM)) {
				for (auto it = att.ValueType().begin() + 1; it != att.ValueType().end(); it++)
				{
					cout << *it << " ";
				}
				cout << endl;
			}
		}
	}
}

/**
*@brief FindAttributeNameAndValueRangeByValueType方法用于查找attribute_name和数值范围或系列字符串
*@author luoaling
*
*FindAttributeNameAndValueRangeByValueType方法是前两种方法，
*即FindAttributeNameByValueType方法和FindMaxAndMinValueByValueType方法
*的结合
*
*@note 只能输入0~4范围内的整型，超出这个范围需要重新输入，
此时输入整型3没有错误，但是只能查找到对应的attribute_name
*/
void FindAndPrint::FindAttributeNameAndValueRangeByValueType(void) {
	
	
	cout << "是否要查找所有属性，包括名称、数值范围或系列字符串？ Y:查找，N:不查找 ";
	if (cin.get() == 'N') { cout << "退出查找" << endl; return; }
	else {
		cout << "请输入您要查找的属性值 0->INT,1->HEX,2->FOLAT,3->STRING,4->ENUM：";
		int value;
		cin.clear();
		cin >> value;
		while ((value<0) | (value>4)) {
			cin.clear();
			cout << "输入错误，请重新输入：";
			cin >> value;
		}
		Attribute::VALUE_TYPE type = Attribute::VALUE_TYPE(value);
		for (auto const & att : descriptor.Attributes()) {
			if ((type == att.GetValueType()) && (type != Attribute::ENUM) && (type != Attribute::STRING)) {
				cout << "Name:" << att.AttributeName() << "  " << "min:" << att.ValueType()[1] << "  " << "max:" << att.ValueType()[2] << endl;
			}
			if ((type == att.GetValueType()) && (type == Attribute::STRING))
			{
				cout << "Name:" << att.AttributeName() << endl;
			}
			if ((type == att.GetValueType()) && (type == Attribute::ENUM)) {
				cout << "Name:" << att.AttributeName() << "  " << "String:";
				for (auto it = att.ValueType().begin() + 1; it != att.ValueType().end(); it++)
				{
					cout << *it << " ";
				}
				cout << endl;
			}
		}
	}
}

/**
*@brief PrintNodes方法用于打印输出节点node部分的内容
*@author luoaling
*/
void FindAndPrint::PrintNodes(void) {
	
	
	for (auto const & it : Nodes()) {
		cout << "BU_: ";
		for (auto const &it_no : it.NodeName()) {
			cout << it_no << " ";
		}
		cout << endl;
	}
}

/**
*@brief PrintMessage方法用于打印输出只有message部分的内容
*@author luoaling
*/
void FindAndPrint::PrintMessage(void) {
	
	
	for (auto const & _msg : Messages()) {
		cout << "BO_ " << _msg.ID() << " " << _msg.Name() << " : " << (int)_msg.GetSize() << " " << _msg.Transmitter() << endl;
	}
	cout << endl;
}

/**
*@brief PrintMessages方法用于打印输出message部分和signal部分的内容
*@author luoaling
*/
void FindAndPrint::PrintMessages(void) {
	
	Signal sig;
	
	for (auto const & _msg : Messages()) {
		cout << "BO_ " << _msg.ID() << " " << _msg.Name() << " : " << (int)_msg.GetSize() << " " << _msg.Transmitter() << endl;
		for (auto const & _signal : _msg.Signals()) {
			cout << " SG_ " << _signal.Name() << " : " << (int)_signal.StartBit() << "|" << (int)_signal.SignalSize() << "@"
				<< (int)_signal.GetByteOrder() << _signal.GetValueType()
				<< " (" << _signal.GetFactor() << "," << _signal.GetOffset() << ") "
				<< " [" << _signal.GetMinimum() << "|" << _signal.GetMaximum() << "] "
				<< "\"" << _signal.Unit() << "\""
				<< " " << _signal.Receiver() << endl;
		}
		cout << endl;
	}
	cout << endl;
}

/**
*@brief PrintAttribute方法用于打印输出attribute definitions部分的内容
*@author luoaling
*@note 由于attribute definitions部分的内容较为复杂，所以需要分情况输出
*其中，default分支是attribute_default部分的内容
*/
void FindAndPrint::PrintAttribute(void) {
	
	
	for (auto const & att : Attributes())
	{
		Attribute::VALUE_TYPE type = att.GetValueType();
		switch (type)
		{
		case Attribute::INT:
		case Attribute::HEX:
		case Attribute::FLOAT:
		case Attribute::ENUM:
			cout << "BA_DEF_ " << att.ObjType() << " " << att.AttributeName() << " ";
			for (auto const & it : att.ValueType())
			{
				cout << it << " ";
			}
			cout << ";" << endl;
			break;
		case Attribute::STRING:
			cout << "BA_DEF_ " << att.ObjType() << " " << att.AttributeName() << " " << att.ValueType()[0] << ";" << endl;
			break;
		default:
			cout << "BA_DEF_DEF_ " << att.AttributeName() << " " << att.DefaultValue() << ";" << endl;
			break;
		}
	}
}
