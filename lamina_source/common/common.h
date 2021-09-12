// 
// created 7/17/21 7:01pm pacific by Carson Fricke 
//

#ifndef __LAMINA_COMMON_H__
#define __LAMINA_COMMON_H__

#include <string>
#include "RefArray.h"
#include "exception.h"


namespace lamina 
{

	typedef RefArray<int64_t> IntRefArray;

	typedef RefArray<uint64_t> UIntRefArray;

	typedef std::string string_t;

	template<typename T>
	using vector_t = std::vector<T>;

}



#endif // end guards
