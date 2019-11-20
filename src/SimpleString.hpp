#pragma once
#include <cstddef>
#include <cassert>
#include <utility>

namespace trgm
{
	//	Simple string with storage on heap.
	//	Not uses small string buffer, not uses COW.
	class SimpleString
	{
	public:
							SimpleString()						{}
								// garbage containing string
		explicit			SimpleString( size_t prefLength )	{ Allocate( prefLength ); }
		explicit			SimpleString( const char* );
							SimpleString( const SimpleString& );
							SimpleString( SimpleString&& ) noexcept;
							~SimpleString() noexcept			{ Deallocate(); }

		size_t				Length() const						{ return length; }	// count of bytes, except \0
		const char*			CStr() const						{ return chars; }	// c-style string

		SimpleString&		operator=( const SimpleString& );
		SimpleString&		operator=( SimpleString&& ) noexcept;
		char&				operator[]( size_t i )				{ assert( i < length + 1 ); return chars[ i ]; }
		const char&			operator[]( size_t i ) const		{ assert( i < length + 1 ); return chars[ i ]; }

	private:
		void				Allocate( size_t size );
		void				Deallocate() noexcept;

	private:
		size_t				length	= 0;
		char*				chars	= emptyChars;
		static char* 		emptyChars;	// prevents memory allocation on empty string
	};

	//	inline implimentation ---------------------------------------------------------------------------------

	namespace details
	{
		//	REMARK:
		//	All operations on char* done via pointer and other arithmetics 
		//	to avoid usage of <string> and <cstring> headers (memcpy, strcpy, strlen, and other).
		//	It is not optimal solution, I know, but task requires it.

		inline void CStringCopy( char* dst, const char* src ) 			{ while( ( *( dst++ ) = *( src++ ) ) );			}
		inline void CStringLength( const char* str, size_t& out )		{ for( auto* curPtr = str; *curPtr++; out++ );	}
	}

	inline SimpleString::SimpleString( const char* cstr )
	{
		assert( cstr );
		details::CStringLength( cstr, length );
		Allocate( length );
		details::CStringCopy( chars, cstr );
	}

	inline SimpleString::SimpleString( const SimpleString& s )
	{
		Allocate( s.length );
		details::CStringCopy( chars, s.chars );
	}

	inline SimpleString::SimpleString( SimpleString&& s ) noexcept
	{
		if( chars != s.chars )
		{
			std::swap( length, s.length );
			std::swap( chars,  s.chars );
		}
	}

	inline SimpleString& SimpleString::operator=( const SimpleString& s )
	{
		Deallocate();
		Allocate( s.length );
		details::CStringCopy( s.chars, chars );
		return *this;
	}

	inline SimpleString& SimpleString::operator=( SimpleString&& s ) noexcept
	{
		if( chars != s.chars )
		{
			// Deallocate();
			std::swap( length, s.length );
			std::swap( chars,  s.chars );
		}
		return *this;
	}

	inline void SimpleString::Allocate( size_t prefLength )
	{
		if( prefLength > 0 )
		{
			chars = reinterpret_cast< char* >( malloc( prefLength + 1 ) );
			chars[ prefLength ] = 0;
		}
		else
		{
			chars = emptyChars;
		}

		length = prefLength;
	}

	inline void SimpleString::Deallocate() noexcept
	{
		if( chars != emptyChars )
			free( chars );
		chars	= emptyChars;
		length	= 0;
	}

	inline SimpleString operator+( const SimpleString& a, const SimpleString& b )
	{
		auto commonLength = a.Length() + b.Length();
		if( commonLength == 0 )
			return SimpleString{};

		auto str = SimpleString{ commonLength };

		for( size_t i = 0; i < a.Length(); i++ )
			str[ i ] = a[ i ];

		for( size_t i = 0; i < b.Length(); i++ )
			str[ i + a.Length() ] = b[ i ];

		return str;
	}
}
