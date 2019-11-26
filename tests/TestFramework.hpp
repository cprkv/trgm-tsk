#pragma once
#include <cstdio>
#include <utility>
#include <vector>
#include <functional>

//	Simple testing framework.
//	I wrote it because of task requirement: "без каких либо сторонних библиотек".

#if defined( EXPECTED ) ||\
	defined( EXPECTED_CSTRING ) ||\
	defined( NOT_EXPECTED_CSTRING ) ||\
	defined( DECLARE_TEST_FUNC ) ||\
	defined( DECLARE_TEST_GROUP )
#error unexpected declaration of macro
#endif

#define EXPECTED( cond ) 															\
	if( !( cond ) ) 	 															\
	{																				\
	 	fprintf( stderr, "\n\texpected value of\n\t\t%s\n\tto be true\n", #cond );	\
		__testRunResult = -1; 														\
	}

#define EXPECTED_CSTRING( result, expected ) 										\
	EXPECTED( strcmp( result, expected ) == 0 )

#define NOT_EXPECTED_CSTRING( result, expected ) 									\
	EXPECTED( strcmp( result, expected ) != 0 )

#define DECLARE_TEST_FUNC( name, ... ) 												\
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

#define DECLARE_TEST_GROUP( name, ... )												\
	static struct name																\
	{																				\
		name()																		\
		{																			\
			auto groupTests = std::vector< trgm::TestPrototype>{ __VA_ARGS__ }; 	\
			auto group = trgm::TestGroup{ #name, std::move( groupTests ) };			\
			trgm::testGroups.push_back( std::move( group ) );						\
		}																			\
	} name##Instance;

namespace trgm
{
	struct TestPrototype
	{
		const char*						name;
		std::function< int () >			func;
	};

	struct TestGroup
	{
		const char*						name;
		std::vector< TestPrototype >	tests;
	};

	extern std::vector< TestGroup >		testGroups;
}
