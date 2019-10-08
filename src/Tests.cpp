#include "TestFramework.hpp"
#include "SimpleString.hpp"
#include <cstring>

using namespace trgm;

DECLARE_TEST_RUNNER(
	DECLARE_TEST_FUNC(
		Empty_Constructors_Makes_String_With_Zero_Size,
		{
			SimpleString s;
			EXPECTED( s.Length() == 0 );
		}
	),
	DECLARE_TEST_FUNC(
		Empty_Constructors_Makes_String_With_Empty_C_String,
		{
			SimpleString s;
			EXPECTED( strcmp( s.CStr(), "" ) == 0 );
		}
	),
);