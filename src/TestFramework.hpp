#pragma once

#include <cstdio>
#include <utility>
#include <vector>
#include <functional>

#if defined( EXPECTED ) ||\
	defined( EXPECTED_CSTRING ) ||\
	defined( DECLARE_TEST_FUNC ) ||\
	defined( DECLARE_TEST_RUNNER )
#error unexpected declaration of macro
#endif

#define EXPECTED( cond ) 								\
	if( !( cond ) ) 	 								\
		return -1;

#define EXPECTED_CSTRING( result, expected ) 			\
	EXPECTED( strcmp( result, expected ) == 0 )

#define DECLARE_TEST_FUNC( name, ... ) 					\
	trgm::TestPrototype									\
	{ 													\
		[]() -> int 									\
		{ 												\
			__VA_ARGS__; 								\
			return 0; 									\
		}, 												\
		#name 											\
	}

#define DECLARE_TEST_RUNNER( ... ) 						\
	int main( int, char** ) 							\
	{													\
		auto tests = std::vector< trgm::TestPrototype >	\
		{ 												\
			__VA_ARGS__									\
		}; 												\
		return trgm::RunAllTests( tests );				\
	}

namespace trgm
{
	using TestFunc		= std::function< int () >;

	struct TestPrototype
	{
		TestFunc 		func;
		const char*		name;
	};

	inline int RunAllTests( const std::vector< TestPrototype >& tests )
	{
		int runResult = 0;

		for( size_t i = 0; i < tests.size(); i++ )
		{
			fprintf( stderr, "running test [%zu/%zu] %s ", i + 1, tests.size(), tests[ i ].name );
			if( tests[ i ].func() < 0 )
			{
				runResult = -1;
				fprintf( stderr, "[FAIL]\n" );
			}
			else
			{
				fprintf( stderr, "[OK]\n" );
			}
		}

		fprintf( stderr, "tests done.\n" );
		return runResult;
	}
}
