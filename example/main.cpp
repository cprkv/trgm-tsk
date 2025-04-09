#include "String.hpp"
#include <algorithm> // std::sort
#include <iostream>	 // std::cin, std::cout
#include <vector>

using namespace trgm;

// Программа должна принимать список строк, затем выдавать его в порядке, обратном
// лексикографическому без учета регистра. Поддержки кодировки ASCII будет достаточно

int main( int, char** )
{
	std::vector<String> list;

	while( !std::cin.eof() )
	{
		String tmp;
		std::cin >> tmp;

		if( tmp.Length() == 0 )
			break;

		list.emplace_back( std::move( tmp ) );
	}

	std::sort( list.begin(), list.end(), comparators::CaseInsensitiveInverse );

	for( const auto& item: list )
		std::cout << item << '\n';

	return 0;
}
