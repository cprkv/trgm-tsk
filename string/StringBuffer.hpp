#pragma once
#include <cstddef> // size_t

namespace trgm
{
	// Manages memory for string.
	// Uses allocation optimization like std::vector.
	class StringBuffer
	{
	public:
		StringBuffer();
		~StringBuffer();

		StringBuffer( const StringBuffer& o );
		StringBuffer& operator=( const StringBuffer& o );

		StringBuffer( StringBuffer&& o );
		StringBuffer& operator=( StringBuffer&& o );

		size_t		Size() const { return m_size; }
		char*		Data() { return m_data; }
		const char* Data() const { return m_data; }

		// Resizes buffer to be able to store data of new size.
		// Does not shrink it.
		void EnsureSize( size_t newSize );

	private:
		void AllocateUnsafe( size_t realSize );

	private:
		size_t m_size;
		char*  m_data;
	};

} // namespace trgm
