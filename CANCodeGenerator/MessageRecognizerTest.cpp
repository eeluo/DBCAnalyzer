//MessageRecognizerTest.cpp�ļ����ڼ���MessageRecognizer�������������ܵ�ʵ��
//���ļ�������һ�� MessageRecognizerTest������ ��ּ�ڼ��ٴ�����ظ��ȣ�����TEST��ȫ���滻��TEST_F��
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

//MessageRecognizer�����У�message_id,message_name,message_size�ļ��飬���У�������ַ���������������ʽ��
//����ÿһ��TEST_F�ڵĵڶ������ԣ��������ڵ�һ�����ԣ�������������ַ���������������ʽ����ϵͳ�ڷ���Messages����ʱ�ᷢ������
//�Ӷ����³����޷���������

////���·ֱ�ʹ�������ַ�����������ȷ�� message_id
//TEST_F(MessageRecognizerTest, id_True001) {	
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(1585, msg_id1);
//}
//TEST_F(MessageRecognizerTest, id_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(1045, msg_id2);
//}
////������ȷ�� message_name
//TEST_F(MessageRecognizerTest, name_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STREQ("MS_APPL1", msg_name1.c_str());
//}
//TEST_F(MessageRecognizerTest, name_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STREQ("NGC_1", msg_name2.c_str());
//}
////������ȷ�� message_size
//TEST_F(MessageRecognizerTest, size_True001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_EQ(8, msg_size1);
//}
//TEST_F(MessageRecognizerTest, size_True002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_EQ(7, msg_size2);
//}
//������ȷ�� transmitter
TEST_F(MessageRecognizerTest, transmitter_True001) {
	EXPECT_TRUE(str1_re);
	EXPECT_STREQ("BCM", trans1.c_str());
}
TEST_F(MessageRecognizerTest, transmitter_True002) {
	EXPECT_TRUE(str2_re);
	EXPECT_STREQ("ENG_PHEV", trans2.c_str());
}

////���Դ���� message_id
//TEST_F(MessageRecognizerTest, id_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(158, msg_id1);
//}
//TEST_F(MessageRecognizerTest, id_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(158, msg_id2);
//}
////���Դ���� message_name
//TEST_F(MessageRecognizerTest, name_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_STRNE("MSAPPL1", msg_name1.c_str());
//}
//TEST_F(MessageRecognizerTest, name_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_STRNE("NGC_159", msg_name2.c_str());
//}
////���Դ���� message_size
//TEST_F(MessageRecognizerTest, size_False001) {
//	EXPECT_TRUE(str1_re);
//	EXPECT_NE(10, msg_size1);
//}
//TEST_F(MessageRecognizerTest, size_False002) {
//	EXPECT_TRUE(str2_re);
//	EXPECT_NE(10, msg_size2);
//}
//���Դ���� transmitter
TEST_F(MessageRecognizerTest, transmitter_False001) {
	EXPECT_TRUE(str1_re);
	EXPECT_STRNE("ENG_PHEV", trans1.c_str());
}
TEST_F(MessageRecognizerTest, transmitter_False002) {
	EXPECT_TRUE(str2_re);
	EXPECT_STRNE("BCM", trans2.c_str());
}