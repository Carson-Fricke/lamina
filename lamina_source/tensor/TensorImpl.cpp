// 
// created 7/17/21 9:43pm pacific by Carson Fricke 
//

#include "TensorImpl.h"
#include "CPUDefaultDevice.h"

namespace lamina 
{
	
	size_t TensorImpl::compute_numel(UIntRefArray sizes)
	{
		int64_t out = 1;

		for (size_t i = 0; i < sizes.size(); i++) 
		{
			out *= sizes[i];
		}
		
		return out;
	}
	
	size_t TensorImpl::compute_storage_size(UIntRefArray sizes, UIntRefArray strides)
	{
		lamina_assert(sizes.size() == strides.size(), "dims of sizes and strides must match");
		
		if (compute_numel(sizes) == 0)
		{
			return 0;
		}

		int64_t out = 1;

		for (size_t i = 0; i < sizes.size(); i++)
		{
			out += strides[i] * (sizes[i] - 1);
		}

		return out;
	}

	bool TensorImpl::compute_contiguous(UIntRefArray sizes, UIntRefArray strides)
	{
		
		lamina_assert(sizes.size() == strides.size(), "dims of sizes and strides must match");
		
		int64_t stride = 1;

		for (int64_t i = sizes.size() - 1; i >= 0; i--) 
		{
			if (sizes[i] != 1) 
			{
				if (strides[i] == stride)
				{
					stride *= sizes[i];
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}

	void TensorImpl::refresh_numel()
	{
		_numel = compute_numel(_sizes);
	}

	void TensorImpl::refresh_contiguous()
	{
		_contiguous = compute_contiguous(_sizes, _strides);
	}

	void TensorImpl::refresh_contiguous_strides()
	{

		// does not check for matching values
		//lamina_assert(_sizes.size() == _strides.size(), "dims of sizes and strides must match");

		int64_t stride = 1;

		for (int64_t i = _dims - 1; i >= 0; i--) 
		{
			_strides[i] = stride;

			stride *= _sizes[i];
		}

	}

	void TensorImpl::set_sizes_strides_offset(UIntRefArray sizes, UIntRefArray strides, size_t offset)
	{
		
		lamina_assert(sizes.size() == strides.size(), "sizes and strides must share the same length");
		lamina_assert(compute_storage_size(sizes, strides) + offset <= _numel, "computed storage size would exceed bounds of tensor");

		_dims = sizes.size();
		_storage_offset = offset;

		_sizes.resize(_dims);
		_strides.resize(_dims);

		for (size_t i = 0; i < _dims; i++) 
		{
			_sizes[i] = sizes[i];
		}

		for (size_t i = 0; i < _dims; i++) 
		{
			_strides[i] = strides[i];
		}

		refresh_numel();
		refresh_contiguous();

	}

	TensorImpl::TensorImpl(UIntRefArray sizes, TypeInfo& type) :
		_data(new DynamicStorage(compute_numel(sizes), type, cpu_default_device)),
		_numel(_data->numel()),
		_dims(sizes.size()),
		_contiguous(true),
		_sizes(sizes.vec()),
		_strides(_dims),
		_storage_offset(0)
	{
		refresh_contiguous_strides();
	}

	TensorImpl::TensorImpl(UIntRefArray sizes, TypeInfo& type, Device& device) :
		_data(new DynamicStorage(compute_numel(sizes), type, device)),
		_numel(_data->numel()),
		_dims(sizes.size()),
		_contiguous(true),
		_sizes(sizes.vec()),
		_strides(_dims),
		_storage_offset(0)
	{
		refresh_contiguous_strides();
	}

	TensorImpl::TensorImpl(DynamicStorage* source, UIntRefArray sizes, UIntRefArray strides, size_t offset) : 
		_data(source),
		_numel(0),
		_dims(0),
		_contiguous(true),
		_sizes(),
		_strides(),
		_storage_offset(0)
	{
		set_sizes_strides_offset(sizes, strides, offset);
		_data->_reference_count++;
	}

	TensorImpl TensorImpl::select(size_t index)
	{
		
		lamina_assert(index < _dims, "index must be in bounds for tensor");

		vector_t<size_t> new_sizes = _sizes;

		vector_t<size_t> new_strides = _strides;

		if (_dims > 1) 
		{
			new_sizes.erase(new_sizes.begin());
			new_strides.erase(new_strides.begin());
		} 
		else
		{
			new_sizes[0] = 1;
			new_strides[0] = 1;
		}

		size_t new_offset = _storage_offset + _strides[0] * index;
		
		return TensorImpl(_data, new_sizes, new_strides, new_offset);
	}

	size_t TensorImpl::numel()
	{
		return _numel;
	}

	size_t TensorImpl::dims()
	{
		return _dims;
	}

	vector_t<size_t> TensorImpl::get_sizes()
	{
		return _sizes;
	}

	vector_t<size_t> TensorImpl::get_strides()
	{
		return _strides;
	}

	int64_t TensorImpl::size(size_t i)
	{
		lamina_assert(i < _dims, "index must be in bounds");

		return _sizes[i];
	}

	int64_t TensorImpl::stride(size_t i)
	{
		lamina_assert(i < _dims, "index must be in bounds");

		return _strides[i];
	}

	TensorImpl::~TensorImpl()
	{
		if (_data && --(_data->_reference_count) == 0) 
		{
			delete _data;
		}
	}


}
