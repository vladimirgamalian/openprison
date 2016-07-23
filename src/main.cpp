#include <iostream>
#include <exception>
#include <memory>
#include "App.h"

int main(int argc, char *args[])
{
	try
	{
		std::unique_ptr<App> app(new App);
		app->execute();
		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
