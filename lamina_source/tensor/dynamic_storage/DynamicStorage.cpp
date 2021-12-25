// 
// created 7/18/21 9:36pm pacific by Carson Fricke 
//

#include "DynamicStorage.h"

namespace lamina 
{
    //DynamicStorage::DynamicStorage() :
    //    _numel(0),
    //    _type(nullptr)
    //{
    //}

    DynamicStorage::DynamicStorage(size_t numel, TypeInfo type, Device& device) :
        _raw_data(device.allocate(numel* type.size())),
        _numel(numel),
        _device(device),
        _type(type),
        _reference_count(1)
    {
        _type.placement_new_wrapper()(_raw_data, _numel);
    }

    size_t DynamicStorage::numel()
    {
        return _numel;
    }

    size_t DynamicStorage::item_size()
    {
        return _type.size();
    }

    Device& DynamicStorage::device()
    {
        return _device;
    }

    TypeInfo DynamicStorage::type()
    {
        return _type;
    }

    DynamicStorage::~DynamicStorage()
    {
        _device.free(_raw_data);
    }

}
