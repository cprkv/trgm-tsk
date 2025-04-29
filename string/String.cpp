#include "String.hpp"
#include <utility>	 // std::swap
#include <algorithm> // std::min, std::max
#include <cstddef>	 // size_t
#include <cctype>	 // std::toupper

using namespace trgm;

// Task requires to implement it because <cstring> header is forbidden.
static void MemoryCopy( char* dst, const char* src, size_t size )
{
	for( ; size--; *( dst++ ) = *( src++ ) );
}

// Task requires to implement it because <cstring> header is forbidden.
static void MemorySet( char* dst, size_t size, char value )
{
	for( ; size--; *( dst++ ) = value );
}

// Task requires to implement it because <cstring> header is forbidden.
static size_t CStrLength( const char* str )
{
	size_t length = 0;

	if( str )
		for( ; *str; length++, str++ );

	return length;
}

static String Concatenate( const char* a, size_t aLength, const char* b, size_t bLength )
{
	String result( aLength + bLength, '\0' );
	MemoryCopy( result.Data(), a, aLength );
	MemoryCopy( result.Data() + aLength, b, bLength );
	return result;
}

String::~String()
{
	free( m_buffer );
}

String::String( const String& o )
{
	Fill( o.Data(), o.Length() );
}

String& String::operator=( const String& o )
{
	if( &o != this )
		Fill( o.Data(), o.Length() );
	return *this;
}

String::String( String&& o )
{
	std::swap( m_buffer, o.m_buffer );
	std::swap( m_length, o.m_length );
}

String& String::operator=( String&& o )
{
	if( &o != this )
	{
		std::swap( m_buffer, o.m_buffer );
		std::swap( m_length, o.m_length );
	}
	return *this;
}

String::String( const char* cstr )
{
	Fill( cstr, CStrLength( cstr ) );
}

String& String::operator=( const char* o )
{
	Fill( o, CStrLength( o ) );
	return *this;
}

String::String( size_t length, char value )
{
	m_buffer = static_cast<char*>( malloc( length ) );
	m_length = length;
	MemorySet( m_buffer, m_length, value );
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
	size_t requiredSize = position + srcSize;

	if( m_length == 0 && requiredSize > 0 )
	{
		m_buffer = static_cast<char*>( malloc( requiredSize ) );
	}
	else if( requiredSize > m_length )
	{
		m_buffer = static_cast<char*>( realloc( m_buffer, requiredSize ) );
	}

	MemoryCopy( m_buffer + position, src, srcSize );
	m_length = requiredSize;
}

std::istream& trgm::operator>>( std::istream& s, String& str )
{
	char buffer[1024]{ 0 };

	if( s.getline( buffer, sizeof( buffer ) ) )
		str = String( buffer );
	else
		str = String();

	return s;
}

String trgm::operator+( const String& a, const String& b )
{
	return Concatenate( a.Data(), a.Length(), b.Data(), b.Length() );
}

String trgm::operator+( const String& a, const char* b )
{
	return Concatenate( a.Data(), a.Length(), b, CStrLength( b ) );
}

String trgm::operator+( const char* a, const String& b )
{
	return Concatenate( a, CStrLength( a ), b.Data(), b.Length() );
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

	for( size_t n = std::min( a.Length(), b.Length() ); n--; aPtr++, bPtr++ )
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
