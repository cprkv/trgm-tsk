#include <SimpleString.hpp>
#include <iostream>

int main( int argc, char** argv )
{
	using namespace trgm;

	SimpleString s{ "abc" };
	SimpleString s1{ std::move( s ) };
	const SimpleString s3 = s + s1;
	const SimpleString s4 = s3;
	const SimpleString s5 = std::move( s1 );
	std::cout << s4.CStr() << '\n';

	const auto a1 = SimpleString{ "qwe" };
	const auto a2 = SimpleString{ "rtytbd" };
	const auto a3 = a1 + a2;
	std::cout << a1.CStr() << '+' << a2.CStr() << '=' << a3.CStr() << '\n';

	return 0;
}
