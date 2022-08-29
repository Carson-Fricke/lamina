// 
// created 7/17/21 9:43pm pacific by Carson Fricke 
//

#ifndef __LAMINA_TENSORIMPL_H__
#define __LAMINA_TENSORIMPL_H__

#include "dynamic_storage/DynamicStorage.h"

namespace lamina 
{

	class TensorImpl 
	{
	
		private:
			
			DynamicStorage* _data;

			size_t _numel;

			size_t _dims;

			bool _contiguous;

			vector_t<size_t> _sizes;

			vector_t<size_t> _strides;

			size_t _storage_offset;

		protected:

			static size_t compute_numel(UIntRefArray sizes);

			static size_t compute_storage_size(UIntRefArray sizes, UIntRefArray strides);

			static bool compute_contiguous(UIntRefArray sizes, UIntRefArray strides);

			void refresh_numel();

			void refresh_contiguous();

			void refresh_contiguous_strides();

			TensorImpl(DynamicStorage* source, UIntRefArray sizes, UIntRefArray strides, size_t offset);

		public:
			
			TensorImpl(UIntRefArray sizes, TypeInfo& type);
			
			TensorImpl(UIntRefArray sizes, TypeInfo& type, Device& device);

			void set_sizes_strides_offset(UIntRefArray sizes, UIntRefArray strides, size_t offset);

			TensorImpl select(size_t index);

			size_t numel();

			size_t dims();

			vector_t<size_t> get_sizes();

			vector_t<size_t> get_strides();

			int64_t size(size_t i);

			int64_t stride(size_t i);

			TypeCast data() 
			{
				return _data->data();
			}

			~TensorImpl();
	
	};

	
}


#endif // end guards
