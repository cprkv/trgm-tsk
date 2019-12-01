#pragma once
#include <cstddef>		// size_t
#include <cstdlib>		// malloc, free, realloc

namespace trgm {

	//	Manages memory for string.
	//	Stores small strings in local space.
	class StrBuffer
	{
		static constexpr char		noSmallString			= -1;
		static constexpr size_t		smallStringSize			= 16;
		static constexpr size_t		smallStringPart			= smallStringSize - sizeof( char* );

		static_assert(	smallStringSize > sizeof( char* ),
						"smallStringSize should be bigger then sizeof pointer" );

	public:
						StrBuffer()							{}
						StrBuffer( const StrBuffer& o );
						StrBuffer( StrBuffer&& o );
						~StrBuffer()						{	if( m_smallFirst[ 0 ] == noSmallString )  free( m_data );			}

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
		// full buffer size, even includes \0 symbol and garbage
		size_t			m_size 		= smallStringSize;

	#pragma pack( push, 1 )
		struct
		{
			char		m_smallFirst[ smallStringPart ]	= { 0 };
			char*		m_data;
		};
	#pragma pack( pop )
	};

}	// namespace trgm
