// 
// created 7/18/21 9:48pm pacific by Carson Fricke 
//

#ifndef __LAMINA_TENSOR_DEVICE_H__
#define __LAMINA_TENSOR_DEVICE_H__


namespace lamina
{

	class Device
	{

		virtual void* allocate(size_t bytes) = 0;

		virtual void deallocate(void* target, size_t bytes) = 0;

	};


}

#endif // end guards
