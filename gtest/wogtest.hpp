/******************************************************************************
 * @project  wogtest
 * @file     wogtest.hpp
 * @version  V2.0f
 * @date     6th of Feb 2024
 * Author    Remo Markgraf
 * Copyright (C) 2025 MicroConsult Academy GmbH. All rights reserved.
 * Originally published (C) 2023 MicroConsult GmbH. All rights reserved.
 *****************************************************************************/
#ifndef WOGTEST_HPP_
#define WOGTEST_HPP_
//---------------------------------------
#define WOGTEST_VERSION V2.0e
//---------------------------------------
//select one of <stdint.h> to use "printf" or <iostream> to use "cout <<"
//---------------------------------------
#include <stdio.h> //use "printf"
//#include <iostream>  //use "cout <<"

//---------------------------------------
//define max number of characters of error messages per ASSERT/EXPECT including your << addons
//no overflow check is performed
//one byte on stack required per character
//---------------------------------------
#define WOGTEST_MESSAGEBUFFERSIZE 1024

//---------------------------------------
//configure if heap should be used for testcases,
//if yes, define TESTCASES_NUM to DYNAMIC
//else,   define TESTCASES_NUM to the number of maximal possible testcases
//Note: Its about testcases, so the number of groups of TESTS or TEST_F
//---------------------------------------
#define WOGTESTCASES_NUM DYNAMIC
//#define WOGTESTCASES_NUM 20

//---------------------------------------
//configure if float/double should be testable,
//if yes, remove comment from define WOGTEST_FLOAT
//---------------------------------------
//#define WOGTEST_FLOAT

//---------------------------------------
//Apply templates for operator<< output extensions
//if yes, remove comment from define USE_TEMPLATES
//---------------------------------------
//#define USE_TEMPLATES

//---------------------------------------
//Apply printf for output of messages
//otherwise putchar is used
//only relevant when streams are NOT used
//if yes, remove comment from define USE_PRINTF
//---------------------------------------
//#define USE_PRINTF

//---------------------------------------
//If your C++ compiler does not initialize the
//private static local member pointer gtests.pTestCases_
//before the linked list is built up by TEST macreos
//you will see 0 tests to be executed.
//In this case you may try the signiture solution and
//remove comment from define SIGNATURE
//---------------------------------------
//#define SIGNATURE 0xFEFFAEFFUL

//---------------------------------------
//no changes required below here
//---------------------------------------
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#ifdef  _IOSTREAM_
#define PRINTSTR(str) std::cout << str
#else   //_IOSTREAM_
#ifdef USE_PRINTF
#define PRINTSTR(str) printf(str)
#else
#define PRINTSTR(str) for(char*ptr=(char*)str;*ptr!=0;ptr++)putchar(*ptr)
#endif //USE_PRINTF
#endif  //_IOSTREAM_

#define STRINGIZE(val) STRINGIZEn(val)
#define STRINGIZEn(str) #str

//Parameter abreviations
//tc test_case
//tn test_name
//tt tests_total
//ts tests_successful
//cnt #of Test

