#include "TypeInfo.h"
#include "TypeInfo.h"
// 
// created 7/18/21 9:46pm pacific by Carson Fricke 
//

#include "TypeInfo.h"

namespace lamina 
{
    
	TypeInfo::TypeInfo(TypeInfoData* data) :
		_data(data)
	{
		_data->_type_cast->_type = _data;
	}

	TypeCast TypeInfo::cast(void* target)
	{
		_data->_type_cast->_data = target;

		return *_data->_type_cast;
	}

	size_t TypeInfo::size()
	{
		return _data->_type_item_size;
	}

	string_t TypeInfo::name() const
	{
		return _data->_type_name;
	}

	size_t TypeInfo::id()
	{
		return _data->_id;
	}

	TypeInfo::New* TypeInfo::new_wrapper()
	{
		return _data->_new;
	}

	TypeInfo::PlacementNew* TypeInfo::placement_new_wrapper()
	{
		return _data->_placement_new;
	}

	TypeInfo::Copy* TypeInfo::copy_wrapper()
	{
		return _data->_copy;
	}

	TypeInfo::Delete* TypeInfo::delete_wrapper()
	{
		return _data->_delete;
	}

	TypeInfo::PlacementDelete* TypeInfo::placement_delete_wrapper()
	{
		return _data->_placement_delete;
	}


	TypeInfo float32_typeinfo = make_typeinfo<float_t>("float32 type", 1);
	TypeInfo int32_typeinfo = make_typeinfo<int32_t>("int32 type", 2);

	TypeInfo float64_typeinfo = make_typeinfo<double_t>("float64 type", 3);
	TypeInfo int64_typeinfo = make_typeinfo<int64_t>("int64 type", 4);

	TypeInfo uint32_typeinfo = make_typeinfo<uint32_t>("uint32 type", 5);
	TypeInfo uint64_typeinfo = make_typeinfo<uint64_t>("uint64 type", 6);

	TypeInfo string_typeinfo = make_typeinfo<string_t>("string type", 7);

}
