/******************************************************************************
 * @project  wogtest
 * @file     wogtest.h
 * @version  V2.0f
 * @date     2nd of Feb 2024
 * Author    Remo Markgraf
 * Copyright (C) 2025 MicroConsult Academy GmbH. All rights reserved.
 * Originally published (C) 2023 MicroConsult GmbH. All rights reserved.
 *****************************************************************************/
#ifndef WOGTEST_H_
#define WOGTEST_H_
//---------------------------------------
#define WOGTEST_VERSION V2.0e
//---------------------------------------
//---------------------------------------
//define max number of characters of error messages per ASSERT/EXPECT
//no overflow check is performed
//one byte on stack required per character
//---------------------------------------
#define WOGTEST_MESSAGEBUFFERSIZE 256

//---------------------------------------
//configure if float/double should be testable,
//if yes, remove comment from define WOGTEST_FLOAT
//---------------------------------------
#define WOGTEST_FLOAT

//---------------------------------------
//Apply printf for output of messages
//to reduce size of image
//otherwise putchar is used
//if yes, remove comment from define USE_PRINTF
//---------------------------------------
//#define USE_PRINTF

//---------------------------------------
//for porting purposes to compiler/linker tool chains
//the WEAKFUNC macro may be adopted accordingly
//---------------------------------------
#define WEAKFUNC __attribute__((weak))

//---------------------------------------
//no changes required below here
//---------------------------------------
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#ifdef USE_PRINTF
#define PRINTSTR(str) printf("%s",str)
#else
#define PRINTSTR(str) for(char*ptr=(char*)str;*ptr!=0;ptr++)putchar(*ptr)
#endif //USE_PRINTF

#define STRINGIZE(val) STRINGIZEn(val)
#define STRINGIZEn(str) #str

typedef struct
{
    uint32_t total_tcs;
    uint32_t total_tests;
    uint32_t total_succ;
    uint32_t tc_tests;
    uint32_t tc_succ;
    char test_message_buffer[WOGTEST_MESSAGEBUFFERSIZE];
    bool tn_passed;
    bool tn_fatal;
} __wogtest_t;
extern __wogtest_t __wogtest;

static inline bool __streq( const char *pStr1, const char *pStr2);
static inline char __tolower(const char c);
static inline bool __strcaseeq( const char *pStr1, const char *pStr2);
static inline const char* __itos(const int32_t num);

static void __printStart(void);
static void __printTestCaseStart(char *ptc);
static void __printTestCaseEnd(char *ptc);
static void __printTestCaseFailed(char *ptc);
static void __printTestNameNl(char *ptc, char *ptn);
static void __printTestRun(char *ptc, char *ptn);
static void __printTestPassed(char *ptc, char *ptn);
static void __printTestFailed(const char *msg, char *ptc, char *ptn);
static void print_file_line(char *file,uint32_t line);
static void print_message_exp_act(uint32_t exp, uint32_t act);

#ifdef WOGTEST_FLOAT
//static bool __floatalmosteq(const float f1,const float f2);
//static bool __doublealmosteq(const double d1,const double d2);
//static const char __ftoc(const float flt, const uint32_t dec);
//static const char* __ftoa(const float flt);
//static const char __dtoc(const double dub, const uint64_t dec);
//static const char* __dtoa(const double dub);
static void print_float_evaluates(char* par,float flt);
static void print_double_evaluates(char* par,double dub);
#endif //WOGTEST_FLOAT

