#include "AttributeAnalyzer.h"
#include "DBCAnalyzer.h"
#include <gtest/gtest.h> 
#include <string>
using namespace std;

TEST(AttributeAnalyzerTest, AttributeRecognizerTest) {
	DBCAnalyzer  dbc;
	DBCFileDescriptor descriptor;
	//�������ļ�test.dbc�ļ���message�Ĳ��ԣ����Խ��Ӧ�þ�ͨ��
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ SG_ \"GenSigTimeout_CMU_05\" INT 0 65535;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0 255;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  \"SamplePointMax\" FLOAT 0 100;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  SG_ \"RID\" STRING;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  BO_ \"TpTxIndex\" INT 0 99;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  SG_ \"FlexKomIsMotorola\" ENUM \"nein\",\"ja\";", descriptor));

	/*EXPECT_FALSE(dbc.AttributeRecognizer("BO_ 1585 23MS_APPL1: 8 ENG_PHEV", descriptor));
	EXPECT_FALSE(dbc.AttributeRecognizer("BO_ 1585 MS_APPL1: 8 ", descriptor));
	EXPECT_FALSE(dbc.AttributeRecognizer("BO_ 1585 MS_APPL1:  ENG_PHEV", descriptor));*/
}