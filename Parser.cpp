#include "EverquestLog.h"
#include <iostream>
int main()
{
	try
	{
		EverquestLog everQuestLog{ "Resources/GildisLog.txt" };
		everQuestLog.PrintData();
	}
	catch (const std::exception& exception)
	{
		std::cout << "Exception thrown: " << exception.what() << std::endl;
	}
	std::cin.get();
}