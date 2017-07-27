//SignalRecognizerTest.cpp文件用于检验SignalRecognizer方法的其他功能的实现
//此文件定义了一个 SignalRecognizerTest测试类 ，旨在减少代码的重复度，并将TEST宏全部替换成TEST_F宏
//由于 SignalRecognizer方法的复杂性，这次没有像 MessageRecognizerTest.cpp 那样只是简单的设置两个字符串
//而是设置了四个符合特定检验要求的字符串，理由是：程序中当 is_big_endian=0 时，会更改 start_bit 的数值，不利于 start_bit 的断言检验
//因此在测试 start_bit 的数值的时候，都改成 is_big_endian=1 的字符串
#include"DBCAnalyzer.h"
#include<string>
#include <gtest/gtest.h> 

class SignalRecognizerTest : public testing::Test {
	
	DBCAnalyzer  dbc;
	Message msg;

public:
	std::string str1 = "SG_ SIG_12_03 : 55|16@1+ (0.001,0) [0|5] \"V\"  ECU,BCM";
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

//SignalRecognizer方法中，signal_name,start_bit,signal_size,is_big_endian,is_unsigned 的检验，其中，输入的字符串均符合正则表达式的
//由于每一个TEST_F内的第二个断言，均依赖于第一个断言，因此如果输入的字符串不符合正则表达式，则系统在访问Singal数组时会发生错误
//从而导致程序无法继续运行

////测试正确的 signal_name
//TEST_F(SignalRecognizerTest, nameTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STREQ("SIG_12_03", sig_name1.c_str());
//}
//TEST_F(SignalRecognizerTest, nameTest_True002) {	
//	EXPECT_TRUE(str2_re);
//	EXPECT_STREQ("TPS_FAIL01", sig_name2.c_str());
//}
////测试正确的 start_bit 
//TEST_F(SignalRecognizerTest, start_bitTest_True001) {	
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(55, start_bit1);
//}
//TEST_F(SignalRecognizerTest, start_bitTest_True002) {	
//	EXPECT_TRUE(str3_re);
//	EXPECT_EQ(45, start_bit2);
//}
////测试正确的 signal_size
//TEST_F(SignalRecognizerTest, sizeTest_True001) {	
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(16, sig_size1);
//}
//TEST_F(SignalRecognizerTest, sizeTest_True002) {	
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(1, sig_size2);
//}
////判断是否是大端，如果是大端，则 is_big_endian = 0 ，此时布尔值为true
//TEST_F(SignalRecognizerTest, big_endianTest_True001) {	
//	EXPECT_TRUE(str2_re);
//	EXPECT_TRUE(is_big_endian2);
//}
//TEST_F(SignalRecognizerTest, big_endianTest_True002) {
//	EXPECT_TRUE(str4_re);
//	EXPECT_TRUE(is_big_endian4);
//}
////判断 is_unsigned 的值，is_unsigned = + , 此时布尔值为true
//TEST_F(SignalRecognizerTest, value_typeTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_TRUE(is_unsigned1);
//}
//TEST_F(SignalRecognizerTest, value_typeTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_TRUE(is_unsigned2);
//}
////测试正确的 factor
//TEST_F(SignalRecognizerTest, sizeTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(16, sig_size1);
//}
//TEST_F(SignalRecognizerTest, sizeTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(1, sig_size2);
//}
//
////测试错误的 signal_name
//TEST_F(SignalRecognizerTest, nameTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STRNE("SIG_1203", sig_name1.c_str());
//}
//TEST_F(SignalRecognizerTest, nameTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STRNE("TPS_FAIL", sig_name2.c_str());
//}
////测试错误的 start_bit 
//TEST_F(SignalRecognizerTest, start_bitTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(5, start_bit1);
//}
//TEST_F(SignalRecognizerTest, start_bitTest_False002) {
//	EXPECT_TRUE(str3_re);
//	EXPECT_NE(10, start_bit2);
//}
////测试错误的 signal_size
//TEST_F(SignalRecognizerTest, sizeTest_Falsee001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(36, sig_size1);
//}
//TEST_F(SignalRecognizerTest, sizeTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(15, sig_size2);
//}
//// 判断是否是大端，如果是大端，则 is_big_endian = 0 ，小端 is_big_endian = 1，此时布尔值为false
//TEST_F(SignalRecognizerTest, big_endianTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_FALSE(is_big_endian1);
//}
//TEST_F(SignalRecognizerTest, big_endianTest_False002) {
//	EXPECT_TRUE(str3_re);
//	EXPECT_FALSE(is_big_endian3);
//}
////判断 is_unsigned 的值，is_unsigned = - , 此时布尔值为false
//TEST_F(SignalRecognizerTest, value_typeTest_False001) {
//	EXPECT_TRUE(str3_re);
//	EXPECT_FALSE(is_unsigned3);
//}
//TEST_F(SignalRecognizerTest, value_typeTest_False002) {
//	EXPECT_TRUE(str4_re);
//	EXPECT_FALSE(is_unsigned4);
//}
