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

#include <Dream/Foundation/Essential/Abstract.hpp>
#include <Dream/Foundation/Essential/Types.hpp>

namespace Dream
{
	interface IAction : public IAbstract
	{
		virtual void performAction() = 0;
        virtual void performAction(__in const string &args) = 0;
	};
}
