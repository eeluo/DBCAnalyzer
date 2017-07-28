//DBCAnalyzerTest.cpp主要用于检验输入的字符串是否符合正则表达式
//以及对SignalRecognizer方法中，输入字符串的 start_bit 数值范围进行判断
//并不对MessageRecognizer方法和SignalRecognizer方法的其他功能进行检验
//两个方法的其他功能的检验，分别在另外两个cpp文件进行
//#include "DBCAnalyzer.h"
//#include <gtest/gtest.h> 
//#include <string>
//using namespace std;
//
////以下是对MessageRecognizer方法中输入字符串与正则的检验
//TEST(DBCAnalyzerTest, MessageRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	//以下是文件test.dbc文件中message的测试，测试结果应该均通过
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 ENG_PHEV", descriptor));
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 Vector__XXX", descriptor));//transmitter部分默认为Vector__XXX
//	//以下是message部分不符合dbc格式要求的，测试结果同样应该均通过
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 23MS_APPL1: 8 ENG_PHEV", descriptor));//message_name不能以数字开头
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 ", descriptor));//transmitter部分为空
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1:  ENG_PHEV", descriptor));//没有message_size
//}
//
////以下是对SignalRecognizer方法中输入字符串与正则的检验，以及对 start_bit 的数值范围进行判断
//TEST(DBCAnalyzerTest, SignalRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	Message msg;
//	//以下是文件test.dbc文件中signal的测试，测试结果应该均通过
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ M_STA : 4|13@0+ (0.25,-500) [-500|1547.5] \"Nm\"  TCU,PHEV,ABS_ASC", msg));
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 55|1@1+ (1,-0.00001) [-0.40|-0.0001] \"\"  TCU,ETACS", msg));
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\"  Vector__XXX", msg));//receiver部分默认为Vector__XXX
//	//以下是signal部分不符合dbc格式要求的，测试结果同样应该均通过
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (0,0) [0|0] \"\"  TCU,ETACS", msg));//factor=0
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 55|1@1+ (0.000,0) [0|0] \"\"  TCU,ETACS", msg));//错误，factor=0.000
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\" ", msg));//receiver部分为空
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ 22TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\"  TCU,ETACS", msg));//signal_name不能以数字开头
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+  [0|0] \"\"  TCU,ETACS", msg));//(factor,offset)部分为空
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0)  \"\"  TCU,ETACS", msg));//[minimum,maximum]部分为空
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@2+ (1,0) [0|0] \"\"  TCU,ETACS", msg));//byte_order=2,只能是0或1
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0]  TCU,ETACS", msg));//unit部分为空
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] 123  TCU,ETACS", msg));//unit部分不是char_string类型
//
//	//正确与错误对比检验,SignalRecognizer的  start_bit范围为 0~8*message_size-1 , 其中 message_size 由MessageRecognizer获得
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1620 CAN_Message_1: 8 BCM", descriptor));
//	auto & _msg1 = descriptor.Messages().back();
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ SIG_12_05 : 63|16@0+ (0.001,0) [0|5] \"V\"  ECU,BCM", _msg1));//正确，63=8*8-1
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ SIG_12_05 : 0|16@0+ (0.001,0) [0|5] \"V\"  ECU,BCM", _msg1));//正确
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ SIG_12_05 : 64|16@0+ (0.001,0) [0|5] \"V\"  ECU,BCM", _msg1));//错误,64=8*8
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ SIG_05 : -7|16@0+ (0.001,0) [0|5] \"V\"  ECU,BCM", _msg1));//错误，-7<0
//
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1045 NGC_1: 7 ENG_PHEV", descriptor));
//	auto & _msg2 = descriptor.Messages().back();
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ BARO : 55|8@1+ (0.4921875,0) [0|125] \"kPa\"  TCU,ETACS,PHEV", _msg2));//正确.55=8*7-1
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\"  TCU,ETACS", _msg2));//正确
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ BARO : 56|8@1+ (0.4921875,0) [0|125] \"kPa\"  TCU,ETACS,PHEV", _msg2));//错误,56=8*7
//	EXPECT_FALSE(dbc.SignalRecognizer("SG_ TPS_FAIL : -2|1@1+ (1,0) [0|0] \"\"  TCU,ETACS", _msg2));//错误,-2<0
//}
