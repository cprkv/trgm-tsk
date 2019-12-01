#include "TestFramework.hpp"
#include "StrBuffer.hpp"
#include <cstring>

using namespace trgm;

static char* RandomString( size_t size )
{
	auto str = reinterpret_cast< char* >( malloc( size ) );
	for( size_t i = 0; i < size - 1; i++ )
		str[ i ] = ( rand() % 20 ) + 'a';
	str[ size - 1 ] = 0;
	return str;
}

TestGroup StrBufferTests()
{
	return { "trgm::StrBuffer tests", {
		TRGM_DECLARE_TEST_FUNC( "Empty constructor makes Buffer at least pointer sized", 
			{
				StrBuffer b;
				TRGM_EXPECTED( b.Size() >= sizeof( void* ) );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Empty Constructor Makes Writable Buffer",
			{
				StrBuffer b;
				auto str = RandomString( b.Size() );
				memcpy( b.Ptr(), str, b.Size() );
				TRGM_EXPECTED_CSTRING( b.Ptr(), str );
				free( str );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Resized To Big Buffer Is Writable",
			{
				StrBuffer b;
				b.EnsureSize( 2048 );
				auto str = RandomString( 2048 );
				memcpy( b.Ptr(), str, 2048 );
				TRGM_EXPECTED_CSTRING( b.Ptr(), str );
				free( str );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Resized To Big Buffer Returns Not Less Size",
			{
				StrBuffer b;
				b.EnsureSize( 519 );
				TRGM_EXPECTED( b.Size() >= 519 );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Resized To Small After To Big Buffer Is Writable",
			{
				StrBuffer b;
				b.EnsureSize( 519 );
				b.EnsureSize( 8 );
				auto str = RandomString( 8 );
				memcpy( b.Ptr(), str, 8 );
				TRGM_EXPECTED_CSTRING( b.Ptr(), str );
				free( str );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Copy Buffer Creates Memory Copy",
			{
				StrBuffer buf;
				buf.EnsureSize( 34 );
				auto str = RandomString( 34 );
				memcpy( buf.Ptr(), str, 34 );

				StrBuffer bufCopy = buf;
				*( bufCopy.Ptr() + 3 ) = '+';

				TRGM_EXPECTED( buf.Ptr() != bufCopy.Ptr() );
				TRGM_EXPECTED_CSTRING( buf.Ptr(), str );
				TRGM_NOT_EXPECTED_CSTRING( bufCopy.Ptr(), str );
				str[ 3 ] = '+';
				TRGM_EXPECTED_CSTRING( bufCopy.Ptr(), str );
				free( str );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Move Constructed Buffer Content Is Same On Big String",
			{
				StrBuffer b;
				b.EnsureSize( 2048 );
				auto str = RandomString( 2048 );
				memcpy( b.Ptr(), str, 2048 );

				StrBuffer moved{ std::move( b ) };
				TRGM_EXPECTED_CSTRING( moved.Ptr(), str );
				free( str );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Move Constructed Buffer Content Is Same On Small String",
			{
				StrBuffer b;
				b.EnsureSize( 8 );
				auto str = RandomString( 8 );
				memcpy( b.Ptr(), str, 8 );

				StrBuffer moved{ std::move( b ) };
				TRGM_EXPECTED_CSTRING( moved.Ptr(), str );
				free( str );
			} ),
		TRGM_DECLARE_TEST_FUNC( "Move Assigned Buffer Content Is Same On Big String",
			{
				StrBuffer b;
				b.EnsureSize( 519 );
				auto str = RandomString( 519 );
				memcpy( b.Ptr(), str, 519 );

				StrBuffer moved;

				moved.EnsureSize( 615 );
				auto str2 = RandomString( 615 );
				memcpy( moved.Ptr(), str2, 615 );
				moved = std::move( b );
				free( str2 );

				TRGM_EXPECTED_CSTRING( moved.Ptr(), str );
				free( str );
			} ),
		TRGM_DECLARE_TEST_FUNC( "EnsureSize On Same Size Not Changes String Nor Changes Size",
			{
				StrBuffer b;
				b.EnsureSize( 519 );
				auto str = RandomString( 519 );
				memcpy( b.Ptr(), str, 519 );
				auto beforePtr = b.Ptr();
				auto beforeSize = b.Size();

				b.EnsureSize( 519 );

				TRGM_EXPECTED_CSTRING( b.Ptr(), str );
				TRGM_EXPECTED( b.Ptr() == beforePtr );
				TRGM_EXPECTED( b.Size() == beforeSize );
				free( str );
			} ),
		TRGM_DECLARE_TEST_FUNC( "EnsureSize Resizes In Stable Way Small Strings",
			{
				auto smallBuffer = StrBuffer{};
				auto smallBufferInitialSize = smallBuffer.Size();

				smallBuffer.EnsureSize( sizeof( void* ) - 1 );
				auto smallBufferAfterSmallResize = smallBuffer.Size();

				smallBuffer.EnsureSize( 1222 );
				smallBuffer.EnsureSize( sizeof( void* ) );
				auto smallBufferAfterBigToShortResize = smallBuffer.Size();

				TRGM_EXPECTED( smallBufferInitialSize == smallBufferAfterSmallResize );
				TRGM_EXPECTED( smallBufferInitialSize == smallBufferAfterBigToShortResize );
			} ), } };
}
