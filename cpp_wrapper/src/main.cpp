#include <iostream>
#include "item.hpp"

int main(void)
{
	cht::item item("./chaussette_file/testlips.LPS", "name", "main");

	if (item.get() == false)
		std::cerr << "item search failed\n";
	std::cout << item["name"] << std::endl;

	return (1);
}