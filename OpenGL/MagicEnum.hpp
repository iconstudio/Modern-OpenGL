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

#define STRINGIFY(a) #a
#define __PLA(enum_name, item) CAT(CAT(enum_name, ::), item)
#define __STR(enum_name, item) STRINGIFY(enum_name::item)
#define __CAP(enum_name, item) STRINGIFY(item)

#define MAGIC_ENUMLIST(enum_name) __magic_##enum_name##_list
#define MAGIC_ENUMFULL(enum_name) __magic_##enum_name##_name
#define MAGIC_ENUMNAME(enum_name) __magic_##enum_name##_caps
#define MAGIC_ENUMSIZE(enum_name) __magic_##enum_name##_size

// 
#define MAGIC_ATTACH_COLONS(enum_name, pred, item) pred(enum_name, item)

// at the end of list
#define MAGIC_ATTACH_COLON_ALL_IMPL_0(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), 

#define MAGIC_ATTACH_COLON_ALL_IMPL_1(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_0(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_2(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_1(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_3(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_2(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_4(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_3(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_5(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_4(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_6(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_5(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_7(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_6(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_8(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_7(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_9(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_8(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_10(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_9(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_11(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_10(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_12(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_11(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_13(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_12(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_14(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_13(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL_IMPL_15(enum_name, pred, item, ...) \
MAGIC_ATTACH_COLONS(enum_name, pred, item), \
MAGIC_ATTACH_COLON_ALL_IMPL_14(enum_name, pred, __VA_ARGS__)

#define MAGIC_ATTACH_COLON_ALL(enum_name, last_index, pred, ...) \
CAT(MAGIC_ATTACH_COLON_ALL_IMPL_, last_index)(enum_name, pred, __VA_ARGS__)

// enum_name -> value_list, pred -> index
#define MAGIC_ASSIGN_VALUE(value_list, index, item) item = value_list[index]
#define MAGIC_INDEXER(index) index + 1

// at the end of list
#define MAGIC_ASSIGN_VALUE_ALL_IMPL_0(value_list, index, item, ...) \
MAGIC_ASSIGN_VALUE(value_list, index, item), 

#define MAGIC_ASSIGN_VALUE_ALL_IMPL_1(value_list, index, item, ...) \
MAGIC_ASSIGN_VALUE(value_list, index, item), \
MAGIC_ASSIGN_VALUE_ALL_IMPL_0(value_list, MAGIC_INDEXER(index), __VA_ARGS__)

#define MAGIC_ASSIGN_VALUE_ALL_IMPL_2(value_list, index, item, ...) \
MAGIC_ASSIGN_VALUE(value_list, index, item), \
MAGIC_ASSIGN_VALUE_ALL_IMPL_1(value_list, MAGIC_INDEXER(index), __VA_ARGS__)

#define MAGIC_ASSIGN_VALUE_ALL_IMPL_3(value_list, index, item, ...) \
MAGIC_ASSIGN_VALUE(value_list, index, item), \
MAGIC_ASSIGN_VALUE_ALL_IMPL_2(value_list, MAGIC_INDEXER(index), __VA_ARGS__)

#define MAGIC_ASSIGN_VALUE_ALL_IMPL_4(value_list, index, item, ...) \
MAGIC_ASSIGN_VALUE(value_list, index, item), \
MAGIC_ASSIGN_VALUE_ALL_IMPL_3(value_list, MAGIC_INDEXER(index), __VA_ARGS__)

#define MAGIC_ASSIGN_VALUE_ALL_IMPL_5(value_list, index, item, ...) \
MAGIC_ASSIGN_VALUE(value_list, index, item), \
MAGIC_ASSIGN_VALUE_ALL_IMPL_4(value_list, MAGIC_INDEXER(index), __VA_ARGS__)

#define MAGIC_ASSIGN_VALUE_ALL_IMPL_6(value_list, index, item, ...) \
MAGIC_ASSIGN_VALUE(value_list, index, item), \
MAGIC_ASSIGN_VALUE_ALL_IMPL_5(value_list, MAGIC_INDEXER(index), __VA_ARGS__)

#define MAGIC_ASSIGN_VALUE_ALL(value_list, last_index, index, ...) \
CAT(MAGIC_ASSIGN_VALUE_ALL_IMPL_, last_index)(value_list, index, __VA_ARGS__)