namespace testing
{
//Add static array to GTEST_API_ if no dynamic allocation from heap
#if defined(WOGTESTCASES_NUM) && WOGTESTCASES_NUM == DYNAMIC
#define WOGTESTCASES_ARRAY
#else
#define WOGTESTCASES_ARRAY TestCase tcarray_[WOGTESTCASES_NUM];
#endif

#ifdef SIGNATURE
#define INIT_SIGNATURE uint32_t gTests::TCSignature_ = 0;
#define RESET_SIGNATURE gTests::resetTCSignature();
#else
#define INIT_SIGNATURE
#define RESET_SIGNATURE
#endif

//Initialization as GTEST_API_ int main    
#define GTEST_API_ namespace testing\
{\
    gTests gtests;\
    bool gTests::tn_fatal_ = false;\
    INIT_SIGNATURE\
    TestCase* gTests::pTestCases_ = nullptr;\
    static inline void InitGoogleTest(void) {RESET_SIGNATURE gTests::printStart();}\
    static inline void InitGoogleTest(const uint32_t *argc, const char **argv) {InitGoogleTest();}\
    WOGTESTCASES_ARRAY\
}

static bool __streq( const char *pStr1, const char *pStr2)
{
    for(;*pStr1 != 0 && *pStr2 != 0;pStr1++,pStr2++)
    {
        if(*pStr1 != *pStr2 ) return false;
    }
    if((*pStr1 != 0 && *pStr2 == 0) || (*pStr1 == 0 && *pStr2 != 0)) return false;
    return true;
}
static char __tolower(char c)
{
    if( c >= 'A' && c <= 'Z') return (c-'A'+'a');
    return c;
}
static bool __strcaseeq( const char *pStr1, const char *pStr2)
{
    for(;*pStr1 != 0 && *pStr2 != 0;pStr1++,pStr2++)
    {
        if(__tolower(*pStr1) != __tolower(*pStr2) ) return false;
    }
    if((*pStr1 != 0 && *pStr2 == 0) || (*pStr1 == 0 && *pStr2 != 0)) return false;
    return true;
}

///Helper __itos
inline const char* __itos(const int32_t num)
{
    uint32_t anum = ((num < 0) ? -num : num);
    static constexpr uint8_t buflen = 12; //sign+10 digits+0
    static char buf[buflen];
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
///Helper __ltos
inline const char* __ltos(const int64_t num)
{
    uint64_t anum = ((num < 0) ? -num : num);
    static constexpr uint8_t buflen = 22; //sign+19 digits+0
    static char buf[buflen];
    char* sptr = buf;
    if (num == 0)
        *sptr++ = '0';
    else
        for (uint64_t digits = 1000000000000000000ULL; digits > 0; digits /= 10)
            if (anum >= digits) *sptr++ = '0' + ((anum / digits) % 10);
    *sptr = '\0';
    return buf;
}
#endif //WOGTEST_FLOAT

class gTests;
class TestCase;
class Test;
class Test_Assert;

#if defined(WOGTESTCASES_NUM) && WOGTESTCASES_NUM != DYNAMIC
extern TestCase tcarray_[WOGTESTCASES_NUM];
#endif

//******
class gTests
//******
{
    public:
        uint32_t get_total_tcs(void) const {return total_tcs_;}
        uint32_t get_total_tests(void) const {return total_tests_;}
        uint32_t get_total_succ(void) const {return total_succ_;}
        uint32_t get_total_failed(void) const {return (total_tests_-total_succ_);}
        uint32_t get_tc_tests(void) const {return tc_tests_;}
        uint32_t get_tc_succ(void) const {return tc_succ_;}
        uint32_t get_tc_failed(void) const {return (tc_tests_-tc_succ_);}
        bool is_passed(void) const {return tn_passed_;}
        bool is_failed(void) const {return !tn_passed_;}
        static bool is_fatal(void) {return tn_fatal_;}
        void set_passed(void) {tn_fatal_ = false;tn_passed_ = true;}
        void set_failed(void) {tn_passed_ = false;}
        void set_fatal(void) {tn_passed_ = false;tn_fatal_ = true;}
        void reset_fatal(void) {tn_fatal_ = false;}
        void reset_testcases(void) {tc_tests_ = 0;tc_succ_ = 0;}
        void inc_testcases(void) {total_tcs_++;}
        void inc_tests(void) {tc_tests_++;}
        void inc_successTests(void) {tc_succ_++;}
        bool is_anyTestCase_failed(void) const {return (tc_succ_ != tc_tests_);}
        void sumup_TestCase(void) {total_tests_ += tc_tests_;total_succ_ += tc_succ_;}
        void linkinTestCase(TestCase& refTC);
        void clear_message_buffer(void);
        void flush_message_buffer(void);
        TestCase& TestCasebyName(const char *tcname);
        uint32_t runTests(void);
        void printSummary(void);
        //gTests(void) {printStart();}
        void append_message_buffer(const char* str)
        {
            char* sptr = test_message_buffer;
            while (*sptr != '\0') sptr++;
            for (const char* pstr = str; *pstr != '\0'; pstr++, sptr++)
                *sptr = *pstr;
            *sptr = '\0';
        }
        void append_message_buffer(const uint32_t num)
        {
            append_message_buffer(__itos(num));
        }
		void append_message_failure(const char* file, const uint32_t line, const char* msg)
		{
			append_message_buffer("  * ");
			append_message_buffer(file);
			append_message_buffer(",[");
			append_message_buffer(line);
			append_message_buffer("]\r\n    ");
			append_message_buffer(msg);
		}
        void append_message_evaluates_to( const char* a1n, const char* a1)
        {
            append_message_buffer("\r\n    ");
            append_message_buffer(a1n);
            append_message_buffer(" evaluates to ");
            append_message_buffer(a1);
        }
        char test_message_buffer[WOGTEST_MESSAGEBUFFERSIZE];
    private:
        uint32_t total_tests_ = 0;
        uint32_t total_succ_ = 0;
        uint32_t total_tcs_ = 0;
        uint32_t tc_tests_ = 0;
        uint32_t tc_succ_ = 0;
        bool tn_passed_ = false;
        static bool tn_fatal_;
        static TestCase* pTestCases_; // = nullptr;
#ifdef SIGNATURE
        static uint32_t TCSignature_;
#endif //SIGNATURE
    public:
#ifdef SIGNATURE
        static void resetTCSignature(void) { TCSignature_ = ~SIGNATURE; }
#endif //SIGNATURE
        static void printStart(void)
        {
            PRINTSTR("********************************\r\n");
            PRINTSTR("***    MicroConsult GmbH     ***\r\n");
            PRINTSTR("*** wogtest C++ Test harnish ***\r\n");
            PRINTSTR("***      Version ");
            PRINTSTR(STRINGIZE(WOGTEST_VERSION));
            PRINTSTR("       ***\r\n");
            PRINTSTR("***     by Remo Markgraf     ***\r\n");
            PRINTSTR("********************************\r\n");
        };
};
extern gTests gtests;

//******
class TestCase
//******
{
    private:
        Test *pTestList_ = nullptr;
        TestCase *pNext_ = nullptr;
        const char *tcn_;
    public:
        TestCase() = default;
        Test* getpTestList(void) const {return pTestList_;}
        void setpTestList(Test *pTest) {pTestList_=pTest;}
        const char *getTestCaseName(void) const { return tcn_;}
        void setTestCaseName(const char * tcn) { tcn_=tcn;}
        TestCase *getTestCaseNextPtr(void) const {return pNext_;}
        void setTestCaseNextPtr(TestCase *pNext) {pNext_ = pNext;}
        inline uint32_t countNumberOfTests(void) const;
        void runTestCase(void);		
        void printTestCase(uint32_t numOfTests)
        {
            PRINTSTR("[----------] ");
            PRINTSTR(__itos(numOfTests));
            PRINTSTR(" tests of ");
            PRINTSTR(tcn_);
            PRINTSTR("\r\n");
        }
        void printTestCaseFailed(void)
        {
            PRINTSTR("\x1b[41m\x1b[97m[   FAILED ] ");
            PRINTSTR(__itos(gtests.get_tc_failed()));
            PRINTSTR(" tests of ");
            PRINTSTR(tcn_);
            PRINTSTR("\x1b[0m\r\n");
        }			
        void printTestCaseStart(void)
        {
            printTestCase(countNumberOfTests());
        }
        void printTestCaseEnd(void)
        {
            printTestCase(gtests.get_tc_tests());
            if (gtests.is_anyTestCase_failed())
            {
                printTestCaseFailed();
                gtests.flush_message_buffer();
            }
            PRINTSTR("\x1b[0m\r\n");
        }
};

//******
class Test
//******
{
    public:
        Test(const char *ptc, const char *ptn) : ptc_(ptc), ptn_(ptn){}
        Test(void) : Test("","") {}
		virtual ~Test() {}
        void linkinTestintoTestCase(Test& refT)
        {
            //TestCase& getTestCasebyName(gTests &refgT, const char *tcname)
            TestCase &refTC = gtests.TestCasebyName(ptc_);
            //linkin Test into Testlist of TestCase
            pNext_ = refTC.getpTestList();
            refTC.setpTestList(this);
        }
        void printTestNameNl()
        {
            PRINTSTR(ptc_);
            PRINTSTR(".");
            PRINTSTR(ptn_);
            PRINTSTR("\r\n");
        }
        void printTestRun()
        {
            PRINTSTR("\x1b[32m[ RUN      ]\x1b[0m ");
            printTestNameNl();
        }
        void printTestPassed()
        {
            PRINTSTR("\x1b[32m[       OK ]\x1b[0m ");
            printTestNameNl();
        }
        void printTestFailed()
        {
            PRINTSTR("\x1b[31m[  FAILED  ]\x1b[0m ");
            printTestNameNl();
        }
        Test *getNextPtr(void) const {return pNext_;}
        void setTestNames(const char* ptc,const char* ptn) {ptc_=ptc;ptn_=ptn;}
        void runTest(void);
        virtual void run(void) = 0;
        virtual void SetUp(void) {}
        virtual void TearDown(void) {}
        bool is_passed(void) const {return gtests.is_passed();}
        bool is_failed(void) const {return !gtests.is_passed();}
        static bool is_fatal(void) {return gTests::is_fatal();}
        void set_passed(void) {gtests.set_passed();}
    private:
        Test *pNext_ = nullptr; 
        const char *ptc_;
        const char *ptn_;  
};

//******
class Test_Assert
//******
{
    private:
        bool ass_passed_ = true;
        bool ass_fatal_ = false;
        bool ass_first_append_ = true;
    public:
        bool is_passed(void) {return ass_passed_;}
        bool is_failed(void) {return !ass_passed_;}
        bool is_fatal(void) {return ass_fatal_;}
        void set_passed(void) {ass_passed_ = true;}
        void set_failed(void) {ass_passed_ = false; gtests.set_failed();}
        void set_fatal(void) {ass_fatal_ = true; gtests.set_fatal();}
        void reset_ass_first_append(void) {ass_first_append_ = false;}
#ifdef USE_TEMPLATES
    template<typename T>
    Test_Assert& operator<<(const T par)
    {
        if( is_failed())
        {
            if( ass_first_append_ ) gtests.append_message_buffer("\r\n    ");
            reset_ass_first_append();
            gtests.append_message_buffer(par);
        }
        return *this;
    }
#else //USE_TEMPLATES
        //append righthand string to gtests.test_message_buffer
        Test_Assert& operator<<(const char *str)
        {
            if( is_failed())
            {
                if( ass_first_append_ ) gtests.append_message_buffer("\r\n    ");
                reset_ass_first_append();
                gtests.append_message_buffer(str);
            }
            return *this;
        }
        //append righthand integer to gtests.test_message_buffer
        Test_Assert& operator<<(uint32_t num)
        {
            if( is_failed())
            {
                if( ass_first_append_ ) gtests.append_message_buffer("\r\n    ");
                reset_ass_first_append();
                gtests.append_message_buffer(num);
            }
            return *this;
        }
#endif //USE_TEMPLATES
        void operator,(Test_Assert& ref)
        {
            //create void return for operator<< by applying
            //return Test_Assert,Test_Assert << output
        }
        inline Test_Assert& assert_base(uint32_t expected,uint32_t actual,bool cond,const bool ass,const char *msg,const char *file,uint32_t line);
        inline Test_Assert& assert_fail(const char *msg,const bool equ,const bool ass,const char *file,uint32_t line);
        inline Test_Assert& assert_true(const bool cond,const bool equ,const bool ass,const char *file,uint32_t line);
        inline Test_Assert& assert_streq(const char* expected,const char* actual,bool equ,const bool casesense,const bool ass,const char *file,uint32_t line);
#ifdef WOGTEST_FLOAT
		inline Test_Assert& assert_floateq(const float f1,const float f2,const bool ass,const char *f1n,const char *f2n,const char *file,uint32_t line);
        inline Test_Assert& assert_doubleeq(const double d1,const double d2,const bool ass,const char *d1n,const char *d2n,const char *file,uint32_t line);
		inline Test_Assert& assert_near(const double d1,const double d2,const double delta,const bool ass,const char *d1n,const char *d2n,const char *deltan,const char *file,uint32_t line);
	private:
		inline bool floatalmosteq(const float f1,const float f2);
		inline bool doublealmosteq(const double d1,const double d2);
        inline const char ftoc(const float flt, const uint32_t dec);
        inline const char* ftoa(const float flt);
        inline const char dtoc(const double dub, const uint64_t dec);
	public:
        inline const char* dtoa(const double dub);
#endif //WOGTEST_FLOAT
};

///Test_Assert::assert_base
inline Test_Assert& Test_Assert::assert_base(uint32_t expected,uint32_t actual,bool cond,const bool ass,const char *msg,const char *file,uint32_t line)
{
    set_passed();
    gtests.reset_fatal();
    gtests.flush_message_buffer();
    if(!(cond))
    {
        set_failed();
        if( ass ) set_fatal();
        gtests.append_message_failure(file,line,msg);
        gtests.append_message_buffer(", expected: ");
        gtests.append_message_buffer(expected);
        gtests.append_message_buffer(", actual: ");
        gtests.append_message_buffer(actual);
    }
    return *this;
}

///Test_Assert::assert_fail
inline Test_Assert& Test_Assert::assert_fail(const char *msg,const bool equ,const bool ass,const char *file,uint32_t line)
{
    set_passed();
    gtests.reset_fatal();
    gtests.flush_message_buffer();
    if (equ)
    {
        set_failed();
        if( ass ) set_fatal();
        gtests.append_message_failure(file,line,msg);
    }
    else
    {
        set_passed();
        gtests.set_passed();
        gtests.append_message_failure(file,line,msg);
    }
    return *this;
}

///Test_Assert::assert_true
inline Test_Assert& Test_Assert::assert_true(const bool cond,const bool equ,const bool ass,const char *file,uint32_t line)
{
    set_passed();
    gtests.flush_message_buffer();
    if ((cond)!=equ)
    {
        set_failed();
        if( ass ) set_fatal();
        gtests.append_message_failure(file,line,"value is not ");
        if (equ) gtests.append_message_buffer("true");
        else     gtests.append_message_buffer("false");
    }
    return *this;
}

///Test_Assert::assert_streq
inline Test_Assert& Test_Assert::assert_streq(const char* expected,const char* actual,bool equ,const bool casesense,const bool ass,const char *file,uint32_t line)
{
    set_passed();
    //gtests.reset_fatal();
    gtests.flush_message_buffer();
    if(actual == nullptr || expected == nullptr)
    {
        set_failed();
        if(ass) set_fatal();
        gtests.append_message_failure(file,line,"NUll pointer passed in argument");
    }
    else if( casesense )
    {
        if (__streq(expected, actual) != equ)
        {
            set_failed();
            if(ass) set_fatal();
            gtests.append_message_failure(file,line,"");
            if(equ)
            {
                gtests.append_message_buffer("String missmatch\r\n    expected: ");
                gtests.append_message_buffer(expected);
                gtests.append_message_buffer("\r\n    actual  : ");
                gtests.append_message_buffer(actual);
            }
            else
            {
                gtests.append_message_buffer("String unintended match\r\n    expected and current string: ");
                gtests.append_message_buffer(expected);
            }
        }
    }
    else //casesense == false
    {
        if (__strcaseeq(expected, actual) != equ)
        {
            set_failed();
            if(ass) set_fatal();
            gtests.append_message_failure(file,line,"");
            if(equ)
            {
                gtests.append_message_buffer("String caseinsensitive missmatch - expected: ");
                gtests.append_message_buffer(expected);
                gtests.append_message_buffer(", actual: ");
                gtests.append_message_buffer(actual);
            }
            else
            {
                gtests.append_message_buffer("String unintended caseinsensitive match - expected: ");
                gtests.append_message_buffer(expected);
                gtests.append_message_buffer(", actual: ");
                gtests.append_message_buffer(actual);
            }
        }
    }
    return *this;
}

#ifdef WOGTEST_FLOAT
///Helper Test_Assert::ftoc
inline const char Test_Assert::ftoc(const float flt, const uint32_t dec)
{
    return (uint8_t)((uint32_t)((flt-(int32_t)flt)*dec)%10);
}
///Helper Test_Assert::ftoa
inline const char* Test_Assert::ftoa(const float flt)
{
    if( flt > (float)INT_MAX ) return "ERROR:FLOAT_OVERFLOW";
    if( flt < (float)INT_MIN ) return "ERROR:FLOAT_UNDERFLOW";
    static constexpr uint8_t predotbuflen = 14;
    static constexpr uint8_t postdotbuflen = 10;
    static constexpr uint8_t buflen = predotbuflen + postdotbuflen;
    static char buf[buflen];
    for(uint_fast8_t j=0;j < sizeof(buf) ; j++) { buf[j]='\0'; }
    uint_fast8_t i=0;
    float aflt = ( flt < 0 ) ? -flt : flt;
    if (flt < 0) { buf[i++] = '-'; }
    const char* ptr = __itos((int)aflt);
    while (*ptr != '\0') { buf[i++] = *ptr++; }
    if (i >= predotbuflen) { return "ERROR:PRE.BUFFER_OVERFLOW"; }
    buf[i++] = '.';
    for(uint32_t div = 10;div <= 10000000; div *=10)
    {
        buf[i++] = '0' + ftoc(aflt,div);
    }
    buf[i++] = '\0' ;
    return buf;
}
///Helper Test_Assert::dtoc
inline const char Test_Assert::dtoc(const double dub, const uint64_t dec)
{
    return (uint8_t)((uint64_t)((dub-(int64_t)dub)*dec)%10);
}
///Helper Test_Assert::dtoa
inline const char* Test_Assert::dtoa(const double dub)
{
    if( dub > (double)LLONG_MAX ) return "ERROR:DOUBLE_OVERFLOW";
    if( dub < (double)LLONG_MIN ) return "ERROR:DOUBLE_UNDERFLOW";
    static constexpr uint8_t predotbuflen = 20; //sign+19
    static constexpr uint8_t postdotbuflen = 16; //dot+14+0
    static constexpr uint8_t buflen = predotbuflen + postdotbuflen;
    static char buf[buflen];
    for(uint_fast8_t j=0;j < sizeof(buf) ; j++){buf[j]='\0';}
    uint_fast8_t i=0;
    double adub = ( dub < 0 ) ? -dub : dub;
    if( dub < 0 ) { buf[i++] = '-'; }
    const char* ptr = __ltos((int64_t)adub);
    while (*ptr != '\0') { buf[i++] = *ptr++; }
    if (i >= predotbuflen) { return "ERROR:PRE.BUFFER_OVERFLOW"; }
    buf[i++] = '.';
    for(uint64_t div = 10ULL;div <= 1000000000000000ULL; div *=10)
    {
        buf[i++] = '0' + dtoc(adub,div);
    }
    buf[i++] = '\0' ;
    return buf;
}

///Helper Test_Assert::floatalmosteq
inline bool Test_Assert::floatalmosteq(const float f1,const float f2)
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
///Test_Assert::assert_floateq
inline Test_Assert& Test_Assert::assert_floateq(const float f1,const float f2,const bool ass,const char *f1n,const char *f2n,const char *file,uint32_t line)
{
    set_passed();
    gtests.flush_message_buffer();
	if (!floatalmosteq(f1,f2))
    {
        set_failed();
        if(ass) set_fatal();
        gtests.append_message_failure(file,line,"Float missmatch:");        
        gtests.append_message_evaluates_to(f1n,ftoa(f1));       
        gtests.append_message_evaluates_to(f2n,ftoa(f2));
    }
	return *this;
}

///Helper Test_Assert::doublealmosteq
inline bool Test_Assert::doublealmosteq(const double d1,const double d2)
{
    int64_t i1 = *((int64_t*)&d1);
	int64_t i2 = *((int64_t*)&d2);
	// Different signs means they do not match.
    if((i1<0) != (i2<0)) return (i1 == i2);// Check for equality to make sure +0==-0
	// Find the difference in ULPs.
    uint64_t ulpsDiff = ((i1 - i2)>0)?(i1 - i2):-(i1 - i2);
    return (ulpsDiff <= 4u);
}

///Test_Assert::assert_doubleeq
inline Test_Assert& Test_Assert::assert_doubleeq(const double d1,const double d2,const bool ass,const char *d1n,const char *d2n,const char *file,uint32_t line)
{
    set_passed();
    gtests.flush_message_buffer();
	if (!doublealmosteq(d1,d2))
    {
        set_failed();
        if(ass) set_fatal();
        gtests.append_message_failure(file,line,"Double missmatch:");
        gtests.append_message_evaluates_to(d1n,dtoa(d1));
        gtests.append_message_evaluates_to(d2n,dtoa(d2));
    }
	return *this;
}

///Test_Assert::assert_near
inline Test_Assert& Test_Assert::assert_near(const double d1,const double d2,const double delta,const bool ass,const char *d1n,const char *d2n,const char *deltan,const char *file,uint32_t line)
{
    set_passed();
    gtests.flush_message_buffer();
	if((((d1 - d2)>0)?(d1 - d2):-(d1 - d2))>delta)
    {
        set_failed();
        //gtests.reset_passed();
        if(ass) set_fatal();
        gtests.append_message_failure(file,line,"Assert Near Error:");
        gtests.append_message_evaluates_to(d1n,dtoa(d1));
        gtests.append_message_evaluates_to(d2n,dtoa(d2));
        gtests.append_message_evaluates_to(deltan,dtoa(delta));
    }
	return *this;
}
#endif //WOGTEST_FLOAT

///gTests::linkinTestCase
inline void gTests::linkinTestCase(TestCase& refTC)
{
#ifdef SIGNATURE
    if (TCSignature_ != SIGNATURE || pTestCases_ == nullptr)
#else
    if (pTestCases_ == nullptr)
#endif
        refTC.setTestCaseNextPtr(nullptr);
    else
        refTC.setTestCaseNextPtr(pTestCases_);
    pTestCases_ = &refTC;
#ifdef SIGNATURE
    TCSignature_ = SIGNATURE;
#endif //SIGNATURE
}

///gTests::TestCasebyName
inline TestCase& gTests::TestCasebyName(const char *tcname)
{
    //find tc from list
    TestCase *pTC = pTestCases_;
    while( pTC != nullptr )
    {
        //compare name with search parameter
        if( __streq(pTC->getTestCaseName(),tcname) ) return *pTC; 
        pTC = pTC->getTestCaseNextPtr();
    }
    //not found, so create new tc
#if defined(WOGTESTCASES_NUM) && WOGTESTCASES_NUM == DYNAMIC
    pTC = new TestCase;
    //pTC = new(std::nothrow) TestCase;
#else
    pTC = nullptr;
    for(uint_fast8_t tcarray_index = 0; tcarray_index < WOGTESTCASES_NUM; tcarray_index++)
    {
        if( tcarray_[tcarray_index].getTestCaseName() == nullptr )
        {
            pTC = &tcarray_[tcarray_index];
            break;
        }
    }
#endif
    if(pTC==nullptr)
    {
        //*** FATAL ERROR ***
        //No space to allocate new TestCase
        //Increase HEAP size or TESTCASE_NUM in wogtest.hpp
        //No chance to print message, since not jet initialized
        while(1){}
    }
    pTC->setTestCaseName(tcname);
    linkinTestCase(*pTC);
    return *pTC;
}

///gTests::runTests
inline uint32_t gTests::runTests(void)
{
    flush_message_buffer();
    PRINTSTR("\r[==========] TEST RUNNER\r\n");
    TestCase *pPrev = nullptr;
    TestCase *pLast = nullptr;
    while( pLast != pTestCases_ )
    {
        TestCase *pTc = pTestCases_;
        do
        {
            pPrev = pTc;
            pTc = pTc->getTestCaseNextPtr();
        } while( pTc != pLast );
        pPrev->runTestCase();
        pLast = pPrev;
    }
    printSummary();
    //return 0 if all tests passed, 1 otherwise
    if(total_succ_ != total_tests_)
        return 1;
    return 0;
}

///gTests::printSummary
inline void gTests::printSummary(void)
{
    PRINTSTR("[==========] SUMMARY\r\n");
    PRINTSTR("[  TOTAL   ] ");
    PRINTSTR(__itos(total_tests_));
    PRINTSTR(" tests of ");
    PRINTSTR(__itos(total_tcs_));
    PRINTSTR(" testcases\r\n");
    PRINTSTR("[  PASSED  ] ");
    PRINTSTR(__itos(total_succ_));
    PRINTSTR(" tests\r\n");
    PRINTSTR("[  FAILED  ] ");
    PRINTSTR(__itos(get_total_failed()));
    PRINTSTR(" tests\r\n");
    PRINTSTR("[==========]\r\n");
    if (total_succ_ != total_tests_)
    {
        PRINTSTR("\r\n\x1b[41m\x1b[97m  ");
        PRINTSTR(__itos(get_total_failed()));
        PRINTSTR(" FAILED TESTS\x1b[0m\r\n\r\n");
    }
    else
    {
        PRINTSTR("\r\n\x1b[42m\x1b[97m  ALL TESTS PASSED\x1b[0m\r\n\r\n");
    }
}

///gTests::clear_message_buffer
inline void gTests::clear_message_buffer(void)
{
    *test_message_buffer='\0';
}

///gTests::flush_message_buffer
inline void gTests::flush_message_buffer(void)
{
    if( *test_message_buffer !='\0' )
    {
        PRINTSTR(test_message_buffer);
        PRINTSTR("\r\n");
        clear_message_buffer();
    }
}

///Test::runTest
inline void Test::runTest(void)
{
    set_passed();
    //gtests.set_passed();
    gtests.inc_tests();
    printTestRun();
    //call virtual methods of individual test
    //empty defaults for setup/teardown are used if not defined by override
    SetUp();
    run();
    TearDown();
    //if(gtests.is_passed())
    if(is_passed())
    {
        gtests.inc_successTests();
        gtests.clear_message_buffer();
        printTestPassed();
    }
    else
    {
        gtests.flush_message_buffer();
        printTestFailed();
    }
}

///TestCase::countNumberOfTests
inline uint32_t TestCase::countNumberOfTests(void) const
{
    uint32_t numOfTests = 0;
    Test *pTn = pTestList_;
    do
    {
        numOfTests++;
        pTn = pTn->getNextPtr();
    } while( pTn != nullptr );
    return numOfTests;
}

///TestCase::runTestCase
inline void TestCase::runTestCase(void)
{
    printTestCaseStart();
    gtests.reset_testcases();
    gtests.inc_testcases();  
    Test *pPrev = nullptr;
    Test *pLast = nullptr;
    while( pLast != pTestList_ )
    {
        Test *pTn = pTestList_;
        do
        {
            pPrev = pTn;
            pTn = pTn->getNextPtr();
        } while( pTn != pLast );
        pPrev->runTest(); //execute Test
        pLast = pPrev;
    }  
    printTestCaseEnd();
    gtests.sumup_TestCase();
}

} //namespace testing
using namespace testing;

///RUN_ALL_TESTS
#define RUN_ALL_TESTS() testing::gtests.runTests();

///TEST 
#define TEST(tc,tn)\
    class tc##_##tn##_Test : public testing::Test {\
    public: tc##_##tn##_Test(const char *ptc, const char *ptn):Test(ptc,ptn){\
            linkinTestintoTestCase(*this);}\
            void run(void) override; };\
    tc##_##tn##_Test tc##_##tn##_TestObj(#tc,#tn);\
    void tc##_##tn##_Test::run()
        
