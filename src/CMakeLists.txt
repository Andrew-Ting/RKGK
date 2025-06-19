# Gather all source files in the current directory
file (GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
)

file (GLOB_RECURSE HEADER_FILES
    "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.h"
)

add_executable (RKGK ${SOURCE_FILES} ${HEADER_FILES})
source_group("Header Files" FILES ${HEADER_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})
set_target_properties (RKGK PROPERTIES FOLDER "Source")
target_include_directories (RKGK PRIVATE ../${VMA_INCLUDE_DIR} ../${SDL_INCLUDE_DIR} ../${IMGUI_DIR} ../${IMGUI_DIR}/backends ../${VOLK_INCLUDE_DIR} ../${VKB_INCLUDE_DIR})
target_compile_definitions(RKGK PRIVATE IMGUI_IMPL_VULKAN_USE_VOLK $<$<CONFIG:RelWithDebInfo>:ENABLE_IMGUI> $<$<CONFIG:Debug>:ENABLE_IMGUI>)
target_link_libraries(RKGK
    PRIVATE SDL3-static Volk SDL_uclibc Imgui glm Vkbootstrap)
