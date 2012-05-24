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

namespace Dream
{
    class Time
    {
        public:
            Time() throw();
            Time(__in time_t value) throw();

        public:
            Time& operator = (__in time_t value) throw();

        public:
            time_t asTime() const throw();
            string asString() const throw();

        private:
            time_t m_value;
    };
}
