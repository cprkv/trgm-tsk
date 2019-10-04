#pragma once
#include <cstdlib>

namespace trgm
{
	/*
		Simple string implimentation.
		Not uses small string buffer, not uses COW.
		Allocates memory even for empty string.
		TODO: too few inline methods. may be some ctors/dctors should be inlined.
	*/
	class SimpleString
	{
	public:
						SimpleString();
		explicit		SimpleString( const char* );
						SimpleString( const SimpleString& );
						SimpleString( SimpleString&& ) noexcept;
						~SimpleString();

		SimpleString&	operator=( const SimpleString& );
		SimpleString&	operator=( SimpleString&& ) noexcept;

		size_t			Length() const				{ return length; }	// count of bytes, except \0
		const char*		CStr() const				{ return chars; }	// c-style string

	private:
		char*			chars;
		size_t			length;
	};

	SimpleString&&		operator+( const SimpleString&, const SimpleString& );

} // namespace trgm
