## Header `<memory>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/memory)  
[Implementation](../ss/include/ss/memory.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented


| Features                              | Standard | Implemented in          |
|---------------------------------------|:--------:|:-----------------------:|
| **Classes**                           |          |                         |
| **Pointer traits**                    |          |                         |
|pointer_traits                         |![][cpp11]| ![][cpp11]              |
| **Garbage collector support**         |          |                         |
|~~pointer_safety~~                     |![][cpp11]| Removed in C++23        |
| **Allocators**                        |          |                         |
|allocator                              |![][legcy]| ![][cpp11]              |
|allocator_traits                       |![][cpp11]| ![][cpp11]*             |
|allocation_result                      |![][cpp23]| ![][cpp11]              |
|allocator_arg_t                        |![][cpp11]| ![][cpp11]              |
|uses_allocator                         |![][cpp11]| ![][cpp11]              |
| **Uninitialized storage**             |          |                         |
|~~raw_storage_iterator~~               |![][legcy]| Removed in C++20        |
| **Smart pointers**                    |          |                         |
|unique_ptr                             |![][cpp11]| ![][cpp11]              |
|shared_ptr                             |![][cpp11]| ![][notyet]             |
|weak_ptr                               |![][cpp11]| ![][notyet]             |
|~~auto_ptr~~                           |![][cpp11]| Removed in C++17        |
| **Helper classes**                    |          |                         |
|ss::atomic\<ss::shared_ptr>            |![][cpp20]| ![][notyet]             |
|ss::atomic\<ss::weak_ptr>              |![][cpp20]| ![][notyet]             |
|owner_less                             |![][cpp11]| ![][notyet]             |
|enable_shared_from_this                |![][cpp11]| ![][notyet]             |
|bad_weak_ptr                           |![][cpp11]| ![][notyet]             |
|default_delete                         |![][cpp11]| ![][cpp11]              |
|ss::hash\<ss::unique_ptr>              |![][cpp11]| ![][notyet]             |
|ss::hash\<ss::shared_ptr>              |![][cpp11]| ![][notyet]             |
| **Smart pointer adaptors**            |          |                         |
|out_ptr_t                              |![][cpp23]| ![][notyet]             |
|inout_ptr_t                            |![][cpp23]| ![][notyet]             |
| **Forward declarations**              |          |                         |
|hash (defined in header functional)    |![][cpp11]| ![][notyet]             |
|inout_ptr_t (defined in header atomic) |![][cpp11]| ![][notyet]             |
|                                       |          |                         |
| **Constants**                         |          |                         |
|allocator_arg                          |![][cpp11]|                         |
|                                       |          |                         |
| **Functions**                         |          |                         |
| **Allocators**                        |          |                         |
|allocate_at_least                      |![][cpp23]| ![][cpp11]              |
| **Miscellaneous**                     |          |                         |
|to_address                             |![][cpp20]| ![][notyet]             |
|addressof                              |![][cpp11]| ![][cpp11]              |
|align                                  |![][cpp11]| ![][notyet]             |
|assume_aligned                         |![][cpp20]| ![][notyet]             |
| **Garbage collector support**         |          |                         |
|~~declare_reachable~~                  |![][cpp11]| Removed in C++23        |
|~~undeclare_reachable~~                |![][cpp11]| Removed in C++23        |
|~~declare_no_pointers~~                |![][cpp11]| Removed in C++23        |
|~~undeclare_no_pointers~~              |![][cpp11]| Removed in C++23        |
|~~get_pointer_safety~~                 |![][cpp11]| Removed in C++23        |
| **Uninitialized storage**             |          |                         |
|uninitialized_copy                     |![][legcy]| ![][notyet]             |
|uninitialized_copy_n                   |![][cpp11]| ![][notyet]             |
|uninitialized_fill                     |![][legcy]| ![][notyet]             |
|uninitialized_fill_n                   |![][legcy]| ![][notyet]             |
|uninitialized_move                     |![][cpp17]| ![][notyet]             |
|uninitialized_move_n                   |![][cpp17]| ![][notyet]             |
|uninitialized_default_construct        |![][cpp17]| ![][notyet]             |
|uninitialized_default_construct_n      |![][cpp17]| ![][notyet]             |
|uninitialized_value_construct          |![][cpp17]| ![][notyet]             |
|uninitialized_value_construct_n        |![][cpp17]| ![][notyet]             |
|construct_at                           |![][cpp20]| ![][notyet]             |
|destroy_at                             |![][cpp17]| ![][notyet]             |
|destroy                                |![][cpp17]| ![][notyet]             |
|destroy_n                              |![][cpp17]| ![][notyet]             |
|~~get_temporary_buffer~~               |![][legcy]| Removed in C++20        |
|~~return_temporary_buffer~~            |![][legcy]| Removed in C++20        |
| **Smart pointer non-member operations**                                                                       |                                           |                            |
|make_unique<br/> make_unique_for_overwrite                                                                     |![][cpp14]<br/> ![][cpp20]                 | ![][notyet]                |
|operator==<br/> operator!=<br/> operator<<br/> operator<=<br/> operator><br/> operator>=<br/> operator<=><br/> |![][cpp11]<br/> ![][cpp20]                 | (`unique_ptr`)![][notyet]  |
|make_shared<br/> make_shared_for_overwrite                                                                     |![][cpp11]<br/> ![][cpp20]                 | ![][notyet]                |
|allocate_shared<br/> allocate_shared_for_overwrite                                                             |![][cpp11]<br/> ![][cpp20]                 | ![][notyet]                |
|static_pointer_cast<br/> dynamic_pointer_cast<br/> const_pointer_cast<br/> reinterpret_pointer_cast            |![][cpp11]<br/> ![][cpp17]<br/> ![][cpp20] | ![][notyet]                |
|get_deleter                                                                                                    |![][legcy]                                 | ![][notyet]                |
|operator==<br/> ~~operator!=~~<br/> ~~operator<~~<br/> ~~operator<=~~<br/> ~~operator>~~<br/> ~~operator>=~~<br/> operator<=><br/> |![][cpp11]<br/> ![][cpp20] | (`shared_ptr`)![][notyet]  |
|operator<<                                                                                                     |![][legcy]                                 | ![][notyet]                |
|ss::swap(ss::unique_ptr)                                                                                       |![][legcy]                                 | ![][notyet]                |
|ss::swap(ss::weak_ptr)                                                                                         |![][legcy]                                 | ![][notyet]                |
| **Smart pointer adaptor creation**       |          |                                 |
|ss::swap(ss::shared_ptr)                  |![][cpp11]| ![][notyet]                     |
|out_ptr                                   |![][cpp23]| ![][notyet]                     |
|inout_ptr                                 |![][cpp23]| ![][notyet]                     |
|~~ss::atomic_...(ss::shared_ptr)~~        |![][cpp11]| Deprecated in C++20             |
|                                          |          |                                 |
| **FUnction-like entities**               |          | Defined in namespace ss::ranges |
| **Uninitialized storage**                |          |                                 |
|ranges::uninitialized_copy                |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_copy_n              |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_fill                |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_fill_n              |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_move                |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_move_n              |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_default_construct   |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_default_construct_n |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_value_construct     |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_value_construct_n   |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_construct_at        |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_destroy_at          |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_destroy             |![][cpp20]| ![][notyet]                     |
|ranges::uninitialized_destroy_n           |![][cpp20]| ![][notyet]                     |

<!-- 
    C++11 : 33  | 7
    C++14 : 1   | 0
    C++17 : 9   | 0
    C++20 : 19  | 0
    C++23 : 6   | 2

    Total: 68   | 9
-->

\* Used `std::numeric_limits`

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red

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

[legcy]: https://img.shields.io/badge/legacy-grey

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green

[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green

[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green

[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green

[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