///TEST_F
//ptc_ = #tc; ptn_ = #tn;       
#define TEST_F(tc,tn)\
    class tc##_##tn##_Test : public tc {\
    public: tc##_##tn##_Test(const char *ptc, const char *ptn){\
            setTestNames(ptc,ptn);\
            linkinTestintoTestCase(*this);}\
            void run(void) override; };\
    tc##_##tn##_Test tc##_##tn##_TestObj(#tc,#tn);\
    void tc##_##tn##_Test::run()

////EXPECT_FAIL and EXPECT_SUCCESS
#define EXPECT_FAIL(msg) EXPECT_FAILn(msg,true,false)
#define EXPECT_SUCCESS(msg) EXPECT_FAILn(msg,false,false)
#define EXPECT_FAILn(msg,equ,ass) EXPECT_FAILnn(msg,equ,ass,__FILE__,__LINE__)
#define EXPECT_FAILnn(msg,equ,ass,file,line) EXPECT_FAILnnn(msg,equ,ass,file,line)
#define EXPECT_FAILnnn(msg,equ,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_fail(msg,equ,ass,file,line)
////ASSERT_FAIL and ASSERT_SUCCESS
#define ASSERT_FAIL(msg) ASSERT_FAILn(msg,true,true)
#define ASSERT_SUCCESS(msg) ASSERT_FAILn(msg,false,true)
#define ASSERT_FAILn(msg,equ,ass) ASSERT_FAILnn(msg,equ,ass,__FILE__,__LINE__)
#define ASSERT_FAILnn(msg,equ,ass,file,line) ASSERT_FAILnnn(msg,equ,ass,file,line)
#define ASSERT_FAILnnn(msg,equ,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_fail(msg,equ,ass,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line
    
