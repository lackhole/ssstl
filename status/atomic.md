## Header `<atomic>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/atomic)  
[Implementation](../ss/include/ss/atomic.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Classes**                                  |                      |                                   |
| atomic                                       | ![][cpp11]           | ![][notyet]                       |
| atomic_ref                                   | ![][cpp20]           | ![][notyet]                       |
| atomic_flag                                  | ![][cpp11]           | ![][notyet]                       |
| memory_order                                 | ![][cpp11]           | ![][notyet]                       |
| atomic_bool                                  | ![][cpp11]           | ![][notyet]                       |
| atomic_char                                  | ![][cpp11]           | ![][notyet]                       |
| atomic_schar                                 | ![][cpp11]           | ![][notyet]                       |
| atomic_uchar                                 | ![][cpp11]           | ![][notyet]                       |
| atomic_short                                 | ![][cpp11]           | ![][notyet]                       |
| atomic_ushort                                | ![][cpp11]           | ![][notyet]                       |
| atomic_int                                   | ![][cpp11]           | ![][notyet]                       |
| atomic_uint                                  | ![][cpp11]           | ![][notyet]                       |
| atomic_long                                  | ![][cpp11]           | ![][notyet]                       |
| atomic_ulong                                 | ![][cpp11]           | ![][notyet]                       |
| atomic_llong                                 | ![][cpp11]           | ![][notyet]                       |
| atomic_ullong                                | ![][cpp11]           | ![][notyet]                       |
| atomic_char8_t                               | ![][cpp20]           | ![][notyet]                       |
| atomic_char16_t                              | ![][cpp11]           | ![][notyet]                       |
| atomic_char32_t                              | ![][cpp11]           | ![][notyet]                       |
| atomic_wchar_t                               | ![][cpp11]           | ![][notyet]                       |
| atomic_int8_t                                | ![][cpp11]           | ![][notyet]                       |
| atomic_uint8_t                               | ![][cpp11]           | ![][notyet]                       |
| atomic_int16_t                               | ![][cpp11]           | ![][notyet]                       |
| atomic_uint16_t                              | ![][cpp11]           | ![][notyet]                       |
| atomic_int32_t                               | ![][cpp11]           | ![][notyet]                       |
| atomic_uint32_t                              | ![][cpp11]           | ![][notyet]                       |
| atomic_int64_t                               | ![][cpp11]           | ![][notyet]                       |
| atomic_uint64_t                              | ![][cpp11]           | ![][notyet]                       |
| atomic_int_least8_t                          | ![][cpp11]           | ![][notyet]                       |
| atomic_uint_least8_t                         | ![][cpp11]           | ![][notyet]                       |
| atomic_int_least16_t                         | ![][cpp11]           | ![][notyet]                       |
| atomic_uint_least16_t                        | ![][cpp11]           | ![][notyet]                       |
| atomic_int_least32_t                         | ![][cpp11]           | ![][notyet]                       |
| atomic_uint_least32_t                        | ![][cpp11]           | ![][notyet]                       |
| atomic_int_least64_t                         | ![][cpp11]           | ![][notyet]                       |
| atomic_uint_least64_t                        | ![][cpp11]           | ![][notyet]                       |
| atomic_int_fast8_t                           | ![][cpp11]           | ![][notyet]                       |
| atomic_uint_fast8_t                          | ![][cpp11]           | ![][notyet]                       |
| atomic_int_fast16_t                          | ![][cpp11]           | ![][notyet]                       |
| atomic_uint_fast16_t                         | ![][cpp11]           | ![][notyet]                       |
| atomic_int_fast32_t                          | ![][cpp11]           | ![][notyet]                       |
| atomic_uint_fast32_t                         | ![][cpp11]           | ![][notyet]                       |
| atomic_int_fast64_t                          | ![][cpp11]           | ![][notyet]                       |
| atomic_uint_fast64_t                         | ![][cpp11]           | ![][notyet]                       |
| atomic_intptr_t                              | ![][cpp11]           | ![][notyet]                       |
| atomic_uintptr_t                             | ![][cpp11]           | ![][notyet]                       |
| atomic_size_t                                | ![][cpp11]           | ![][notyet]                       |
| atomic_ptrdiff_t                             | ![][cpp11]           | ![][notyet]                       |
| atomic_intmax_t                              | ![][cpp11]           | ![][notyet]                       |
| atomic_uintmax_t                             | ![][cpp11]           | ![][notyet]                       |
| atomic_signed_lock_free                      | ![][cpp20]           | ![][notyet]                       |
| atomic_unsigned_lock_free                    | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| atomic_is_lock_free                          | ![][cpp11]           | ![][notyet]                       |
| atomic_store <br/>atomic_store_explicit      | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_load <br/>atomic_load_explicit        | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_exchange <br/>atomic_exchange_explicit | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_compare_exchange_weak <br/>atomic_compare_exchange_weak_explicit <br/>atomic_compare_exchange_strong <br/>atomic_compare_exchange_strong_explicit | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_fetch_add <br/>atomic_fetch_add_explicit | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_fetch_sub <br/>atomic_fetch_sub_explicit | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_fetch_and <br/>atomic_fetch_and_explicit | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_fetch_or <br/>atomic_fetch_or_explicit | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_fetch_xor <br/>atomic_fetch_xor_explicit | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_wait <br/>atomic_wait_explicit        | ![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
| atomic_notify_one                            | ![][cpp20]           | ![][notyet]                       |
| atomic_notify_all                            | ![][cpp20]           | ![][notyet]                       |
| atomic_flag_test <br/>atomic_flag_test_explicit | ![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
| atomic_flag_test_and_set <br/>atomic_flag_test_and_set_explicit | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_flag_clear <br/>atomic_flag_clear_explicit | ![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| atomic_flag_wait <br/>atomic_flag_wait_explicit | ![][cpp20] <br/>![][cpp20] | ![][notyet]                       |
| atomic_flag_notify_one                       | ![][cpp20]           | ![][notyet]                       |
| atomic_flag_notify_all                       | ![][cpp20]           | ![][notyet]                       |
| ~~atomic_init~~                              | ![][cpp11]           | Deprecated in C++20               |
| kill_dependency                              | ![][cpp11]           | ![][notyet]                       |
| atomic_thread_fence                          | ![][cpp11]           | ![][notyet]                       |
| atomic_signal_fence                          | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Macros**                                   |                      |                                   |
| ~~ATOMIC_VAR_INIT~~                          | ![][cpp11]           | Deprecated in C++20               |
| ATOMIC_FLAG_INIT                             | ![][cpp11]           | ![][notyet]                       |


<!--
	C++11: 53	| 0
	C++20: 8	| 0

	Total: 61	| 0-->

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red
[legacy]: https://img.shields.io/badge/legacy-grey

[cppno11]: https://img.shields.io/badge/C%2B%2B-11-red
[cppno14]: https://img.shields.io/badge/C%2B%2B-14-red
[cppno17]: https://img.shields.io/badge/C%2B%2B-17-red
[cppno20]: https://img.shields.io/badge/C%2B%2B-20-red
[cppno23]: https://img.shields.io/badge/C%2B%2B-23-red

[cpppt11]: https://img.shields.io/badge/C%2B%2B-11-blue
[cpppt14]: https://img.shields.io/badge/C%2B%2B-14-blue
[cpppt17]: https://img.shields.io/badge/C%2B%2B-17-blue
[cpppt20]: https://img.shields.io/badge/C%2B%2B-20-blue
[cpppt23]: https://img.shields.io/badge/C%2B%2B-23-blue

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green
[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green
[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green
[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green
[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
