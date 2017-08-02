/**@file
*@brief ������һ��SignalRecognizerTest������
*@author luoaling
*
*������ SignalRecognizerTest������ ��ּ�ڼ���
*������ظ��ȣ�����TEST��ȫ���滻��TEST_F��
*
*/
#include"DBCAnalyzer.h"
#include<string>
#include <gtest/gtest.h> 

/**
*@class
*@biref SignalRecognizerTest�����SignalRecognizer�������������ܵ�ʵ��
*
*���SignalRecognizer������,signal_name,satrt_bit,signal_size,byte_order,
*value_type,factor,offset,minimum,maximum,unit��receiver�ļ���.
*���� SignalRecognizer�����ĸ����ԣ����û����MessageRecognizerTest����ֻ�Ǽ򵥵����������ַ�����
*�����������ĸ������ض�����Ҫ����ַ���.�����ǣ������е� is_big_endian=0 ʱ��
*����� start_bit ����ֵ�������� start_bit �Ķ��Լ���,����ڲ��� start_bit ����ֵ��ʱ��
*���ĳ� is_big_endian=1 ���ַ���
*
*@note ����ÿһ��TEST_F�ڵĵڶ������ԣ��������ڵ�һ�����ԣ�
*���������ַ�����Ҫ����������ʽ�����������������޷���������
*/
class SignalRecognizerTest : public testing::Test {
	
	DBCAnalyzer  dbc;
	Message msg;

public:
	std::string str1 = "SG_ SIG_12_03 : 55|16@1+ (2,0) [0|5] \"V\"  ECU,BCM";
	std::string str2 = "SG_ TPS_FAIL01 : 0|1@0+ (1,0) [0|0] \"\"  TCU,ETACS";
	std::string str3 = "SG_ SIG_12_ : 45|10@1- (0.001,0) [0|5] \"V\"  ECU,BCM";
	std::string str4 = "SG_ TPS_FAIL02 : 59|15@0- (1,0) [0|0] \"\"  TCU,ETACS";
	bool str1_re = dbc.SignalRecognizer(str1, msg);
	bool str2_re = dbc.SignalRecognizer(str2, msg);
	bool str3_re = dbc.SignalRecognizer(str3, msg);
	bool str4_re = dbc.SignalRecognizer(str4, msg);
	std::string   sig_name1 = msg.Signals()[0].Name();
	std::string   sig_name2 = msg.Signals()[1].Name();
	uint8_t    start_bit1 = msg.Signals()[0].StartBit();
	uint8_t    start_bit2 = msg.Signals()[2].StartBit();
	uint8_t    sig_size1 = msg.Signals()[0].SignalSize();
	uint8_t    sig_size2 = msg.Signals()[1].SignalSize();

	bool is_big_endian1 = msg.Signals()[0].IsBigEndian();
	bool is_big_endian2 = msg.Signals()[1].IsBigEndian();
	bool is_big_endian3 = msg.Signals()[2].IsBigEndian();
	bool is_big_endian4 = msg.Signals()[3].IsBigEndian();
	bool is_unsigned1 = msg.Signals()[0].IsUnsigned();
	bool is_unsigned2 = msg.Signals()[1].IsUnsigned();
	bool is_unsigned3 = msg.Signals()[2].IsUnsigned();
	bool is_unsigned4 = msg.Signals()[3].IsUnsigned();

	double factor1 = msg.Signals()[0].GetFactor();
	double factor2 = msg.Signals()[1].GetFactor();
	double offset1 = msg.Signals()[0].GetOffset();
	double offset2 = msg.Signals()[1].GetOffset();
	double min1 = msg.Signals()[0].GetMinimum();
	double min2 = msg.Signals()[1].GetMinimum();
	double max1 = msg.Signals()[0].GetMaximum();
	double max2 = msg.Signals()[1].GetMaximum();
	std::string   unit1 = msg.Signals()[0].Unit();
	std::string   unit2 = msg.Signals()[1].Unit();
	std::string   receiver1 = msg.Signals()[0].Receiver();
	std::string   receiver2 = msg.Signals()[1].Receiver();

