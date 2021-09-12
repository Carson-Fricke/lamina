// 
// created 7/17/21 6:47pm pacific by Carson Fricke 
//

#include <iostream>
#include "common/common.h"
#include "tensor/dynamic_storage/TypeInfo.h"

using namespace std;

using namespace lamina;

int main()
{
	
	TypeInfo typex = _make_type_info_<int>("test int");

	

	UIntRefArray x({1, 2, 3, 4});

	cout << typex.type_size() << endl;

	cout << x << " hello" << endl;

	return 0;
}
