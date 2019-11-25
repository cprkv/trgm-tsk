#include "SimpleString.hpp"
#include "SimpleStringComparator.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace trgm;

int main( int argc, char** argv )
{
	auto list = std::vector< SimpleString >
	{
		SimpleString{ "abcd" },
		SimpleString{ "ABC" },
		SimpleString{ "Bcd" },
		SimpleString{ "dbc" },
		SimpleString{ "bCda" },
		SimpleString{ "bCdE" },
		SimpleString{ "abc" },
	};

	std::sort(	std::begin(list), std::end(list), 
				SimpleStringComparator::CaseInsensitiveInverse );

	for( auto& item : list )
		std::cout << item.CStr() << '\n';

	return 0;
}
