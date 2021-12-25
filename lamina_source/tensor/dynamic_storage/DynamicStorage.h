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
			
			friend class TensorImpl;

			void* _raw_data;

			size_t _numel;

			Device& _device;

			TypeInfo _type;

			size_t _reference_count;

		public:

			DynamicStorage(size_t numel, TypeInfo type_info, Device& device);

			size_t numel();

			size_t item_size();

			Device& device();

			TypeInfo type();


			// only returns the data if it matches the TypeInfo
			template<typename T>
			T* data() 
			{
				if (_type != get_typeinfo<T>()) 
				{
					lamina_throw("Type T does not match the TypeInfo stored in _type");
				}

				return static_cast<T*>(_raw_data);
			}

			template<typename T>
			T* unsafe_data() 
			{
				return static_cast<T*>(_raw_data);
			}

			~DynamicStorage();

	};


}

#endif // end guards
