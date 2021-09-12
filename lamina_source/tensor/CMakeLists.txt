# add sources
set(lamina_tensor_sources_list
	"Tensor.cpp"
	"Tensor.h"
	"TensorImpl.cpp"
	"TensorImpl.h"
)

# add library and include directories
add_library("lamina_tensor" ${lamina_tensor_sources_list})
target_include_directories("lamina_tensor" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# add subdirectories
add_subdirectory("dynamic_storage")

# link libraries
target_link_libraries("lamina_tensor" LINK_PUBLIC 
	"lamina_tensor_dynamic_storage"
)