# add sources
set(lamina_tensor_sources_list
	"Tensor.cpp"
	"Tensor.h"
)

# add library and include directories
add_library("lamina_tensor" ${lamina_tensor_sources_list})
target_include_directories("lamina_tensor" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# add subdirectories

# link libraries