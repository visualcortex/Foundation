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
		/** Provides support for listening handler events
		 */
		interface IHandlerListener : public IAbstract
		{
			virtual void onExceptionThrown
				(__in const Diagnostics::Exception &exception) throw() = 0;
		};
	}
}
