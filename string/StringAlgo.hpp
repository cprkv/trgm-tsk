#pragma once
#include <cstddef> // size_t

namespace trgm
{
	// Common algorithms on string.
	// Task requires to implement them because <cstring> header is forbidden..

	// Same as `memcpy`.
	void MemoryCopy( char* dst, const char* src, size_t size );

	// Same as `strlen`, except for nullptr returns 0.
	size_t CStrLength( const char* str );

	// Returns number of preffered bytes to allocate for requested string size.
	// If grow optimization is disabled, always returns `requestedSize`.
	size_t StringAllocationStrategy( size_t requestedSize );

} // namespace trgm