///EXPECT_TRUE and EXPECT_FALSE
#define EXPECT_TRUE(cond)  EXPECT_TRUEn(cond,true,false)
#define EXPECT_FALSE(cond) EXPECT_TRUEn(cond,false,false)    
#define EXPECT_TRUEn(cond,equ,ass) EXPECT_TRUEnn(cond,equ,ass,__FILE__,__LINE__)
#define EXPECT_TRUEnn(cond,equ,ass,file,line) EXPECT_TRUEnnn(cond,equ,ass,file,line)
#define EXPECT_TRUEnnn(cond,equ,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_true(cond,equ,ass,file,line)
///ASSERT_TRUE and ASSERT_FALSE
#define ASSERT_TRUE(cond) ASSERT_TRUEn(cond,true,true)
#define ASSERT_FALSE(cond) ASSERT_TRUEn(cond,false,true)
#define ASSERT_TRUEn(cond,equ,ass) ASSERT_TRUEnn(cond,equ,ass,__FILE__,__LINE__)
#define ASSERT_TRUEnn(cond,equ,ass,file,line) ASSERT_TRUEnnn(cond,equ,ass,file,line)
#define ASSERT_TRUEnnn(cond,equ,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_true(cond,equ,ass,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXPECT_EQ
#define EXPECT_EQ(expected,actual) EXPECT_EQn(expected,actual,false)    
#define EXPECT_EQn(expected,actual,ass) EXPECT_EQnn(expected,actual,ass,__FILE__,__LINE__)
#define EXPECT_EQnn(expected,actual,ass,file,line) EXPECT_EQnnn(expected,actual,ass,file,line)
#define EXPECT_EQnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected==actual,ass,"Wrong value, expected to be equal",file,line)
///ASSERT_EQ
#define ASSERT_EQ(expected,actual) ASSERT_EQn(expected,actual,true)   
#define ASSERT_EQn(expected,actual,ass) ASSERT_EQnn(expected,actual,ass,__FILE__,__LINE__)
#define ASSERT_EQnn(expected,actual,ass,file,line) ASSERT_EQnnn(expected,actual,ass,file,line)
#define ASSERT_EQnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected==actual,ass,"Wrong value, expected to be equal",file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXPECT_NE
#define EXPECT_NE(expected,actual) EXPECT_NEn(expected,actual,false) 
#define EXPECT_NEn(expected,actual,ass) EXPECT_NEnn(expected,actual,ass,__FILE__,__LINE__)
#define EXPECT_NEnn(expected,actual,ass,file,line) EXPECT_NEnnn(expected,actual,ass,file,line)
#define EXPECT_NEnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected!=actual,ass,"Wrong value, expected to be unequal",file,line)
///ASSERT_NE
#define ASSERT_NE(expected,actual) ASSERT_NEn(expected,actual,true)
#define ASSERT_NEn(expected,actual,ass) ASSERT_NEnn(expected,actual,ass,__FILE__,__LINE__)
#define ASSERT_NEnn(expected,actual,ass,file,line) ASSERT_NEnnn(expected,actual,ass,file,line)
#define ASSERT_NEnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected!=actual,ass,"Wrong value, expected to be unequal",file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXPECT_GT
#define EXPECT_GT(expected,actual) EXPECT_GTn(expected,actual,false)    
#define EXPECT_GTn(expected,actual,ass) EXPECT_GTnn(expected,actual,ass,__FILE__,__LINE__)
#define EXPECT_GTnn(expected,actual,ass,file,line) EXPECT_GTnnn(expected,actual,ass,file,line)
#define EXPECT_GTnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected>actual,ass,"Wrong value, expected to be bigger",file,line)
///ASSERT_GT
#define ASSERT_GT(expected,actual) ASSERT_GTn(expected,actual,true)
#define ASSERT_GTn(expected,actual,ass) ASSERT_GTnn(expected,actual,ass,__FILE__,__LINE__)
#define ASSERT_GTnn(expected,actual,ass,file,line) ASSERT_GTnnn(expected,actual,ass,file,line)
#define ASSERT_GTnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected>actual,ass,"Wrong value, expected to be bigger",file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXPECT_GE
#define EXPECT_GE(expected,actual) EXPECT_GEn(expected,actual,false)    
#define EXPECT_GEn(expected,actual,ass) EXPECT_GEnn(expected,actual,ass,__FILE__,__LINE__)
#define EXPECT_GEnn(expected,actual,ass,file,line) EXPECT_GEnnn(expected,actual,ass,file,line)
#define EXPECT_GEnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected>=actual,ass,"Wrong value, expected to be bigger or equal",file,line)
///ASSERT_GE
#define ASSERT_GE(expected,actual) ASSERT_GEn(expected,actual,true)
#define ASSERT_GEn(expected,actual,ass) ASSERT_GEnn(expected,actual,ass,__FILE__,__LINE__)
#define ASSERT_GEnn(expected,actual,ass,file,line) ASSERT_GEnnn(expected,actual,ass,file,line)
#define ASSERT_GEnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected>=actual,ass,"Wrong value, expected to be bigger or equal",file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXPECT_LT
#define EXPECT_LT(expected,actual) EXPECT_LTn(expected,actual,false)    
#define EXPECT_LTn(expected,actual,ass) EXPECT_LTnn(expected,actual,ass,__FILE__,__LINE__)
#define EXPECT_LTnn(expected,actual,ass,file,line) EXPECT_LTnnn(expected,actual,ass,file,line)
#define EXPECT_LTnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected<actual,ass,"Wrong value, expected to be smaller",file,line)
///ASSERT_LT
#define ASSERT_LT(expected,actual) ASSERT_LTn(expected,actual,true)   
#define ASSERT_LTn(expected,actual,ass) ASSERT_LTnn(expected,actual,ass,__FILE__,__LINE__)
#define ASSERT_LTnn(expected,actual,ass,file,line) ASSERT_LTnnn(expected,actual,ass,file,line)
#define ASSERT_LTnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected<actual,ass,"Wrong value, expected to be smaller",file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXPECT_LE
#define EXPECT_LE(expected,actual) EXPECT_LEn(expected,actual,false)    
#define EXPECT_LEn(expected,actual,ass) EXPECT_LEnn(expected,actual,ass,__FILE__,__LINE__)
#define EXPECT_LEnn(expected,actual,ass,file,line) EXPECT_LEnnn(expected,actual,ass,file,line)
#define EXPECT_LEnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected<=actual,ass,"Wrong value, expected to be smaller or equal",file,line)
///ASSERT_LE
#define ASSERT_LE(expected,actual) ASSERT_LEn(expected,actual,true)
#define ASSERT_LEn(expected,actual,ass) ASSERT_LEnn(expected,actual,ass,__FILE__,__LINE__)
#define ASSERT_LEnn(expected,actual,ass,file,line) ASSERT_LEnnn(expected,actual,ass,file,line)
#define ASSERT_LEnnn(expected,actual,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_base(expected,actual,expected<=actual,ass,"Wrong value, expected to be smaller or equal",file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

