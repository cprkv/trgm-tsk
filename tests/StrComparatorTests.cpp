#include "TestFramework.hpp"
#include "StrComparator.hpp"

using namespace trgm;

DECLARE_TEST_GROUP
(
	Simple_String_Comparator_Tests,

	DECLARE_TEST_FUNC
	(
		Comparators_Returns_True_On_Single_Character_Strings,
		{
			EXPECTED( StrComparator::CaseInsensitive( Str{ "a" }, Str{ "B" } ) );
			EXPECTED( StrComparator::CaseInsensitive( Str{ "a" }, Str{ "b" } ) );
			EXPECTED( StrComparator::CaseInsensitive( Str{ "A" }, Str{ "b" } ) );
			EXPECTED( StrComparator::CaseInsensitive( Str{ "A" }, Str{ "B" } ) );
		}
	),
	DECLARE_TEST_FUNC
	(
		Inverse_Comparators_Returns_False_On_Single_Character_Strings,
		{
			EXPECTED( ! StrComparator::CaseInsensitiveInverse( Str{ "a" }, Str{ "B" } ) );
			EXPECTED( ! StrComparator::CaseInsensitiveInverse( Str{ "a" }, Str{ "b" } ) );
			EXPECTED( ! StrComparator::CaseInsensitiveInverse( Str{ "A" }, Str{ "b" } ) );
			EXPECTED( ! StrComparator::CaseInsensitiveInverse( Str{ "A" }, Str{ "B" } ) );
		}
	)
);
