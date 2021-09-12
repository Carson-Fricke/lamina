// 
// created 7/18/21 9:46pm pacific by Carson Fricke 
//

#ifndef __LAMINA_TENSOR_TYPEINFO_H__
#define __LAMINA_TENSOR_TYPEINFO_H__

#include "../../common/common.h"


namespace lamina
{

	class TypeInfo
	{

		using New = void*();
		using PlacementNew = void(void*, size_t);
		using Copy = void(const void*, void*, size_t);
		using Delete = void(void*);
		using PlacementDelete = void(void*, size_t);


		private:
			
			size_t _type_item_size;
			string_t _type_name;
			//size_t _id;

			New* _new;
			PlacementNew* _placement_new;
			Copy* _copy;
			Delete* _delete;
			PlacementDelete* _placement_delete;
		
		public:

			size_t type_size() 
			{
				return _type_item_size;
			}

			string_t type_name() 
			{
				return _type_name;
			}

			TypeInfo
			(
				size_t type_size,
				string_t type_name,
				New* new_function,
				PlacementNew* placement_new_function,
				Copy* copy_function,
				Delete* delete_function,
				PlacementDelete* placement_delete_function
			) :
				_type_item_size(type_size),
				_type_name(type_name),
				_new(new_function),
				_placement_new(placement_new_function), 
				_copy(copy_function),
				_delete(delete_function),
				_placement_delete(placement_delete_function)
			{}


	};


	// wrapper for the new builtin
	template<typename T>
	inline void* _new_() 
	{
		return new T;
	}

	template<typename T>
	inline void* _new_unsupported_()
	{
		lamina_throw("Type T is not default constructable, new builtin is unsupported");
		return nullptr;
	}

	// determines whether the new keyword works for T
	template<typename T,
	typename std::enable_if<std::is_default_constructible<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfo::New* _choose_new_() 
	{
		return &_new_<T>;
	}

	template<typename T,
	typename std::enable_if<!std::is_default_constructible<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfo::New* _choose_new_()
	{
		return &_new_unsupported_<T>;
	}


	// wrapper for new array initialization
	template<typename T>
	inline void _placement_new_(void* target, size_t size) 
	{
		T* typed = static_cast<T*>(target);
		for (size_t index = 0; index < size; index++) 
		{
			new (typed + index) T;
		}
	}

	template<typename T>
	inline void _placement_new_unsupported_(void* target, size_t size) 
	{
		lamina_throw("Type T is not default constructable, placement new is unsupported")
	}

	// determines whether placement new works for T
	template<typename T,
	typename std::enable_if<std::is_default_constructible<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfo::PlacementNew* _choose_placement_new_()
	{
		return &_placement_new_<T>;
	}

	template<typename T,
	typename std::enable_if<!std::is_default_constructible<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfo::PlacementNew* _choose_placement_new_()
	{
		return &_placement_new_unsupported_<T>;
	}


	// wrapper for copy functionality
	template<typename T>
	inline void _copy_(const void* source, void* target, size_t size)
	{
		const T* typed_source = static_cast<const T*>(source);
		T* typed_target = static_cast<T*>(target);

		for (size_t index = 0; index < size; index++) 
		{
			typed_target[index] = typed_source[index];
		}
	}

	template<typename T>
	inline void _copy_unsupported_(const void* source, void* target, size_t size) 
	{
		lamina_throw("Type T is not copy assignable, copy unsupported");
	}

	template<typename T, 
	typename std::enable_if<std::is_copy_assignable<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfo::Copy* _choose_copy_() 
	{
		if (std::is_fundamental<T>::value || std::is_pointer<T>::value) 
		{
			return nullptr;
		}
		else 
		{
			return &_copy_<T>;
		}
	}

	template<typename T,
	typename std::enable_if<!std::is_copy_assignable<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfo::Copy* _choose_copy_()
	{
		lamina_assert(!std::is_fundamental<T>::value && !std::is_pointer<T>::value, "this should have picked the other case");

		return &_copy_unsupported_<T>;
	}


	// wrapper for delete builtin functionality
	template<typename T>
	inline void _delete_(void* target) 
	{
		T* typed = static_cast<T*>(target);

		delete typed;
	}

	// no need for enable ifs and _delete_unsupported_ because everything is delete-able
	template<typename T>
	inline constexpr TypeInfo::Delete* _choose_delete_() 
	{
		return &_delete_<T>;
	}
	

	// wrapper for placement delete
	template<typename T>
	inline void _placement_delete_(void* target, size_t size) 
	{
		T* typed = static_cast<T*>(target);

		for (size_t index = 0; index < size; index++)
		{
			typed[index].~T();
		}
		delete typed;
		typed = nullptr;
	}

	template<typename T>
	inline constexpr TypeInfo::PlacementDelete* _choose_placement_delete_() 
	{
		if (std::is_fundamental<T>::value || std::is_pointer<T>::value)
		{
			return nullptr;
		}
		else
		{
			return &_placement_delete_<T>;
		}
	}


	template<typename T>
	inline TypeInfo _make_type_info_(string_t type_name)
	{		
		return {
			sizeof(T),
			type_name,
			_choose_new_<T>(),
			_choose_placement_new_<T>(),
			_choose_copy_<T>(),
			_choose_delete_<T>(),
			_choose_placement_delete_<T>()
		};
	}

}

#endif // end guards
