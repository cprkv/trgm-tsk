#include "TestFramework.hpp"
#include "SimpleString.hpp"
#include <cstring>

using namespace trgm;

DECLARE_TEST_GROUP
(
	Simple_String_Tests,

	DECLARE_TEST_FUNC
	(
		Empty_Constructors_Makes_String_With_Zero_Size,
		{
			SimpleString s;
			EXPECTED( s.Length() == 0 );
		}
	),
	DECLARE_TEST_FUNC
	(
		Empty_Constructors_Makes_String_With_Empty_C_String,
		{
			SimpleString s;
			EXPECTED_CSTRING( s.CStr(), "" );
		}
	),
	DECLARE_TEST_FUNC
	(
		Sum_Of_Strings_Returns_Zero_Terminated_C_String,
		{
			SimpleString a{ "abc" };
			SimpleString b{ "defgh" };
			SimpleString sum = a + b;
			EXPECTED_CSTRING( sum.CStr(), "abcdefgh" );
			EXPECTED( sum.Length() == ( 3 + 5 ) );
		}
	),
	DECLARE_TEST_FUNC
	(
		Sum_Append_For_Strings_Returns_Zero_Terminated_C_String,
		{
			SimpleString a{ "abc" };
			SimpleString b{ "defgh" };
			a += b;
			EXPECTED_CSTRING( a.CStr(), "abcdefgh" );
			EXPECTED( a.Length() == ( 3 + 5 ) );
		}
	),
	DECLARE_TEST_FUNC
	(
		Sum_Append_For_Character_Returns_Zero_Terminated_C_String,
		{
			SimpleString a{ "abc" };
			a += 'd';
			EXPECTED_CSTRING( a.CStr(), "abcd" );
			EXPECTED( a.Length() == ( 3 + 1 ) );
		}
	),
);
