#include "TestFramework.hpp"
#include "SimpleStringComparator.hpp"

using namespace trgm;

DECLARE_TEST_GROUP
(
	Simple_String_Comparator_Tests,
	DECLARE_TEST_FUNC
	(
		Comparators_Returns_True_On_Single_Character_Strings,
		{
			EXPECTED( SimpleStringComparator::CaseInsensitive( SimpleString{ "a" }, SimpleString{ "B" } ) );
			EXPECTED( SimpleStringComparator::CaseInsensitive( SimpleString{ "a" }, SimpleString{ "b" } ) );
			EXPECTED( SimpleStringComparator::CaseInsensitive( SimpleString{ "A" }, SimpleString{ "b" } ) );
			EXPECTED( SimpleStringComparator::CaseInsensitive( SimpleString{ "A" }, SimpleString{ "B" } ) );
		}
	),
	DECLARE_TEST_FUNC
	(
		Inverse_Comparators_Returns_False_On_Single_Character_Strings,
		{
			EXPECTED( ! SimpleStringComparator::CaseInsensitiveInverse( SimpleString{ "a" }, SimpleString{ "B" } ) );
			EXPECTED( ! SimpleStringComparator::CaseInsensitiveInverse( SimpleString{ "a" }, SimpleString{ "b" } ) );
			EXPECTED( ! SimpleStringComparator::CaseInsensitiveInverse( SimpleString{ "A" }, SimpleString{ "b" } ) );
			EXPECTED( ! SimpleStringComparator::CaseInsensitiveInverse( SimpleString{ "A" }, SimpleString{ "B" } ) );
		}
	)
);
