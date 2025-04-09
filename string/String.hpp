#pragma once
#include "StringBuffer.hpp"
#include <istream> // std::istream
#include <ostream> // std::ostream
#include <cstddef> // size_t

namespace trgm
{
	//	Simple ASCII string. Not null-terminated. Uses buffer with some capacity.
	class String
	{
	public:
		String() = default;
		explicit String( const char* cstr );
		String& operator=( const char* o );

		size_t		Length() const { return m_length; }
		const char* Data() const { return m_buffer.Data(); } // NOTE: NOT null terminated

		String& operator+=( char c );
		String& operator+=( const String& o );
		String& operator+=( const char* o );

	private:
		// Copies chars from `src` of size `srcSize` into buffer at `position`.
		// Increases buffer size and length if needed.
		void Fill( const char* src, size_t srcSize, size_t position = 0 );

	private:
		size_t		 m_length = 0;
		StringBuffer m_buffer = StringBuffer{};
	};

	inline String operator+( const String& a, const String& b ) { return ( String{} += a ) += b; }
	inline String operator+( const String& a, const char* b ) { return ( String{} += a ) += b; }
	inline String operator+( const char* a, const String& b ) { return ( String{} += a ) += b; }

	std::istream& operator>>( std::istream& s, String& a );
	std::ostream& operator<<( std::ostream& s, const String& a );

	namespace comparators
	{
		bool CaseInsensitive( const String& a, const String& b );
		bool CaseInsensitiveInverse( const String& a, const String& b );

	} // namespace comparators

} // namespace trgm
