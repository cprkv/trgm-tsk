#pragma once
#include <cstddef>

namespace trgm
{
	/*
		Simple string implimentation.
		Not uses small string buffer, not uses COW.
		I hope LTO will do magic with inlining some methods.
	*/
	class SimpleString
	{
	public:
							SimpleString();
								// initializes string of prefLength, containing garbage
							SimpleString( size_t prefLength );
		explicit			SimpleString( const char* );
							SimpleString( const SimpleString& );
							SimpleString( SimpleString&& ) noexcept;
							~SimpleString();

		size_t				Length() const			{ return length; }	// count of bytes, except \0
		const char*			CStr() const			{ return chars; }	// c-style string

		SimpleString&		operator=( const SimpleString& );
		SimpleString&		operator=( SimpleString&& ) noexcept;
		char&				operator[]( size_t i ) 			{ return chars[i]; }
		const char&			operator[]( size_t i ) const 	{ return chars[i]; }

	private:
		char*				chars;
		size_t				length;
	};

	SimpleString			operator+( const SimpleString&, const SimpleString& );
}
