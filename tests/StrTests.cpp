#include "TestFramework.hpp"
#include "Str.hpp"
#include <cstring>

using namespace trgm;

TRGM_DECLARE_TEST_GROUP
(
	Simple_String_Tests,

	TRGM_DECLARE_TEST_FUNC
	(
		Empty_Constructors_Makes_String_With_Zero_Size,
		{
			Str s;
			TRGM_EXPECTED( s.Length() == 0 );
		}
	),
	TRGM_DECLARE_TEST_FUNC
	(
		Empty_Constructors_Makes_String_With_Empty_C_String,
		{
			Str s;
			TRGM_EXPECTED_CSTRING( s.CStr(), "" );
		}
	),
	TRGM_DECLARE_TEST_FUNC
	(
		Sum_Of_Strings_Returns_Zero_Terminated_C_String,
		{
			Str a{ "abc" };
			Str b{ "defgh" };
			Str sum = a + b;
			TRGM_EXPECTED_CSTRING( sum.CStr(), "abcdefgh" );
			TRGM_EXPECTED( sum.Length() == ( 3 + 5 ) );
		}
	),
	TRGM_DECLARE_TEST_FUNC
	(
		Sum_Append_For_Strings_Returns_Zero_Terminated_C_String,
		{
			Str a{ "abc" };
			Str b{ "defgh" };
			a += b;
			TRGM_EXPECTED_CSTRING( a.CStr(), "abcdefgh" );
			TRGM_EXPECTED( a.Length() == ( 3 + 5 ) );
		}
	),
	TRGM_DECLARE_TEST_FUNC
	(
		Sum_Append_For_Character_Returns_Zero_Terminated_C_String,
		{
			Str a{ "abc" };
			a += 'd';
			TRGM_EXPECTED_CSTRING( a.CStr(), "abcd" );
			TRGM_EXPECTED( a.Length() == ( 3 + 1 ) );
		}
	),
);
