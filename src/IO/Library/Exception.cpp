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

#include <Dream/Foundation/IO/Exception.hpp>

namespace Dream
{
	namespace IO
	{
		Exception::Exception
			(__in const string &source, 
			 __in result_t result) throw()
			 : Diagnostics::Exception(source, result)
		{}

		Exception::Exception
			(__in const string &source,
			 __in result_t result,
			 __in const string &message) throw()
			 : Diagnostics::Exception(source, result, message)
		{}
	}
}
