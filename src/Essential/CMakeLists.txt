set(PROJECT Dream.Foundation.Essential)
project(${PROJECT})

file(GLOB SOURCES ./Library/*.cpp)

file(GLOB LIB_HEADERS ./Library/*.hpp)
file(GLOB SDK_HEADERS ../../inc/Dream/Foundation/Essential/*.hpp)

set(HEADERS ${LIB_HEADERS} ${SDK_HEADERS} ../../inc/Dream/Foundation/Essential.hpp)

if(MSVC)
    foreach(src_file ${SOURCES})
        if(${src_file} MATCHES Precompiled.cpp)
			set_source_files_properties(${src_file} PROPERTIES
				COMPILE_FLAGS "/YcPrecompiled.hpp")
		else(${src_file} MATCHES Precompiled.cpp)
			set_source_files_properties(${src_file} PROPERTIES
				COMPILE_FLAGS "/YuPrecompiled.hpp")
		endif()
    endforeach(src_file ${SOURCES})
endif(MSVC)

add_library(${PROJECT} ${HEADERS} ${SOURCES})
install(TARGETS Dream.Foundation.Essential DESTINATION ${CMAKE_INSTALL_PREFIX})
