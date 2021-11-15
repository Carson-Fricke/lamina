// 
// created 7/17/21 6:47pm pacific by Carson Fricke 
//

#include <iostream>
#include "common/common.h"
#include "tensor/dynamic_storage/DynamicStorage.h"
#include "tensor/dynamic_storage/CPUDefaultDevice.h"

using namespace std;

using namespace lamina;

int main()
{

	UIntRefArray x({1, 2, 3, 4});

	DynamicStorage storage(10, int32_typeinfo, cpu_default_device);


	cout << int32_typeinfo.name() << endl;

	cout << x << " hello" << endl;

	return 0;
}
