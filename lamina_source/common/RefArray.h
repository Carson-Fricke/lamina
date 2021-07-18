// 
// created 7/17/21 7:04pm pacific by Carson Fricke 
//

#include <array>
#include <vector>
#include <iostream>
#include <initializer_list>


#ifndef __LAMINA_REFARRAY_H__
#define __LAMINA_REFARRAY_H__

namespace lamina 
{

	template<typename T>
	class RefArray 
	{

		private:

			const T* _data;

			size_t _numel;


		public:
	

			constexpr RefArray() :
				_data(nullptr),
				_numel(0) {}

			constexpr RefArray(const T& arg) :
				_data(&arg),
				_numel(1) {}

			constexpr RefArray(const T* begin, const T* end) :
				_data(begin),
				_numel(end - begin) {}

			constexpr RefArray(const std::vector<T>& arg) :
				_data(arg.data()),
				_numel(arg.size()) {}

			template<size_t N>
			constexpr RefArray(const std::array<T, N>& arg) :
				_data(arg.data()),
				_numel(N) {}

			template<size_t N>
			constexpr RefArray(const T(&arg)[N]) :
				_data(arg),
				_numel(N) {}

			constexpr RefArray(std::initializer_list<T> arg) :
				_data(arg.begin()),
				_numel(arg.size()) {}

			constexpr const T* begin() const 
			{
				return _data;
			}

			constexpr const T* end() const 
			{
				return _data + _numel;
			}

			constexpr size_t size() const 
			{
				return _numel;
			}

			constexpr size_t numel() const 
			{
				return _numel;
			}

			constexpr const T& operator[](size_t index) const 
			{
				return _data[index];
			}

			std::vector<T> vec() const 
			{
				return std::vector<T>(_data, _data + _numel);
			}

			void free() 
			{
				delete[] _data;
			}
			
	};

	
	template <typename T>
	std::ostream& operator<<(std::ostream& out, RefArray<T> list) {
		int i = 0;
		out << "[";
		for (auto e : list) {
			if (i++ > 0) {
				out << ", ";
			}
			out << e;
		}
		out << "]";
		return out;
	}
	
} // namespace swing

#endif // end guards