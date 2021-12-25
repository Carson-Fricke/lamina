// 
// created 11/13/21 2:56pm pacific by Carson Fricke 
//

#ifndef __LAMINA_TENSOR_CPUDEFAULTDEVICE_H__
#define __LAMINA_TENSOR_CPUDEFAULTDEVICE_H__

#include "Device.h"
#include <utility>

namespace lamina 
{

	class CPUDefaultDevice : public Device 
	{
	
		public:

			void* allocate(size_t bytes) override;

			void free(void* target) override;

	};

	static CPUDefaultDevice cpu_default_device;

}


#endif // end guards