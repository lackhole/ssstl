## Header `<flat_map>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/flat_map)  
[Implementation](../ss/include/ss/flat_map.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<compare>                                   | ![][cpp20]           | ![][notyet]                       |
| \<initializer_list>                          | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| flat_map                                     | ![][cpp23]           | ![][notyet]                       |
| flat_multimap                                | ![][cpp23]           | ![][notyet]                       |
| sorted_unique_t                              | ![][cpp23]           | ![][notyet]                       |
| sorted_equivalent_t                          | ![][cpp23]           | ![][notyet]                       |
| ss::uses_allocator\<ss::flat_map>            | ![][cpp23]           | ![][notyet]                       |
| ss::uses_allocator\<ss::flat_multimap>       | ![][cpp23]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| erase_if(ss::flat_map)                       | ![][cpp23]           | ![][notyet]                       |
| erase_if(ss::flat_multimap)                  | ![][cpp23]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Constants**                                |                      |                                   |
| sorted_unique                                | ![][cpp23]           | ![][notyet]                       |
| sorted_equivalent                            | ![][cpp23]           | ![][notyet]                       |


<!--
	C++11: 1	| 0
	C++20: 1	| 0
	C++23: 10	| 0

	Total: 12	| 0-->

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
