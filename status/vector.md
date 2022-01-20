## Header `<vector>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/vector)  
[Implementation](../ss/include/ss/vector.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard                   | Implemented in                    |
|----------------------------------------------|:--------------------------:|:---------------------------------:|
| **Includes**                                 |                            |                                   |
| \<compare>                                   | ![][cpp20]                 |                                   |
| \<initializer_list>                          | ![][cpp11]                 |                                   |
|                                              |                            |                                   |
| **Classes**                                  |                            |                                   |
| vector                                       | ![][cpp11]                 | ![][notyet]                       |
| vector\<bool>                                | ![][cpp11]                 | ![][notyet]                       |
| ss::hash\<ss::vector\<bool>>                 | ![][cpp11]                 | ![][notyet]                       |
| **Forward declarations**                     |                            |                                   |
| hash                                         | ![][cpp11]                 | ![][cpp11]                        |
|                                              |                            |                                   |
| **Functions**                                |                            |                                   |
| operator== <br/>~~operator!=~~ <br/>~~operator\<~~ <br/>~~operator\<=~~ <br/>~~operator>~~ <br/>~~operator>=~~ <br/>operator\<=> | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp20] | ![][notyet]                       |
| ss::swap(ss::vector)                         | ![][cpp11]                 | ![][notyet]                       |
| erase(ss::vector) <br/>erase_if(ss::vector)  | ![][cpp20]                 | ![][notyet]                       |

<!--
	C++11: 6	| 1
	C++14: 0	| 0
	C++17: 0	| 0
	C++20: 2	| 0

	Total: 8	| 1 -->

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

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green
[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green
[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green
[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green
[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
