#include "StringAlgo.hpp"
#include <cstddef> // size_t
#include <climits> // INT_MAX
#include <cassert> // assert

// NOTE: uncomment this line to enable string buffer grow optimization (like std::vector)
// #define TRGM_USE_STR_GROW_OPTIMIZATION

using namespace trgm;

void trgm::MemoryCopy( char* dst, const char* src, size_t size )
{
	for( ; size--; *( dst++ ) = *( src++ ) );
}

size_t trgm::CStrLength( const char* str )
{
	size_t length = 0;

	if( str )
		for( ; *str; length++, str++ );

	return length;
}

#ifdef TRGM_USE_STR_GROW_OPTIMIZATION

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

static size_t NextDivisibleBy( size_t x, size_t denominator )
{
	return ( x / denominator + 1 ) * denominator;
}

size_t trgm::StringAllocationStrategy( size_t requestedSize )
{
	if( requestedSize == 0 )
		return 0;

	if( 0 < requestedSize && requestedSize <= 512 )
		return NextDivisibleBy( requestedSize, 64 ); // 64,128,192,256 .. 512 (div 64)

	if( 512 < requestedSize && requestedSize < 4096 )
		return NextDivisibleBy( requestedSize, 512 ); // 1024,1536,2048,2560 .. 4096 (div 512)

	if( requestedSize < size_t{ INT_MAX } )
		return NextPowerOfTwo( static_cast<int>( requestedSize ) );

	return requestedSize + 1024; // string is too big anyway...
}

#else

size_t trgm::StringAllocationStrategy( size_t requestedSize )
{
	return requestedSize;
}

#endif // ifdef TRGM_USE_STR_GROW_OPTIMIZATION
