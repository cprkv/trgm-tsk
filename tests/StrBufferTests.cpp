#include "TestFramework.hpp"
#include "StrBuffer.hpp"
#include <cstring>

using namespace trgm;

static char* RandomString( size_t size )
{
	auto str = static_cast< char* >( malloc( size ) );
	for( size_t i = 0; i < size - 1; i++ )
		str[ i ] = ( rand() % 20 ) + 'a';
	str[ size - 1 ] = 0;
	return str;
}

DECLARE_TEST_GROUP
(
	String_Buffer_Tests,

	DECLARE_TEST_FUNC
	(
		Empty_Constructor_Makes_Buffer_At_Least_Pointer_Sized,
		{
			StrBuffer b;
			EXPECTED( b.Size() >= sizeof( void* ) );
		}
	),
	DECLARE_TEST_FUNC
	(
		Empty_Constructor_Makes_Writable_Buffer,
		{
			StrBuffer b;
			auto str = RandomString( b.Size() );
			memcpy( b.Ptr(), str, b.Size() );
			EXPECTED_CSTRING( b.Ptr(), str );
			free( str );
		}
	),
	DECLARE_TEST_FUNC
	(
		Resized_To_Big_Buffer_Is_Writable,
		{
			StrBuffer b;
			b.EnsureSize( 2048 );
			auto str = RandomString( 2048 );
			memcpy( b.Ptr(), str, 2048 );
			EXPECTED_CSTRING( b.Ptr(), str );
			free( str );
		}
	),
	DECLARE_TEST_FUNC
	(
		Resized_To_Big_Buffer_Returns_Not_Less_Size,
		{
			StrBuffer b;
			b.EnsureSize( 519 );
			EXPECTED( b.Size() >= 519 );
		}
	),
	DECLARE_TEST_FUNC
	(
		Resized_To_Small_After_To_Big_Buffer_Is_Writable,
		{
			StrBuffer b;
			b.EnsureSize( 519 );
			b.EnsureSize( 8 );
			auto str = RandomString( 8 );
			memcpy( b.Ptr(), str, 8 );
			EXPECTED_CSTRING( b.Ptr(), str );
			free( str );
		}
	),
	DECLARE_TEST_FUNC
	(
		Copy_Buffer_Creates_Memory_Copy,
		{
			StrBuffer buf;
			buf.EnsureSize( 34 );
			auto str = RandomString( 34 );
			memcpy( buf.Ptr(), str, 34 );

			StrBuffer bufCopy = buf;
			*( bufCopy.Ptr() + 3 ) = '+';

			EXPECTED( buf.Ptr() != bufCopy.Ptr() );
			EXPECTED_CSTRING( buf.Ptr(), str );
			NOT_EXPECTED_CSTRING( bufCopy.Ptr(), str );
			str[ 3 ] = '+';
			EXPECTED_CSTRING( bufCopy.Ptr(), str );
			free( str );
		}
	),
	DECLARE_TEST_FUNC
	(
		Move_Constructed_Buffer_Content_Is_Same_On_Big_String,
		{
			StrBuffer b;
			b.EnsureSize( 2048 );
			auto str = RandomString( 2048 );
			memcpy( b.Ptr(), str, 2048 );

			StrBuffer moved{ std::move( b ) };
			EXPECTED_CSTRING( moved.Ptr(), str );
			free( str );
		}
	),
	DECLARE_TEST_FUNC
	(
		Move_Constructed_Buffer_Content_Is_Same_On_Small_String,
		{
			StrBuffer b;
			b.EnsureSize( 8 );
			auto str = RandomString( 8 );
			memcpy( b.Ptr(), str, 8 );

			StrBuffer moved{ std::move( b ) };
			EXPECTED_CSTRING( moved.Ptr(), str );
			free( str );
		}
	),
	DECLARE_TEST_FUNC
	(
		Move_Assigned_Buffer_Content_Is_Same_On_Big_String,
		{
			StrBuffer b;
			b.EnsureSize( 519 );
			auto str = RandomString( 519 );
			memcpy( b.Ptr(), str, 519 );

			StrBuffer moved;
			{
				moved.EnsureSize( 615 );
				auto str2 = RandomString( 615 );
				memcpy( moved.Ptr(), str2, 615 );
				moved = std::move( b );
				free( str2 );
			}

			EXPECTED_CSTRING( moved.Ptr(), str );
			free( str );
		}
	),
	DECLARE_TEST_FUNC
	(
		EnsureSize_On_Same_Size_Not_Changes_String_Nor_Changes_Size,
		{
			StrBuffer b;
			b.EnsureSize( 519 );
			auto str = RandomString( 519 );
			memcpy( b.Ptr(), str, 519 );
			auto beforePtr = b.Ptr();
			auto beforeSize = b.Size();

			b.EnsureSize( 519 );

			EXPECTED_CSTRING( b.Ptr(), str );
			EXPECTED( b.Ptr() == beforePtr );
			EXPECTED( b.Size() == beforeSize );
			free( str );
		}
	),
	DECLARE_TEST_FUNC
	(
		EnsureSize_Resizes_In_Stable_Way_Small_Strings,
		{
			auto smallBuffer = StrBuffer{};
			auto smallBufferInitialSize = smallBuffer.Size();

			smallBuffer.EnsureSize( sizeof( void* ) - 1 );
			auto smallBufferAfterSmallResize = smallBuffer.Size();

			smallBuffer.EnsureSize( 1222 );
			smallBuffer.EnsureSize( sizeof( void* ) );
			auto smallBufferAfterBigToShortResize = smallBuffer.Size();

			EXPECTED( smallBufferInitialSize == smallBufferAfterSmallResize );
			EXPECTED( smallBufferInitialSize == smallBufferAfterBigToShortResize );
		}
	),
);
