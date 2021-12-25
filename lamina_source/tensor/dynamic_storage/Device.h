// 
// created 7/18/21 9:48pm pacific by Carson Fricke 
//

#ifndef __LAMINA_TENSOR_DEVICE_H__
#define __LAMINA_TENSOR_DEVICE_H__

#include "TypeInfo.h"


namespace lamina
{

	class Device
	{
		
		protected:

			//vector_t<std::pair<void*, size_t>> _raw_memory;
		
		public:

			virtual void* allocate(size_t bytes) = 0;

			virtual void free(void* target) = 0;

	};


}

#endif // end guards
