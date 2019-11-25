#include "TestFramework.hpp"

using namespace trgm;

std::vector< TestGroup > trgm::testGroups;

static int RunTestsInGroup( const char* groupName, 
							const std::vector< TestPrototype >& tests )
{
	int runResult = 0;

	for( size_t i = 0; i < tests.size(); i++ )
	{
		const char* namedResult = "OK";

		if( tests[ i ].func() < 0 )
		{
			runResult	= -1;
			namedResult	= "FAIL";
		}

		fprintf( stderr, "[%zu/%zu][%s]\t%s - %s\n",
					i + 1,
					tests.size(),
					namedResult,
					groupName,
					tests[ i ].name );
	}

	return runResult;
}

int main( int argc, char** argv )
{
	int runResult = 0;

	for( auto& group : testGroups )
	{
		auto res = RunTestsInGroup( group.name, group.tests );
		if( res < 0 )
			runResult = res;
	}

	if( runResult < 0 )
		fprintf( stderr, "[SOME FAIL]\n" );
	else
		fprintf( stderr, "[ALL OK]\n" );

	fflush( stderr );
	return runResult;
}
