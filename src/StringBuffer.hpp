#pragma once
#include <cstddef>		// size_t
#include <cstdlib>		// malloc, free, realloc
#include <climits>		// INT_MAX
#include <cassert>		// assert

namespace trgm
{
	//	manages memory for string
	class StringBuffer
	{
		static constexpr char		noSmallString					= -1;
		static constexpr size_t		smallStringSize					= 16;
		static constexpr size_t		smallStringPart					= smallStringSize - sizeof( char* );

		static_assert				( smallStringSize > sizeof( char* ), "smallStringSize should be bigger then sizeof pointer" );

	public:
									StringBuffer()					{}
									~StringBuffer()					{ if( smallFirst[ 0 ] == noSmallString ) free( data ); }

		size_t						Size()							{ return size; }
		char*						Ptr()							{ return smallFirst[ 0 ] == noSmallString ? data : smallFirst; }
		void						EnsureSize( size_t newSize );

	private:
		size_t						size 							= smallStringSize;	// full buffer size, even includes \0 symbol and garbage
		struct
		{
			char					smallFirst[ smallStringPart ]	= { 0 };
			char*					data;
		};
	};

	//	inline implimentation -------------------------------------------------------------------------------------------------------------------

	namespace details
	{
		//	REMARK:
		//		All operations on void* done via pointer and other arithmetics 
		//		to avoid usage of <string> and <cstring> headers (memcpy, and other).
		//		It is not optimal solution, I know, but task require to implement it that way.

		inline void BufferCopy( char* dst, const char* src, size_t size )
		{
			for( ; size--; *( dst++ ) = *( src++ ) );
		}

		inline int NextPowerOfTwo( int x )
		{
			assert( x > 0 );
			x--;
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;
			return x + 1;
		}
	}

	inline void StringBuffer::EnsureSize( size_t newSize )
	{
		if( newSize != size )								// could be skipped or inverted statement be unlikely
		{
			if( newSize > smallStringSize )					// new sized buffer should live on heap
			{
				if( newSize < size_t{ INT_MAX } )
					newSize = details::NextPowerOfTwo( static_cast< int >( newSize ) );

				if( smallFirst[ 0 ] != noSmallString )		// it was small string, but now it should be relocated to heap
				{
					auto* newData = reinterpret_cast< char* >( malloc( newSize ) );
					details::BufferCopy( newData, smallFirst, size );
					smallFirst[ 0 ]	= noSmallString;
					data = newData;
				}
				else if( newSize != size )					// it was allocated in heap, and now it should be resized
				{
					data = reinterpret_cast< char* >( realloc( data, newSize ) );
				}
			}

			// remark: skipped for optimization
			// else if( smallFirst[ 0 ] == noSmallString )		// it was allocated in heap, but now it needs to be relocated to stack
			// {
			// 	auto* oldData = data;
			// 	details::BufferCopy( smallFirst, oldData, newSize );
			// 	free( oldData );
			// }

			size = newSize;
		}
	}
} // namespace trgm
