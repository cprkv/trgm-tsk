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
	defined( TRGM_DECLARE_TEST_FUNC )
#error unexpected declaration of macro
#endif

#define TRGM_EXPECTED( cond ) 														\
	if( !( cond ) ) 	 															\
	{																				\
	 	fprintf( stderr, "\n\texpected value of\n\t\t%s\n\tto be true\n", #cond );	\
		return -1; 																	\
	}

#define TRGM_EXPECTED_CSTRING( result, expected ) 									\
	TRGM_EXPECTED( strcmp( result, expected ) == 0 )

#define TRGM_NOT_EXPECTED_CSTRING( result, expected ) 								\
	TRGM_EXPECTED( strcmp( result, expected ) != 0 )

#define TRGM_DECLARE_TEST_FUNC( name, ... ) 										\
	trgm::TestPrototype																\
	{ 																				\
		name, 																		\
		[]() -> int 																\
		{ 																			\
			int __testRunResult = 0;												\
			__VA_ARGS__; 															\
			return __testRunResult; 												\
		}, 																			\
	}

namespace trgm {

	struct TestPrototype
	{
		const char*				m_name;
		std::function< int() >	m_func;
	};

	class TestGroup
	{
	public:
		using					Tests					= std::vector< TestPrototype >;

	public:
								TestGroup( const char* name, Tests&& tests ) : m_name( name ), m_tests( tests ) {};
								~TestGroup()			= default;

		int						Run();

	private:
		const char*				m_name;
		Tests					m_tests;
	};

	using						TestGroups				= std::vector< TestGroup >;

	int 						RunGroups( TestGroups&& testGroups );

}	// namespace trgm
