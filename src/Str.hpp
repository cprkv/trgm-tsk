#pragma once
#include "StrBuffer.hpp"
#include <cstddef>		// size_t
#include <istream>		// istream
#include <ostream>		// ostream

namespace trgm {

	//	Simple ASCII string.
	class Str
	{
	public:
						Str()																				{}
		explicit		Str( const char* cstr );
						Str( const Str& o )		: m_length( o.m_length ), m_buffer( o.m_buffer )			{}
						Str( Str&& o );
						~Str()																				{}

		size_t			Length() const									{	return m_length;				}
		const char*		CStr() const									{	return m_buffer.Ptr();			}

		Str&			operator=( const Str& o );
		Str&			operator=( Str&& o );
		Str&			operator+=( char c );
		Str&			operator+=( const Str& o );

	private:
		size_t			m_length										= 0;
		StrBuffer		m_buffer										= StrBuffer{};
	};

	inline Str			operator+( const Str& a, const Str& b )			{	return ( Str{} += a ) += b;		}
	std::istream& 		operator>>( std::istream& s, Str& a );
	std::ostream& 		operator<<( std::ostream& s, Str& a );

namespace comparators {

	bool				CaseInsensitive( const Str& a, const Str& b );
	bool				CaseInsensitiveInverse( const Str& a, const Str& b );

}	// namespace comparators
}	// namespace trgm
