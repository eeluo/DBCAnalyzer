/**@file
*@brief 对DBCAnalyzer.cpp文件中几个主要函数单元测试
*@author luoaling
*
*主要是针对几个*Recognizer方法的单元测试，以检验正则表达式
*的编写正确，并根据单元测试的成果对正则表达式进行完善，
*本cpp文件最终只检验几个函数的返回值，不对函数内的具体内容
*进行测试，会有专门的cpp文件单独测试
*
*/
#include "DBCAnalyzer.h"
#include <gtest/gtest.h> 
#include <string>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief 以下的TEST宏是对MessageRecognizer方法中的字符串与正则的检验
*@author luoaling
*
*构造正确和错误的字符串，然后分别利用EXPECT_TRUE和EXPECT_FALSE断言，
*当TEST宏内的所有断言都通过时，说明正则表达式通过验证
*
*/
//TEST(MessageAnalyzerTest, MessageRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	//以下是message正确的字符串，测试结果均通过
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 ENG_PHEV", descriptor));
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 Vector__XXX", descriptor));//transmitter部分默认为Vector__XXX
//	//以下是message错误的字符串，测试结果均通过
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 23MS_APPL1: 8 ENG_PHEV", descriptor));//message_name不能以数字开头
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 ", descriptor));//transmitter部分为空
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1:  ENG_PHEV", descriptor));//没有message_size
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief 以下的TEST宏是对SignalRecognizer方法中的字符串与正则的检验，以及对 start_bit 的数值范围进行判断
*@author luoaling
*
*构造正确和错误的字符串，然后分别利用EXPECT_TRUE和EXPECT_FALSE断言，
*当TEST宏内的所有断言都通过时，说明正则表达式通过验证
*
*@note start_bit范围为 0~8*message_size-1 , 其中 message_size 由MessageRecognizer获得
*因此检验start_bit时，需要先利用MessageRecognizer函数获得message_size
*/
//TEST(SignalAnalyzerTest, SignalRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	Message msg;
//	//以下是signal正确的字符串，测试结果均通过
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ M_STA : 4|13@0+ (0.25,-500) [-500|1547.5] \"Nm\"  TCU,PHEV,ABS_ASC", msg));
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 55|1@1+ (1,-0.00001) [-0.40|-0.0001] \"\"  TCU,ETACS", msg));
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\"  Vector__XXX", msg));//receiver部分默认为Vector__XXX
//	//以下是signal错误的字符串，测试结果均通过
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
//	//正确与错误对比检验,SignalRecognizer的 start_bit范围为 0~8*message_size-1 , 其中 message_size 由MessageRecognizer获得
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief 以下的TEST宏是对AttributeRecognizer方法中的字符串与正则的检验
*@author luoaling
*
*构造正确和错误的字符串，然后分别利用EXPECT_TRUE和EXPECT_FALSE断言，
*当TEST宏内的所有断言都通过时，说明正则表达式通过验证
*
*@note attribute definitions包括attribute_definition和attribute_default两部分
*两者是有差别的，应分开进行测试
*/
//TEST(AttributeAnalyzerTest, AttributeRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	//以下attribut_definition正确的字符串，测试结果均通过
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ SG_ \"GenSigTimeout_CMU_05\" INT 0 65535;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0 255;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  \"SamplePointMax\" FLOAT 0 100;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ BU_ \"RID\" STRING ;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ BO_ \"TpTxIndex\" INT 0 99;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ EV_ \"FlexKomIsMotorola\" ENUM \"nein\",\"ja\";", descriptor));
//	//以下attribut_default正确的字符串，测试结果均通过
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_ \"T78R - GTD\" \"\";", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_ \"CRmu - vty\" 0;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_  \"fty - HY\" 50000.0;", descriptor));
//	//以下attribut_definition错误的字符串，测试结果均通过
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_ \"GenSigTimeout_CMU_05\" INT 0 65535;", descriptor));//object_type为空
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_ BU_ \"RID\" STRING;", descriptor));//STRING后面应该有至少一个空格
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_ BO_ \"TpTxIndex\" INT 0,99;", descriptor));//0 99 之间应以空格分隔
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0,255;", descriptor));//同上
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_ EV_ \"FlexKomIsMotorola\" ENUM \"nein\" \"ja\";", descriptor));//ENUM后面的字符串应以逗号分隔
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  NWID HEX 0 255;", descriptor));//attribute_name两边应有双引号
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0,255", descriptor));//字符串应以分号;结尾
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"8NWID\" HEX 0 255", descriptor));//attribute_name不能以数字开头
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0;", descriptor));//数值范围欠缺
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" 0 255;", descriptor));//HEX欠缺
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  HEX 0 255;", descriptor));//attribute_name欠缺
//	//以下attribut_default错误的字符串，测试结果均通过
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_DEF_ \"CRmu - vty\";", descriptor));//attri_value为空
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_DEF_ 50000.0;", descriptor));//attribute_name为空
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_DEF_ \"CRmu - vty\" 0 4;", descriptor));//attri_value只能有一个数值
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief 以下的TEST宏是对NodeRecognizer方法中的字符串与正则的检验
*@author luoaling
*
*构造正确和错误的字符串，然后分别利用EXPECT_TRUE和EXPECT_FALSE断言，
*当TEST宏内的所有断言都通过时，说明正则表达式通过验证
*
*/
TEST(NodeAnalyzerTest, NodeRecognizerTest) {
	DBCAnalyzer  dbc;
	DBCFileDescriptor descriptor;
	//以下node正确的字符串，测试结果均通过
	EXPECT_TRUE(dbc.NodeRecognizer("BU_: TCU TESTER SRS SAS PHEV OCM LDW_RLSM ENG_PHEV ACCS_FCM ABS_ASC ", descriptor));
	EXPECT_TRUE(dbc.NodeRecognizer("BU_: TESTER TCU BMU2 CSM CMU_TEST CMU_12 CMU_11 CMU_10 CMU_09", descriptor));
	//以下node错误的字符串，测试结果均通过
	EXPECT_FALSE(dbc.NodeRecognizer("BU_ TESTER TCU BMU2 CSM CMU_TEST CMU_12 CMU_11 CMU_10 CMU_09", descriptor));//BU_后面应接一个冒号
	EXPECT_FALSE(dbc.NodeRecognizer("BU_: 9TESTER 8TCU BMU2 CSM CMU_TEST CMU_12 CMU_11", descriptor));//node_name不能以数字开头
	EXPECT_FALSE(dbc.NodeRecognizer("BU_: TESTER,TCU,BMU2 CSM CMU_TEST CMU_12 CMU_11 CMU_10 CMU_09", descriptor));//node_name之间应以空格分隔
}