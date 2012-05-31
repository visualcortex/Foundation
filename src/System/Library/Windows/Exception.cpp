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

#include "../Precompiled.hpp"

#include <Dream/Foundation/System/Exception.hpp>
#include <Dream/Foundation/System/Environment.hpp>

namespace Dream
{
	namespace System
	{
		Exception::Exception(__in const string &source) throw()
			: Diagnostics::Exception(source, Environment::GetLastError())
		{}

		Exception::Exception(__in const string &source, __in const string &message) throw()
			: Diagnostics::Exception(source, Environment::GetLastError(), message)
		{}
	}
}
