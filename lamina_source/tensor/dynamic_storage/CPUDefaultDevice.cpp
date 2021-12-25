// 
// created 11/13/21 2:56pm pacific by Carson Fricke 
//

#include "CPUDefaultDevice.h"

void* lamina::CPUDefaultDevice::allocate(size_t bytes)
{

	//_raw_memory.push_back(std::pair<void*, size_t>(malloc(bytes), bytes));
	
	//return _raw_memory[_raw_memory.size()-1].first;

	return malloc(bytes);
}

void lamina::CPUDefaultDevice::free(void* target)
{
	std::free(target);
}
