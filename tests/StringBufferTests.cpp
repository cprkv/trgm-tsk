#include "TestFramework.hpp"
#include "StringBuffer.hpp"
#include <cstring>

using namespace trgm;

static char* RandomString( size_t size )
{
	auto str = reinterpret_cast<char*>( malloc( size ) );
	for( size_t i = 0; i < size - 1; i++ )
		str[i] = ( rand() % 20 ) + 'a';
	str[size - 1] = 0;
	return str;
}

static TestCaseResult EmptyConstructorIsOptimal()
{
	StringBuffer b;
	TRGM_REQUIRE( b.Size() == 0 );
	TRGM_REQUIRE( b.Data() == nullptr );
	return TestCaseResult::OK;
}

static TestCaseResult ResizedToBigBufferIsWritable()
{
	StringBuffer b;
	b.EnsureSize( 2048 );
	auto str = RandomString( 2048 );
	memcpy( b.Data(), str, 2048 );
	TRGM_REQUIRE_CSTRING( b.Data(), str );
	free( str );
	return TestCaseResult::OK;
}

static TestCaseResult ResizedToBigBufferReturnsNotLessSize()
{
	StringBuffer b;
	b.EnsureSize( 519 );
	TRGM_REQUIRE( b.Size() >= 519 );
	return TestCaseResult::OK;
}

static TestCaseResult ResizedToSmallAfterToBigBufferIsWritable()
{
	StringBuffer b;
	b.EnsureSize( 519 );
	b.EnsureSize( 8 );
	auto str = RandomString( 8 );
	memcpy( b.Data(), str, 8 );
	TRGM_REQUIRE_CSTRING( b.Data(), str );
	free( str );
	return TestCaseResult::OK;
}

static TestCaseResult CopyBufferCreatesMemoryCopy()
{
	StringBuffer buf;
	buf.EnsureSize( 34 );
	auto str = RandomString( 34 );
	memcpy( buf.Data(), str, 34 );

	StringBuffer bufCopy	= buf;
	*( bufCopy.Data() + 3 ) = '+';

	TRGM_REQUIRE( buf.Data() != bufCopy.Data() );
	TRGM_REQUIRE_CSTRING( buf.Data(), str );
	TRGM_NOT_EXPECTED_CSTRING( bufCopy.Data(), str );
	str[3] = '+';
	TRGM_REQUIRE_CSTRING( bufCopy.Data(), str );
	free( str );
	return TestCaseResult::OK;
}

static TestCaseResult MoveConstructedBufferContentIsSameOnBigString()
{
	StringBuffer b;
	b.EnsureSize( 2048 );
	auto str = RandomString( 2048 );
	memcpy( b.Data(), str, 2048 );

	StringBuffer moved{ std::move( b ) };
	TRGM_REQUIRE_CSTRING( moved.Data(), str );
	free( str );
	return TestCaseResult::OK;
}

static TestCaseResult MoveConstructedBufferContentIsSameOnSmallString()
{
	StringBuffer b;
	b.EnsureSize( 8 );
	auto str = RandomString( 8 );
	memcpy( b.Data(), str, 8 );

	StringBuffer moved{ std::move( b ) };
	TRGM_REQUIRE_CSTRING( moved.Data(), str );
	free( str );
	return TestCaseResult::OK;
}

static TestCaseResult MoveAssignedBufferContentIsSameOnBigString()
{
	StringBuffer b;
	b.EnsureSize( 519 );
	auto str = RandomString( 519 );
	memcpy( b.Data(), str, 519 );

	StringBuffer moved;

	moved.EnsureSize( 615 );
	auto str2 = RandomString( 615 );
	memcpy( moved.Data(), str2, 615 );
	moved = std::move( b );
	free( str2 );

	TRGM_REQUIRE_CSTRING( moved.Data(), str );
	free( str );
	return TestCaseResult::OK;
}

static TestCaseResult EnsureSizeOnSameSizeNotChangesStringNorChangesSize()
{
	StringBuffer b;
	b.EnsureSize( 519 );
	auto str = RandomString( 519 );
	memcpy( b.Data(), str, 519 );
	auto beforePtr	= b.Data();
	auto beforeSize = b.Size();

	b.EnsureSize( 519 );

	TRGM_REQUIRE_CSTRING( b.Data(), str );
	TRGM_REQUIRE( b.Data() == beforePtr );
	TRGM_REQUIRE( b.Size() == beforeSize );
	free( str );
	return TestCaseResult::OK;
}

static TestCaseResult EnsureSizeResizesInStableWaySmallStrings()
{
	StringBuffer smallBuffer;
	auto		 smallBufferInitialSize = smallBuffer.Size();
	TRGM_REQUIRE( smallBufferInitialSize == 0 );

	smallBuffer.EnsureSize( 8 );
	auto smallBufferAfterSmallResize = smallBuffer.Size();
	TRGM_REQUIRE( smallBufferAfterSmallResize >= 8 );

	smallBuffer.EnsureSize( 1222 );
	smallBuffer.EnsureSize( 8 );
	auto smallBufferAfterBigToShortResize = smallBuffer.Size();
	TRGM_REQUIRE( smallBufferAfterBigToShortResize == smallBufferAfterSmallResize );

	return TestCaseResult::OK;
}

TRGM_REGISTER_TEST_CASE( EmptyConstructorIsOptimal );
TRGM_REGISTER_TEST_CASE( ResizedToBigBufferIsWritable );
TRGM_REGISTER_TEST_CASE( ResizedToBigBufferReturnsNotLessSize );
TRGM_REGISTER_TEST_CASE( ResizedToSmallAfterToBigBufferIsWritable );
TRGM_REGISTER_TEST_CASE( CopyBufferCreatesMemoryCopy );
TRGM_REGISTER_TEST_CASE( MoveConstructedBufferContentIsSameOnBigString );
TRGM_REGISTER_TEST_CASE( MoveConstructedBufferContentIsSameOnSmallString );
TRGM_REGISTER_TEST_CASE( MoveAssignedBufferContentIsSameOnBigString );
TRGM_REGISTER_TEST_CASE( EnsureSizeOnSameSizeNotChangesStringNorChangesSize );
TRGM_REGISTER_TEST_CASE( EnsureSizeResizesInStableWaySmallStrings );