static inline bool __streq( const char *pStr1, const char *pStr2)
{
    for(;*pStr1 != 0 && *pStr2 != 0;pStr1++,pStr2++)
    {
        if(*pStr1 != *pStr2 ) return false;
    }
    if((*pStr1 != 0 && *pStr2 == 0) || (*pStr1 == 0 && *pStr2 != 0)) return false;
    return true;
}
static inline char __tolower(const char c)
{
    if( c >= 'A' && c <= 'Z') return (c-'A'+'a');
    return c;
}
static inline bool __strcaseeq( const char *pStr1, const char *pStr2)
{
    for(;*pStr1 != 0 && *pStr2 != 0;pStr1++,pStr2++)
    {
        if(__tolower(*pStr1) != __tolower(*pStr2) ) return false;
    }
    if((*pStr1 != 0 && *pStr2 == 0) || (*pStr1 == 0 && *pStr2 != 0)) return false;
    return true;
}
///Helper __itos
static inline const char* __itos(const int32_t num)
{
    uint32_t anum = ((num < 0) ? -num : num);
#define __ITOS_BUFLEN 12 //sign+10 digits+0
    static char buf[__ITOS_BUFLEN];
    char* sptr = buf;
    if (num == 0)
        *sptr++ = '0';
    else
        for (uint32_t digits = 1000000000; digits > 0; digits /= 10)
            if (anum >= digits) *sptr++ = '0' + ((anum / digits) % 10);
    *sptr = '\0';
    return buf;
}
#ifdef WOGTEST_FLOAT
static const char* __ltos(const int64_t num);
static bool __floatalmosteq(const float f1,const float f2);
static bool __doublealmosteq(const double d1,const double d2);
static const char __ftoc(const float flt, const uint32_t dec);
static const char* __ftoa(const float flt);
static const char __dtoc(const double dub, const uint64_t dec);
static const char* __dtoa(const double dub);
///Helper __ltos
static const char* __ltos(const int64_t num)
{
    uint64_t anum = ((num < 0) ? -num : num);
#define __LTOS_BUFLEN 22 //sign+19 digits+0
    static char buf[__LTOS_BUFLEN];
    char* sptr = buf;
    if (num == 0)
        *sptr++ = '0';
    else
        for (uint64_t digits = 1000000000000000000ULL; digits > 0; digits /= 10)
            if (anum >= digits) *sptr++ = '0' + ((anum / digits) % 10);
    *sptr = '\0';
    return buf;
}
///Helper Test_Assert::ftoc
static const char __ftoc(const float flt, const uint32_t dec)
{
    return (uint8_t)((uint32_t)((flt-(int32_t)flt)*dec)%10);
}
///Helper Test_Assert::ftoa
static const char* __ftoa(const float flt)
{
    if( flt > (float)INT_MAX ) return "ERROR:FLOAT_OVERFLOW";
    if( flt < (float)INT_MIN ) return "ERROR:FLOAT_UNDERFLOW";
    float aflt = ((flt<0)?-flt:flt);
#define FLOATpredotbuflen 14  //sign+13
#define FLOATpostdotbuflen 10 //dot+7+0+align
#define FLOATbuflen (FLOATpredotbuflen + FLOATpostdotbuflen)
    static char buf[FLOATbuflen];
    for(uint_fast8_t j=0;j < sizeof(buf) ; j++){buf[j]='\0';}
    uint_fast8_t i=0;
    if (flt < 0) { buf[i++] = '-'; }
    const char* ptr = __itos((int)aflt);
    while (*ptr != '\0') { buf[i++] = *ptr++; }
    if (i >= FLOATpredotbuflen) { return "ERROR:PRE.BUFFER_OVERFLOW"; }
    buf[i++] = '.';
    for(uint32_t div = 10;div <= 10000000; div *=10)
    {
        buf[i++] = '0' + __ftoc(aflt,div);
    }
    buf[i++] = '\0' ;
    return buf;
}
///Helper Test_Assert::dtoc
static const char __dtoc(const double dub, const uint64_t dec)
{
    return (uint8_t)((uint64_t)((dub-(int64_t)dub)*dec)%10);
}
///Helper Test_Assert::dtoa
static const char* __dtoa(const double dub)
{
    if( dub > (double)LONG_MAX ) return "ERROR:DOUBLE_OVERFLOW";
    if( dub < (double)LONG_MIN ) return "ERROR:DOUBLE_UNDERFLOW";
    double adub = ((dub<0)?-dub:dub);
#define DOUBLEpredotbuflen 20 //sign+19
#define DOUBLEpostdotbuflen 16 //dot+14+0
#define DOUBLEbuflen (DOUBLEpredotbuflen + DOUBLEpostdotbuflen)
    static char buf[DOUBLEbuflen];
    for(uint_fast8_t j=0;j < sizeof(buf) ; j++){buf[j]='\0';}
    uint_fast8_t i=0;
    if( dub < 0 ) { buf[i++] = '-'; }
    const char* ptr = __ltos((int64_t)adub);
    while (*ptr != '\0') { buf[i++] = *ptr++; }
    if (i >= DOUBLEpredotbuflen) { return "ERROR:PRE.BUFFER_OVERFLOW"; }
    buf[i++] = '.';
    for(uint64_t div = 10ULL;div <= 1000000000000000ULL; div *=10)
    {
        buf[i++] = '0' + __dtoc(adub,div);
    }
    buf[i++] = '\0' ;
    return buf;
}
///Helper Test_Assert::floatalmosteq
static bool __floatalmosteq(const float f1,const float f2)
{
	int32_t i1 = *((int32_t*)&f1);
	int32_t i2 = *((int32_t*)&f2);
	//Different signs means they do not match, despite both are 0
    if((i1<0) != (i2<0)) return (i1 == i2);// Check for equality to make sure +0==-0
	//Find the difference in ULPs.
    uint32_t ulpsDiff = ((i1 - i2)>0)?(i1 - i2):-(i1 - i2);
    //static constexpr uint32_t maxUlpsDiff = 4u;
    return (ulpsDiff <= 4u);
}
///Helper Test_Assert::doublealmosteq
static bool __doublealmosteq(const double d1,const double d2)
{
    int64_t i1 = *((int64_t*)&d1);
	int64_t i2 = *((int64_t*)&d2);
	// Different signs means they do not match.
    if((i1<0) != (i2<0)) return (i1 == i2);// Check for equality to make sure +0==-0
	// Find the difference in ULPs.
    uint64_t ulpsDiff = ((i1 - i2)>0)?(i1 - i2):-(i1 - i2);
    return (ulpsDiff <= 4u);
}
#endif //WOGTEST_FLOAT

//Parameter abreviations
//tc test_case
//tn test_name
//tt tests_total
//ts tests_successful
//cnt #of Test

