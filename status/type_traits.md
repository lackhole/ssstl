## Header `<type_traits>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/type_traits)  
[Implementation](../ss/include/ss/type_traits.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Implemented with C++ N
* ![][notyet]: Not yet implemented


| C++11 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Helper Classes**               |                         |
|integral_constant                 | ![][cpp11]              |
|                                  |                         |
| **Primary type categories**      |                         |
|is_void                           | ![][cpp11]              |
|is_integral                       | ![][cppno11]            |
|is_floating_point                 | ![][cpp11]              |
|is_array                          | ![][cpp11]              |
|is_enum                           | ![][cppno11]            |
|is_union                          | ![][cppno11]            |
|is_class                          | ![][cppno11]            |
|is_function                       | ![][cpp11]              |
|is_pointer                        | ![][cpp11]              |
|is_lvalue_reference               | ![][cpp11]              |
|is_rvalue_reference               | ![][cpp11]              |
|is_member_object_pointer          | ![][cpp11]              |
|is_member_function_pointer        | ![][cpp11]              |
|                                  |                         |
| **Composite type categories**    |                         |
|is_fundamental                    | ![][cpp11]              |
|is_arithmetic                     | ![][cpp11]              |
|is_scalar                         | ![][cpp11]              |
|is_object                         | ![][cpp11]              |
|is_compound                       | ![][cpp11]              |
|is_reference                      | ![][cpp11]              |
|is_member_pointer                 | ![][cpp11]              |
|                                  |                         |
| **Type properties**              |                         |
|is_const                          | ![][cpp11]              |
|is_volatile                       | ![][cpp11]              |
|is_trivial                        | ![][cpp11]              |
|is_trivially_copyable             | ![][cppno11]            |
|is_standard_layout                | ![][cppno11]            |
|is_pod                            | ![][cpp11]              |
|~~is_literal_type~~               | ![][removed]            |
|is_empty                          | ![][cpp11]              |
|is_polymorphic                    | ![][cpp11]              |
|is_abstract                       | ![][cpp11]              |
|is_signed                         | ![][cpp11]              |
|is_unsigned                       | ![][cpp11]              |
|                                  |                         |
| **Supported operations**         |                         |
|is_constructible                  | ![][cpp11]*             |
|is_trivially_constructible        | ![][cppno11]            |
|is_nothrow_constructible          | ![][cpp11]*             |
|is_default_constructible          | ![][cpp11]              |
|is_trivially_default_constructible| ![][cpp11]              |
|is_nothrow_default_constructible  | ![][cpp11]              |
|is_copy_constructible             | ![][cpp11]              |
|is_trivially_copy_constructible   | ![][cpp11]              |
|is_nothrow_copy_constructible     | ![][cpp11]              |
|is_move_constructible             | ![][cpp11]              |
|is_trivially_move_constructible   | ![][cpp11]              |
|is_nothrow_move_constructible     | ![][cpp11]              |
|is_assignable                     | ![][cpp11]*             |
|is_trivially_assignable           | ![][cppno11]            |
|is_nothrow_assignable             | ![][cpp11]*             |
|is_copy_assignable                | ![][cpp11]              |
|is_trivially_copy_assignable      | ![][cpp11]              |
|is_nothrow_copy_assignable        | ![][cpp11]              |
|is_move_assignable                | ![][cpp11]              |
|is_trivially_move_assignable      | ![][cpp11]              |
|is_nothrow_move_assignable        | ![][cpp11]              |
|is_destructible                   | ![][cpp11]*             |
|is_trivially_destructible         | ![][cppno11]            |
|is_nothrow_destructible           | ![][cpp11]*             |
|has_virtual_destructor            | ![][cppno11]            |
|                                  |                         |
| **Property queries**             |                         |
|alignment_of                      | ![][cpp11]              |
|rank                              | ![][cpp11]              |
|extent                            | ![][cpp11]              |
|is_same                           | ![][cpp11]              |
|is_base_of                        | ![][cpp11]              |
|is_convertible                    | ![][cpp11]*             |
|                                  |                         |
| **Const-volatility specifiers**  |                         |
|remove_cv                         | ![][cpp11]              |
|remove_const                      | ![][cpp11]              |
|remove_volatile                   | ![][cpp11]              |
|add_cv                            | ![][cpp11]              |
|add_const                         | ![][cpp11]              |
|add_volatile                      | ![][cpp11]              |
|                                  |                         |
| **References**                   |                         |
|remove_reference                  | ![][cpp11]              |
|add_lvalue_reference              | ![][cpp11]              |
|add_rvalue_reference              | ![][cpp11]              |
|                                  |                         |
| **Pointers**                     |                         |
|remove_pointer                    | ![][cpp11]              |
|add_pointer                       | ![][cpp11]              |
|                                  |                         |
| **Sign modifiers**               |                         |
|make_signed                       | ![][cpp11]              |
|make_unsigned                     | ![][cpp11]              |
|                                  |                         |
| **Arrays**                       |                         |
|remove_extent                     | ![][cpp11]              |
|remove_all_extents                | ![][cpp11]              |
|                                  |                         |
| **Miscellaneous transformations**|                         |
|aligned_storage                   | ![][cppno11]            |
|aligned_union                     | ![][cpp11]**            |
|decay                             | ![][cpp11]              |
|enable_if                         | ![][cpp11]              |
|conditional                       | ![][cpp11]              |
|common_type                       | ![][cpp11]*             |
|underlying_type                   | ![][cpp11]              |
|~~result_of~~                     | ![][removed]            |
|invoke_result                     | ![][notyet]             |

| C++14 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Primary type categories**      |                         |
|is_null_pointer                   | ![][cpp11]              |
|                                  |                         |
| **Type properties**              |                         |
|is_final                          | ![][cppno14]            |

| C++17 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Helper Classes**               |                         |
|bool_constant                     | ![][cpp11]              |
|                                  |                         |
| **Type properties**              |                         |
|has_unique_object_representations | ![][cppno17]            |
|is_aggregate                      | ![][cppno17]            |
|                                  |                         |
| **Supported operations**         |                         |
|is_swappable_with                 | ![][cpp11]*             |
|is_swappable                      | ![][cpp11]              |
|is_nothrow_swappable_with         | ![][cpp11]*             |
|is_nothrow_swappable              | ![][cpp11]              |
|                                  |                         |
| **Property queries**             |                         |
|is_invocable                      | ![][notyet]             |
|is_invocable_r                    | ![][notyet]             |
|is_nothrow_invocable              | ![][notyet]             |
|is_nothrow_invocable_r            | ![][notyet]             |
|                                  |                         |
| **Miscellaneous transformations**|                         |
|invoke_result                     | ![][notyet]             |
|void_t                            | ![][cpp11]              |
|                                  |                         |
| **Operations on traits**         |                         |
|conjunction                       | ![][cpp11]              |
|disjunction                       | ![][cpp11]              |
|negation                          | ![][cpp11]              |

| C++20 Features                   | Implemented in          |
|----------------------------------|:-----------------------:|
| **Type properties**              |                         |
|is_bounded_array                  | ![][cpp11]              |
|is_unbounded_array                | ![][cpp11]              |
|                                  |                         |
| **Property queries**             |                         |
|is_nothrow_convertible            | ![][cpp11]*             |
|is_layout_compatible              | ![][cppno20]            |
|is_pointer_interconvertible_base_of| ![][cppno20]           |
|                                  |                         |
| **Miscellaneous transformations**|                         |
|remove_cvref                      | ![][cpp11]              |
|common_reference <br/> basic_common_reference | ![][cpp11]  |
|type_identity                     | ![][cpp11]              |
|                                  |                         |
| **Member relationships**         |                         |
|is_pointer_interconvertible_with_class | ![][cppno20]       |
|is_corresponding_member           | ![][cppno20]            |
|                                  |                         |
| **Constant evaluation context**  |                         |
|is_constant_evaluated             | ![][cppno20] ![][cpp23] |

---
\* Used `std::declval<T>`  
\*\* Used `std::max`

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red

[cppno11]: https://img.shields.io/badge/C%2B%2B-11-red
[cppno14]: https://img.shields.io/badge/C%2B%2B-14-red
[cppno17]: https://img.shields.io/badge/C%2B%2B-17-red
[cppno20]: https://img.shields.io/badge/C%2B%2B-20-red
[cppno23]: https://img.shields.io/badge/C%2B%2B-23-red

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green

[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green

[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green

[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green

[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
