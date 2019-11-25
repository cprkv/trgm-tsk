#include "SimpleString.hpp"
#include "SimpleStringComparator.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace trgm;

int main( int argc, char** argv )
{
	auto list = std::vector< SimpleString >{};

	SimpleString tmp;

	do
	{
		std::cin >> tmp;
		if( tmp.Length() == 0 )
			continue;
		list.push_back( std::move( tmp ) );
	}
	while( ! std::cin.eof() );

	std::sort(	std::begin(list), std::end(list), 
				SimpleStringComparator::CaseInsensitiveInverse );

	for( auto& item : list )
		std::cout << item.CStr() << '\n';

	return 0;
}
