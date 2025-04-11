#include "TestFramework.hpp"
#include "String.hpp"
#include <string>
#include <sstream>
#include <type_traits>

using namespace trgm;

static_assert( std::is_move_constructible<String>::value, "Should be move constructible" );
static_assert( std::is_move_assignable<String>::value, "Should be move assignable" );

static std::string ToSTLString( const String& str )
{
	return std::string( str.Data(), str.Data() + str.Length() );
}

static TestCaseResult EmptyConstructorsMakesStringWithZeroSize()
{
	String s;
	TRGM_REQUIRE( s.Length() == 0 );
	return TestCaseResult::OK;
}

static TestCaseResult EmptyConstructorsMakesStringWithEmptyCString()
{
	String s;
	TRGM_REQUIRE( ToSTLString( s ) == "" );
	return TestCaseResult::OK;
}

static TestCaseResult SumOfStringsReturnsSum()
{
	String a{ "abc" };
	String b{ "defgh" };
	String sum = a + b;
	TRGM_REQUIRE( ToSTLString( sum ) == "abcdefgh" );
	TRGM_REQUIRE( sum.Length() == ( 3 + 5 ) );
	return TestCaseResult::OK;
}

static TestCaseResult StringMoveConstructorWorks()
{
	String a{ "abc" };
	auto*  ptr1 = a.Data();
	String b{ std::move( a ) };
	auto*  ptr2 = b.Data();

	TRGM_REQUIRE( ToSTLString( b ) == "abc" );
	TRGM_REQUIRE( ptr1 == ptr2 );
	TRGM_REQUIRE( a.Data() == nullptr );
	return TestCaseResult::OK;
}

static TestCaseResult StringMoveOperatorWorks()
{
	String a{ "abc" };
	auto*  ptr1 = a.Data();
	String b;
	b		   = std::move( a );
	auto* ptr2 = b.Data();

	TRGM_REQUIRE( ToSTLString( b ) == "abc" );
	TRGM_REQUIRE( ptr1 == ptr2 );
	TRGM_REQUIRE( a.Data() == nullptr );
	return TestCaseResult::OK;
}

static TestCaseResult SumWithCStringReturnsSum()
{
	auto sum = String{ "abc" } + "defgh";
	TRGM_REQUIRE( ToSTLString( sum ) == "abcdefgh" );
	TRGM_REQUIRE( sum.Length() == ( 3 + 5 ) );

	auto sum2 = "defgh" + String{ "abc" };
	TRGM_REQUIRE( ToSTLString( sum ) == "abcdefgh" );
	TRGM_REQUIRE( sum.Length() == ( 3 + 5 ) );

	return TestCaseResult::OK;
}

static TestCaseResult AppendForStringReturnsSum()
{
	String a{ "abc" };
	String b{ "defgh" };
	auto&  r = ( a += b );
	TRGM_REQUIRE( ToSTLString( a ) == "abcdefgh" );
	TRGM_REQUIRE( a.Length() == ( 3 + 5 ) );
	TRGM_REQUIRE( &r == &a );
	return TestCaseResult::OK;
}

static TestCaseResult AppendForCharacterReturnsSum()
{
	String a{ "abc" };
	a += 'd';
	TRGM_REQUIRE( ToSTLString( a ) == "abcd" );
	TRGM_REQUIRE( a.Length() == ( 3 + 1 ) );
	return TestCaseResult::OK;
}

static TestCaseResult AssignCStrinModifiesItsValue()
{
	String a{ "abcdef" };
	auto&  r = ( a = "bcd" );
	TRGM_REQUIRE( ToSTLString( a ) == "bcd" );
	TRGM_REQUIRE( a.Length() == 3 );
	TRGM_REQUIRE( &r == &a );

	String b{ "a" };
	auto&  r2 = ( b = "def" );
	TRGM_REQUIRE( ToSTLString( b ) == "def" );
	TRGM_REQUIRE( b.Length() == 3 );
	TRGM_REQUIRE( &r2 == &b );

	return TestCaseResult::OK;
}

static TestCaseResult InsertionOperatorWorks()
{
	String			  a{ "abc" };
	std::stringstream s;
	s << a;
	TRGM_REQUIRE( s.str() == "abc" );
	return TestCaseResult::OK;
}

static TestCaseResult ExtractionOperatorWorks()
{
	std::stringstream s;
	s << "abc";
	String a;
	s >> a;
	TRGM_REQUIRE_CSTRING( ToSTLString( a ).c_str(), "abc" );
	return TestCaseResult::OK;
}

TRGM_REGISTER_TEST_CASE( EmptyConstructorsMakesStringWithZeroSize );
TRGM_REGISTER_TEST_CASE( EmptyConstructorsMakesStringWithEmptyCString );
TRGM_REGISTER_TEST_CASE( SumOfStringsReturnsSum );
TRGM_REGISTER_TEST_CASE( StringMoveConstructorWorks );
TRGM_REGISTER_TEST_CASE( StringMoveOperatorWorks );
TRGM_REGISTER_TEST_CASE( SumWithCStringReturnsSum );
TRGM_REGISTER_TEST_CASE( AppendForStringReturnsSum );
TRGM_REGISTER_TEST_CASE( AppendForCharacterReturnsSum );
TRGM_REGISTER_TEST_CASE( AssignCStrinModifiesItsValue );
TRGM_REGISTER_TEST_CASE( InsertionOperatorWorks );
TRGM_REGISTER_TEST_CASE( ExtractionOperatorWorks );
