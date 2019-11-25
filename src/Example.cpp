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
	while( ! std::cin.eof() )
	{
		std::cin >> tmp;
		list.push_back( std::move( tmp ) );
	}

	std::sort(	std::begin(list), std::end(list), 
				SimpleStringComparator::CaseInsensitiveInverse );

	for( auto& item : list )
		std::cout << item.CStr() << '\n';

	return 0;
}
