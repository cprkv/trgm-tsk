#include "TestFramework.hpp"
#include "SimpleString.hpp"
#include <cstring>

using namespace trgm;

// todo tests for SimpleStringComparator

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
);
