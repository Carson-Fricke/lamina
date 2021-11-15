# add sources
set(lamina_tensor_dynamic_storage_sources_list
	"CPUDefaultDevice.cpp"
	"CPUDefaultDevice.h"
	"Device.cpp"	
	"Device.h"
	"DynamicStorage.cpp"
	"DynamicStorage.h"
	"TypeInfo.cpp"
	"TypeInfo.h"
)

# add library and include directories
add_library("lamina_tensor_dynamic_storage" ${lamina_tensor_dynamic_storage_sources_list})
target_include_directories("lamina_tensor_dynamic_storage" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# add subdirectories

# link libraries