//STRING ASSERTIONS
///EXPECT_STREQ and EXPECT_STRNE
#define EXPECT_STREQ(expected,actual) EXPECT_STREQn(expected,actual,true,false)
#define EXPECT_STRNE(expected,actual) EXPECT_STREQn(expected,actual,false,false)
#define EXPECT_STREQn(expected,actual,equ,ass) EXPECT_STREQnn(expected,actual,equ,ass,__FILE__,__LINE__)
#define EXPECT_STREQnn(expected,actual,equ,ass,file,line) EXPECT_STREQnnn(expected,actual,equ,ass,file,line)
#define EXPECT_STREQnnn(expected,actual,equ,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_streq(expected,actual,equ,true,ass,file,line)
///ASSERT_STREQ and ASSERT_STRNE
#define ASSERT_STREQ(expected,actual) ASSERT_STREQn(expected,actual,true,true)
#define ASSERT_STRNE(expected,actual) ASSERT_STREQn(expected,actual,false,true)
#define ASSERT_STREQn(expected,actual,equ,ass) ASSERT_STREQnn(expected,actual,equ,ass,__FILE__,__LINE__)
#define ASSERT_STREQnn(expected,actual,equ,ass,file,line) ASSERT_STREQnnn(expected,actual,equ,ass,file,line)
#define ASSERT_STREQnnn(expected,actual,equ,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_streq(expected,actual,equ,true,ass,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line
///EXPECT_STRCASEEQ and EXPECT_STRCASENE
#define EXPECT_STRCASEEQ(expected,actual) EXPECT_STRCASEEQn(expected,actual,true,false)
#define EXPECT_STRCASENE(expected,actual) EXPECT_STRCASEEQn(expected,actual,false,false)
#define EXPECT_STRCASEEQn(expected,actual,equ,ass) EXPECT_STRCASEEQnn(expected,actual,equ,ass,__FILE__,__LINE__)
#define EXPECT_STRCASEEQnn(expected,actual,equ,ass,file,line) EXPECT_STRCASEEQnnn(expected,actual,equ,ass,file,line)
#define EXPECT_STRCASEEQnnn(expected,actual,equ,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_streq(expected,actual,equ,false,ass,file,line)
///ASSERT_STRCASEEQ and ASSERT_STRCASENE
#define ASSERT_STRCASEEQ(expected,actual) ASSERT_STRCASEEQn(expected,actual,true,true)
#define ASSERT_STRCASENE(expected,actual) ASSERT_STRCASEEQn(expected,actual,false,true)
#define ASSERT_STRCASEEQn(expected,actual,equ,ass) ASSERT_STRCASEEQnn(expected,actual,equ,ass,__FILE__,__LINE__)
#define ASSERT_STRCASEEQnn(expected,actual,equ,ass,file,line) ASSERT_STRCASEEQnnn(expected,actual,equ,ass,file,line)
#define ASSERT_STRCASEEQnnn(expected,actual,equ,ass,file,line)\
    Test_Assert Test_AssertObj##line;\
    Test_AssertObj##line.assert_streq(expected,actual,equ,false,ass,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

