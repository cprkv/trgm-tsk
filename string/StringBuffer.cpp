#include "StringBuffer.hpp"
#include "StringAlgo.hpp"
#include <utility> // std::swap
#include <new>	   // std::bad_alloc
#include <cstddef> // size_t
#include <cstdlib> // malloc, realloc, free

using namespace trgm;

// NOTE: In C++ STL this behaviour is clarified: throw std::bad_alloc();
//       In specific gamedev cases this could be abort() or continue like nothing happened.
//       I do not prefer any option here - anyway application will crash. So I do same as STL.
#define TRGM_CHECK_ALLOCATION( ... ) \
	if( !__VA_ARGS__ )               \
	{                                \
		throw std::bad_alloc();      \
	}

StringBuffer::StringBuffer()
{
	AllocateUnsafe( 0 );
}

StringBuffer::~StringBuffer()
{
	free( m_data );
}

StringBuffer::StringBuffer( const StringBuffer& other )
{
	AllocateUnsafe( other.m_size );
	MemoryCopy( m_data, other.m_data, m_size );
}

StringBuffer& StringBuffer::operator=( const StringBuffer& other )
{
	free( m_data );
	AllocateUnsafe( other.m_size );
	MemoryCopy( m_data, other.m_data, m_size );
	return *this;
}

StringBuffer::StringBuffer( StringBuffer&& other )
{
	AllocateUnsafe( 0 );
	std::swap( m_size, other.m_size );
	std::swap( m_data, other.m_data );
}

StringBuffer& StringBuffer::operator=( StringBuffer&& other )
{
	free( m_data );
	AllocateUnsafe( 0 );
	std::swap( m_size, other.m_size );
	std::swap( m_data, other.m_data );
	return *this;
}

void StringBuffer::EnsureSize( size_t newSize )
{
	newSize = StringAllocationStrategy( newSize );

	if( !newSize )
	{
		free( m_data );
		m_data = nullptr;
	}
	else if( newSize > m_size )
	{
		m_data = static_cast<char*>( realloc( m_data, newSize ) );
		TRGM_CHECK_ALLOCATION( m_data );
	}

	m_size = newSize;
}

void StringBuffer::AllocateUnsafe( size_t realSize )
{
	m_size = realSize;

	if( m_size )
	{
		m_data = static_cast<char*>( malloc( m_size ) );
		TRGM_CHECK_ALLOCATION( m_data );
	}
	else
	{
		m_data = nullptr;
	}
}
