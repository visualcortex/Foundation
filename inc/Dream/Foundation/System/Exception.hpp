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

#include <Dream/Foundation/Essential.hpp>

namespace Dream
{
	namespace System 
	{
		class Exception : public Diagnostics::Exception
		{
			public:
				Exception
					( __in const string &source) throw();

				Exception
					( __in const string &source, 
					  __in const string &message) throw();
		};
	}
}
