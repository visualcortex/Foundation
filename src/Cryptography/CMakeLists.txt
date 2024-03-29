set(PROJECT Dream.Foundation.Cryptography)
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
file(GLOB SDK_HEADERS ../../inc/Dream/Foundation/Cryptography/*.hpp)

set(HEADERS ${LIB_HEADERS} ${SDK_HEADERS} ${PLATFORM_HEADERS} ../../inc/Dream/Foundation/Cryptography.hpp)
set(SOURCES ${SOURCES} ${PLATFORM_SOURCES})

add_library(${PROJECT} ${HEADERS} ${SOURCES})
install(TARGETS Dream.Foundation.Cryptography DESTINATION ${CMAKE_INSTALL_PREFIX})

#------------------------------------------------------------------------------
# TEST
#------------------------------------------------------------------------------

set(TEST ${PROJECT}.Test)

file(GLOB TEST_SOURCES ./Tests/*.cpp)
file(GLOB TEST_HEADERS ./Tests/*.hpp)

add_executable(${TEST} ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(${TEST} ${PROJECT} ${Boost_LIBRARIES})

enable_testing()
add_test(${TEST} ${TEST})
