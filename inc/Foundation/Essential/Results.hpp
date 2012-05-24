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

#include <Foundation/Essential/Types.hpp>

#define DREAM_FACILITY_ITF   4
#define DREAM_FACILITY_WIN32 7

#define DREAM_HRESULT_FROM_WIN32(x)                             \
    ((Dream::result_t)(x) <= 0 ?                                \
        ((Dream::result_t)(x))                                  \
        : ((Dream::result_t) (((x) & 0x0000FFFF)                \
            | (DREAM_FACILITY_WIN32 << 16) | 0x80000000)))

#define DREAM_MAKE_HRESULT(sev, fac, code)                      \
    ((Dream::result_t) (((Dream::uint32)(sev) << 31)            \
    | ((Dream::uint32)(fac) << 16) | ((Dream::uint32)(code))))

namespace Dream
{
    namespace Results
    {
        string ToString(__in result_t value) throw();
    }

    /**************************************************************************
     * WINDOWS ERROR CODES
     *************************************************************************/

    /// Cannot create a file when that file already exists
    const result_t DREAM_E_ALREADY_EXISTS =
	    DREAM_HRESULT_FROM_WIN32(183L);       // ERROR_ALREADY_EXIST

    /// An attempt was made to perform an initialization operation
    /// when initialization has already been completed
    const result_t DREAM_E_ALREADY_INITIALIZED =
        DREAM_HRESULT_FROM_WIN32(1247L);      // ERROR_ALREADY_INITIALIZED

    /// One or more arguments are not correct
    const result_t DREAM_E_INVALID_ARGUMENTS =
	    DREAM_HRESULT_FROM_WIN32(160L);       // ERROR_BAD_ARGUMENTS

    /**************************************************************************
     * CUSTOM ERROR CODES
     *************************************************************************/

    const result_t DREAM_E_FRESH_INFECTION = 
        DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000201);

    const result_t DREAM_E_NO_CURE =
        DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000202);

    const result_t DREAM_E_KEY_NOT_FOUND =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000203);

    const result_t DREAM_E_TOO_MANY_KEYS_FOUND =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000204);

    const result_t DREAM_E_INVALID_KEY_SIZE =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000205);

    const result_t DREAM_E_ENTRY_SECTION_NOT_FOUND =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000206);

    const result_t DREAM_E_NOT_EXECUTABLE =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000207);

    const result_t DREAM_E_NOT_WIN_EXECUTABLE =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000208);

    const result_t DREAM_E_NOT_WIN32_NOR_WIN64_EXECUTABLE =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000209);

    const result_t DREAM_E_NO_INFECTED_SECTIONS_FOUND =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x0000020A);

    const result_t DREAM_E_SUSPICIOUS_SECTION_FOUND =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x0000020B);

    const result_t DREAM_E_TOO_MANY_SUSPICIOUS_SECTIONS_FOUND =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x0000020C);

    const result_t DREAM_E_TOO_MANY_INFECTED_SECTIONS_FOUND =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x0000020D);

    const result_t DREAM_E_EMPTY_FILE =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x0000020E);

    const result_t DREAM_E_CORRUPTED_FILE =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x0000020F);

    const result_t DREAM_E_OPERATION_CANCELLED =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000210);

    const result_t DREAM_E_FILE_IS_TOO_SMALL =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000211);

    const result_t DREAM_E_TOO_MANY_THREADS =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000212);

    const result_t DREAM_E_INSUFFICIENT_RESOURCES =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000214);

    const result_t DREAM_E_INVALID_HASH =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000215);

    const result_t DREAM_E_UNSUPPORTED_FORMAT_DOS =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000216);

    const result_t DREAM_E_UNSUPPORTED_FORMAT_OS216 =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000217);

    const result_t DREAM_E_UNSUPPORTED_FORMAT_PIF =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000218);

    const result_t DREAM_E_UNSUPPORTED_FORMAT_POSIX =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000219);

    const result_t DREAM_E_UNSUPPORTED_FORMAT_WIN16 =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000220);

    const result_t DREAM_E_HASH_ALREADY_COMPUTED =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000221);

    const result_t DREAM_E_NOT_ENOUGH_DATA =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000222);

    const result_t DREAM_E_WRITTEN_LESS_THAN_SPECIFIED =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000223);

    const result_t DREAM_E_READ_LESS_THAN_SPECIFIED =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000224);

    const result_t DREAM_E_FILE_IS_TOO_LARGE =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000225);

    const result_t DREAM_E_OUT_OF_RANGE =
	    DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000226);

    const result_t DREAM_E_NOT_INITIALIZED = 
        DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000227);

    const result_t DREAM_E_NOT_IMPLEMENTED = 
        DREAM_MAKE_HRESULT(1, DREAM_FACILITY_ITF, 0x00000228);
}
