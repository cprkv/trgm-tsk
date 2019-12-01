#include "TestFramework.hpp"
#include "Str.hpp"
#include <cstring>

using namespace trgm;

TestGroup StrTests()
{
	return { "trgm::Str tests", {
		TRGM_DECLARE_TEST_FUNC( "Empty Constructors Makes String With Zero Size",
			{
				Str s;
				TRGM_EXPECTED( s.Length() == 0 );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Empty Constructors Makes String With Empty C String",
			{
				Str s;
				TRGM_EXPECTED_CSTRING( s.CStr(), "" );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Sum Of Strings Returns Zero Terminated C String",
			{
				Str a{ "abc" };
				Str b{ "defgh" };
				Str sum = a + b;
				TRGM_EXPECTED_CSTRING( sum.CStr(), "abcdefgh" );
				TRGM_EXPECTED( sum.Length() == ( 3 + 5 ) );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Append For String Returns Zero Terminated C String",
			{
				Str a{ "abc" };
				Str b{ "defgh" };
				a += b;
				TRGM_EXPECTED_CSTRING( a.CStr(), "abcdefgh" );
				TRGM_EXPECTED( a.Length() == ( 3 + 5 ) );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Append For Character Returns Zero Terminated C String",
			{
				Str a{ "abc" };
				a += 'd';
				TRGM_EXPECTED_CSTRING( a.CStr(), "abcd" );
				TRGM_EXPECTED( a.Length() == ( 3 + 1 ) );
			} ), } };
}
