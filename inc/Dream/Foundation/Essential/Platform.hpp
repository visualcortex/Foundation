/******************************************************************************
 * @file
 * @author Ivan Makarov <im.visualcortex@gmail.com>
 * 
 * @section LICENSE
 *
 * Copyright (C) 2012, Ivan Makarov
 * Licensed under the MIT license.
 *
 *****************************************************************************/

#pragma once

#define DREAM_PLATFORM_OS_ANDROID					0x00000001
#define DREAM_PLATFORM_OS_IOS 						0x00000002
#define DREAM_PLATFORM_OS_LINUX						0x00000003
#define DREAM_PLATFORM_OS_WINDOWS					0x00000004

#define DREAM_PLATFORM_COMPILER_NAME_GCC			0x00000001
#define DREAM_PLATFORM_COMPILER_NAME_MSVC			0x00000002

#define DREAM_PLATFORM_COMPILER_VERSION_MSVC_11		110

#if defined (_MSC_VER)
#	define DREAM_PLATFORM_OS_NAME DREAM_PLATFORM_OS_WINDOWS
#	define DREAM_PLATFORM_COMPILER_NAME DREAM_PLATFORM_COMPILER_NAME_MSVC
#	if defined(_MT)
#		define DREAM_PLATFORM_MULTITHREADED
#	endif
#	if defined(_DLL)
#		define DREAM_PLATFORM_SHARED_RUNTIME
#	endif
#	if _MSC_VER == 1700
#		define DREAM_PLATFORM_COMPILER_VERSION DREAM_PLATFORM_COMPILER_VERSION_MSVC_11
#		define DREAM_PLATFORM_CONFIGURED
#	endif
#endif

#if !defined(DREAM_PLATFORM_CONFIGURED)
#	error "Only Microsoft Windows and Microsoft Visual Studio C++ 11 compiler supported."
#endif

#if defined(DEBUG) || defined(_DEBUG)
#	define DREAM_PLATFORM_DEBUG
#endif

#if !defined(interface)
#	define interface struct
#endif

#if defined(preconditions)
#	pragma message("'preconditions' macro already defined.")
#endif

#if defined(postconditions)
#	pragma message("'postconditions' macro already defined.")
#endif

#define preconditions
#define postconditions

#if defined(DREAM_PLATFORM_DEBUG)
#	define DREAM_NODEFAULT DREAM_ASSERT(0)
#else
#	define DREAM_NODEFAULT __assume(0)
#endif

#define DREAM_UNREFERENCED_PARAMETER(p) (p)

#define DREAM_STRINGIFY_(x) #x
#define DREAM_STRINGIFY(x) DREAM_STRINGIFY_(x)

#define DREAM_SIZEOF(s, m) sizeof(((s *)(0))->m)
#define DREAM_OFFSETOF(s, m) offsetof(s, m)
#define DREAM_ELEMENTOF(s, m) { DREAM_SIZEOF(s, m), DREAM_OFFSETOF(s, m) }

#if DREAM_PLATFORM_COMPILER_NAME != DREAM_PLATFORM_COMPILER_NAME_MSVC
#   define __in
#   define __out
#endif

#if DREAM_PLATFORM_COMPILER_NAME == DREAM_PLATFORM_COMPILER_NAME_MSVC
#	if defined DREAM_PLATFORM_MULTITHREADED
#		if defined DREAM_PLATFORM_SHARED_RUNTIME
#			if defined DREAM_PLATFORM_DEBUG
#				define DREAM_PLATFORM_LIBRARY_NAME_SUFFIX "-vc" DREAM_STRINGIFY(DREAM_PLATFORM_COMPILER_VERSION) "-mt-gd.lib"
#			else
#				define DREAM_PLATFORM_LIBRARY_NAME_SUFFIX "-vc" DREAM_STRINGIFY(DREAM_PLATFORM_COMPILER_VERSION) "-mt.lib"
#			endif
#		else
#			if defined DREAM_PLATFORM_DEBUG
#				define DREAM_PLATFORM_LIBRARY_NAME_SUFFIX "-vc" DREAM_STRINGIFY(DREAM_PLATFORM_COMPILER_VERSION) "-mt-sgd.lib"
#			else
#				define DREAM_PLATFORM_LIBRARY_NAME_SUFFIX "-vc" DREAM_STRINGIFY(DREAM_PLATFORM_COMPILER_VERSION) "-mt-s.lib"
#			endif
#		endif
#	else
#		if defined DREAM_PLATFORM_SHARED_RUNTIME
#			if defined DREAM_PLATFORM_DEBUG
#				define DREAM_PLATFORM_LIBRARY_NAME_SUFFIX "-vc" DREAM_STRINGIFY(DREAM_PLATFORM_COMPILER_VERSION) "-gd.lib"
#			else
#				define DREAM_PLATFORM_LIBRARY_NAME_SUFFIX "-vc" DREAM_STRINGIFY(DREAM_PLATFORM_COMPILER_VERSION) ".lib"
#			endif
#		else
#			if defined DREAM_PLATFORM_DEBUG
#				define DREAM_PLATFORM_LIBRARY_NAME_SUFFIX "-vc" DREAM_STRINGIFY(DREAM_PLATFORM_COMPILER_VERSION) "-sgd.lib"
#			else
#				define DREAM_PLATFORM_LIBRARY_NAME_SUFFIX "-vc" DREAM_STRINGIFY(DREAM_PLATFORM_COMPILER_VERSION) "-s.lib"
#			endif
#		endif
#	endif
#endif

#define DREAM_COMPOSE_LIBRARY_NAME(baseName) \
	baseName DREAM_PLATFORM_LIBRARY_NAME_SUFFIX

namespace Dream
{
	/// Invalid size
	const size_t INVALID_SIZE = static_cast<size_t>(-1);

	/// Max reasonable size
	const size_t MAX_REASONABLE_SIZE = 104857600; // 100 mb
}
