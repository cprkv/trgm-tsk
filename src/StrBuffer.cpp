#include "StrBuffer.hpp"
#include <climits>		// INT_MAX
#include <cassert>		// assert
#include <utility>		// std::swap

using namespace trgm;

//	All operations on char* done via pointer and other arithmetics to avoid usage of <string> and <cstring> headers.
//	It is not optimal solution, I know, but task require to implement it that way.
//	This is actually memcpy
static void BufferCopy( char* dst, const char* src, size_t size )
{
	for( ; size--; *( dst++ ) = *( src++ ) );
}

static int NextPowerOfTwo( int x )
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


StrBuffer::StrBuffer( const StrBuffer& other )
{
	m_size = other.m_size;

	if( other.m_smallFirst[ 0 ] == noSmallString )
	{
		m_smallFirst[ 0 ] = noSmallString;
		m_data = static_cast< char* >( malloc( m_size ) );
		BufferCopy( m_data, other.m_data, m_size );
	}
	else
	{
		BufferCopy( m_smallFirst, other.m_smallFirst, m_size );
	}
}

StrBuffer::StrBuffer( StrBuffer&& other )
{
	std::swap( m_size, other.m_size );
	std::swap< char, smallStringPart >( m_smallFirst, other.m_smallFirst );
	std::swap( m_data, other.m_data );
}

void StrBuffer::EnsureSize( size_t newSize )
{
	if( newSize != m_size )								// could be skipped or inverted statement be unlikely
	{
		if( newSize > smallStringSize )					// new sized buffer should live on heap
		{
			if( newSize < size_t{ INT_MAX } )
				newSize = NextPowerOfTwo( static_cast< int >( newSize ) );

			if( m_smallFirst[ 0 ] != noSmallString )		// it was small string, but now it should be relocated to heap
			{
				auto* newData = static_cast< char* >( malloc( newSize ) );
				BufferCopy( newData, m_smallFirst, m_size );
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
				BufferCopy( m_smallFirst, oldData, newSize );
				free( oldData );
			}

			m_size = smallStringSize;
		}
	}
}

void StrBuffer::Fill( const char* src, size_t srcSize, ptrdiff_t shift )
{
	size_t requiredSize = shift + srcSize;
	if( requiredSize > m_size )
		EnsureSize( requiredSize );

	BufferCopy( Ptr() + shift, src, srcSize );
}

StrBuffer& StrBuffer::operator=( const StrBuffer& other )
{
	if( m_smallFirst[ 0 ] == noSmallString )
		free( m_data );

	m_size = other.m_size;

	if( other.m_smallFirst[ 0 ] == noSmallString )
	{
		m_smallFirst[ 0 ] = noSmallString;
		m_data = static_cast< char* >( malloc( m_size ) );
		BufferCopy( m_data, other.m_data, m_size );
	}
	else
	{
		BufferCopy( m_smallFirst, other.m_smallFirst, m_size );
	}

	return *this;
}

StrBuffer& StrBuffer::operator=( StrBuffer&& other )
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