//FLOATING POINT ASSERTIONS
///EXPECT_FLOAT_EQ
#define EXPECT_FLOAT_EQ(f1,f2) EXPECT_FLOATEQn(f1,f2,false)
#define EXPECT_FLOATEQn(f1,f2,ass) EXPECT_FLOATEQnn(f1,f2,ass,#f1,#f2,__FILE__,__LINE__)
#define EXPECT_FLOATEQnn(f1,f2,ass,f1n,f2n,file,line) EXPECT_FLOATEQnnn(f1,f2,ass,f1n,f2n,file,line)
#define EXPECT_FLOATEQnnn(f1,f2,ass,f1n,f2n,file,line)\
	Test_Assert Test_AssertObj##line;\
	Test_AssertObj##line.assert_floateq(f1,f2,ass,f1n,f2n,file,line)
///ASSERT_FLOAT_EQ
#define ASSERT_FLOAT_EQ(f1,f2) ASSERT_FLOATEQn(f1,f2,true)
#define ASSERT_FLOATEQn(f1,f2,ass) ASSERT_FLOATEQnn(f1,f2,ass,#f1,#f2,__FILE__,__LINE__)
#define ASSERT_FLOATEQnn(f1,f2,ass,f1n,f2n,file,line) ASSERT_FLOATEQnnn(f1,f2,ass,f1n,f2n,file,line)
#define ASSERT_FLOATEQnnn(f1,f2,ass,f1n,f2n,file,line)\
	Test_Assert Test_AssertObj##line;\
	Test_AssertObj##line.assert_floateq(f1,f2,ass,f1n,f2n,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXPECT_DOUBLE_EQ
