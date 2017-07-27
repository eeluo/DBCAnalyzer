//MessageRecognizerTest.cpp文件用于检验MessageRecognizer方法的其他功能的实现
//此文件定义了一个 MessageRecognizerTest测试类 ，旨在减少代码的重复度，并将TEST宏全部替换成TEST_F宏
#include"DBCAnalyzer.h"
#include<string>
#include <gtest/gtest.h> 

class MessageRecognizerTest : public testing ::Test{

	DBCAnalyzer  dbc;
	DBCFileDescriptor descriptor;

public:
	std::string str1 = "BO_ 1585 MS_APPL1: 8 BCM";
	std::string str2 = "BO_ 1045 NGC_1: 7 ENG_PHEV";
	bool str1_re = dbc.MessageRecognizer(str1, descriptor);
	bool str2_re = dbc.MessageRecognizer(str2, descriptor);
	uint32_t    msg_id1= descriptor.Messages()[0].ID();
	uint32_t    msg_id2 = descriptor.Messages()[1].ID();
	std::string   msg_name1= descriptor.Messages()[0].Name();
	std::string   msg_name2 = descriptor.Messages()[1].Name();
	uint8_t    msg_size1= descriptor.Messages()[0].GetSize();
	uint8_t    msg_size2 = descriptor.Messages()[1].GetSize();
	std::string trans1 = descriptor.Messages()[0].Transmitter();
	std::string trans2 = descriptor.Messages()[1].Transmitter();
	virtual void SetUp() {}
	virtual void TearDown() {}
};

//MessageRecognizer方法中，message_id,message_name,message_size的检验，其中，输入的字符串均符合正则表达式的
//由于每一个TEST_F内的第二个断言，均依赖于第一个断言，因此如果输入的字符串不符合正则表达式，则系统在访问Messages数组时会发生错误
//从而导致程序无法继续运行

////以下分别使用两个字符串，测试正确的 message_id
//TEST_F(MessageRecognizerTest, id_True001) {	
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(1585, msg_id1);
//}
//TEST_F(MessageRecognizerTest, id_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(1045, msg_id2);
//}
////测试正确的 message_name
//TEST_F(MessageRecognizerTest, name_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STREQ("MS_APPL1", msg_name1.c_str());
//}
//TEST_F(MessageRecognizerTest, name_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STREQ("NGC_1", msg_name2.c_str());
//}
////测试正确的 message_size
//TEST_F(MessageRecognizerTest, size_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(8, msg_size1);
//}
//TEST_F(MessageRecognizerTest, size_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(7, msg_size2);
//}
//测试正确的 transmitter
TEST_F(MessageRecognizerTest, transmitter_True001) {
	EXPECT_TRUE(str1_re);
	EXPECT_STREQ("BCM", trans1.c_str());
}
TEST_F(MessageRecognizerTest, transmitter_True002) {
	EXPECT_TRUE(str2_re);
	EXPECT_STREQ("ENG_PHEV", trans2.c_str());
}

////测试错误的 message_id
//TEST_F(MessageRecognizerTest, id_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(158, msg_id1);
//}
//TEST_F(MessageRecognizerTest, id_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(158, msg_id2);
//}
////测试错误的 message_name
//TEST_F(MessageRecognizerTest, name_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STRNE("MSAPPL1", msg_name1.c_str());
//}
//TEST_F(MessageRecognizerTest, name_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STRNE("NGC_159", msg_name2.c_str());
//}
////测试错误的 message_size
//TEST_F(MessageRecognizerTest, size_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(10, msg_size1);
//}
//TEST_F(MessageRecognizerTest, size_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(10, msg_size2);
//}
//测试错误的 transmitter
TEST_F(MessageRecognizerTest, transmitter_False001) {
	EXPECT_TRUE(str1_re);
	EXPECT_STRNE("ENG_PHEV", trans1.c_str());
}
TEST_F(MessageRecognizerTest, transmitter_False002) {
	EXPECT_TRUE(str2_re);
	EXPECT_STRNE("BCM", trans2.c_str());
}