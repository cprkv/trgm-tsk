#include "TestFramework.hpp"
#include "Str.hpp"

using namespace trgm;

TestGroup StrComparatorTests()
{
	return { "trgm::comparators tests", {
		TRGM_DECLARE_TEST_FUNC( "Comparators Returns True On Single Character Strings",
			{
				TRGM_EXPECTED( comparators::CaseInsensitive( Str{ "a" }, Str{ "B" } ) );
				TRGM_EXPECTED( comparators::CaseInsensitive( Str{ "a" }, Str{ "b" } ) );
				TRGM_EXPECTED( comparators::CaseInsensitive( Str{ "A" }, Str{ "b" } ) );
				TRGM_EXPECTED( comparators::CaseInsensitive( Str{ "A" }, Str{ "B" } ) );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Inverse Comparators Returns False On Single Character Strings",
			{
				TRGM_EXPECTED( ! comparators::CaseInsensitiveInverse( Str{ "a" }, Str{ "B" } ) );
				TRGM_EXPECTED( ! comparators::CaseInsensitiveInverse( Str{ "a" }, Str{ "b" } ) );
				TRGM_EXPECTED( ! comparators::CaseInsensitiveInverse( Str{ "A" }, Str{ "b" } ) );
				TRGM_EXPECTED( ! comparators::CaseInsensitiveInverse( Str{ "A" }, Str{ "B" } ) );
			} ), } };
}
