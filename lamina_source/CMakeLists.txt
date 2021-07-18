# add sources
set(lamina_sources_list
	"lamina.hpp"
	"lamina.cpp"
)

# add library and include directories
add_library("lamina" ${lamina_sources_list})
target_include_directories("lamina" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# add subdirectories
add_subdirectory("common")
add_subdirectory("tensor")

# link libraries
target_link_libraries("lamina" LINK_PUBLIC
	"lamina_common"
	"lamina_tensor"
)