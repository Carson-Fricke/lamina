// 
// created 11/13/21 2:56pm pacific by Carson Fricke 
//

#include "CPUDefaultDevice.h"

void* lamina::CPUDefaultDevice::allocate(size_t bytes)
{
	return std::malloc(bytes);
}

void lamina::CPUDefaultDevice::free(void* target)
{
	std::free(target);
}
