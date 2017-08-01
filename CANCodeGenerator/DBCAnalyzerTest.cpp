/**@file
*@brief ��DBCAnalyzer.cpp�ļ��м�����Ҫ������Ԫ����
*@author luoaling
*
*��Ҫ����Լ���*Recognizer�����ĵ�Ԫ���ԣ��Լ���������ʽ
*�ı�д��ȷ�������ݵ�Ԫ���Եĳɹ���������ʽ�������ƣ�
*��cpp�ļ�����ֻ���鼸�������ķ���ֵ�����Ժ����ڵľ�������
*���в��ԣ�����ר�ŵ�cpp�ļ���������
*
*/
#include "DBCAnalyzer.h"
#include <gtest/gtest.h> 
#include <string>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief ���µ�TEST���Ƕ�MessageRecognizer�����е��ַ���������ļ���
*@author luoaling
*
*������ȷ�ʹ�����ַ�����Ȼ��ֱ�����EXPECT_TRUE��EXPECT_FALSE���ԣ�
*��TEST���ڵ����ж��Զ�ͨ��ʱ��˵��������ʽͨ����֤
*
*/
//TEST(MessageAnalyzerTest, MessageRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	//������message��ȷ���ַ��������Խ����ͨ��
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 ENG_PHEV", descriptor));
//	EXPECT_TRUE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 Vector__XXX", descriptor));//transmitter����Ĭ��ΪVector__XXX
//	//������message������ַ��������Խ����ͨ��
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 23MS_APPL1: 8 ENG_PHEV", descriptor));//message_name���������ֿ�ͷ
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1: 8 ", descriptor));//transmitter����Ϊ��
//	EXPECT_FALSE(dbc.MessageRecognizer("BO_ 1585 MS_APPL1:  ENG_PHEV", descriptor));//û��message_size
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief ���µ�TEST���Ƕ�SignalRecognizer�����е��ַ���������ļ��飬�Լ��� start_bit ����ֵ��Χ�����ж�
*@author luoaling
*
*������ȷ�ʹ�����ַ�����Ȼ��ֱ�����EXPECT_TRUE��EXPECT_FALSE���ԣ�
*��TEST���ڵ����ж��Զ�ͨ��ʱ��˵��������ʽͨ����֤
*
*@note start_bit��ΧΪ 0~8*message_size-1 , ���� message_size ��MessageRecognizer���
*��˼���start_bitʱ����Ҫ������MessageRecognizer�������message_size
*/
//TEST(SignalAnalyzerTest, SignalRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	Message msg;
//	//������signal��ȷ���ַ��������Խ����ͨ��
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ M_STA : 4|13@0+ (0.25,-500) [-500|1547.5] \"Nm\"  TCU,PHEV,ABS_ASC", msg));
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 55|1@1+ (1,-0.00001) [-0.40|-0.0001] \"\"  TCU,ETACS", msg));
//	EXPECT_TRUE(dbc.SignalRecognizer("SG_ TPS_FAIL : 0|1@1+ (1,0) [0|0] \"\"  Vector__XXX", msg));//receiver����Ĭ��ΪVector__XXX
//	//������signal������ַ��������Խ����ͨ��
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
//	//��ȷ�����Աȼ���,SignalRecognizer�� start_bit��ΧΪ 0~8*message_size-1 , ���� message_size ��MessageRecognizer���
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief ���µ�TEST���Ƕ�AttributeRecognizer�����е��ַ���������ļ���
*@author luoaling
*
*������ȷ�ʹ�����ַ�����Ȼ��ֱ�����EXPECT_TRUE��EXPECT_FALSE���ԣ�
*��TEST���ڵ����ж��Զ�ͨ��ʱ��˵��������ʽͨ����֤
*
*@note attribute definitions����attribute_definition��attribute_default������
*�������в��ģ�Ӧ�ֿ����в���
*/
//TEST(AttributeAnalyzerTest, AttributeRecognizerTest) {
//	DBCAnalyzer  dbc;
//	DBCFileDescriptor descriptor;
//	//����attribut_definition��ȷ���ַ��������Խ����ͨ��
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ SG_ \"GenSigTimeout_CMU_05\" INT 0 65535;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0 255;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  \"SamplePointMax\" FLOAT 0 100;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ BU_ \"RID\" STRING ;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ BO_ \"TpTxIndex\" INT 0 99;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ EV_ \"FlexKomIsMotorola\" ENUM \"nein\",\"ja\";", descriptor));
//	//����attribut_default��ȷ���ַ��������Խ����ͨ��
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_ \"T78R - GTD\" \"\";", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_ \"CRmu - vty\" 0;", descriptor));
//	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_  \"fty - HY\" 50000.0;", descriptor));
//	//����attribut_definition������ַ��������Խ����ͨ��
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_ \"GenSigTimeout_CMU_05\" INT 0 65535;", descriptor));//object_typeΪ��
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_ BU_ \"RID\" STRING;", descriptor));//STRING����Ӧ��������һ���ո�
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_ BO_ \"TpTxIndex\" INT 0,99;", descriptor));//0 99 ֮��Ӧ�Կո�ָ�
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0,255;", descriptor));//ͬ��
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_ EV_ \"FlexKomIsMotorola\" ENUM \"nein\" \"ja\";", descriptor));//ENUM������ַ���Ӧ�Զ��ŷָ�
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  NWID HEX 0 255;", descriptor));//attribute_name����Ӧ��˫����
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0,255", descriptor));//�ַ���Ӧ�Էֺ�;��β
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"8NWID\" HEX 0 255", descriptor));//attribute_name���������ֿ�ͷ
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0;", descriptor));//��ֵ��ΧǷȱ
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" 0 255;", descriptor));//HEXǷȱ
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_  HEX 0 255;", descriptor));//attribute_nameǷȱ
//	//����attribut_default������ַ��������Խ����ͨ��
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_DEF_ \"CRmu - vty\";", descriptor));//attri_valueΪ��
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_DEF_ 50000.0;", descriptor));//attribute_nameΪ��
//	EXPECT_FALSE(dbc.AttributeRecognizer("BA_DEF_DEF_ \"CRmu - vty\" 0 4;", descriptor));//attri_valueֻ����һ����ֵ
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
*@brief ���µ�TEST���Ƕ�NodeRecognizer�����е��ַ���������ļ���
*@author luoaling
*
*������ȷ�ʹ�����ַ�����Ȼ��ֱ�����EXPECT_TRUE��EXPECT_FALSE���ԣ�
*��TEST���ڵ����ж��Զ�ͨ��ʱ��˵��������ʽͨ����֤
*
*/
TEST(NodeAnalyzerTest, NodeRecognizerTest) {
	DBCAnalyzer  dbc;
	DBCFileDescriptor descriptor;
	//����node��ȷ���ַ��������Խ����ͨ��
	EXPECT_TRUE(dbc.NodeRecognizer("BU_: TCU TESTER SRS SAS PHEV OCM LDW_RLSM ENG_PHEV ACCS_FCM ABS_ASC ", descriptor));
	EXPECT_TRUE(dbc.NodeRecognizer("BU_: TESTER TCU BMU2 CSM CMU_TEST CMU_12 CMU_11 CMU_10 CMU_09", descriptor));
	//����node������ַ��������Խ����ͨ��
	EXPECT_FALSE(dbc.NodeRecognizer("BU_ TESTER TCU BMU2 CSM CMU_TEST CMU_12 CMU_11 CMU_10 CMU_09", descriptor));//BU_����Ӧ��һ��ð��
	EXPECT_FALSE(dbc.NodeRecognizer("BU_: 9TESTER 8TCU BMU2 CSM CMU_TEST CMU_12 CMU_11", descriptor));//node_name���������ֿ�ͷ
	EXPECT_FALSE(dbc.NodeRecognizer("BU_: TESTER,TCU,BMU2 CSM CMU_TEST CMU_12 CMU_11 CMU_10 CMU_09", descriptor));//node_name֮��Ӧ�Կո�ָ�
}