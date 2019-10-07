#include "SimpleString.hpp"
#include <utility>
#include <cassert>

using namespace trgm;

// prevents memory allocation on empty string
static constexpr char* emptyChars = const_cast< char* >( "" );

SimpleString::SimpleString()
    : chars( emptyChars )
    , length( 0 )
{
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
    // TODO
    return *this;
}

SimpleString& SimpleString::operator=( SimpleString&& s ) noexcept
{
    // TODO
    return *this;
}

SimpleString trgm::operator+( const SimpleString& a, const SimpleString& b )
{
    // TODO
    return SimpleString{};
}