#define EXPECT_DOUBLE_EQ(d1,d2) EXPECT_DOUBLEEQn(d1,d2,false)
#define EXPECT_DOUBLEEQn(d1,d2,ass) EXPECT_DOUBLEEQnn(d1,d2,ass,#d1,#d2,__FILE__,__LINE__)
#define EXPECT_DOUBLEEQnn(d1,d2,ass,d1n,d2n,file,line) EXPECT_DOUBLEEQnnn(d1,d2,ass,d1n,d2n,file,line)
#define EXPECT_DOUBLEEQnnn(d1,d2,ass,d1n,d2n,file,line)\
	Test_Assert Test_AssertObj##line;\
	Test_AssertObj##line.assert_doubleeq(d1,d2,ass,d1n,d2n,file,line)
///ASSERT_DOUBLE_EQ
#define ASSERT_DOUBLE_EQ(d1,d2) ASSERT_DOUBLEEQn(d1,d2,true)
#define ASSERT_DOUBLEEQn(d1,d2,ass) ASSERT_DOUBLEEQnn(d1,d2,ass,#d1,#d2,__FILE__,__LINE__)
#define ASSERT_DOUBLEEQnn(d1,d2,ass,d1n,d2n,file,line) ASSERT_DOUBLEEQnnn(d1,d2,ass,d1n,d2n,file,line)
#define ASSERT_DOUBLEEQnnn(d1,d2,ass,d1n,d2n,file,line)\
	Test_Assert Test_AssertObj##line;\
	Test_AssertObj##line.assert_doubleeq(d1,d2,ass,d1n,d2n,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXPECT_NEAR
