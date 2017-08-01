/**@file
*@brief FindAndPrint���к����ľ���ʵ��
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
*@brief FindMessageAndSignalNameByNodeName�������ڲ���message_name��signal_name
*@author luoaling
*
*FindMessageAndSignalNameByNodeName����ȷ��Ҫ����֮��ͨ������
*�ڵ�node���ֵ�node_name������FindMessageNameByTransmitter����
*��FindSignalsNameByReceiver�����ҵ���Ӧ��message_name��signal_name��
*�������ҵ��Ľ����ӡ���
*
*/
void FindAndPrint::FindMessageAndSignalNameByNodeName(void) {
	
	string str;
	cout << "�Ƿ�Ҫ���ҽڵ㣿 Y:���ң�N:������ ";
	cin >> str;
	if (cin.get() == 'N') { cout << "�˳�����" << endl; return; }
	else {
		cout << "��������Ҫ���ҵĽڵ����ƣ�";
		cin.clear();
		cin >> str;
		FindMessageNameByTransmitter(str);
		FindSignalsNameByReceiver(str);
	}
}

/**
*@brief FindMessageNameByTransmitter�������ڲ���message_name
*@author luoaling
*
*FindMessageNameByTransmitter����������FindMessageAndSignalNameByNodeName������ʹ�ã�
*Ҳ���Ե�������ͨ�����뷢�ͽڵ�transmitter�����ƣ��ҵ���Ӧ��message_name������ӡ���
*
*@param[in] str str��Ϊ���ͽڵ�transmitter������
*/
void FindAndPrint::FindMessageNameByTransmitter(const string &str) {
	
	
	auto msg = Messages();
	cout << "���ڷ��ͽڵ� \"" << str << " \"" << ", �ҵ����µ�message_name: " << endl;
	for (auto const & _msg : Messages()) {
		if (_msg.Transmitter() == str)
		{
			cout << _msg.Name() << endl;
		}
	}
}

/**
*@brief FindSignalsNameByReceiver�������ڲ���signal_name
*@author luoaling
*
*FindSignalsNameByReceiver����������FindMessageAndSignalNameByNodeName������ʹ�ã�
*Ҳ���Ե�������ͨ��������սڵ�receiver�����ƣ��ҵ���Ӧ��signal_name������ӡ���
*
*@param[in] str str��Ϊ���սڵ�receiver������
*/
void FindAndPrint::FindSignalsNameByReceiver(const string &str) {
	
	Signal sig;
	
	cout << "���ڽ��սڵ� \"" << str << " \"" << ", �ҵ����µ�signal_name: " << endl;
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
*@brief FindAttributeNameByValueType�������ڲ���attribute_name
*@author luoaling
*
*FindAttributeNameByValueType�����������0~4��Χ�ڵ�����ǿ��ת����ö��ֵ��
*Ȼ����ͨ��ö��ֵ���ҵ���Ӧ��attribute_name
*
*@note ֻ������0~4��Χ�ڵ����ͣ����������Χ��Ҫ��������
*/
void FindAndPrint::FindAttributeNameByValueType(void) {
	
	
	cout << "�Ƿ�Ҫ�����������ƣ� Y:���ң�N:������ ";
	if (cin.get() == 'N') { cout << "�˳�����" << endl; return; }
	else {
		cout << "��������Ҫ���ҵ�����ֵ 0->INT,1->HEX,2->FOLAT,3->STRING,4->ENUM��";
		int value;
		cin.clear();
		cin >> value;
		while ((value<0) | (value>4)) {
			cin.clear();
			cout << "����������������룺";
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
*@brief FindMaxAndMinValueByValueType�������ڲ�����ֵ��Χ��ϵ���ַ���
*@author luoaling
*
*FindMaxAndMinValueByValueType�����������0��1��2��4������ǿ��ת����ö��ֵ��
*Ȼ��ͨ��0��1��2��Ӧ��ö��ֵ���ҵ���ֵ��Χ��ͨ����4��Ӧ��ö��ֵ���ҵ�ϵ���ַ�����
*���������ӡ���
*
*@note ֻ������0~4��Χ�ڵ����ͣ����������Χ��Ҫ�������룬
��ʱ��������3�Ǵ���ģ���ΪSTRING����ֵ�����ַ������Բ���
*/
void FindAndPrint::FindMaxAndMinValueByValueType(void) {
	
	
	cout << "STRING�����޷����ң�ENUM������һϵ���ַ�����" << endl;
	cout << "�Ƿ�Ҫ�������Ե���ֵ��Χ�� Y:���ң�N:������ ";
	if (cin.get() == 'N') { cout << "�˳�����" << endl; return; }
	else {
		cout << "��������Ҫ���ҵ�����ֵ 0->INT,1->HEX,2->FOLAT,4->ENUM��";
		int value;
		cin.clear();
		cin >> value;
		while ((value<0) | (value == 3) | (value>4)) {
			cin.clear();
			if (value == 3) {
				cout << "�������STRING����û����ֵ�����������룺";
			}
			else {
				cout << "����������������룺";
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
*@brief FindAttributeNameAndValueRangeByValueType�������ڲ���attribute_name����ֵ��Χ��ϵ���ַ���
*@author luoaling
*
*FindAttributeNameAndValueRangeByValueType������ǰ���ַ�����
*��FindAttributeNameByValueType������FindMaxAndMinValueByValueType����
*�Ľ��
*
*@note ֻ������0~4��Χ�ڵ����ͣ����������Χ��Ҫ�������룬
��ʱ��������3û�д��󣬵���ֻ�ܲ��ҵ���Ӧ��attribute_name
*/
void FindAndPrint::FindAttributeNameAndValueRangeByValueType(void) {
	
	
	cout << "�Ƿ�Ҫ�����������ԣ��������ơ���ֵ��Χ��ϵ���ַ����� Y:���ң�N:������ ";
	if (cin.get() == 'N') { cout << "�˳�����" << endl; return; }
	else {
		cout << "��������Ҫ���ҵ�����ֵ 0->INT,1->HEX,2->FOLAT,3->STRING,4->ENUM��";
		int value;
		cin.clear();
		cin >> value;
		while ((value<0) | (value>4)) {
			cin.clear();
			cout << "����������������룺";
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
*@brief PrintNodes�������ڴ�ӡ����ڵ�node���ֵ�����
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
*@brief PrintMessage�������ڴ�ӡ���ֻ��message���ֵ�����
*@author luoaling
*/
void FindAndPrint::PrintMessage(void) {
	
	
	for (auto const & _msg : Messages()) {
		cout << "BO_ " << _msg.ID() << " " << _msg.Name() << " : " << (int)_msg.GetSize() << " " << _msg.Transmitter() << endl;
	}
	cout << endl;
}

/**
*@brief PrintMessages�������ڴ�ӡ���message���ֺ�signal���ֵ�����
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
*@brief PrintAttribute�������ڴ�ӡ���attribute definitions���ֵ�����
*@author luoaling
*@note ����attribute definitions���ֵ����ݽ�Ϊ���ӣ�������Ҫ��������
*���У�default��֧��attribute_default���ֵ�����
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
