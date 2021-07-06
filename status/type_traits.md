## Header <type_traits> implementation status

[Reference](https://en.cppreference.com/w/cpp/header/type_traits)

* ![](https://img.shields.io/badge/Impossible-N-red): Cannot implement with language itself. Need compiler support
  Used STL with C++ version of N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Implemented with C++ N. Same version as STL
* ![](https://img.shields.io/badge/C%2B%2B-X--%3EY-blue): STL items in C++ X is implemented in C++ Y.
* ![][notyet]: Not yet implemented


| Name                             | Version (STL &#8594; Mine) |
|----------------------------------|:-----------------------:|
| **Helper Classes**               |                         |
|integral_constant                 | ![][cpp11]              |
|bool_constant                     | ![][cpp1711]            |
|                                  |                         |
| **Primary type categories**      |                         |
|is_void                           | ![][cpp11]              |
|is_null_pointer                   | ![][cpp1411]            |
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
|has_unique_object_representations | ![][cppno17]            |
|is_empty                          | ![][cpp11]              |
|is_polymorphic                    | ![][cpp11]              |
|is_abstract                       | ![][cpp11]              |
|is_final                          | ![][cppno14]            |
|is_aggregate                      | ![][cppno17]            |
|is_signed                         | ![][cpp11]              |
|is_unsigned                       | ![][cpp11]              |
|is_bounded_array                  | ![][cpp2011]            |
|is_unbounded_array                | ![][cpp2011]            |
|is_scoped_enum                    | ![][cppno23]            |
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
|is_swappable_with                 | ![][cpp11]*             |
|is_swappable                      | ![][cpp11]              |
|is_nothrow_swappable_with         | ![][cpp11]*             |
|is_nothrow_swappable              | ![][cpp11]              |
|                                  |                         |
| **Property queries**             |                         |
|alignment_of                      | ![][cpp11]              |
|rank                              | ![][cpp11]              |
|extent                            | ![][cpp11]              |
|is_same                           | ![][cpp11]              |
|is_base_of                        | ![][cpp11]              |
|is_convertible                    | ![][cpp11]*             |
|is_nothrow_convertible            | ![][cpp11]*             |
|is_layout_compatible              | ![][cppno20]            |
|is_pointer_interconvertible_base_of| ![][cppno20]           |
|is_invocable                      | ![][notyet]             |
|is_invocable_r                    | ![][notyet]             |
|is_nothrow_invocable              | ![][notyet]             |
|is_nothrow_invocable_r            | ![][notyet]             |
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
|remove_cvref                      | ![][cpp11]              |
|enable_if                         | ![][cpp11]              |
|conditional                       | ![][cpp11]              |
|common_type                       | ![][cpp11]*             |
|underlying_type                   | ![][cpp11]              |
|result_of                         | ![][cpp11]              |
|invoke_result                     | ![][notyet]             |
|void_t                            | ![][cpp11]              |
|type_identity                     | ![][cpp11]              |
|                                  |                         |
| **Operations on traits**         |                         |
|conjunction                       | ![][cpp11]              |
|disjunction                       | ![][cpp11]              |
|negation                          | ![][cpp11]              |
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

[cppno]: https://img.shields.io/badge/Impossible-red
[cppno11]: https://img.shields.io/badge/Impossible-11-red
[cppno14]: https://img.shields.io/badge/Impossible-14-red
[cppno17]: https://img.shields.io/badge/Impossible-17-red
[cppno20]: https://img.shields.io/badge/Impossible-20-red
[cppno23]: https://img.shields.io/badge/Impossible-23-red

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green
[cpp1411]: https://img.shields.io/badge/C%2B%2B-14--%3E11-blue
[cpp1711]: https://img.shields.io/badge/C%2B%2B-17--%3E11-blue
[cpp2011]: https://img.shields.io/badge/C%2B%2B-20--%3E11-blue
[cpp2311]: https://img.shields.io/badge/C%2B%2B-23--%3E11-blue

[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green
[cpp1714]: https://img.shields.io/badge/C%2B%2B-17--%3E14-blue
[cpp1714]: https://img.shields.io/badge/C%2B%2B-20--%3E14-blue
[cpp1714]: https://img.shields.io/badge/C%2B%2B-23--%3E14-blue

[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green
[cpp2017]: https://img.shields.io/badge/C%2B%2B-20--%3E17-blue
[cpp2317]: https://img.shields.io/badge/C%2B%2B-23--%3E17-blue

[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green
[cpp2320]: https://img.shields.io/badge/C%2B%2B-23--%3E20-blue

[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
