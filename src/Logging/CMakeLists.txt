set(PROJECT Dream.Foundation.Logging)
project(${PROJECT})

file(GLOB SOURCES ./Library/*.cpp)

if(MSVC)
	file(GLOB PLATFORM_HEADERS ./Library/Windows/*.hpp)
	file(GLOB PLATFORM_SOURCES ./Library/Windows/*.cpp)
    foreach(src_file ${SOURCES})
        if(${src_file} MATCHES Precompiled.cpp)
			set_source_files_properties(${src_file} PROPERTIES
         		COMPILE_FLAGS "/YcPrecompiled.hpp")
		else(${src_file} MATCHES Precompiled.cpp)
			set_source_files_properties(${src_file} PROPERTIES
				COMPILE_FLAGS "/YuPrecompiled.hpp")
		endif()
    endforeach(src_file ${SOURCES})
    foreach(src_file ${PLATFORM_SOURCES})
        if(${src_file} MATCHES Precompiled.cpp)
			set_source_files_properties(${src_file} PROPERTIES
         		COMPILE_FLAGS "/Yc../Precompiled.hpp")
		else(${src_file} MATCHES Precompiled.cpp)
			set_source_files_properties(${src_file} PROPERTIES
				COMPILE_FLAGS "/Yu../Precompiled.hpp")
		endif()
    endforeach(src_file ${PLATFORM_SOURCES})
endif(MSVC)

file(GLOB LIB_HEADERS ./Library/*.hpp)
file(GLOB SDK_HEADERS ../../inc/Dream/Foundation/Logging/*.hpp)

set(HEADERS ${LIB_HEADERS} ${SDK_HEADERS} ${PLATFORM_HEADERS} ../../inc/Dream/Foundation/Logging.hpp)
set(SOURCES ${SOURCES} ${PLATFORM_SOURCES})

add_library(${PROJECT} ${HEADERS} ${SOURCES})
install(TARGETS Dream.Foundation.Logging DESTINATION ${CMAKE_INSTALL_PREFIX})
