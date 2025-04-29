#pragma once
#include <istream> // std::istream
#include <ostream> // std::ostream
#include <cstddef> // size_t

namespace trgm
{
	// Simple ASCII string. Not null-terminated.
	class String
	{
	public:
		String() = default;
		~String();

		String( const String& cstr );
		String& operator=( const String& o );

		String( String&& cstr );
		String& operator=( String&& o );

		explicit String( const char* cstr );
		String& operator=( const char* o );

		explicit String( size_t length, char value );

		size_t		Length() const { return m_length; }
		char*		Data() { return m_buffer; }		  // NOTE: NOT null terminated
		const char* Data() const { return m_buffer; } // NOTE: NOT null terminated

		String& operator+=( char c );
		String& operator+=( const String& o );
		String& operator+=( const char* o );

		// Copies chars from `src` of size `srcSize` into buffer at `position`.
		// Increases length if needed.
		void Fill( const char* src, size_t srcSize, size_t position = 0 );

	private:
		char*  m_buffer = nullptr;
		size_t m_length = 0;
	};

	String operator+( const String& a, const String& b );
	String operator+( const String& a, const char* b );
	String operator+( const char* a, const String& b );

	std::istream& operator>>( std::istream& s, String& a );
	std::ostream& operator<<( std::ostream& s, const String& a );

	namespace comparators
	{
		bool CaseInsensitive( const String& a, const String& b );
		bool CaseInsensitiveInverse( const String& a, const String& b );
	} // namespace comparators

} // namespace trgm
