#include "SimpleString.hpp"
#include <utility>
#include <cassert>

using namespace trgm;

//	REMARK:
//	All operations on char* done via pointer and other arithmetics 
//	to avoid usage of <string> and <cstring> headers (memcpy, strcpy, strlen, and other).
//	It's not optimal solution, I know, but task requires it.

// prevents memory allocation on empty string
static constexpr char* emptyChars = const_cast< char* >( "" );

SimpleString::SimpleString()
	: chars( emptyChars )
	, length( 0 )
{
}

SimpleString::SimpleString( size_t prefLength )
	: chars( emptyChars )
	, length( 0 )
{
	if( prefLength > 0 )
	{
		length 	= prefLength;
		chars 	= new char[ prefLength + 1 ];
		chars[ prefLength ] = 0;
	}
}

SimpleString::SimpleString( const char* cstr )
	: chars( emptyChars )
	, length( 0 )
{
	assert( cstr );
	auto* copyPtr = cstr;

	while( *copyPtr++ )
		length++;

	if( length > 0 )
	{
		chars 			= new char[ length + 1 ];
		copyPtr 		= cstr;
		auto* curPtr 	= chars;
		while( ( *( curPtr++ ) = *( copyPtr++ ) ) );
	}
}

SimpleString::SimpleString( const SimpleString& s )
	: chars( emptyChars )
	, length( 0 )
{
	if( chars != s.chars && s.length > 0 )
	{
		length			= s.length;
		chars			= new char[ s.length + 1 ];
		auto* curPtr 	= chars;
		auto* copyPtr	= s.chars;
		while( ( *( curPtr++) = *( copyPtr++ ) ) );
	}
}

SimpleString::SimpleString( SimpleString&& s ) noexcept
	: chars( emptyChars )
	, length( 0 )
{
	if( chars != s.chars )
	{
		std::swap( length, s.length );
		std::swap( chars,  s.chars );
	}
}

SimpleString::~SimpleString()
{
	if( chars != emptyChars )
		delete[] chars;
}

SimpleString& SimpleString::operator=( const SimpleString& s )
{
	if( chars != emptyChars )
		delete[] chars;
	if( s.length )
	{
		chars           = new char[ s.length + 1 ];
		auto* curPtr    = chars;
		auto* copyPtr   = s.chars;
		while( ( *( curPtr++) = *( copyPtr++ ) ) );
	}
	else
	{
		chars = emptyChars;
		length = 0;
	}
	return *this;
}

SimpleString& SimpleString::operator=( SimpleString&& s ) noexcept
{
	if( chars != s.chars )
	{
		*this = SimpleString{};
		std::swap( length, s.length );
		std::swap( chars,  s.chars );
	}
	return *this;
}

SimpleString trgm::operator+( const SimpleString& a, const SimpleString& b )
{
	auto commonLength = a.Length() + b.Length();
	if( !commonLength )
		return SimpleString{};
	auto str = SimpleString{ commonLength };
	for( size_t i = 0; i < a.Length(); i++ )
		str[ i ] = a[ i ];
	for( size_t i = 0; i < b.Length(); i++ )
		str[ i + a.Length() ] = b[ i ];
	return str;
}
