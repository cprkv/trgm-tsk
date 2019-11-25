#pragma once
#include <cstddef>
#include <stdlib.h>

namespace trgm
{
	//	Manages memory for string.
	class StringBuffer
	{
		static constexpr char		hasSmallString				= -1;
		static constexpr char		noSmallString				= -2;
		static constexpr size_t		smallStringSize				= 16;
		static constexpr size_t		smallStringPartSize			= smallStringSize - sizeof( char* );

		static_assert				( smallStringSize > sizeof( char* ), 
									"smallStringSize should be bigger then sizeof pointer" );

	public:
									StringBuffer()				{}

		size_t						Size()						{ return size; }
		char*						Ptr()						{ return smallFirst[ 0 ] == hasSmallString ? smallFirst : data; }
		void						Resize( size_t newSize );

	private:
		size_t						size;	// full size, even includes \0 symbol
		struct
		{
			char					smallFirst[ smallStringPartSize ] = { 0 };
			char*					data;
		};
	};

	// inline realization --------------------------------------------------------------------------

	namespace details
	{
		//	REMARK:
		//	All operations on void* done via pointer and other arithmetics 
		//	to avoid usage of <string> and <cstring> headers (memcpy, and other).
		//	It is not optimal solution, I know, but task require to implement it that way.
		inline void BufferCopy( char* dst, const char* src, size_t size )	{ for( ; size--; *( dst++ ) = *( src++ ) ); }
	}

	inline void StringBuffer::Resize( size_t newSize )
	{
		if( smallFirst[ 0 ] == hasSmallString && newSize > smallStringSize )
		{
			auto* newData = reinterpret_cast< char* >( malloc( newSize ) );
			details::BufferCopy( newData, smallFirst, size );
			smallFirst[ 0 ]	= noSmallString;
			data = newData;
		}
		else if( smallFirst[ 0 ] == noSmallString && newSize <= smallStringSize )
		{
			auto* oldData = data;
			details::BufferCopy( smallFirst, oldData, newSize );
		}
		else if( smallFirst[ 0 ] == noSmallString && newSize > smallStringSize )
			data = reinterpret_cast< char* >( realloc( data, newSize ) );
		else if( smallFirst[ 0 ] == hasSmallString && newSize <= smallStringSize )
			size = newSize;
		else
			abort(); // unreal case

		size = newSize;
	}
} // namespace trgm