static void __printStart(void)
{
	if( 0 ) //dummy calls to get rid of warnings
    {
		__printTestCaseStart("");
		__printTestCaseEnd("");
		__printTestCaseFailed("");
		__printTestRun("","");
		__printTestPassed("","");
		__printTestFailed("","","");
		print_file_line("",0UL);
		print_message_exp_act(0UL,0UL);
#ifdef WOGTEST_FLOAT
		__floatalmosteq(0.0,0.0);
		__doublealmosteq(0.0L,0.0L);
		print_float_evaluates("",0.0);
		print_double_evaluates("",0.0L);
#endif //WOGTEST_FLOAT
    }

    PRINTSTR("********************************\r\n");
    PRINTSTR("***    MicroConsult GmbH     ***\r\n");
    PRINTSTR("***  wogtest C Test harnish  ***\r\n");
    PRINTSTR("***      Version ");
    PRINTSTR(STRINGIZE(WOGTEST_VERSION));
    PRINTSTR("       ***\r\n");
    PRINTSTR("***     by Remo Markgraf     ***\r\n");
    PRINTSTR("********************************\r\n");
	PRINTSTR("\r[==========] TEST RUNNER\r\n");
};

static inline void __printSummary(void)
{
	if( 0 ) {__printStart();}//dummy call to get rid of warnings
    PRINTSTR("[==========] SUMMARY\r\n");
#ifdef USE_PRINTF
    printf("[  TOTAL   ] %lu tests from %lu testcases\r\n",__wogtest.total_tests,__wogtest.total_tcs);
    printf("[  PASSED  ] %lu tests\r\n",__wogtest.total_succ);
    printf("[  FAILED  ] %lu tests\r\n",__wogtest.total_tests-__wogtest.total_succ);
#else //USE_PRINTF
    PRINTSTR("[  TOTAL   ] ");
    PRINTSTR(__itos(__wogtest.total_tests));
    PRINTSTR(" tests of ");
    PRINTSTR(__itos(__wogtest.total_tcs));
    PRINTSTR(" testcases\r\n");
    PRINTSTR("[  PASSED  ] ");
    PRINTSTR(__itos(__wogtest.total_succ));
    PRINTSTR(" tests\r\n");
    PRINTSTR("[  FAILED  ] ");
    PRINTSTR(__itos(__wogtest.total_tests-__wogtest.total_succ));
    PRINTSTR(" tests\r\n");
#endif //USE_PRINTF
    PRINTSTR("[==========]\r\n");
    if (__wogtest.total_succ != __wogtest.total_tests)
    {
        PRINTSTR("\r\n\x1b[41m\x1b[97m  ");
#ifdef USE_PRINTF
        printf("%lu",__wogtest.total_tests-__wogtest.total_succ);
#else //USE_PRINTF
        PRINTSTR(__itos(__wogtest.total_tests-__wogtest.total_succ));
#endif //USE_PRINTF
        PRINTSTR(" FAILED TESTS\x1b[0m\r\n\r\n");
    }
    else
    {
        PRINTSTR("\r\n\x1b[42m\x1b[97m  ALL TESTS PASSED\x1b[0m\r\n\r\n");
    }
  }


#define GTEST_API_ \
__wogtest_t __wogtest = {\
    .total_tcs = 0,\
    .total_tests = 0,\
    .total_succ = 0,\
    .tc_tests = 0,\
    .tc_succ = 0,\
    .tn_passed = false,\
    .tn_fatal = false, };\
WEAKFUNC void RunTestcase_0(void) {};\
WEAKFUNC void RunTestcase_1(void) {};\
WEAKFUNC void RunTestcase_2(void) {};\
WEAKFUNC void RunTestcase_3(void) {};\
WEAKFUNC void RunTestcase_4(void) {};\
WEAKFUNC void RunTestcase_5(void) {};\
WEAKFUNC void RunTestcase_6(void) {};\
WEAKFUNC void RunTestcase_7(void) {};\
WEAKFUNC void RunTestcase_8(void) {};\
WEAKFUNC void RunTestcase_9(void) {};\
WEAKFUNC void RunTestcase_10(void) {};\
WEAKFUNC void RunTestcase_11(void) {};\
WEAKFUNC void RunTestcase_12(void) {};\
WEAKFUNC void RunTestcase_13(void) {};\
WEAKFUNC void RunTestcase_14(void) {};\
WEAKFUNC void RunTestcase_15(void) {};\
WEAKFUNC void RunTestcase_16(void) {};\
WEAKFUNC void RunTestcase_17(void) {};\
WEAKFUNC void RunTestcase_18(void) {};\
WEAKFUNC void RunTestcase_19(void) {};\
static bool __wogtestrunner(void){\
    __printStart();\
    RunTestcase_0();\
    RunTestcase_1();\
    RunTestcase_2();\
    RunTestcase_3();\
    RunTestcase_4();\
    RunTestcase_5();\
    RunTestcase_6();\
    RunTestcase_7();\
    RunTestcase_8();\
    RunTestcase_9();\
    RunTestcase_10();\
    RunTestcase_11();\
    RunTestcase_12();\
    RunTestcase_13();\
    RunTestcase_14();\
    RunTestcase_15();\
    RunTestcase_16();\
    RunTestcase_17();\
    RunTestcase_18();\
    RunTestcase_19();\
    __printSummary();\
    return (bool)(__wogtest.total_tests-__wogtest.total_succ);}

#define RUN_ALL_TESTS() __wogtestrunner()

