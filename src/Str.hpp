#pragma once
//						|			-			|			-			|			-			|			-			|			-
#include "StrBuffer.hpp"
#include <cstddef>
#include <cassert>
#include <utility>
#include <istream>

namespace trgm
{
	//	Simple ASCII string implimentation.
	class Str
	{
	public:
						Str()																				{}
						~Str()																				{}
		explicit		Str( const char* cstr );
						Str( const Str& o )		: m_length( o.m_length ), m_buffer( o.m_buffer )			{}
						Str( Str&& o );

		size_t			Length() const									{	return m_length;				}
		const char*		CStr() const									{	return m_buffer.Ptr();			}

		Str&			operator=( const Str& o );
		Str&			operator=( Str&& o );
		Str&			operator+=( char c );
		Str&			operator+=( const Str& o );

	private:
		size_t			m_length				= 0;
		StrBuffer		m_buffer				= StrBuffer{};
	};

	inline Str			operator+( const Str& a, const Str& b )			{	return ( Str{} += a ) += b;		}

	std::istream& 		operator>>( std::istream& s, Str& a );
	std::ostream& 		operator<<( std::ostream& s, Str& a );


	//	inline implimentation -------------------------------------------------------------------------------------------

	inline Str::Str( const char* cstr )
	{
		assert( cstr );

		//	All operations on char* done via pointer and other arithmetics to avoid usage of <string> and <cstring> headers.
		//	It is not optimal solution, I know, but task require to implement it that way.
		//	This is actually	length = strlen( cstr );
		for( auto* curPtr = cstr; *curPtr++; m_length++ );

		m_buffer.Fill( cstr, m_length + 1 );
	}

	inline Str::Str( Str&& o )
	{
		std::swap( m_length, o.m_length );
		std::swap( m_buffer, o.m_buffer );
	}

	inline Str& Str::operator=( const Str& o )
	{
		if( m_buffer.Ptr() != o.m_buffer.Ptr() )
		{
			m_length = o.m_length;
			m_buffer = o.m_buffer;
		}
		return *this;
	}

	inline Str& Str::operator=( Str&& o )
	{
		if( m_buffer.Ptr() != o.m_buffer.Ptr() )
		{
			m_buffer = StrBuffer{};
			m_length = 0;
			std::swap( m_length, o.m_length );
			std::swap( m_buffer, o.m_buffer );
		}
		return *this;
	}

	inline Str& Str::operator+=( char c )
	{
		m_buffer.EnsureSize( ++m_length + 1 );
		auto* str = m_buffer.Ptr();
		str[ m_length - 1 ] = c;
		str[ m_length ] = 0;
		return *this;
	}

	inline Str& Str::operator+=( const Str& o )
	{
		m_buffer.Fill( o.m_buffer.Ptr(), o.m_buffer.Size(), m_length );
		m_length += o.m_length;
		return *this;
	}

	inline std::istream& operator>>( std::istream& s, Str& str )
	{
		auto state		= static_cast< std::ios_base::iostate >( std::istream::goodbit );
		auto changed	= false;
		size_t len		= 0;

		if( std::istream::sentry{ s, true } )	// state okay, extract characters (could be inverted with unlikely)
		{
			try									// some strange technique of using input streams (msvcrt)
			{
				for( auto c = s.rdbuf()->sgetc(); ; c = s.rdbuf()->snextc() )
				{
					auto character = std::istream::traits_type::to_char_type( c );

					if( c == std::istream::traits_type::eof() )
					{
						state |= std::istream::eofbit;
						break;
					}
					else if( std::istream::traits_type::eq( character, '\r' ) )
					{
						changed = true;
						s.rdbuf()->sbumpc();	// skip, we dont need it
					}
					else if( std::istream::traits_type::eq( character, '\n' ) )
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

				// actually it does 'reraise' parameter of istream::setstate
				// but it's not standard cpp feature
				throw;
			}
		}

		if( ! changed )
			state |= std::istream::failbit;

		s.setstate( state );
		return s;
	}

	inline std::ostream& operator<<( std::ostream& s, Str& a )
	{
		s.write( a.CStr(), a.Length() );
		return s;
	}
}