#define EXPECT_NEAR(f1,f2,delta) EXPECT_NEARn(f1,f2,delta,false)
#define EXPECT_NEARn(f1,f2,delta,ass) EXPECT_NEARnn(f1,f2,delta,ass,#f1,#f2,#delta,__FILE__,__LINE__)
#define EXPECT_NEARnn(f1,f2,delta,ass,f1n,f2n,deltan,file,line) EXPECT_NEARnnn(f1,f2,delta,ass,f1n,f2n,deltan,file,line) 
#define EXPECT_NEARnnn(f1,f2,delta,ass,f1n,f2n,deltan,file,line)\
	Test_Assert Test_AssertObj##line;\
	Test_AssertObj##line.assert_near(f1,f2,delta,ass,f1n,f2n,deltan,file,line)
///ASSERT_NEAR
#define ASSERT_NEAR(f1,f2,delta) ASSERT_NEARn(f1,f2,delta,true)
#define ASSERT_NEARn(f1,f2,delta,ass) ASSERT_NEARnn(f1,f2,delta,ass,#f1,#f2,#delta,__FILE__,__LINE__)
#define ASSERT_NEARnn(f1,f2,delta,ass,f1n,f2n,deltan,file,line) ASSERT_NEARnnn(f1,f2,delta,ass,f1n,f2n,deltan,file,line) 
#define ASSERT_NEARnnn(f1,f2,delta,ass,f1n,f2n,deltan,file,line)\
	Test_Assert Test_AssertObj##line;\
	Test_AssertObj##line.assert_near(f1,f2,delta,ass,f1n,f2n,deltan,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line

///EXCEPTION TRY/CATCH TESTS
///EXPECT_NO_THROW
#define EXPECT_NO_THROW(method) EXPECT_NO_THROWn(method,false)
#define EXPECT_NO_THROWn(method,ass) EXPECT_NO_THROWnn(method,ass,__FILE__,__LINE__)
#define EXPECT_NO_THROWnn(method,ass,file,line) EXPECT_NO_THROWnnn(method,ass,file,line)
#define EXPECT_NO_THROWnnn(method,ass,file,line)\
    bool __except##line = false;\
    try{method;}\
    catch(...){__except##line = true;}\
    Test_Assert Test_AssertObj##line;\
    if(__except##line)Test_AssertObj##line.assert_fail("EXCEPTION THROWN",true,ass,file,line)

///ASSERT_NO_THROW
#define ASSERT_NO_THROW(method) ASSERT_NO_THROWn(method,true)
#define ASSERT_NO_THROWn(method,ass) ASSERT_NO_THROWnn(method,ass,__FILE__,__LINE__)
#define ASSERT_NO_THROWnn(method,ass,file,line) ASSERT_NO_THROWnnn(method,ass,file,line)
#define ASSERT_NO_THROWnnn(method,ass,file,line)\
    bool __except##line = false;\
    try{method;}\
    catch(...){__except##line = true;}\
    Test_Assert Test_AssertObj##line;\
    if(__except##line)Test_AssertObj##line.assert_fail("EXCEPTION THROWN",true,ass,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line
    
///EXPECT_THROW
#define EXPECT_THROW(method,exc) EXPECT_THROWn(method,exc,false)
#define EXPECT_THROWn(method,exc,ass) EXPECT_THROWnn(method,exc,ass,__FILE__,__LINE__)
#define EXPECT_THROWnn(method,exc,ass,file,line) EXPECT_THROWnnn(method,exc,ass,file,line)
#define EXPECT_THROWnnn(method,exc,ass,file,line)\
    bool __except##line = false;\
    const char *__msg##line = "NO EXCEPTION THROWN";\
    try{method;}\
    catch(exc){__except##line = true;}\
    catch(...){__msg##line="UNEXPECTED EXCEPTION THROWN";}\
    Test_Assert Test_AssertObj##line;\
    if(!__except##line) Test_AssertObj##line.assert_fail(__msg##line,true,ass,file,line)    
///ASSERT_THROW
#define ASSERT_THROW(method,exc) ASSERT_THROWn(method,exc,true)
#define ASSERT_THROWn(method,exc,ass) ASSERT_THROWnn(method,exc,ass,__FILE__,__LINE__)
#define ASSERT_THROWnn(method,exc,ass,file,line) ASSERT_THROWnnn(method,exc,ass,file,line)
#define ASSERT_THROWnnn(method,exc,ass,file,line)\
    bool __except##line = false;\
    const char *__msg##line = "NO EXCEPTION THROWN";\
    try{method;}\
    catch(exc){__except##line = true;}\
    catch(...){__msg##line="UNEXPECTED EXCEPTION THROWN";}\
    Test_Assert Test_AssertObj##line;\
    if(!__except##line) Test_AssertObj##line.assert_fail(__msg##line,true,ass,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line  
    
///EXPECT_ANY_THROW
#define EXPECT_ANY_THROW(method) EXPECT_ANY_THROWn(method,false)
#define EXPECT_ANY_THROWn(method,ass) EXPECT_ANY_THROWnn(method,ass,__FILE__,__LINE__)
#define EXPECT_ANY_THROWnn(method,ass,file,line) EXPECT_ANY_THROWnnn(method,ass,file,line)
#define EXPECT_ANY_THROWnnn(method,ass,file,line)\
    bool __except##line = false;\
    try{method;}\
    catch(...){__except##line = true;}\
    Test_Assert Test_AssertObj##line;\
    if(!__except##line) Test_AssertObj##line.assert_fail("NO EXCEPTION THROWN",true,ass,file,line)    
///ASSERT_ANY_THROW
#define ASSERT_ANY_THROW(method) ASSERT_ANY_THROWn(method,true)
#define ASSERT_ANY_THROWn(method,ass) ASSERT_ANY_THROWnn(method,ass,__FILE__,__LINE__)
#define ASSERT_ANY_THROWnn(method,ass,file,line) ASSERT_ANY_THROWnnn(method,ass,file,line)
#define ASSERT_ANY_THROWnnn(method,ass,file,line)\
    bool __except##line = false;\
    try{method;}\
    catch(...){__except##line = true;}\
    Test_Assert Test_AssertObj##line;\
    if(!__except##line) Test_AssertObj##line.assert_fail("NO EXCEPTION THROWN",true,ass,file,line);\
    if(Test_AssertObj##line.is_fatal())return Test_AssertObj##line,Test_AssertObj##line  
    
//HASxyzFailure to exit subroutines or TESTs
// e.g. if(HasFailure()) return;
#define HasFatalFailure()     is_fatal()
#define HasNonfatalFailure() (is_failed() && !is_fatal())
#define HasFailure()          is_failed()

//Explicit Success and Failure
#define SUCCEED() ASSERT_SUCCESS("SUCCEEDED")
#define FAIL() ASSERT_FAIL("FAILED")
#define ADD_FAILURE() EXPECT_FAIL("FAILURE ADDED")
#define ADD_FAILURE_AT(file,line) EXPECT_FAILnn("FAILURE ADDED AT",true,false,file,line)
    
#endif  // WOGTEST_HPP_
