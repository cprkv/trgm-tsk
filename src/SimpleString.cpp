#include <SimpleString.h>

using namespace trgm;

SimpleString::SimpleString()
{
	length = 0;
	chars = static_cast< char* >( malloc( 1 ) );
	chars[ 0 ] = 0;
}

SimpleString::SimpleString( const char* cstr )
{
	const char* copyPtr = cstr;
	length = 0;
	while( *copyPtr++ )
		length++;
	chars = nullptr;
	if( length > 0 )
	{
		chars = static_cast< char* >( malloc( length + 1 ) );
		copyPtr = cstr;
		char* curPtr = chars;
		while( ( *( curPtr++ ) = *( copyPtr++ ) ) ) {}
	}
}

SimpleString::SimpleString( const SimpleString& s )
{
	length = s.length;
	chars = static_cast< char* >( malloc( length + 1 ) );
	char* curPtr = chars;
	const char* copyPtr = s.chars;
	while( ( *( curPtr++ ) = *( copyPtr++ ) ) ) {}
}

SimpleString::SimpleString( SimpleString&& s ) noexcept
{
	length = s.length;
	chars = s.chars;
	s.length = 0;
	s.chars = static_cast< char* >( malloc( 1 ) );
	s.chars[ 0 ] = 0;
}

SimpleString::~SimpleString()
{
	free( chars );
}

SimpleString& SimpleString::operator=( const SimpleString& s )
{
	// TODO
	return *this;
}

SimpleString& SimpleString::operator=( SimpleString&& s ) noexcept
{
	// TODO
	return *this;
}

SimpleString&& trgm::operator+( const SimpleString& a, const SimpleString& b )
{
	// TODO
	return SimpleString();
}
