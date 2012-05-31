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

#include <Dream/Foundation/Essential/Types.hpp>

#include <type_traits>

namespace Dream
{
	namespace Internal
	{
		char (& int2id(int8) )[1];
		char (& int2id(uint8) )[2];

		char (& int2id(int16) )[3];
		char (& int2id(uint16) )[4];

		char (& int2id(int32) )[5];
		char (& int2id(uint32) )[6];

		char (& int2id(int64) )[7];
		char (& int2id(uint64) )[8];

		template<size_t N>
			struct integral_type
			{
				static_assert(0 < N && N < 9,
					"No template specializations available.");
			};

		template<> struct integral_type<1> { typedef int8 type; };
		template<> struct integral_type<2> { typedef uint8 type; };

		template<> struct integral_type<3> { typedef int16 type; };
		template<> struct integral_type<4> { typedef uint16 type; };

		template<> struct integral_type<5> { typedef int32 type; };
		template<> struct integral_type<6> { typedef uint32 type; };

		template<> struct integral_type<7> { typedef int64 type; };
		template<> struct integral_type<8> { typedef uint64 type; };
	}

	/**************************************************************************
	 * integral_type
	 *************************************************************************/

	template<typename T>
		struct integral_type
		{
			typedef typename Internal::integral_type
				<sizeof(Internal::int2id(T()))>::type type;
		};
}
