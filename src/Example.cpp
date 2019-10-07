#include <SimpleString.hpp>
#include <iostream>

int main( int argc, char** argv )
{
	using namespace trgm;
	SimpleString s{ "abc" };
	SimpleString s1{ std::move( s ) };
	const SimpleString s3 = s + s1;
	const SimpleString s4 = s3;
	std::cout << s4.CStr() << '\n';
	return 0;
}
