#pragma once
#include <string_view>

#define MAGIC_ENUM_HEAD(name, underlying_type)\
	enum class [[nodiscard]] name : underlying_type

#define MAGIC_DIS_ENUM_HEAD(name, underlying_type) \
	enum class name : underlying_type

#define MAGIC_FREE_ENUM_HEAD(name, underlying_type) \
	enum [[nodiscard]] name : underlying_type

#define MAGIC_FREE_DIS_ENUM_HEAD(name, underlying_type) \
	enum name : underlying_type

#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define CAT(name, ...) PRIMITIVE_CAT(name, __VA_ARGS__)

#define IIF(condition) PRIMITIVE_CAT(IIF_, condition)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t
#define IIF_false(t, ...) __VA_ARGS__
#define IIF_true(t, ...) t
#define IIF_FALSE(t, ...) __VA_ARGS__
#define IIF_TRUE(t, ...) t

#define __PLA(item) item
#define __STR(item) #item

#define MAGIC_ENUMLIST(enum_name) __magic_##enum_name##_list
#define MAGIC_ENUMNAME(enum_name) __magic_##enum_name##_name
#define MAGIC_ENUMSIZE(enum_name) __magic_##enum_name##_size

#define MAGIC_ATTACH_COLONS(enum_name, pred, item) pred(enum_name##::##item)

// at the end of list
#define MAGIC_ITERATE_IMPL_0(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), 

#define MAGIC_ITERATE_IMPL_1(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), MAGIC_ITERATE_IMPL_0(enum_name, pred, __VA_ARGS__)

#define MAGIC_ITERATE_IMPL_2(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), MAGIC_ITERATE_IMPL_1(enum_name, pred, __VA_ARGS__)

#define MAGIC_ITERATE_IMPL_3(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), MAGIC_ITERATE_IMPL_2(enum_name, pred, __VA_ARGS__)

#define MAGIC_ITERATE_IMPL_4(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), MAGIC_ITERATE_IMPL_3(enum_name, pred, __VA_ARGS__)

// to continuation of list
#define MAGIC_ITERATE(enum_name, last_index, pred, ...) \
CAT(MAGIC_ITERATE_IMPL_, last_index)(enum_name, pred, __VA_ARGS__)

#define MAGIC_MAKE_LIST(enum_name, enum_last_index, type, wrap, pred, ...) \
inline constexpr type wrap(enum_name)[] = { MAGIC_ITERATE(enum_name, enum_last_index, pred, __VA_ARGS__) }

#define MAGIC_MAKE_LISTs(enum_name, enum_last_index, ...) \
MAGIC_MAKE_LIST(enum_name, enum_last_index, enum_name, MAGIC_ENUMLIST, __PLA, __VA_ARGS__); \
MAGIC_MAKE_LIST(enum_name, enum_last_index, std::string_view, MAGIC_ENUMNAME, __STR, __VA_ARGS__)

#define MAGIC_FIND_ITEM(name, item) \


#define MAGIC_ENUM(enum_name, underlying_type, enum_last_index, ...) \
	MAGIC_ENUM_HEAD(enum_name, underlying_type) \
{ \
	__VA_ARGS__,\
}; \
inline constexpr std::size_t MAGIC_ENUMSIZE(enum_name) = enum_last_index + 1; \
MAGIC_MAKE_LISTs(enum_name, enum_last_index, __VA_ARGS__)

namespace gl::detail
{
	enum class test { aa, bb, cc };
	inline constexpr test test_names[] = { aa, bb, cc };

	MAGIC_ENUM(AASDEWQDSFD, int, 3, a, b, c, d);

	constexpr auto aaa_i = MAGIC_ENUMLIST(AASDEWQDSFD)[0];
	constexpr auto aaa_n = MAGIC_ENUMNAME(AASDEWQDSFD)[0];
}
