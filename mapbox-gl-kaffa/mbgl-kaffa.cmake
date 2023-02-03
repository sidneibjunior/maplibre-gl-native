find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

add_library(
    mbgl-kaffa
    SHARED
    ${PROJECT_SOURCE_DIR}/mapbox-gl-kaffa/src/main/c/MapboxNativeBridge.cpp
)

target_link_libraries(
    mbgl-kaffa
    PRIVATE 
        Mapbox::Base
        Mapbox::Base::Extras::args
        mbgl-compiler-options
        mbgl-core
)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

if(MSVC)
    find_package(libuv REQUIRED)

    target_link_libraries(
        mbgl-kaffa PRIVATE uv_a
    )

    set_source_files_properties(
        ${PROJECT_SOURCE_DIR}/mapbox-gl-kaffa/src/main/c/MapboxNativeBridge.cpp
        PROPERTIES COMPILE_FLAGS "/wd4244"
    )
endif()

set_target_properties(mbgl-kaffa PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/mapbox-gl-kaffa/build)

install(TARGETS mbgl-kaffa RUNTIME DESTINATION mapbox-gl-kaffa/build)