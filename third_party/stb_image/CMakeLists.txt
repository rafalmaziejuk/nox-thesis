add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>")
target_compile_definitions(stb_image INTERFACE STB_IMAGE_IMPLEMENTATION)
