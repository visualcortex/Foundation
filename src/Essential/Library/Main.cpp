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

#include "Precompiled.hpp"

#include <Dream/Foundation/Essential.hpp>

//#include <vld.h>

namespace Dream
{
    namespace Results
    {
        string ToString(__in result_t value) throw()
        {
            switch (value)
            {
                case DREAM_E_FRESH_INFECTION:                     return "The fresh infection";
                case DREAM_E_NO_CURE:                             return "No cure";
                case DREAM_E_KEY_NOT_FOUND:                       return "The key not found";
                case DREAM_E_TOO_MANY_KEYS_FOUND:                 return "Too many keys found";
                case DREAM_E_INVALID_KEY_SIZE:                    return "The size of key is invalid";
                case DREAM_E_ENTRY_SECTION_NOT_FOUND:             return "The entry point section was not found";
                case DREAM_E_NOT_EXECUTABLE:                      return "Not executable file";
                case DREAM_E_NOT_WIN_EXECUTABLE:                  return "Not Windows executable file";
                case DREAM_E_NOT_WIN32_NOR_WIN64_EXECUTABLE:      return "Not win32 nor win64 executable file";
                case DREAM_E_NO_INFECTED_SECTIONS_FOUND:          return "No infected sections found";
                case DREAM_E_SUSPICIOUS_SECTION_FOUND:            return "Suspicious section was found";
                case DREAM_E_TOO_MANY_SUSPICIOUS_SECTIONS_FOUND:  return "Too many suspicious sections were found";
                case DREAM_E_TOO_MANY_INFECTED_SECTIONS_FOUND:    return "Too many infected sections were found";
                case DREAM_E_EMPTY_FILE:                          return "The file is empty";
                case DREAM_E_CORRUPTED_FILE:                      return "The file is corrupted";
                case DREAM_E_OPERATION_CANCELLED:                 return "Operation was cancelled";
                case DREAM_E_FILE_IS_TOO_SMALL:                   return "File is too small";
                case DREAM_E_TOO_MANY_THREADS:                    return "Too many threads";
                case DREAM_E_INVALID_ARGUMENTS:                   return "Invalid arguments";
                case DREAM_E_INSUFFICIENT_RESOURCES:              return "Insufficient resources";
                case DREAM_E_INVALID_HASH:                        return "Invalid hash";
                case DREAM_E_UNSUPPORTED_FORMAT_DOS:              return "Unsupported format: DOS";
                case DREAM_E_UNSUPPORTED_FORMAT_OS216:            return "Unsupported format: OS2/16";
                case DREAM_E_UNSUPPORTED_FORMAT_PIF:              return "Unsupported format: PIF";
                case DREAM_E_UNSUPPORTED_FORMAT_POSIX:            return "Unsupported format: POSIX";
                case DREAM_E_UNSUPPORTED_FORMAT_WIN16:            return "Unsupported format: WIN16";
                case DREAM_E_ALREADY_EXISTS:                      return "Already exists";
                case DREAM_E_HASH_ALREADY_COMPUTED:               return "The hash value already computed";
                case DREAM_E_NOT_ENOUGH_DATA:                     return "Not enough data";
                case DREAM_E_WRITTEN_LESS_THAN_SPECIFIED:         return "Written less than specified";
                case DREAM_E_READ_LESS_THAN_SPECIFIED:            return "Read less than specified";
                case DREAM_E_FILE_IS_TOO_LARGE:                   return "File is too large";
                case DREAM_E_OUT_OF_RANGE:                        return "Out of range";
                case DREAM_E_NOT_IMPLEMENTED:                     return "Not implemented";
            }

            LPSTR buffer;
            DWORD sizeBuffer = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM, 
                NULL, value, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);

            string retval = "";
            if (sizeBuffer != 0)
            {
                retval = buffer;
                ::LocalFree(buffer);
            }

            return retval;
        }
    }
}
