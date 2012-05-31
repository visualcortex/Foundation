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

#include <Dream/Foundation/Essential/Platform.hpp>

namespace Dream
{
	interface IAbstract
	{
        virtual ~IAbstract() throw() = 0;
	};

    inline IAbstract::~IAbstract() throw()
    {}
}