// to continuation of list
#define MAGIC_ITERATE(enum_name, enum_last_index, fn, pred, ...) \
fn(enum_name, enum_last_index, pred, __VA_ARGS__)

// read the buffer
#define MAGIC_ITERATE_FROM(value_list, enum_last_index, fn, first_index, ...) \
fn(value_list, enum_last_index, first_index, __VA_ARGS__)

#define MAGIC_MAKE_LIST(enum_name, enum_last_index, type, fn, wrap, pred, ...) \
inline constexpr type wrap(enum_name)[] = { MAGIC_ITERATE(enum_name, enum_last_index, fn, pred, __VA_ARGS__) }

#define MAGIC_MAKE_LISTs(enum_name, enum_last_index, ...) \
MAGIC_MAKE_LIST(enum_name, enum_last_index, enum_name \
, MAGIC_ATTACH_COLON_ALL, MAGIC_ENUMLIST, __PLA, __VA_ARGS__); \
MAGIC_MAKE_LIST(enum_name, enum_last_index, std::string_view \
, MAGIC_ATTACH_COLON_ALL, MAGIC_ENUMFULL, __STR, __VA_ARGS__); \
MAGIC_MAKE_LIST(enum_name, enum_last_index, std::string_view \
, MAGIC_ATTACH_COLON_ALL, MAGIC_ENUMNAME, __CAP, __VA_ARGS__)

#define MAGIC_ENUM_IOTA(enum_name, underlying_type, enum_last_index, first_value, first_item, ...) \
	MAGIC_ENUM_HEAD(enum_name, underlying_type) \
{ \
	first_item = first_value, \
	__VA_ARGS__,\
}; \
inline constexpr std::size_t MAGIC_ENUMSIZE(enum_name) = enum_last_index + 1; \
MAGIC_MAKE_LISTs(enum_name, enum_last_index, first_item, __VA_ARGS__)

#define MAGIC_ENUM(enum_name, underlying_type, enum_last_index, ...) \
	MAGIC_ENUM_HEAD(enum_name, underlying_type) \
{ \
	__VA_ARGS__, \
}; \
inline constexpr std::size_t MAGIC_ENUMSIZE(enum_name) = enum_last_index + 1; \
MAGIC_MAKE_LISTs(enum_name, enum_last_index, __VA_ARGS__)

#define MAGIC_ENUM_FROM(enum_name, underlying_type, enum_last_index, value_list, ...) \
	MAGIC_ENUM_HEAD(enum_name, underlying_type) \
{ \
	MAGIC_ITERATE_FROM(value_list, enum_last_index \
	, MAGIC_ASSIGN_VALUE_ALL, 0, __VA_ARGS__) \
}; \
inline constexpr std::size_t MAGIC_ENUMSIZE(enum_name) = std::size(value_list); \
MAGIC_MAKE_LISTs(enum_name, enum_last_index, __VA_ARGS__)

namespace gl::detail::test
{
	MAGIC_ENUM(AASDEWQDSFD, int, 9, a, b, c, d, e, f, g, h, i, j, k, l);
	constexpr auto aaa_i = MAGIC_ENUMLIST(AASDEWQDSFD)[0];
	constexpr auto aaa_n = MAGIC_ENUMFULL(AASDEWQDSFD)[0];
	constexpr auto aaa_t = MAGIC_ENUMNAME(AASDEWQDSFD)[0];

	MAGIC_ENUM_IOTA(DFIFJEIAS, long, 5, 10, aaa, b, c, d, e, f);
	constexpr auto dfi_i = MAGIC_ENUMLIST(DFIFJEIAS)[0];
	constexpr auto dfi_n = MAGIC_ENUMFULL(DFIFJEIAS)[0];
	constexpr auto dfi_t = MAGIC_ENUMNAME(DFIFJEIAS)[0];

	inline constexpr short test_predef[] =
	{
		10, 20, 40, 100, 120, 160, 170
	};

	MAGIC_ENUM_FROM(YOQWROB, short, 6, test_predef, qqq, www, eee, rrr, fff, eee, ttt);

	constexpr auto yoq_i = MAGIC_ENUMLIST(YOQWROB)[6];
	constexpr auto yoq_n = MAGIC_ENUMFULL(YOQWROB)[0];
	constexpr auto yoq_t = MAGIC_ENUMNAME(YOQWROB)[0];
}
