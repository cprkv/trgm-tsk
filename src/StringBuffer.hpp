#pragma once
#include <cstddef>		// size_t
#include <cstdlib>		// malloc, free, realloc
#include <climits>		// INT_MAX
#include <cassert>		// assert
#include <utility>		// std::swap

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
									StringBuffer( const StringBuffer& );
									StringBuffer( StringBuffer&& );
									~StringBuffer()					{ if( smallFirst[ 0 ] == noSmallString )  free( data ); }

		size_t						Size() const					{ return size; }
		char*						Ptr()							{ return smallFirst[ 0 ] == noSmallString ? data : smallFirst; }
		const char*					Ptr() const						{ return smallFirst[ 0 ] == noSmallString ? data : smallFirst; }
		void						EnsureSize( size_t newSize );		// resize buffer for it to be able to store data of new size
		void						Fill( const char* src, size_t srcSize, ptrdiff_t shift = 0 );	// copy src content into buffer

		StringBuffer&				operator=( const StringBuffer& );
		StringBuffer&				operator=( StringBuffer&& );

	private:
		size_t						size = smallStringSize;		// full buffer size, even includes \0 symbol and garbage

	#pragma pack( push, 1 )
		struct
		{
			char					smallFirst[ smallStringPart ]	= { 0 };
			char*					data;
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

	inline StringBuffer::StringBuffer( const StringBuffer& other )
	{
		size = other.size;

		if( other.smallFirst[ 0 ] == noSmallString )
		{
			smallFirst[ 0 ] = noSmallString;
			data = static_cast< char* >( malloc( size ) );
			details::BufferCopy( data, other.data, size );
		}
		else
		{
			details::BufferCopy( smallFirst, other.smallFirst, size );
		}
	}

	inline StringBuffer::StringBuffer( StringBuffer&& other )
	{
		std::swap( size, other.size );
		std::swap< char, smallStringPart >( smallFirst, other.smallFirst );
		std::swap( data, other.data );
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
					auto* newData = static_cast< char* >( malloc( newSize ) );
					details::BufferCopy( newData, smallFirst, size );
					smallFirst[ 0 ]	= noSmallString;
					data = newData;
				}
				else if( newSize != size )					// it was allocated in heap, and now it should be resized
				{
					data = static_cast< char* >( realloc( data, newSize ) );
				}

				size = newSize;
			}
			else
			{
				if( smallFirst[ 0 ] == noSmallString )		// it was allocated in heap, but now it needs to be relocated to stack
				{
					auto* oldData = data;
					details::BufferCopy( smallFirst, oldData, newSize );
					free( oldData );
				}

				size = smallStringSize;
			}
		}
	}

	inline void StringBuffer::Fill( const char* src, size_t srcSize, ptrdiff_t shift )
	{
		size_t requiredSize = shift + srcSize;
		if( requiredSize > size )
			EnsureSize( requiredSize );

		details::BufferCopy( Ptr() + shift, src, srcSize );
	}

	inline StringBuffer& StringBuffer::operator=( const StringBuffer& other )
	{
		if( smallFirst[ 0 ] == noSmallString )
			free( data );

		size = other.size;

		if( other.smallFirst[ 0 ] == noSmallString )
		{
			smallFirst[ 0 ] = noSmallString;
			data = static_cast< char* >( malloc( size ) );
			details::BufferCopy( data, other.data, size );
		}
		else
		{
			details::BufferCopy( smallFirst, other.smallFirst, size );
		}

		return *this;
	}

	inline StringBuffer& StringBuffer::operator=( StringBuffer&& other )
	{
		if( smallFirst[ 0 ] == noSmallString )
			free( data );

		size = smallStringSize;
		smallFirst[ 0 ] = 0;

		std::swap( size, other.size );
		std::swap< char, smallStringPart >( smallFirst, other.smallFirst );
		std::swap( data, other.data );

		return *this;
	}
}
