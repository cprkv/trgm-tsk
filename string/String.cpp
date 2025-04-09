#include "String.hpp"
#include "StringAlgo.hpp"
#include <algorithm> // std::min, std::max
#include <cstddef>	 // size_t
#include <cctype>	 // std::toupper

using namespace trgm;

String::String( const char* cstr )
{
	Fill( cstr, CStrLength( cstr ) );
}

String& String::operator=( const char* o )
{
	size_t new_length = CStrLength( o );
	Fill( o, new_length );
	m_length = new_length;
	return *this;
}

String& String::operator+=( char c )
{
	Fill( &c, 1, m_length );
	return *this;
}

String& String::operator+=( const String& o )
{
	Fill( o.Data(), o.Length(), m_length );
	return *this;
}

String& String::operator+=( const char* o )
{
	Fill( o, CStrLength( o ), m_length );
	return *this;
}

void String::Fill( const char* src, size_t srcSize, size_t position )
{
	const auto requiredSize = position + srcSize;
	m_buffer.EnsureSize( requiredSize );
	MemoryCopy( m_buffer.Data() + position, src, srcSize );
	m_length = std::max( m_length, requiredSize );
}

std::istream& trgm::operator>>( std::istream& s, String& str )
{
	if( !std::istream::sentry{ s, true } )
		return s;

	auto state	 = static_cast<std::ios_base::iostate>( std::istream::goodbit );
	bool changed = false;

	try // Some strange technique of using input streams (msvcrt).
	{
		for( auto c = s.rdbuf()->sgetc();; c = s.rdbuf()->snextc() )
		{
			auto character = std::istream::traits_type::to_char_type( c );

			if( c == std::istream::traits_type::eof() )
			{
				state |= std::istream::eofbit;
				break;
			}
			else if( std::istream::traits_type::eq( character, '\r' ) )
			{
				changed = true;
				s.rdbuf()->sbumpc(); // skip, we dont need it
			}
			else if( std::istream::traits_type::eq( character, '\n' ) )
			{
				changed = true;
				s.rdbuf()->sbumpc(); // skip, we dont need it
				break;
			}
			else
			{
				str += character;
			}
		}
	}
	catch( ... )
	{
		s.setstate( std::istream::badbit );
		throw;
	}

	if( !changed )
		state |= std::istream::failbit;

	s.setstate( state );
	return s;
}

std::ostream& trgm::operator<<( std::ostream& s, const String& a )
{
	s.write( a.Data(), a.Length() );
	return s;
}

bool comparators::CaseInsensitive( const String& a, const String& b )
{
	const auto* aPtr = a.Data();
	const auto* bPtr = b.Data();

	for( auto n = std::min( a.Length(), b.Length() ); n--; aPtr++, bPtr++ )
	{
		if( std::toupper( *aPtr ) < std::toupper( *bPtr ) )
			return true;
		if( std::toupper( *aPtr ) > std::toupper( *bPtr ) )
			return false;
	}

	return a.Length() < b.Length();
}

bool comparators::CaseInsensitiveInverse( const String& a, const String& b )
{
	return comparators::CaseInsensitive( b, a );
}
