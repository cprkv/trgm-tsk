#include "TestFramework.hpp"
#include "Str.hpp"

using namespace trgm;

TRGM_DECLARE_TEST_GROUP
(
	Simple_String_Comparator_Tests,

	TRGM_DECLARE_TEST_FUNC
	(
		Comparators_Returns_True_On_Single_Character_Strings,
		{
			TRGM_EXPECTED( comparators::CaseInsensitive( Str{ "a" }, Str{ "B" } ) );
			TRGM_EXPECTED( comparators::CaseInsensitive( Str{ "a" }, Str{ "b" } ) );
			TRGM_EXPECTED( comparators::CaseInsensitive( Str{ "A" }, Str{ "b" } ) );
			TRGM_EXPECTED( comparators::CaseInsensitive( Str{ "A" }, Str{ "B" } ) );
		}
	),
	TRGM_DECLARE_TEST_FUNC
	(
		Inverse_Comparators_Returns_False_On_Single_Character_Strings,
		{
			TRGM_EXPECTED( ! comparators::CaseInsensitiveInverse( Str{ "a" }, Str{ "B" } ) );
			TRGM_EXPECTED( ! comparators::CaseInsensitiveInverse( Str{ "a" }, Str{ "b" } ) );
			TRGM_EXPECTED( ! comparators::CaseInsensitiveInverse( Str{ "A" }, Str{ "b" } ) );
			TRGM_EXPECTED( ! comparators::CaseInsensitiveInverse( Str{ "A" }, Str{ "B" } ) );
		}
	)
);
