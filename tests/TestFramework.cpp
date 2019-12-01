#include "TestFramework.hpp"

using namespace trgm;

int TestGroup::Run()
{
	int runResult = 0;

	fprintf( stderr, "\n[GROUP]\t\t%s\n", m_name );

	for( size_t i = 0; i < m_tests.size(); i++ )
	{
		const char* namedResult = "OK";

		if( m_tests[ i ].m_func() < 0 )
		{
			runResult	= -1;
			namedResult	= "FAIL";
		}

		fprintf( stderr, "[%2zu/%2zu] [%s]\t%s\n", i + 1, m_tests.size(), namedResult, m_tests[ i ].m_name );
	}

	return runResult;
}

int trgm::RunGroups( std::vector< TestGroup > testGroups )
{
	int runResult = 0;

	for( auto& group : testGroups )
	{
		auto res = group.Run();
		if( res < 0 )
			runResult = res;
	}

	fprintf( stderr, "\n" );

	if( runResult < 0 )
		fprintf( stderr, "[SOME FAIL]\n" );
	else
		fprintf( stderr, "[ALL OK]\n" );

	fflush( stderr );
	return runResult;
}
