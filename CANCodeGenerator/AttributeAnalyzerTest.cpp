/**@file
*@brief ������һ��AttributeAnalyzerTest������
*@author luoaling
*
*������ AttributeAnalyzerTest������ ��ּ�ڼ���
*������ظ��ȣ�����TEST��ȫ���滻��TEST_F��
*
*/
#include"DBCAnalyzer.h"
#include<string>
#include <gtest/gtest.h> 

/**
*@class
*@biref AttributeAnalyzerTest�����AttributeRecognizer�������������ܵ�ʵ��
*
*���AttributeRecognizer������,����attribute_definition���ֵ�object_type,attribute_name,
*attribute_value_type�е�ö��ֵ����ֵ��ϵ���ַ����ļ���.
*���У�attribute_default���ֵ�attribute_name��attribute_value�ļ���
*
*@note ����ÿһ��TEST_F�ڵĵڶ������ԣ��������ڵ�һ�����ԣ�
*���������ַ�����Ҫ����������ʽ�����������������޷���������
*/
class AttributeAnalyzerTest:public testing::Test{
	DBCAnalyzer  dbc;
	DBCFileDescriptor descriptor;

public:
	std::string str1_d = "BA_DEF_ SG_ \"GenSigTimeout_CMU_05\" INT 0 65535;";
	std::string str2_d = "BA_DEF_   \"NWID\" HEX 0 255;";
	std::string str3_d = "BA_DEF_ BO_  \"NWM - Botschaft\" ENUM \"nein\",\"ja\";";
	std::string str1_dd = "BA_DEF_DEF_  \"BusType\" \"\";";
	std::string str2_dd = "BA_DEF_DEF_  \"dNBU\" 0;";
	bool str1_d_re = dbc.AttributeRecognizer(str1_d,descriptor);
	bool str2_d_re = dbc.AttributeRecognizer(str2_d, descriptor);
	bool str3_d_re = dbc.AttributeRecognizer(str3_d, descriptor);
	bool str1_dd_re = dbc.AttributeRecognizer(str1_dd, descriptor);
	bool str2_dd_re = dbc.AttributeRecognizer(str2_dd, descriptor);
	std::string obj_type1 = descriptor.Attributes()[0].ObjType();
	std::string obj_type2 = descriptor.Attributes()[1].ObjType();
	std::string obj_type3 = descriptor.Attributes()[2].ObjType();
	std::string att_name1 = descriptor.Attributes()[0].AttributeName();
	std::string att_name2 = descriptor.Attributes()[1].AttributeName();
	std::string att_name3 = descriptor.Attributes()[2].AttributeName();
	std::string att_name1_d = descriptor.Attributes()[3].AttributeName();
	std::string att_name2_d = descriptor.Attributes()[4].AttributeName();
	Attribute::VALUE_TYPE value_type1 = descriptor.Attributes()[0].GetValueType();
	Attribute::VALUE_TYPE value_type2 = descriptor.Attributes()[1].GetValueType();
	Attribute::VALUE_TYPE value_type3 = descriptor.Attributes()[2].GetValueType();
	uint32_t att_val_min1 = std::stoi(descriptor.Attributes()[0].ValueType()[1]);
	uint32_t att_val_min2 = std::stoi(descriptor.Attributes()[1].ValueType()[1]);
	uint32_t att_val_max1 = std::stoi(descriptor.Attributes()[0].ValueType()[2]);
	uint32_t att_val_max2 = std::stoi(descriptor.Attributes()[1].ValueType()[2]);
	std::string att_val_enum1 = descriptor.Attributes()[2].ValueType()[1];
	std::string att_val_enum2 = descriptor.Attributes()[2].ValueType()[2];
	std::string att_val_d1 = descriptor.Attributes()[3].DefaultValue();
	std::string att_val_d2 = descriptor.Attributes()[4].DefaultValue();
	virtual void SetUp() {}
	virtual void TearDown() {}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief ���µ�TEST_F���Ƕ�attribute���ض����ֵļ���
*@author luoaling
*
*��ֵ�������EXPECT_EQ��EXPECT_NE���ԣ�
*�ַ����������EXPECT_STREQ��EXPECT_STRNE����
*ö��ֵ�������
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//���·ֱ�ʹ�������ַ���������attribute_definion��ȷ�� object_type
//TEST_F(AttributeAnalyzerTest, objtype_true001) {
//	EXPECT_TRUE(str1_d_re);
//	EXPECT_STREQ("SG_", obj_type1.c_str());
//}
//TEST_F(AttributeAnalyzerTest, objtype_true002) {
//	EXPECT_TRUE(str2_d_re);
//	EXPECT_STREQ(" ", obj_type2.c_str());
//}
//TEST_F(AttributeAnalyzerTest, objtype_true003) {
//	EXPECT_TRUE(str3_d_re);
//	EXPECT_STREQ("BO_", obj_type3.c_str());
//}
////���·ֱ�ʹ�������ַ���������attribute_definion��ȷ�� attribute_name
//TEST_F(AttributeAnalyzerTest, attname_true001) {
//	EXPECT_TRUE(str1_d_re);
//	EXPECT_STREQ("\"GenSigTimeout_CMU_05\"", att_name1.c_str());
//}
//TEST_F(AttributeAnalyzerTest, attname_true002) {
//	EXPECT_TRUE(str2_d_re);
//	EXPECT_STREQ("\"NWID\"", att_name2.c_str());
//}
//TEST_F(AttributeAnalyzerTest, attname_true003) {
//	EXPECT_TRUE(str3_d_re);
//	EXPECT_STREQ("\"NWM - Botschaft\"", att_name3.c_str());
//}
////���·ֱ�ʹ�������ַ���������attribute_definion��ȷ�� value_type����һ��ö��ֵ
//TEST_F(AttributeAnalyzerTest, valtype_true001) {
//	EXPECT_TRUE(str1_d_re);
//	EXPECT_EQ(INT, value_type1);
//}
//TEST_F(AttributeAnalyzerTest, valtype_enum_true002) {
//	EXPECT_TRUE(str2_d_re);
//	EXPECT_EQ("HEX", value_type2);
//}
//TEST_F(AttributeAnalyzerTest, valtype_enum_true003) {
//	EXPECT_TRUE(str3_d_re);
//	EXPECT_EQ("ENUM", value_type3);
//}
//���·ֱ�ʹ�������ַ���������attribute_definion��ȷ�� value_type����һ����ֵ
//TEST_F(AttributeAnalyzerTest, valtype_minval_true001) {
//	EXPECT_TRUE(str1_d_re);
//	EXPECT_EQ(0, att_val_min1);
//}
//TEST_F(AttributeAnalyzerTest, valtype_minval_true002) {
//	EXPECT_TRUE(str2_d_re);
//	EXPECT_EQ(0, att_val_min2);
//}
//TEST_F(AttributeAnalyzerTest, valtype_maxval_true001) {
//	EXPECT_TRUE(str1_d_re);
//	EXPECT_EQ(65535, att_val_max1);
//}
//TEST_F(AttributeAnalyzerTest, valtype_maxval_true002) {
//	EXPECT_TRUE(str2_d_re);
//	EXPECT_EQ(255, att_val_max2);
//}
////����ʹ��һ���ַ���������attribute_definion��ȷ�� value_type����ϵ���ַ���������������
//TEST_F(AttributeAnalyzerTest, valtype_str_true001) {
//	EXPECT_TRUE(str3_d_re);
//	EXPECT_STREQ("\"nein\"", att_val_enum1.c_str());
//}
//TEST_F(AttributeAnalyzerTest, valtype_str_true002) {
//	EXPECT_TRUE(str3_d_re);
//	EXPECT_STREQ("\"ja\"", att_val_enum2.c_str());
//}
//
//
//
//
//
//
//
//
//
//
//
//
////���·ֱ�ʹ�������ַ���������attribute_default��ȷ�� attribute_name
//TEST_F(AttributeAnalyzerTest, attnamedef_true001) {
//	EXPECT_TRUE(str1_dd_re);
//	EXPECT_STREQ("\"BusType\"", att_name1_d.c_str());
//}
//TEST_F(AttributeAnalyzerTest, attnamedef_true002) {
//	EXPECT_TRUE(str2_dd_re);
//	EXPECT_STREQ("\"dNBU\"", att_name2_d.c_str());
//}
////���·ֱ�ʹ�������ַ���������attribute_default��ȷ�� attribute_value
//TEST_F(AttributeAnalyzerTest, attvaldef_true001) {
//	EXPECT_TRUE(str1_dd_re);
//	EXPECT_STREQ("\"\"", att_val_d1.c_str());
//}
//TEST_F(AttributeAnalyzerTest, attvaldef_true002) {
//	EXPECT_TRUE(str2_dd_re);
//	EXPECT_STREQ("0", att_val_d2.c_str());
//}