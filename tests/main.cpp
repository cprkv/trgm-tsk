#include "TestFramework.hpp"
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE

using namespace trgm;

int main( int, char** )
{
	const auto result = RunTests();
	return result == TestCaseResult::OK
			   ? EXIT_SUCCESS
			   : EXIT_FAILURE;
}
