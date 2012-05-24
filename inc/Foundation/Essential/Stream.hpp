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

#include <Foundation/Essential/Abstract.hpp>

namespace Dream
{
	interface IStream : public IAbstract
	{
		virtual int readByte() = 0;
	};
}
