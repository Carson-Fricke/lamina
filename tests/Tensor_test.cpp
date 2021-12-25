// 
// created 7/17/21 6:47pm pacific by Carson Fricke 
//

#include <iostream>
#include "common/common.h"
#include "tensor/dynamic_storage/DynamicStorage.h"
#include "tensor/dynamic_storage/CPUDefaultDevice.h"
#include "tensor/TensorImpl.h"

using namespace std;

using namespace lamina;

int main()
{


	TensorImpl tens({7, 8, 9}, float64_typeinfo);

	cout << tens.numel() << " tensor numel" << endl;

	cout << tens.stride(0) << " " << tens.stride(1) << " " << tens.stride(2) << " tensor strides" << endl;

	tens.set_sizes_strides_offset({2, 252}, {252, 1}, 0);

	cout << tens.numel() << " tensor numel" << endl;

	cout << tens.stride(0) << " " << tens.stride(1) << " tensor strides" << endl;

	double* x = tens.data<double>();

	TensorImpl tens2 = tens.select(6);

	return 0;

}
