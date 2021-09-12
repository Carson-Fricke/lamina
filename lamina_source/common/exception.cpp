
#include "exception.h"
#include <stdexcept>
#include <iostream>

namespace lamina 
{
	
	void lamina_assert(bool condition, std::string error_message)
	{
		if (!condition) 
		{
			lamina_throw(error_message);
		}
	}
	
	void lamina_throw(std::string error_message)
	{
		
		std::cout << "Runtime Error: " << error_message << std::endl;
		
		throw std::runtime_error(error_message);
	}

}