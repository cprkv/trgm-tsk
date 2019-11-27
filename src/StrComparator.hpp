#pragma once
#include "Str.hpp"
#include <cctype>		// std::toupper
#include <algorithm>	// std::min

namespace trgm
{
	namespace StrComparator
	{
		bool CaseInsensitive( const Str& a, const Str& b );
		bool CaseInsensitiveInverse( const Str& a, const Str& b );
	}


	//	inline implimentation ------------------------------------------------------------------------------

	inline bool StrComparator::CaseInsensitive( const Str& a, const Str& b )
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

	inline bool StrComparator::CaseInsensitiveInverse( const Str& a, const Str& b )
	{
		return StrComparator::CaseInsensitive( b, a );
	}
}