	virtual void SetUp() {}
	virtual void TearDown() {}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief ���µ�TEST_F���Ƕ�signal���ض����ֵļ���
*@author luoaling
*
*��ֵ�������EXPECT_EQ��EXPECT_NE���ԣ�
*�ַ����������EXPECT_STREQ��EXPECT_STRNE����
*����ֵ�������EXPECT_TRUE��EXPECT_FALSE����
*
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//������ȷ�� signal_name
//TEST_F(SignalRecognizerTest, nameTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STREQ("SIG_12_03", sig_name1.c_str());
//}
//TEST_F(SignalRecognizerTest, nameTest_True002) {	
//	EXPECT_TRUE(str2_re);
//	EXPECT_STREQ("TPS_FAIL01", sig_name2.c_str());
//}
////������ȷ�� start_bit 
//TEST_F(SignalRecognizerTest, start_bitTest_True001) {	
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(55, start_bit1);
//}
//TEST_F(SignalRecognizerTest, start_bitTest_True002) {	
//	EXPECT_TRUE(str3_re);
//	EXPECT_EQ(45, start_bit2);
//}
////������ȷ�� signal_size
//TEST_F(SignalRecognizerTest, sizeTest_True001) {	
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(16, sig_size1);
//}
//TEST_F(SignalRecognizerTest, sizeTest_True002) {	
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(1, sig_size2);
//}
////�ж��Ƿ��Ǵ�ˣ�����Ǵ�ˣ��� is_big_endian = 0 ����ʱ����ֵΪtrue
//TEST_F(SignalRecognizerTest, big_endianTest_True001) {	
//	EXPECT_TRUE(str2_re);
//	EXPECT_TRUE(is_big_endian2);
//}
//TEST_F(SignalRecognizerTest, big_endianTest_True002) {
//	EXPECT_TRUE(str4_re);
//	EXPECT_TRUE(is_big_endian4);
//}
////�ж� is_unsigned ��ֵ��is_unsigned = + , ��ʱ����ֵΪtrue
//TEST_F(SignalRecognizerTest, value_typeTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_TRUE(is_unsigned1);
//}
//TEST_F(SignalRecognizerTest, value_typeTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_TRUE(is_unsigned2);
//}
////������ȷ�� factor
//TEST_F(SignalRecognizerTest, factorTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(2, factor1);
//}
//TEST_F(SignalRecognizerTest, factorTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(1, factor2);
//}
////������ȷ�� offset
//TEST_F(SignalRecognizerTest, offsetTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(0, offset1);
//}
//TEST_F(SignalRecognizerTest, offsetTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(0, offset2);
//}
////������ȷ�� minimum
//TEST_F(SignalRecognizerTest, minimumTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(0, min1);
//}
//TEST_F(SignalRecognizerTest, minimumTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(0, min2);
//}
////������ȷ�� maximum
//TEST_F(SignalRecognizerTest, maximumTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(5, max1);
//}
//TEST_F(SignalRecognizerTest, maximumTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(0, max2);
//}
////������ȷ�� unit
//TEST_F(SignalRecognizerTest, unitTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STREQ("V", unit1.c_str());
//}
//TEST_F(SignalRecognizerTest, unitTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STREQ("", unit2.c_str());
//}
////������ȷ�� receiver
//TEST_F(SignalRecognizerTest, receiverTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STREQ("ECU,BCM", receiver1.c_str());
//}
//TEST_F(SignalRecognizerTest, receiverTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STREQ("TCU,ETACS", receiver2.c_str());
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////���Դ���� signal_name
//TEST_F(SignalRecognizerTest, nameTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STRNE("SIG_1203", sig_name1.c_str());
//}
//TEST_F(SignalRecognizerTest, nameTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STRNE("TPS_FAIL", sig_name2.c_str());
//}
////���Դ���� start_bit 
//TEST_F(SignalRecognizerTest, start_bitTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(5, start_bit1);
//}
//TEST_F(SignalRecognizerTest, start_bitTest_False002) {
//	EXPECT_TRUE(str3_re);
//	EXPECT_NE(10, start_bit2);
//}
////���Դ���� signal_size
//TEST_F(SignalRecognizerTest, sizeTest_Falsee001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(36, sig_size1);
//}
//TEST_F(SignalRecognizerTest, sizeTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(15, sig_size2);
//}
//// �ж��Ƿ��Ǵ�ˣ�����Ǵ�ˣ��� is_big_endian = 0 ��С�� is_big_endian = 1����ʱ����ֵΪfalse
//TEST_F(SignalRecognizerTest, big_endianTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_FALSE(is_big_endian1);
//}
//TEST_F(SignalRecognizerTest, big_endianTest_False002) {
//	EXPECT_TRUE(str3_re);
//	EXPECT_FALSE(is_big_endian3);
//}
////�ж� is_unsigned ��ֵ��is_unsigned = - , ��ʱ����ֵΪfalse
//TEST_F(SignalRecognizerTest, value_typeTest_False001) {
//	EXPECT_TRUE(str3_re);
//	EXPECT_FALSE(is_unsigned3);
//}
//TEST_F(SignalRecognizerTest, value_typeTest_False002) {
//	EXPECT_TRUE(str4_re);
//	EXPECT_FALSE(is_unsigned4);
//}
////���Դ���� factor
//TEST_F(SignalRecognizerTest, factorTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(0.1, factor1);
//}
//TEST_F(SignalRecognizerTest, factorTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(0.1, factor2);
//}
////���Դ���� offset
//TEST_F(SignalRecognizerTest, offsetTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(1, offset1);
//}
//TEST_F(SignalRecognizerTest, offsetTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(2, offset2);
//}
////���Դ���� minimum
//TEST_F(SignalRecognizerTest, minimumTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(1, min1);
//}
//TEST_F(SignalRecognizerTest, minimumTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(2, min2);
//}
////���Դ���� maximum
//TEST_F(SignalRecognizerTest, maximumTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(10, max1);
//}
//TEST_F(SignalRecognizerTest, maximumTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(10, max2);
//}
////���Դ���� unit
//TEST_F(SignalRecognizerTest, unitTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STRNE("", unit1.c_str());
//}
//TEST_F(SignalRecognizerTest, unitTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STRNE("V", unit2.c_str());
//}
////���Դ���� receiver
//TEST_F(SignalRecognizerTest, receiverTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STRNE("TCU,ETACS", receiver1.c_str());
//}
//TEST_F(SignalRecognizerTest, receiverTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STRNE("ECU,BCM", receiver2.c_str());
//}
