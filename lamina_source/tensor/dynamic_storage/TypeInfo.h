// 
// created 7/18/21 9:46pm pacific by Carson Fricke 
//

#ifndef __LAMINA_TENSOR_TYPEINFO_H__
#define __LAMINA_TENSOR_TYPEINFO_H__

#include "../../common/common.h"


namespace lamina
{


	struct TypeCast;

	struct TypeInfoData
	{

		using New = void*();
		using PlacementNew = void(void*, size_t);
		using Copy = void(const void*, void*, size_t);
		using Delete = void(void*);
		using PlacementDelete = void(void*, size_t);


		public:

			size_t _type_item_size;
			string_t _type_name;
			size_t _id;

			New* _new;
			PlacementNew* _placement_new;
			Copy* _copy;
			Delete* _delete;
			PlacementDelete* _placement_delete;

			TypeCast* _type_cast;

			TypeInfoData
			(
				size_t type_size,
				string_t type_name,
				size_t id,
				New* new_function,
				PlacementNew* placement_new_function,
				Copy* copy_function,
				Delete* delete_function,
				PlacementDelete* placement_delete_function,
				TypeCast* type_cast
			) :
				_type_item_size(type_size),
				_type_name(type_name),
				_id(id),
				_new(new_function),
				_placement_new(placement_new_function),
				_copy(copy_function),
				_delete(delete_function),
				_placement_delete(placement_delete_function),
				_type_cast(type_cast)
			{}


	};


	// wrapper for the new builtin
	template<typename T>
	inline void* _new_() 
	{
		return new T();
	}

	template<typename T>
	inline void* _new_unsupported_()
	{
		lamina_throw("Type T is not default constructable, new builtin is unsupported");
		return nullptr;
	}

	// determines whether the new keyword works for T
	template<typename T,
	typename std::enable_if<std::is_trivially_default_constructible<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfoData::New* _choose_new_() 
	{
		return &_new_<T>;
	}

	template<typename T,
	typename std::enable_if<!std::is_trivially_default_constructible<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfoData::New* _choose_new_()
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
			new (typed + index) T();
		}
	}

	template<typename T>
	inline void _placement_new_unsupported_(void* target, size_t size) 
	{
		lamina_throw("Type T is not default constructable, placement new is unsupported");
	}

	// determines whether placement new works for T
	template<typename T,
	typename std::enable_if<std::is_trivially_default_constructible<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfoData::PlacementNew* _choose_placement_new_()
	{
		return &_placement_new_<T>;
	}

	template<typename T,
	typename std::enable_if<!std::is_trivially_default_constructible<T>::value, void>::type* = nullptr>
	inline constexpr TypeInfoData::PlacementNew* _choose_placement_new_()
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
	inline constexpr TypeInfoData::Copy* _choose_copy_() 
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
	inline constexpr TypeInfoData::Copy* _choose_copy_()
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
	inline constexpr TypeInfoData::Delete* _choose_delete_() 
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
	}

	template<typename T>
	inline constexpr TypeInfoData::PlacementDelete* _choose_placement_delete_() 
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
	inline constexpr TypeCast* _choose_type_cast_() 
	{
		return new TypeCast();
	}


	// creates a TypeInfo
	template<typename T>
	inline TypeInfoData _construct_type_info_(string_t type_name, size_t id)
	{		
		
		return TypeInfoData
		(
			sizeof(T),
			type_name,
			id,
			_choose_new_<T>(),
			_choose_placement_new_<T>(),
			_choose_copy_<T>(),
			_choose_delete_<T>(),
			_choose_placement_delete_<T>(),
			_choose_type_cast_<T>()
		);
		
	}



	// register for unique TypeInfoDatas based on Type
	// should disalow multiple allocation for the same type
	template<typename T>
	class TypeRegister 
	{

		private:
			
			static TypeInfoData* singleton;

		public:

			static constexpr TypeInfoData* register_type(string_t type_name, size_t id) 
			{
				if (!singleton) 
				{
					singleton = new TypeInfoData(std::move(_construct_type_info_<T>(type_name, id)));
						
					return singleton;
				}
				else 
				{
					return singleton;
				}
			}

			static constexpr TypeInfoData* get() 
			{
				if (singleton) 
				{
					return singleton;
				}
				else
				{
					lamina_throw("Type T is not a registered TypeInfo");
					return nullptr;
				}
			}

	};

	template<typename T>
	TypeInfoData* TypeRegister<T>::singleton = nullptr;


	// wrapper for TypeInfoData
	// contains a pointer to a unique TypeInfoData stored in 
	class TypeInfo 
	{
	
		using New = TypeInfoData::New;
		using PlacementNew = TypeInfoData::PlacementNew;
		using Copy = TypeInfoData::Copy;
		using Delete = void(void*);
		using PlacementDelete = void(void*, size_t);

		friend bool operator==(TypeInfo arg0, TypeInfo arg1);

		private:

			TypeInfoData* _data;

		public:
			
			TypeInfo(TypeInfoData* data);

			TypeCast cast(void* target);

			size_t size();

			string_t name() const;

			size_t id();

			New* new_wrapper();

			PlacementNew* placement_new_wrapper();

			Copy* copy_wrapper();

			Delete* delete_wrapper();

			PlacementDelete* placement_delete_wrapper();

	};

	static bool operator==(TypeInfo arg0, TypeInfo arg1)
	{
		return arg0._data == arg1._data;
	}

	static bool operator!=(TypeInfo arg0, TypeInfo arg1) 
	{
		return !operator==(arg0, arg1);
	}

	

	template<typename T>
	static TypeInfo get_typeinfo()
	{
		return TypeInfo(TypeRegister<T>::get());
	}

	template<typename T>
	static TypeInfo make_typeinfo(string_t name, size_t id)
	{
		return TypeInfo(TypeRegister<T>::register_type(name, id));
	}


	struct TypeCast
	{

		void* _data;

		TypeInfoData* _type;



		public:

			TypeCast() :
				_data(nullptr),
				_type(nullptr)
			{
			}

			template<typename T>
			static T& deref(T& target) 
			{
				return target;
			}

			template<typename T>
			static T& deref(T*& target)
			{
				return *target;
			}

			template<typename T> struct remove_pointer { typedef T type; };
			template<typename T> struct remove_pointer<T*> { typedef T type; };
			template<typename T> struct remove_pointer<T* const> { typedef T type; };
			template<typename T> struct remove_pointer<T* volatile> { typedef T type; };
			template<typename T> struct remove_pointer<T* const volatile> { typedef T type; };


			template<typename T>
			operator T()
			{

				using raw_type = remove_pointer<T>::type;

				if (TypeRegister<raw_type>::get() != _type)
				{
					lamina_throw("Type " + _type->_type_name + " cannot be interpreted as " + get_typeinfo<raw_type>().name());
				}

				
				return static_cast<T>(_data);
			}
	};

	extern TypeInfo float32_typeinfo;
	extern TypeInfo int32_typeinfo;

	extern TypeInfo float64_typeinfo;
	extern TypeInfo int64_typeinfo;

	extern TypeInfo uint32_typeinfo;
	extern TypeInfo uint64_typeinfo;

	extern TypeInfo string_typeinfo;
	

} // namespace lamina

#endif // end guards