#pragma once
#include <cstring>	// strcmp
#include <iostream> // std::cerr

//	Very compact and simple testing framework.
//	I wrote it because of task requirement: "без каких либо сторонних библиотек".

#define TRGM_REQUIRE( cond )                                                 \
	if( !( cond ) )                                                          \
	{                                                                        \
		std::cerr << "\n\texpected value of\n\t\t" #cond "\n\tto be true\n"; \
		return TestCaseResult::FAILED;                                       \
	}

#define TRGM_REQUIRE_CSTRING( result, expected ) \
	TRGM_REQUIRE( strcmp( result, expected ) == 0 )

#define TRGM_NOT_EXPECTED_CSTRING( result, expected ) \
	TRGM_REQUIRE( strcmp( result, expected ) != 0 )

#define TRGM_TOKEN_CONCAT_1( x, y ) x##y
#define TRGM_TOKEN_CONCAT( x, y ) TRGM_TOKEN_CONCAT_1( x, y )

#define TRGM_REGISTER_TEST_CASE( func )                                \
	static trgm::TestCase TRGM_TOKEN_CONCAT( g_testCase_, __LINE__ ) = \
		trgm::RegisterGlobalTestCase( trgm::TestCase{ #func, func } )

namespace trgm
{
	enum class TestCaseResult
	{
		OK,
		FAILED,
	};

	struct TestCase
	{
		const char* m_name;
		TestCaseResult ( *m_func )();
	};

	TestCase	   RegisterGlobalTestCase( TestCase testCase );
	TestCaseResult RunTests();

} // namespace trgm
