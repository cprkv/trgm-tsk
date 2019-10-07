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
		explicit			SimpleString( const char* );
							SimpleString( const SimpleString& );
							SimpleString( SimpleString&& ) noexcept;
							~SimpleString();

		size_t				Length() const	{ return length; }	// count of bytes, except \0
		const char*			CStr() const	{ return chars; }	// c-style string

		SimpleString&		operator=( const SimpleString& );
		SimpleString&		operator=( SimpleString&& ) noexcept;

	private:
		char*				chars;
		size_t				length;
	};

	SimpleString			operator+( const SimpleString&, const SimpleString& );
}