static void __printTestNameNl(char *ptc, char *ptn)
{
#ifdef USE_PRINTF
    printf("%s.%s\r\n",ptc,ptn);
#else
    PRINTSTR(ptc);
    PRINTSTR(".");
    PRINTSTR(ptn);
    PRINTSTR("\r\n");
#endif
}
static void __printTestRun(char *ptc, char *ptn)
{
#ifdef USE_PRINTF
    printf("\x1b[32m[ RUN      ]\x1b[0m ");
#else
    PRINTSTR("\x1b[32m[ RUN      ]\x1b[0m ");
#endif
    __printTestNameNl(ptc, ptn);
}
static void __printTestPassed(char *ptc, char *ptn)
{
#ifdef USE_PRINTF
    printf("\x1b[32m[       OK ]\x1b[0m ");
#else
    PRINTSTR("\x1b[32m[       OK ]\x1b[0m ");
#endif
    __printTestNameNl(ptc, ptn);
}
static void __printTestFailed(const char *msg, char *ptc, char *ptn)
{
#ifdef USE_PRINTF
    printf("%s\x1b[31m[  FAILED  ]\x1b[0m ",msg);
#else
    PRINTSTR(msg);\
    PRINTSTR("\x1b[31m[  FAILED  ]\x1b[0m ");
#endif
    __printTestNameNl(ptc, ptn);
}

static void __printTestCaseStart(char *ptc)
{
    PRINTSTR("[----------] tests of ");
    PRINTSTR(ptc);
    PRINTSTR("\r\n");
}
static void __printTestCaseEnd(char *ptc)
{
    PRINTSTR("[----------] ");
#ifdef USE_PRINTF
    printf("%lu tests of %s",__wogtest.tc_tests,ptc);
#else
    PRINTSTR(__itos(__wogtest.tc_tests));
    PRINTSTR(" tests of ");
    PRINTSTR(ptc);
#endif
    PRINTSTR("\r\n");
}
static void __printTestCaseFailed(char *ptc)
{
    PRINTSTR("\x1b[41m\x1b[97m[   FAILED ] ");
#ifdef USE_PRINTF
    printf("%lu tests of %s",__wogtest.tc_tests-__wogtest.tc_succ,ptc);
#else
    PRINTSTR(__itos(__wogtest.tc_tests-__wogtest.tc_succ));
    PRINTSTR(" tests of ");
    PRINTSTR(ptc);
#endif
    PRINTSTR("\x1b[0m\r\n");
}

