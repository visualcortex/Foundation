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

#include <Dream/Foundation/Essential/Time.hpp>

namespace Dream
{
    Time::Time() throw()
        : m_value(0)
    {}

    Time::Time(__in time_t value) throw()
        : m_value(value)
    {}

    Time& Time::operator = (__in time_t value) throw()
    {
        m_value = value;
        return *this;
    }

    time_t Time::asTime() const throw()
    {
        return m_value;
    }

    // @todo Error checking...
    string Time::asString() const throw()
    {
        struct tm tm;
        gmtime_s(&tm, &m_value);

        const size_t bufsize = 256;
        char buf[bufsize];

        strftime(buf, bufsize, "%d/%m/%Y %H:%M:%S", &tm);
        return buf;
    }
}
