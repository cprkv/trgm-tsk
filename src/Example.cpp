#include "Str.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace trgm;

int main( int argc, char** argv )
{
	auto list = std::vector< Str >{};

	for( Str tmp; ! std::cin.eof(); )
	{
		std::cin >> tmp;
		if( tmp.Length() == 0 )
			break;
		list.push_back( std::move( tmp ) );
	}

	std::sort( std::begin( list ), std::end( list ), comparators::CaseInsensitiveInverse );

	for( auto& item : list )
		std::cout << item << '\n';

	return 0;
}
