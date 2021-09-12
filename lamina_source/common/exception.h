#ifndef __LAMINA_COMMON_EXCEPTION_H__
#define __LAMINA_COMMON_EXCEPTION_H__

#include <string>


namespace lamina 
{

	void lamina_assert(bool condition, std::string error_message);

	void lamina_throw(std::string error_message);

}

#endif // end guards
