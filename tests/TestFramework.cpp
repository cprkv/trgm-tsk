#include "TestFramework.hpp"
#include <iostream> // std::cout
#include <vector>	// std::vector

using namespace trgm;

static std::vector<TestCase>& GetGlobalTestCaseContainer()
{
	static std::vector<TestCase> testCases;
	return testCases;
}

TestCase trgm::RegisterGlobalTestCase( TestCase testCase )
{
	GetGlobalTestCaseContainer().push_back( testCase );
	return testCase;
}

TestCaseResult trgm::RunTests()
{
	const auto& testCases = GetGlobalTestCaseContainer();
	auto		runResult = TestCaseResult::OK;

	for( size_t i = 0; i < testCases.size(); ++i )
	{
		std::cout << '[' << i + 1 << '/' << testCases.size() << "] " << testCases[i].m_name << "... ";

		const char* namedResult = "OK";
		const auto	result		= testCases[i].m_func();

		if( result != TestCaseResult::OK )
		{
			runResult	= TestCaseResult::FAILED;
			namedResult = "FAIL";
		}

		std::cout << namedResult << '\n';
	}

	return runResult;
}
