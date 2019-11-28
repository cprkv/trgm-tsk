#pragma once
#include <cstdio>
#include <utility>
#include <vector>
#include <functional>

//	Simple testing framework.
//	I wrote it because of task requirement: "без каких либо сторонних библиотек".

#if defined( TRGM_EXPECTED ) ||\
	defined( TRGM_EXPECTED_CSTRING ) ||\
	defined( TRGM_NOT_EXPECTED_CSTRING ) ||\
	defined( TRGM_DECLARE_TEST_FUNC ) ||\
	defined( TRGM_DECLARE_TEST_GROUP )
#error unexpected declaration of macro
#endif

#define TRGM_EXPECTED( cond ) 														\
	if( !( cond ) ) 	 															\
	{																				\
	 	fprintf( stderr, "\n\texpected value of\n\t\t%s\n\tto be true\n", #cond );	\
		__testRunResult = -1; 														\
	}

#define TRGM_EXPECTED_CSTRING( result, expected ) 									\
	TRGM_EXPECTED( strcmp( result, expected ) == 0 )

#define TRGM_NOT_EXPECTED_CSTRING( result, expected ) 								\
	TRGM_EXPECTED( strcmp( result, expected ) != 0 )

#define TRGM_DECLARE_TEST_FUNC( name, ... ) 										\
	trgm::TestPrototype																\
	{ 																				\
		#name, 																		\
		[]() -> int 																\
		{ 																			\
			int __testRunResult = 0;												\
			__VA_ARGS__; 															\
			return __testRunResult; 												\
		}, 																			\
	}

#define TRGM_DECLARE_TEST_GROUP( name, ... )										\
	static struct name																\
	{																				\
		name()																		\
		{																			\
			auto groupTests = std::vector< trgm::TestPrototype>{ __VA_ARGS__ }; 	\
			auto group = trgm::TestGroup{ #name, std::move( groupTests ) };			\
			trgm::testGroups.push_back( std::move( group ) );						\
		}																			\
	} name##Instance;


namespace trgm {

	struct TestPrototype
	{
		const char*						m_name;
		std::function< int () >			m_func;
	};

	struct TestGroup
	{
		const char*						m_name;
		std::vector< TestPrototype >	m_tests;
	};

	extern std::vector< TestGroup >		testGroups;

}	// namespace trgm
