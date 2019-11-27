#pragma once
#include <cstddef>		// size_t
#include <cstdlib>		// malloc, free, realloc
#include <climits>		// INT_MAX
#include <cassert>		// assert
#include <utility>		// std::swap

namespace trgm
{
	//	manages memory for string
	class StrBuffer
	{
		static constexpr char		noSmallString			= -1;
		static constexpr size_t		smallStringSize			= 16;
		static constexpr size_t		smallStringPart			= smallStringSize - sizeof( char* );

		static_assert(	smallStringSize > sizeof( char* ),
						"smallStringSize should be bigger then sizeof pointer" );

	public:
						StrBuffer()							{}
						~StrBuffer()						{	if( m_smallFirst[ 0 ] == noSmallString )  free( m_data );			}
						StrBuffer( const StrBuffer& o );
						StrBuffer( StrBuffer&& o );

		size_t			Size() const						{	return m_size; 														}
		char*			Ptr()								{	return m_smallFirst[ 0 ] == noSmallString ? m_data : m_smallFirst; 	}
		const char*		Ptr() const							{	return m_smallFirst[ 0 ] == noSmallString ? m_data : m_smallFirst; 	}

		// resizes buffer to be able to store data of new size
		void			EnsureSize( size_t newSize );

		// copies src content into buffer
		void			Fill( const char* src, size_t srcSize, ptrdiff_t shift = 0 );

		StrBuffer&		operator=( const StrBuffer& o );
		StrBuffer&		operator=( StrBuffer&& o );

	private:
		size_t			m_size 		= smallStringSize;		// full buffer size, even includes \0 symbol and garbage

	#pragma pack( push, 1 )
		struct
		{
			char		m_smallFirst[ smallStringPart ]	= { 0 };
			char*		m_data;
		};
	#pragma pack( pop )
	};


	//	inline implimentation ----------------------------------------------------------------------------------------------------

	namespace details
	{
		//	All operations on char* done via pointer and other arithmetics to avoid usage of <string> and <cstring> headers.
		//	It is not optimal solution, I know, but task require to implement it that way.
		//	This is actually memcpy
		inline void BufferCopy( char* dst, const char* src, size_t size )
		{
			for( ; size--; *( dst++ ) = *( src++ ) );
		}

		inline int NextPowerOfTwo( int x )
		{
			assert( x > 0 );
			// bits magic
			x--;
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;
			return x + 1;
		}
	}

	inline StrBuffer::StrBuffer( const StrBuffer& other )
	{
		m_size = other.m_size;

		if( other.m_smallFirst[ 0 ] == noSmallString )
		{
			m_smallFirst[ 0 ] = noSmallString;
			m_data = static_cast< char* >( malloc( m_size ) );
			details::BufferCopy( m_data, other.m_data, m_size );
		}
		else
		{
			details::BufferCopy( m_smallFirst, other.m_smallFirst, m_size );
		}
	}

	inline StrBuffer::StrBuffer( StrBuffer&& other )
	{
		std::swap( m_size, other.m_size );
		std::swap< char, smallStringPart >( m_smallFirst, other.m_smallFirst );
		std::swap( m_data, other.m_data );
	}

	inline void StrBuffer::EnsureSize( size_t newSize )
	{
		if( newSize != m_size )								// could be skipped or inverted statement be unlikely
		{
			if( newSize > smallStringSize )					// new sized buffer should live on heap
			{
				if( newSize < size_t{ INT_MAX } )
					newSize = details::NextPowerOfTwo( static_cast< int >( newSize ) );

				if( m_smallFirst[ 0 ] != noSmallString )		// it was small string, but now it should be relocated to heap
				{
					auto* newData = static_cast< char* >( malloc( newSize ) );
					details::BufferCopy( newData, m_smallFirst, m_size );
					m_smallFirst[ 0 ] = noSmallString;
					m_data = newData;
				}
				else if( newSize != m_size )					// it was allocated in heap, and now it should be resized
				{
					m_data = static_cast< char* >( realloc( m_data, newSize ) );
				}

				m_size = newSize;
			}
			else
			{
				if( m_smallFirst[ 0 ] == noSmallString )		// it was allocated in heap, but now it needs to be relocated to stack
				{
					auto* oldData = m_data;
					details::BufferCopy( m_smallFirst, oldData, newSize );
					free( oldData );
				}

				m_size = smallStringSize;
			}
		}
	}

	inline void StrBuffer::Fill( const char* src, size_t srcSize, ptrdiff_t shift )
	{
		size_t requiredSize = shift + srcSize;
		if( requiredSize > m_size )
			EnsureSize( requiredSize );

		details::BufferCopy( Ptr() + shift, src, srcSize );
	}

	inline StrBuffer& StrBuffer::operator=( const StrBuffer& other )
	{
		if( m_smallFirst[ 0 ] == noSmallString )
			free( m_data );

		m_size = other.m_size;

		if( other.m_smallFirst[ 0 ] == noSmallString )
		{
			m_smallFirst[ 0 ] = noSmallString;
			m_data = static_cast< char* >( malloc( m_size ) );
			details::BufferCopy( m_data, other.m_data, m_size );
		}
		else
		{
			details::BufferCopy( m_smallFirst, other.m_smallFirst, m_size );
		}

		return *this;
	}

	inline StrBuffer& StrBuffer::operator=( StrBuffer&& other )
	{
		if( m_smallFirst[ 0 ] == noSmallString )
			free( m_data );

		m_size = smallStringSize;
		m_smallFirst[ 0 ] = 0;

		std::swap( m_size, other.m_size );
		std::swap< char, smallStringPart >( m_smallFirst, other.m_smallFirst );
		std::swap( m_data, other.m_data );

		return *this;
	}
}