#define TESTCASE(tc) TESTCASEn(tc,__COUNTER__)
#define TESTCASEn(tc,cnt) TESTCASEnn(tc,cnt)
#define TESTCASEnn(tc,cnt)\
    WEAKFUNC void tc##_RunTest_0(void) {}\
    WEAKFUNC void tc##_RunTest_1(void) {}\
    WEAKFUNC void tc##_RunTest_2(void) {}\
    WEAKFUNC void tc##_RunTest_3(void) {}\
    WEAKFUNC void tc##_RunTest_4(void) {}\
    WEAKFUNC void tc##_RunTest_5(void) {}\
    WEAKFUNC void tc##_RunTest_6(void) {}\
    WEAKFUNC void tc##_RunTest_7(void) {}\
    WEAKFUNC void tc##_RunTest_8(void) {}\
    WEAKFUNC void tc##_RunTest_9(void) {}\
    WEAKFUNC void tc##_RunTest_10(void) {}\
    WEAKFUNC void tc##_RunTest_11(void) {}\
    WEAKFUNC void tc##_RunTest_12(void) {}\
    WEAKFUNC void tc##_RunTest_13(void) {}\
    WEAKFUNC void tc##_RunTest_14(void) {}\
    WEAKFUNC void tc##_RunTest_15(void) {}\
    WEAKFUNC void tc##_RunTest_16(void) {}\
    WEAKFUNC void tc##_RunTest_17(void) {}\
    WEAKFUNC void tc##_RunTest_18(void) {}\
    WEAKFUNC void tc##_RunTest_19(void) {}\
    WEAKFUNC void tc##_RunTest_20(void) {}\
    WEAKFUNC void tc##_RunTest_21(void) {}\
    WEAKFUNC void tc##_RunTest_22(void) {}\
    WEAKFUNC void tc##_RunTest_23(void) {}\
    WEAKFUNC void tc##_RunTest_24(void) {}\
    WEAKFUNC void tc##_RunTest_25(void) {}\
    WEAKFUNC void tc##_RunTest_26(void) {}\
    WEAKFUNC void tc##_RunTest_27(void) {}\
    WEAKFUNC void tc##_RunTest_28(void) {}\
    WEAKFUNC void tc##_RunTest_29(void) {}\
    WEAKFUNC void tc##_RunTest_30(void) {}\
    WEAKFUNC void tc##_RunTest_31(void) {}\
    WEAKFUNC void tc##_RunTest_32(void) {}\
    WEAKFUNC void tc##_RunTest_33(void) {}\
    WEAKFUNC void tc##_RunTest_34(void) {}\
    WEAKFUNC void tc##_RunTest_35(void) {}\
    WEAKFUNC void tc##_RunTest_36(void) {}\
    WEAKFUNC void tc##_RunTest_37(void) {}\
    WEAKFUNC void tc##_RunTest_38(void) {}\
    WEAKFUNC void tc##_RunTest_39(void) {}\
    WEAKFUNC void tc##_RunTest_40(void) {}\
    WEAKFUNC void tc##_RunTest_41(void) {}\
    WEAKFUNC void tc##_RunTest_42(void) {}\
    WEAKFUNC void tc##_RunTest_43(void) {}\
    WEAKFUNC void tc##_RunTest_44(void) {}\
    WEAKFUNC void tc##_RunTest_45(void) {}\
    WEAKFUNC void tc##_RunTest_46(void) {}\
    WEAKFUNC void tc##_RunTest_47(void) {}\
    WEAKFUNC void tc##_RunTest_48(void) {}\
    WEAKFUNC void tc##_RunTest_49(void) {}\
    WEAKFUNC void tc##_RunTest_50(void) {}\
    WEAKFUNC void tc##_RunTest_51(void) {}\
    WEAKFUNC void tc##_RunTest_52(void) {}\
    WEAKFUNC void tc##_RunTest_53(void) {}\
    WEAKFUNC void tc##_RunTest_54(void) {}\
    WEAKFUNC void tc##_RunTest_55(void) {}\
    WEAKFUNC void tc##_RunTest_56(void) {}\
    WEAKFUNC void tc##_RunTest_57(void) {}\
    WEAKFUNC void tc##_RunTest_58(void) {}\
    WEAKFUNC void tc##_RunTest_59(void) {}\
    WEAKFUNC void tc##_RunTest_60(void) {}\
    WEAKFUNC void tc##_RunTest_61(void) {}\
    WEAKFUNC void tc##_RunTest_62(void) {}\
    WEAKFUNC void tc##_RunTest_63(void) {}\
    WEAKFUNC void tc##_RunTest_64(void) {}\
    WEAKFUNC void tc##_RunTest_65(void) {}\
    WEAKFUNC void tc##_RunTest_66(void) {}\
    WEAKFUNC void tc##_RunTest_67(void) {}\
    WEAKFUNC void tc##_RunTest_68(void) {}\
    WEAKFUNC void tc##_RunTest_69(void) {}\
    WEAKFUNC void tc##_RunTest_70(void) {}\
    WEAKFUNC void tc##_RunTest_71(void) {}\
    WEAKFUNC void tc##_RunTest_72(void) {}\
    WEAKFUNC void tc##_RunTest_73(void) {}\
    WEAKFUNC void tc##_RunTest_74(void) {}\
    WEAKFUNC void tc##_RunTest_75(void) {}\
    WEAKFUNC void tc##_RunTest_76(void) {}\
    WEAKFUNC void tc##_RunTest_77(void) {}\
    WEAKFUNC void tc##_RunTest_78(void) {}\
    WEAKFUNC void tc##_RunTest_79(void) {}\
    WEAKFUNC void tc##_RunTest_80(void) {}\
    WEAKFUNC void tc##_RunTest_81(void) {}\
    WEAKFUNC void tc##_RunTest_82(void) {}\
    WEAKFUNC void tc##_RunTest_83(void) {}\
    WEAKFUNC void tc##_RunTest_84(void) {}\
    WEAKFUNC void tc##_RunTest_85(void) {}\
    WEAKFUNC void tc##_RunTest_86(void) {}\
    WEAKFUNC void tc##_RunTest_87(void) {}\
    WEAKFUNC void tc##_RunTest_88(void) {}\
    WEAKFUNC void tc##_RunTest_89(void) {}\
    WEAKFUNC void tc##_RunTest_90(void) {}\
    WEAKFUNC void tc##_RunTest_91(void) {}\
    WEAKFUNC void tc##_RunTest_92(void) {}\
    WEAKFUNC void tc##_RunTest_93(void) {}\
    WEAKFUNC void tc##_RunTest_94(void) {}\
    WEAKFUNC void tc##_RunTest_95(void) {}\
    WEAKFUNC void tc##_RunTest_96(void) {}\
    WEAKFUNC void tc##_RunTest_97(void) {}\
    WEAKFUNC void tc##_RunTest_98(void) {}\
    WEAKFUNC void tc##_RunTest_99(void) {}\
    static void RunTestcase_##tc(void);\
    void RunTestcase_##cnt(void);\
    void RunTestcase_##cnt(void){RunTestcase_##tc();}\
    static void RunTestcase_##tc(void)\
    {\
    __wogtest.tc_tests = 0;\
    __wogtest.tc_succ = 0;\
    __wogtest.total_tcs++;\
    __printTestCaseStart(#tc);\
    tc##_RunTest_0();\
    tc##_RunTest_1();\
    tc##_RunTest_2();\
    tc##_RunTest_3();\
    tc##_RunTest_4();\
    tc##_RunTest_5();\
    tc##_RunTest_6();\
    tc##_RunTest_7();\
    tc##_RunTest_8();\
    tc##_RunTest_9();\
    tc##_RunTest_10();\
    tc##_RunTest_11();\
    tc##_RunTest_12();\
    tc##_RunTest_13();\
    tc##_RunTest_14();\
    tc##_RunTest_15();\
    tc##_RunTest_16();\
    tc##_RunTest_17();\
    tc##_RunTest_18();\
    tc##_RunTest_19();\
    tc##_RunTest_20();\
    tc##_RunTest_21();\
    tc##_RunTest_22();\
    tc##_RunTest_23();\
    tc##_RunTest_24();\
    tc##_RunTest_25();\
    tc##_RunTest_26();\
    tc##_RunTest_27();\
    tc##_RunTest_28();\
    tc##_RunTest_29();\
    tc##_RunTest_30();\
    tc##_RunTest_31();\
    tc##_RunTest_32();\
    tc##_RunTest_33();\
    tc##_RunTest_34();\
    tc##_RunTest_35();\
    tc##_RunTest_36();\
    tc##_RunTest_37();\
    tc##_RunTest_38();\
    tc##_RunTest_39();\
    tc##_RunTest_40();\
    tc##_RunTest_41();\
    tc##_RunTest_42();\
    tc##_RunTest_43();\
    tc##_RunTest_44();\
    tc##_RunTest_45();\
    tc##_RunTest_46();\
    tc##_RunTest_47();\
    tc##_RunTest_48();\
    tc##_RunTest_49();\
    tc##_RunTest_50();\
    tc##_RunTest_51();\
    tc##_RunTest_52();\
    tc##_RunTest_53();\
    tc##_RunTest_54();\
    tc##_RunTest_55();\
    tc##_RunTest_56();\
    tc##_RunTest_57();\
    tc##_RunTest_58();\
    tc##_RunTest_59();\
    tc##_RunTest_60();\
    tc##_RunTest_61();\
    tc##_RunTest_62();\
    tc##_RunTest_63();\
    tc##_RunTest_64();\
    tc##_RunTest_65();\
    tc##_RunTest_66();\
    tc##_RunTest_67();\
    tc##_RunTest_68();\
    tc##_RunTest_69();\
    tc##_RunTest_70();\
    tc##_RunTest_71();\
    tc##_RunTest_72();\
    tc##_RunTest_73();\
    tc##_RunTest_74();\
    tc##_RunTest_75();\
    tc##_RunTest_76();\
    tc##_RunTest_77();\
    tc##_RunTest_78();\
    tc##_RunTest_79();\
    tc##_RunTest_80();\
    tc##_RunTest_81();\
    tc##_RunTest_82();\
    tc##_RunTest_83();\
    tc##_RunTest_84();\
    tc##_RunTest_85();\
    tc##_RunTest_86();\
    tc##_RunTest_87();\
    tc##_RunTest_88();\
    tc##_RunTest_89();\
    tc##_RunTest_90();\
    tc##_RunTest_91();\
    tc##_RunTest_92();\
    tc##_RunTest_93();\
    tc##_RunTest_94();\
    tc##_RunTest_95();\
    tc##_RunTest_96();\
    tc##_RunTest_97();\
    tc##_RunTest_98();\
    tc##_RunTest_99();\
    __printTestCaseEnd(#tc);\
    if(__wogtest.tc_succ != __wogtest.tc_tests)\
    {\
        __printTestCaseFailed(#tc);\
    }\
    PRINTSTR("\x1b[0m\r\n");\
    __wogtest.total_tests += __wogtest.tc_tests;\
    __wogtest.total_succ += __wogtest.tc_succ;\
}

#define TEST(tc,tn) TESTn(tc,tn,__COUNTER__)
#define TESTn(tc,tn,cnt) TESTnn(tc,tn,cnt)
#define TESTnn(tc,tn,cnt)\
    static void tc##_##tn(const char** message);\
    void tc##_RunTest_##cnt(void){RUN_TEST(tc,tn,&__wogtest.tc_tests,&__wogtest.tc_succ);}\
    static void tc##_##tn(const char** message)

#define RUN_TEST(tc,tn,tt,ts)\
  do {\
    const char* message = 0;\
    __wogtest.tn_passed = true;\
    __wogtest.tn_fatal = false;\
    ++*tt;\
    __printTestRun(#tc,#tn);\
    tc##_##tn(&message);\
    if (__wogtest.tn_passed) {\
      ++*ts;\
      __printTestPassed(#tc,#tn);\
    } else {\
      __printTestFailed(message,#tc,#tn);\
    }\
  } while (0)

#define PRINT_FILE_LINE PRINT_FILE_LINEn(__FILE__,__LINE__)
#define PRINT_FILE_LINEn(file,line) PRINT_FILE_LINEnn(file,line)
#define PRINT_FILE_LINEnn(file,line) print_file_line(file,line)
static void print_file_line(char *file,uint32_t line);
static void print_file_line(char *file,uint32_t line)
{
#ifdef USE_PRINTF
    printf("    %s [%lu]\r\n    ",file,line);
#else
    PRINTSTR("    ");
    PRINTSTR(file);
    PRINTSTR(" [");
    PRINTSTR(__itos(line));
    PRINTSTR("]\r\n");
    PRINTSTR("    ");
#endif
}

#define PRINT_MESSAGE_EXP_ACT(exp,act) print_message_exp_act(exp, act)
static void print_message_exp_act(uint32_t exp, uint32_t act);
static void print_message_exp_act(uint32_t exp, uint32_t act)
{
#ifdef USE_PRINTF
      printf(", expected: %lu , actual: %lu\r\n",exp,act);
#else
      PRINTSTR(", expected: ");
      PRINTSTR(__itos(exp));
      PRINTSTR(", actual: ");
      PRINTSTR(__itos(act));
      PRINTSTR("\r\n");
#endif
}
#define ASSERT_TRUEn(cond, equ, ass)\
  do {\
    if (cond!=equ) {\
      __wogtest.tn_passed = false;\
      PRINT_FILE_LINE;\
      PRINTSTR("value is not ");\
      PRINTSTR((equ)?"true":"false");\
      PRINTSTR("\r\n");\
      if( ass ) {__wogtest.tn_fatal=true;return;}\
    }\
  } while (0)
#define ASSERT_TRUE(cond) ASSERT_TRUEn((bool)cond, true, true)
#define EXPECT_TRUE(cond) ASSERT_TRUEn((bool)cond, true, false)
#define ASSERT_FALSE(cond) ASSERT_TRUEn((bool)cond, false, true)
#define EXPECT_FALSE(cond) ASSERT_TRUEn((bool)cond, false, false)
  
#define ASSERT_FAILnn(error_message,ass,file,line)\
  do {\
      __wogtest.tn_passed = false;\
      PRINT_FILE_LINEnn(file,line);\
      PRINTSTR(error_message);\
      PRINTSTR("\r\n");\
      if( ass ) {__wogtest.tn_fatal=true;return;}\
  } while (0)
#define ASSERT_FAIL(error_message) ASSERT_FAILn(error_message,true,__FILE__, __LINE__)
#define EXPECT_FAIL(error_message) ASSERT_FAILn(error_message,false,__FILE__, __LINE__)
#define ASSERT_FAILn(error_message,ass,file,line) ASSERT_FAILnn(error_message,ass,file,line)

#define ASSERT_SUCCEEDn(error_message,ass)\
  do {\
      PRINT_FILE_LINE;\
      PRINTSTR(error_message);\
      PRINTSTR("\r\n");\
      if( ass ) {__wogtest.tn_fatal=true;return;}\
  } while (0)
#define ASSERT_SUCCEED(error_message) ASSERT_SUCCEEDn(error_message,true)
#define EXPECT_SUCCEED(error_message) ASSERT_SUCCEEDn(error_message,false)

#define ASSERT_EQn(expected,actual,equ,ass)\
  do {\
    if ((actual != expected)==equ) {\
      __wogtest.tn_passed = false;\
      PRINT_FILE_LINE;\
      PRINTSTR("Wrong value, expected to be ");\
      PRINTSTR((equ)?"equal":"unequal");\
      PRINT_MESSAGE_EXP_ACT(expected,actual);\
      if( ass ) {__wogtest.tn_fatal=true;return;}\
    }\
  } while (0)
#define ASSERT_EQ(expected,actual) ASSERT_EQn(expected,actual,true,true)
#define EXPECT_EQ(expected,actual) ASSERT_EQn(expected,actual,true,false)
#define ASSERT_NE(expected,actual) ASSERT_EQn(expected,actual,false,true)
#define EXPECT_NE(expected,actual) ASSERT_EQn(expected,actual,false,false)

#define ASSERT_GTn(expected,actual,equ,ass)\
  do {\
    if((expected > actual)!=equ) {\
      __wogtest.tn_passed = false;\
      PRINT_FILE_LINE;\
      PRINTSTR("Wrong value, expected to be ");\
      PRINTSTR((equ)?"bigger":"smaller or equal");\
      PRINT_MESSAGE_EXP_ACT(expected,actual);\
      if( ass ) {__wogtest.tn_fatal=true;return;}\
    }\
  } while (0)
#define ASSERT_GT(expected,actual) ASSERT_GTn(expected,actual,true,true)
#define EXPECT_GT(expected,actual) ASSERT_GTn(expected,actual,true,false)
#define ASSERT_LE(expected,actual) ASSERT_GTn(expected,actual,false,true)
#define EXPECT_LE(expected,actual) ASSERT_GTn(expected,actual,false,false)
    
#define ASSERT_LTn(expected,actual,equ,ass)\
  do {\
    if((expected < actual)!=equ) {\
      __wogtest.tn_passed = false;\
      PRINT_FILE_LINE;\
      PRINTSTR("Wrong value, expected to be ");\
      PRINTSTR((equ)?"smaller":"greater or equal");\
      PRINT_MESSAGE_EXP_ACT(expected,actual);\
      if( ass ) {__wogtest.tn_fatal=true;return;}\
    }\
  } while (0)
#define ASSERT_LT(expected,actual) ASSERT_LTn(expected,actual,true,true)
#define EXPECT_LT(expected,actual) ASSERT_LTn(expected,actual,true,false)
#define ASSERT_GE(expected,actual) ASSERT_LTn(expected,actual,false,true)
#define EXPECT_GE(expected,actual) ASSERT_LTn(expected,actual,false,false)

#ifdef USE_PRINTF
#define PRINT_FAIL_STREQ(expected,actual,equ)\
    printf("%s, expected: %s, current: %s\r\n",(equ)?"String missmatch":"Unintended string match",expected,actual)
#else
#define PRINT_FAIL_STREQ(expected,actual,equ)\
    PRINTSTR((equ)?"String missmatch":"Unintended string match");\
    PRINTSTR(", expected: ");\
    PRINTSTR(expected);\
    PRINTSTR(", current: ");\
    PRINTSTR(actual);\
    PRINTSTR("\r\n")
#endif

#define ASSERT_STREQn(expected,actual,equ,cas,ass)\
  do {\
    const char *pAct=actual,*pExp=expected;\
	if(pAct == NULL || pExp == NULL) {\
        __wogtest.tn_passed = false;\
        PRINT_FILE_LINE;\
        PRINTSTR("NUll pointer passed as argument\r\n");\
		if( ass ) {__wogtest.tn_fatal=true;return;}\
	}\
    else if((cas?__strcaseeq(pAct,pExp):__streq(pAct,pExp))!=equ){\
        __wogtest.tn_passed = false;\
        PRINT_FILE_LINE;\
        PRINTSTR((equ)?"String missmatch":"Unintended string match");\
        PRINTSTR(", expected: ");\
        PRINTSTR(expected);\
        PRINTSTR(", current: ");\
        PRINTSTR(actual);\
        PRINTSTR("\r\n");\
        if( ass ) {__wogtest.tn_fatal=true;return;}\
    }\
  } while (0)
//                                                                   // logic case  assert
#define ASSERT_STREQ(expected,actual)     ASSERT_STREQn(expected,actual,true ,false,true )
#define EXPECT_STREQ(expected,actual)     ASSERT_STREQn(expected,actual,true ,false,false)
#define ASSERT_STRNE(expected,actual)     ASSERT_STREQn(expected,actual,false,false,true )
#define EXPECT_STRNE(expected,actual)     ASSERT_STREQn(expected,actual,false,false,false)
#define ASSERT_STRCASEEQ(expected,actual) ASSERT_STREQn(expected,actual,true ,true ,true )
#define EXPECT_STRCASEEQ(expected,actual) ASSERT_STREQn(expected,actual,true ,true ,false)
#define ASSERT_STRCASENE(expected,actual) ASSERT_STREQn(expected,actual,false,true ,true )
#define EXPECT_STRCASENE(expected,actual) ASSERT_STREQn(expected,actual,false,true ,false)

#ifdef WOGTEST_FLOAT
//static bool __floatalmosteq(const float f1,const float f2);
//static bool __doublealmosteq(const double d1,const double d2);
//static const char __ftoc(const float flt, const uint32_t dec);
//static const char* __ftoa(const float flt);
//static const char __dtoc(const double dub, const uint64_t dec);
//static const char* __dtoa(const double dub);

static void print_float_evaluates(char* par,float flt);
static void print_float_evaluates(char* par,float flt)
{
#ifdef USE_PRINTF
    printf("    %s  evaluates to %s\r\n",par,__ftoa(flt));
#else
    PRINTSTR("    ");
    PRINTSTR(par);
    PRINTSTR("  evaluates to ");
    PRINTSTR(__ftoa(flt));
    PRINTSTR("\r\n");
#endif
}

static void print_double_evaluates(char* par,double dub);
static void print_double_evaluates(char* par,double dub)
{
#ifdef USE_PRINTF
    printf("    %s  evaluates to %s\r\n",par,__dtoa(dub));
#else
    PRINTSTR("    ");
    PRINTSTR(par);
    PRINTSTR("  evaluates to ");
    PRINTSTR(__dtoa(dub));
    PRINTSTR("\r\n");
#endif
}

#define ASSERT_FLOATEQn(f1,f2,ass)\
  do {\
    if (!__floatalmosteq(f1,f2)){\
        __wogtest.tn_passed = false;\
        PRINT_FILE_LINE;\
        PRINTSTR("    Float missmatch\r\n");\
        print_float_evaluates(#f1,f1);\
        print_float_evaluates(#f2,f2);\
        if( ass ) {__wogtest.tn_fatal=true;return;}\
    }\
  } while (0)
#define ASSERT_FLOAT_EQ(f1,f2) ASSERT_FLOATEQn(f1,f2,true)
#define EXPECT_FLOAT_EQ(f1,f2) ASSERT_FLOATEQn(f1,f2,false)
    
///Helper Test_Assert::doublealmosteq
#define ASSERT_DOUBLEEQn(d1,d2,ass)\
  do {\
    if (!__doublealmosteq(d1,d2)){\
        __wogtest.tn_passed = false;\
        PRINT_FILE_LINE;\
        PRINTSTR("Double missmatch\r\n");\
        print_double_evaluates(#d1,d1);\
        print_double_evaluates(#d2,d2);\
        if( ass ) {__wogtest.tn_fatal=true;return;}\
    }\
  } while (0)
#define ASSERT_DOUBLE_EQ(d1,d2) ASSERT_DOUBLEEQn(d1,d2,true)
#define EXPECT_DOUBLE_EQ(d1,d2) ASSERT_DOUBLEEQn(d1,d2,false)

#define ASSERT_NEARn(d1,d2,delta,ass)\
  do {\
    if((((d1 - d2)>0)?(d1 - d2):-(d1 - d2))>delta){\
        __wogtest.tn_passed = false;\
        PRINT_FILE_LINE;\
        PRINTSTR("Near Double missmatch\r\n");\
        print_double_evaluates(#d1,d1);\
        print_double_evaluates(#d2,d2);\
        print_double_evaluates(#delta,delta);\
        if( ass ) {__wogtest.tn_fatal=true;return;}\
    }\
  } while (0)
#define ASSERT_NEAR(d1,d2,delta) ASSERT_NEARn(d1,d2,delta,true)
#define EXPECT_NEAR(d1,d2,delta) ASSERT_NEARn(d1,d2,delta,false)

#endif //WOGTEST_FLOAT

//HASxyzFailure to exit subroutines or TESTs
// e.g. if(HasFailure()) return;
#define HasFatalFailure()    (__wogtest.tn_fatal)
#define HasNonfatalFailure() (!__wogtest.tn_passed && !__wogtest.tn_fatal)
#define HasFailure()         (!__wogtest.tn_passed)

//Explicit Success and Failure
#define SUCCEED() ASSERT_SUCCEED("SUCCEEDED")
#define FAIL() ASSERT_FAIL("FAILED")
#define ADD_FAILURE() EXPECT_FAIL("FAILURE ADDED")
#define ADD_FAILURE_AT(file,line) ASSERT_FAILnn("FAILURE ADDED AT",false,file,line)
    
#endif  // WOGTEST_H_
