/**@file
*@brief 定义了一个SignalRecognizerTest测试类
*@author luoaling
*
*定义了 SignalRecognizerTest测试类 ，旨在减少
*代码的重复度，并将TEST宏全部替换成TEST_F宏
*
*/
#include"DBCAnalyzer.h"
#include<string>
#include <gtest/gtest.h> 

/**
*@class
*@biref SignalRecognizerTest类测试SignalRecognizer方法的其他功能的实现
*
*针对SignalRecognizer方法中,signal_name,satrt_bit,signal_size,byte_order,
*value_type,factor,offset,minimum,maximum,unit和receiver的检验.
*由于 SignalRecognizer方法的复杂性，这次没有像MessageRecognizerTest那样只是简单的设置两个字符串，
*而是设置了四个符合特定检验要求的字符串.理由是：程序中当 is_big_endian=0 时，
*会更改 start_bit 的数值，不利于 start_bit 的断言检验,因此在测试 start_bit 的数值的时候，
*都改成 is_big_endian=1 的字符串
*
*@note 由于每一个TEST_F内的第二个断言，均依赖于第一个断言，
*因此输入的字符串均要符合正则表达式，否则程序崩溃导致无法继续运行
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
*@brief 以下的TEST_F宏是对signal中特定部分的检验
*@author luoaling
*
*数值检验采用EXPECT_EQ和EXPECT_NE断言，
*字符串检验采用EXPECT_STREQ和EXPECT_STRNE断言
*布尔值检验采用EXPECT_TRUE和EXPECT_FALSE断言
*
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//测试正确的 signal_name
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
//TEST_F(SignalRecognizerTest, factorTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(2, factor1);
//}
//TEST_F(SignalRecognizerTest, factorTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(1, factor2);
//}
////测试正确的 offset
//TEST_F(SignalRecognizerTest, offsetTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(0, offset1);
//}
//TEST_F(SignalRecognizerTest, offsetTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(0, offset2);
//}
////测试正确的 minimum
//TEST_F(SignalRecognizerTest, minimumTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(0, min1);
//}
//TEST_F(SignalRecognizerTest, minimumTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(0, min2);
//}
////测试正确的 maximum
//TEST_F(SignalRecognizerTest, maximumTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(5, max1);
//}
//TEST_F(SignalRecognizerTest, maximumTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(0, max2);
//}
////测试正确的 unit
//TEST_F(SignalRecognizerTest, unitTest_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STREQ("V", unit1.c_str());
//}
//TEST_F(SignalRecognizerTest, unitTest_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STREQ("", unit2.c_str());
//}
////测试正确的 receiver
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
////测试错误的 factor
//TEST_F(SignalRecognizerTest, factorTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(0.1, factor1);
//}
//TEST_F(SignalRecognizerTest, factorTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(0.1, factor2);
//}
////测试错误的 offset
//TEST_F(SignalRecognizerTest, offsetTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(1, offset1);
//}
//TEST_F(SignalRecognizerTest, offsetTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(2, offset2);
//}
////测试错误的 minimum
//TEST_F(SignalRecognizerTest, minimumTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(1, min1);
//}
//TEST_F(SignalRecognizerTest, minimumTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(2, min2);
//}
////测试错误的 maximum
//TEST_F(SignalRecognizerTest, maximumTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(10, max1);
//}
//TEST_F(SignalRecognizerTest, maximumTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(10, max2);
//}
////测试错误的 unit
//TEST_F(SignalRecognizerTest, unitTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STRNE("", unit1.c_str());
//}
//TEST_F(SignalRecognizerTest, unitTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STRNE("V", unit2.c_str());
//}
////测试错误的 receiver
//TEST_F(SignalRecognizerTest, receiverTest_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STRNE("TCU,ETACS", receiver1.c_str());
//}
//TEST_F(SignalRecognizerTest, receiverTest_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STRNE("ECU,BCM", receiver2.c_str());
//}
