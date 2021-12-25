// 
// created 7/18/21 9:46pm pacific by Carson Fricke 
//

#include "TypeInfo.h"

namespace lamina 
{
    
	TypeInfo::TypeInfo(TypeInfoData* data) :
		_data(data)
	{}

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

}
