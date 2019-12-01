#include "TestFramework.hpp"

using namespace trgm;

extern TestGroup StrTests();
extern TestGroup StrBufferTests();
extern TestGroup StrComparatorTests();

int main( int, char** )
{
	return RunGroups( { StrTests(),
						StrBufferTests(),
						StrComparatorTests(), } );
}
