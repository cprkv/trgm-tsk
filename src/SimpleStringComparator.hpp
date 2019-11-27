#pragma once
#include "SimpleString.hpp"
#include <cctype>		// std::toupper
#include <algorithm>	// std::min

namespace trgm
{
	namespace SimpleStringComparator
	{
		static bool CaseInsensitive( const SimpleString& a, const SimpleString& b );
		static bool CaseInsensitiveInverse( const SimpleString& a, const SimpleString& b );
	}

	//	inline implimentation ------------------------------------------------------------------------------

	inline bool SimpleStringComparator::CaseInsensitive( const SimpleString& a, const SimpleString& b )
	{
		const auto* aPtr = a.CStr();
		const auto* bPtr = b.CStr();

		for( auto n = std::min( a.Length(), b.Length() ); n--; aPtr++, bPtr++ )
		{
			if ( std::toupper( *aPtr ) < std::toupper( *bPtr ) )
				return true;
			if ( std::toupper( *aPtr ) > std::toupper( *bPtr ) )
				return false;
		}

		return a.Length() < b.Length();
	}

	inline bool SimpleStringComparator::CaseInsensitiveInverse( const SimpleString& a, const SimpleString& b )
	{
		return SimpleStringComparator::CaseInsensitive( b, a );
	}
}
