#include "AttributeAnalyzer.h"
#include "DBCAnalyzer.h"
#include <gtest/gtest.h> 
#include <string>
using namespace std;

TEST(AttributeAnalyzerTest, AttributeRecognizerTest) {
	DBCAnalyzer  dbc;
	DBCFileDescriptor descriptor;
	//以下是文件test.dbc文件中message的测试，测试结果应该均通过
	/*EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_ SG_ \"GenSigTimeout_CMU_05\" INT 0 65535;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  \"NWID\" HEX 0 255;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  \"SamplePointMax\" FLOAT 0 100;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  SG_ \"RID\" STRING;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  BO_ \"TpTxIndex\" INT 0 99;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_  SG_ \"FlexKomIsMotorola\" ENUM \"nein\",\"ja\";", descriptor));

	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_  \"T78R - GTD\" \"\";", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_  \"CRmu - vty\" 0;", descriptor));
	EXPECT_TRUE(dbc.AttributeRecognizer("BA_DEF_DEF_  \"fty - HY\" 50000.0;", descriptor));*/

	

	/*EXPECT_FALSE(dbc.AttributeRecognizer("BO_ 1585 23MS_APPL1: 8 ENG_PHEV", descriptor));
	EXPECT_FALSE(dbc.AttributeRecognizer("BO_ 1585 MS_APPL1: 8 ", descriptor));
	EXPECT_FALSE(dbc.AttributeRecognizer("BO_ 1585 MS_APPL1:  ENG_PHEV", descriptor));*/
	
	
	EXPECT_TRUE(dbc.NodeRecognizer("BU_: TESTER TCU BMU2 CSM CMU_TEST CMU_12 CMU_11 CMU_10 CMU_09 CMU_08 CMU_07 CMU_06 CMU_05", descriptor));
}