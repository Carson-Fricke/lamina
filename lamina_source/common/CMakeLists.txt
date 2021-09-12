# add sources
set(lamina_common_sources_list
	"common.cpp"	
	"common.h"
	"exception.cpp"
	"exception.h"
	"RefArray.h"
)

# add library and include directories
add_library("lamina_common" ${lamina_common_sources_list})
target_include_directories("lamina_common" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# add subdirectories

# link libraries
