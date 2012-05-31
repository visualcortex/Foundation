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
	namespace Logging
	{
		class Exception : public Diagnostics::Exception
		{
			public:
				Exception
					(__in const string &source,
					 __in result_t result) throw();

				Exception
					(__in const string &source,
					 __in result_t result,
					 __in const string &message) throw();				
		};
	}
}
