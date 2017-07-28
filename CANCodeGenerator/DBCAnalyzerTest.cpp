//DBCAnalyzerTest.cpp��Ҫ���ڼ���������ַ����Ƿ����������ʽ
//�Լ���SignalRecognizer�����У������ַ����� start_bit ��ֵ��Χ�����ж�
//������MessageRecognizer������SignalRecognizer�������������ܽ��м���
//�����������������ܵļ��飬�ֱ�����������cpp�ļ�����
//#include "DBCAnalyzer.h"
//#include <gtest/gtest.h> 
//#include <string>
//using namespace std;
//
////�����Ƕ�MessageRecognizer�����������ַ���������ļ���
//TEST(DBCAnalyzerTest, MessageRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	//�������ļ�test.dbc�ļ���message�Ĳ��ԣ����Խ��Ӧ�þ�ͨ��
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 ENG_PHEV", descriptor));
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 Vector__XXX", descriptor));//transmitter����Ĭ��ΪVector__XXX
//	//������message���ֲ�����dbc��ʽҪ��ģ����Խ��ͬ��Ӧ�þ�ͨ��
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 23MS_APPL1: 8 ENG_PHEV", descriptor));//message_name���������ֿ�ͷ
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 ", descriptor));//transmitter����Ϊ��
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1:  ENG_PHEV", descriptor));//û��message_size
//}
//
////�����Ƕ�SignalRecognizer�����������ַ���������ļ��飬�Լ��� start_bit ����ֵ��Χ�����ж�
//TEST(DBCAnalyzerTest, SignalRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	Message msg;
//	//�������ļ�test.dbc�ļ���signal�Ĳ��ԣ����Խ��Ӧ�þ�ͨ��
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ M_STA : 4|13@0+ (0.25,-500) [-500|1547.5] \"Nm\"  TCU,PHEV,ABS_ASC", msg));
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 55|1@1+ (1,-0.00001) [-0.40|-0.0001] \"\"  TCU,ETACS", msg));
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\"  Vector__XXX", msg));//receiver����Ĭ��ΪVector__XXX
//	//������signal���ֲ�����dbc��ʽҪ��ģ����Խ��ͬ��Ӧ�þ�ͨ��
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (0,0) [0|0] \"\"  TCU,ETACS", msg));//factor=0
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 55|1@1+ (0.000,0) [0|0] \"\"  TCU,ETACS", msg));//����factor=0.000
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\" ", msg));//receiver����Ϊ��
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ 22TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\"  TCU,ETACS", msg));//signal_name���������ֿ�ͷ
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+  [0|0] \"\"  TCU,ETACS", msg));//(factor,offset)����Ϊ��
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0)  \"\"  TCU,ETACS", msg));//[minimum,maximum]����Ϊ��
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@2+ (1,0) [0|0] \"\"  TCU,ETACS", msg));//byte_order=2,ֻ����0��1
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0]  TCU,ETACS", msg));//unit����Ϊ��
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] 123  TCU,ETACS", msg));//unit���ֲ���char_string����
//
//	//��ȷ�����Աȼ���,SignalRecognizer��  start_bit��ΧΪ 0~8*message_size-1 , ���� message_size ��MessageRecognizer���
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1620 CAN_Message_1: 8 BCM", descriptor));
//	auto & _msg1 = descriptor.Messages().back();
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ SIG_12_05 : 63|16@0+ (0.001,0) [0|5] \"V\"  ECU,BCM", _msg1));//��ȷ��63=8*8-1
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ SIG_12_05 : 0|16@0+ (0.001,0) [0|5] \"V\"  ECU,BCM", _msg1));//��ȷ
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ SIG_12_05 : 64|16@0+ (0.001,0) [0|5] \"V\"  ECU,BCM", _msg1));//����,64=8*8
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ SIG_05 : -7|16@0+ (0.001,0) [0|5] \"V\"  ECU,BCM", _msg1));//����-7<0
//
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1045 NGC_1: 7 ENG_PHEV", descriptor));
//	auto & _msg2 = descriptor.Messages().back();
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ BARO : 55|8@1+ (0.4921875,0) [0|125] \"kPa\"  TCU,ETACS,PHEV", _msg2));//��ȷ.55=8*7-1
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\"  TCU,ETACS", _msg2));//��ȷ
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ BARO : 56|8@1+ (0.4921875,0) [0|125] \"kPa\"  TCU,ETACS,PHEV", _msg2));//����,56=8*7
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : -2|1@1+ (1,0) [0|0] \"\"  TCU,ETACS", _msg2));//����,-2<0
//}
