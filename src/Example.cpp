#include <SimpleString.h>
#include <memory>

using namespace trgm;

int main(int argc, char** argv)
{	
	SimpleString s{ "abc" };
	SimpleString s1{ std::move( s ) };
	SimpleString s3 = s + s1;
	return 0;
}
