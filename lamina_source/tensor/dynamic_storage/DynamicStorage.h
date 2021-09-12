// 
// created 7/18/21 9:36pm pacific by Carson Fricke 
//

#ifndef __LAMINA_TENSOR_DYNAMICSTORAGE_H__
#define __LAMINA_TENSOR_DYNAMICSTORAGE_H__

#include "Device.h"
#include "TypeInfo.h"


namespace lamina 
{

	class DynamicStorage 
	{
		
		private:
			
			void* _raw_data;

			size_t _size;

			Device* _device;

			TypeInfo _type;

		public:
			
			DynamicStorage();

			DynamicStorage(TypeInfo type_info);

			DynamicStorage(size_t size, TypeInfo type_info);

			void bind_type(TypeInfo type_info);

			void allocate(size_t size);

	};


}

#endif // end guards
