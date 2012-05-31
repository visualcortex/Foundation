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

#include <Dream/Foundation/Essential/TypeTraits.hpp>

namespace Dream
{
	template<typename Enum>
		struct bitset
		{
			static_assert(std::is_enum<Enum>::value,
				"Only enumeration type is supported as an underlying type.");

			public:
				typedef typename std::underlying_type<Enum>::type Flags;
				Flags flags;

			public:
				bitset() throw()
					: flags(0)
				{}

				bitset(__in Enum flag) throw()
					: flags(static_cast<Flags>(flag))
				{}

			public:
				operator const void* () const throw()
				{
					return reinterpret_cast<const void*>(flags);
				}

			public:
				/// Flip all the bits in the bitset
				void flip() throw()
				{
					flags = ~flags;
				}

				/// Reset all the bits in the bitset.
				void reset() throw()
				{
					flags = 0;
				}

				/// Test whether any of the bits in the bitset is set.
				bool any() const throw()
				{
					return flags != 0;
				}

				/// Test whether none of the bits in the bitset are set.
				bool none() const throw()
				{
					return flags == 0;
				}

				/// Returns the amount of bits in the bitset that are set.
				size_t count() const throw()
				{
					size_t retval = 0;
					for (std::make_unsigned<Flags>::type i = flags; i; i &= i - 1)
						retval++;

					return retval;
				}

				/// Returns the number of bits in the bitset.
				size_t size() const throw()
				{
					return sizeof Flags;
				}

			public:
				bitset operator ~ () const throw()
				{
                	return static_cast<Enum>(~flags);
                }

            public:
				bitset& operator |= (__in const bitset &rhs) throw()
        		{
                	flags |= rhs.flags;
                	return *this;
                }

                bitset& operator &= (__in const bitset &rhs) throw()
        		{
                	flags &= rhs.flags;
                	return *this;
                }

        		bitset& operator ^= (__in const bitset &rhs) throw()
        		{
                	flags ^= rhs.flags;
                	return *this;
                }
		};

	template<class Enum>
		bool operator == 
			(__in const bitset<Enum> &lhs, __in const bitset<Enum> &rhs) throw()
		{
			return lhs.flags == rhs.flags;
		}

	template<class Enum>
		bool operator ==
			(__in const bitset<Enum> &lhs, __in Enum rhs) throw()
		{
			typedef typename bitset<Enum>::Flags Flags;
			return lhs.flags == static_cast<Flags>(rhs);
		}

	template<class Enum>
		bool operator ==
			(__in Enum lhs, __in const bitset<Enum> &rhs) throw()
		{
			typedef typename bitset<Enum>::Flags Flags;
			return static_cast<Flags>(lhs) == rhs.flags;
		}

	template<class Enum>
		bool operator != 
			(__in const bitset<Enum> &lhs, __in const bitset<Enum> &rhs) throw()
		{
			return !(lhs == rhs);
		}

	template<class Enum>
		bool operator !=
			(__in const bitset<Enum> &lhs, __in Enum rhs) throw()
		{
			return !(lhs == rhs);
		}

	template<class Enum>
		bool operator !=
			(__in Enum lhs, __in const bitset<Enum> &rhs) throw()
		{
			return !(lhs == rhs);
		}

	template<class Enum>
		bitset<Enum> operator | 
			(__in const bitset<Enum> &lhs, __in const bitset<Enum> &rhs) throw()
		{
			return static_cast<Enum>(lhs.flags | rhs.flags);
		}

	template<class Enum>
		bitset<Enum> operator | 
			(__in const bitset<Enum> &lhs, __in Enum rhs) throw()
		{
			typedef typename bitset<Enum>::Flags Flags;
			return static_cast<Enum>(lhs.flags | static_cast<Flags>(rhs));
		}

	template<class Enum>
		bitset<Enum> operator |
			(__in Enum lhs, __in const bitset<Enum> &rhs) throw()
		{
			typedef typename bitset<Enum>::Flags Flags;
			return static_cast<Enum>(static_cast<Flags>(lhs) | rhs.flags);
		}

	template<class Enum>
		bitset<Enum> operator &
			(__in const bitset<Enum> &lhs, __in const bitset<Enum> &rhs) throw()
		{
			return static_cast<Enum>(lhs.flags & rhs.flags);
		}

	template<class Enum>
		bitset<Enum> operator &
			(__in const bitset<Enum> &lhs, __in Enum rhs) throw()
		{
			typedef typename bitset<Enum>::Flags Flags;
			return static_cast<Enum>(lhs.flags & static_cast<Flags>(rhs));
		}

	template<class Enum>
		bitset<Enum> operator &
			(__in Enum lhs, __in const bitset<Enum> &rhs) throw()
		{
			typedef typename bitset<Enum>::Flags Flags;
			return static_cast<Enum>(static_cast<Flags>(lhs) & rhs.flags);
		}

	template<class Enum>
		bitset<Enum> operator ^
			(__in const bitset<Enum> &lhs, __in const bitset<Enum> &rhs) throw()
		{
			return static_cast<Enum>(lhs.flags ^ rhs.flags);
		}

	template<class Enum>
		bitset<Enum> operator ^
			(__in const bitset<Enum> &lhs, __in Enum rhs) throw()
		{
			typedef typename bitset<Enum>::Flags Flags;
			return static_cast<Enum>(lhs.flags ^ static_cast<Flags>(rhs));
		}

	template<class Enum>
		bitset<Enum> operator ^
			(__in Enum lhs, __in const bitset<Enum> &rhs) throw()
		{
			typedef typename bitset<Enum>::Flags Flags;
			return static_cast<Enum>(static_cast<Flags>(lhs) ^ rhs.flags);
		}
}

#define DREAM_BITSET(Enum)													\
	inline Dream::bitset<Enum>												\
		operator ~ (__in Enum rhs) throw()									\
	{																		\
		typedef Dream::bitset<Enum>::Flags Flags;							\
		return static_cast<Enum>(~static_cast<Flags>(rhs));					\
	}																		\
																			\
	inline Dream::bitset<Enum>												\
		operator | (__in Enum lhs, __in Enum rhs) throw()					\
	{																		\
		typedef Dream::bitset<Enum>::Flags Flags;							\
		return static_cast<Enum>(											\
			static_cast<Flags>(lhs) | static_cast<Flags>(rhs));				\
	}																		\
																			\
	inline Dream::bitset<Enum>												\
		operator & (__in Enum lhs, __in Enum rhs) throw()					\
	{																		\
		typedef Dream::bitset<Enum>::Flags Flags;							\
		return static_cast<Enum>(											\
			static_cast<Flags>(lhs) & static_cast<Flags>(rhs));				\
	}																		\
																			\
	inline Dream::bitset<Enum>												\
		operator ^ (__in Enum lhs, __in Enum rhs) throw()					\
	{																		\
		typedef Dream::bitset<Enum>::Flags Flags;							\
		return static_cast<Enum>(											\
			static_cast<Flags>(lhs) ^ static_cast<Flags>(rhs));				\
	}
