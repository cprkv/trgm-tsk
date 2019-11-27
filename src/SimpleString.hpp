#pragma once
#include "StringBuffer.hpp"
#include <cstddef>
#include <cassert>
#include <utility>
#include <istream>

namespace trgm
{
	//	Simple ASCII string implimentation.
	class SimpleString
	{
	public:
							SimpleString()							{}
		explicit			SimpleString( const char* );
							SimpleString( const SimpleString& );
							SimpleString( SimpleString&& ) noexcept;
							~SimpleString() noexcept				{}

		size_t				Length() const							{ return length; }			// count of chars, except \0
		const char*			CStr() const							{ return buffer.Ptr(); }	// c-style string

		SimpleString&		operator=( const SimpleString& );
		SimpleString&		operator=( SimpleString&& ) noexcept;
		char&				operator[]( size_t i )					{ assert( i < length + 1 ); return buffer.Ptr()[ i ]; }
		const char&			operator[]( size_t i ) const			{ assert( i < length + 1 ); return buffer.Ptr()[ i ]; }
		SimpleString&		operator+=( char );
		SimpleString&		operator+=( const SimpleString& );

	private:
		size_t				length = 0;
		StringBuffer		buffer;
	};

	SimpleString 			operator+( const SimpleString& a, const SimpleString& b );
	std::istream& 			operator>>( std::istream& s, SimpleString& a );
	std::ostream& 			operator<<( std::ostream& s, SimpleString& a );

	//	inline implimentation ---------------------------------------------------------------------------------

	namespace details
	{
		//	REMARK:
		//		All operations on char* done via pointer and other arithmetics 
		//		to avoid usage of <string> and <cstring> headers (memcpy, strcpy, strlen, and other).
		//		It is not optimal solution, I know, but task require to implement it that way.

		inline void CStringCopy( char* dst, const char* src ) 		{ while( ( *( dst++ ) = *( src++ ) ) );			}
		inline void CStringLength( const char* str, size_t& out )	{ for( auto* curPtr = str; *curPtr++; out++ );	}
	}

	inline SimpleString::SimpleString( const char* cstr )
	{
		assert( cstr );
		details::CStringLength( cstr, length );
		buffer.EnsureSize( length + 1 );
		details::CStringCopy( buffer.Ptr(), cstr );
	}

	inline SimpleString::SimpleString( const SimpleString& other )
		: length( other.length )
		, buffer( other.buffer )
	{
	}

	inline SimpleString::SimpleString( SimpleString&& other ) noexcept
	{
		std::swap( length, other.length );
		std::swap( buffer, other.buffer );
	}

	inline SimpleString& SimpleString::operator=( const SimpleString& other )
	{
		if( buffer.Ptr() != other.buffer.Ptr() )
		{
			length = other.length;
			buffer = other.buffer;
			return *this;
		}
	}

	inline SimpleString& SimpleString::operator=( SimpleString&& other ) noexcept
	{
		if( buffer.Ptr() != other.buffer.Ptr() )
		{
			buffer = StringBuffer{};
			length = 0;
			std::swap( length, other.length );
			std::swap( buffer, other.buffer );
		}
		return *this;
	}

	inline SimpleString& SimpleString::operator+=( char c )
	{
		buffer.EnsureSize( ++length + 1 );
		buffer.Ptr()[ length - 1 ] = c;
		buffer.Ptr()[ length ] = 0;
		return *this;
	}

	inline SimpleString& SimpleString::operator+=( const SimpleString& other )
	{
		buffer.EnsureSize( length + other.length + 1 );
		details::CStringCopy( buffer.Ptr() + length, other.buffer.Ptr() );
		length += other.length;
		return *this;
	}

	inline SimpleString operator+( const SimpleString& a, const SimpleString& b )
	{
		auto str = SimpleString{};
		str += a;
		str += b;
		return str;
	}

	inline std::istream& operator>>( std::istream& s, SimpleString& str )
	{
		auto state		= static_cast< std::ios_base::iostate >( std::istream::goodbit );
		auto changed	= false;
		size_t len		= 0;

		if( std::istream::sentry{ s, true } )	// state okay, extract characters (could be inverted with unlikely)
		{
			try
			{
				for( auto c = s.rdbuf()->sgetc(); ; c = s.rdbuf()->snextc() )
				{
					auto character = std::istream::traits_type::to_char_type( c );

					if( c == std::istream::traits_type::eof() )
					{
						state |= std::istream::eofbit;
						break;
					}
					else if( character == '\n' || character == '\r' )
					{
						changed = true;
						s.rdbuf()->sbumpc();	// skip, we dont need it
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
				return s;
			}
		}

		if( ! changed )
			state |= std::istream::failbit;

		s.setstate( state );
		return s;
	}

	inline std::ostream& operator<<( std::ostream& s, SimpleString& a )
	{
		s.write( a.CStr(), a.Length() );
		return s;
	}
}
