#include "TestFramework.hpp"
#include "String.hpp"

using namespace trgm;

static TestCaseResult ComparatorsReturnsTrueOnSingleCharacterStrings()
{
	TRGM_REQUIRE( comparators::CaseInsensitive( String{ "a" }, String{ "B" } ) );
	TRGM_REQUIRE( comparators::CaseInsensitive( String{ "a" }, String{ "b" } ) );
	TRGM_REQUIRE( comparators::CaseInsensitive( String{ "A" }, String{ "b" } ) );
	TRGM_REQUIRE( comparators::CaseInsensitive( String{ "A" }, String{ "B" } ) );
	return TestCaseResult::OK;
}

static TestCaseResult InverseComparatorsReturnsFalseOnSingleCharacterStrings()
{
	TRGM_REQUIRE( !comparators::CaseInsensitiveInverse( String{ "a" }, String{ "B" } ) );
	TRGM_REQUIRE( !comparators::CaseInsensitiveInverse( String{ "a" }, String{ "b" } ) );
	TRGM_REQUIRE( !comparators::CaseInsensitiveInverse( String{ "A" }, String{ "b" } ) );
	TRGM_REQUIRE( !comparators::CaseInsensitiveInverse( String{ "A" }, String{ "B" } ) );
	return TestCaseResult::OK;
}

TRGM_REGISTER_TEST_CASE( ComparatorsReturnsTrueOnSingleCharacterStrings );
TRGM_REGISTER_TEST_CASE( InverseComparatorsReturnsFalseOnSingleCharacterStrings );
