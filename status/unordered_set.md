## Header `<unordered_set>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/unordered_set)  
[Implementation](../ss/include/ss/unordered_set.h)

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
| unordered_set                                | ![][cpp11]           | ![][notyet]                       |
| unordered_multiset                           | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| operator== <br/>~~operator!=~~               | ![][legacy] <br/>![][legacy] | ![][notyet]                       |
| ss::swap(ss::unordered_set)                  | ![][cpp11]           | ![][notyet]                       |
| erase_if(ss::unordered_set)                  | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>~~operator!=~~               | ![][legacy] <br/>![][legacy] | ![][notyet]                       |
| ss::swap(ss::unordered_multiset)             | ![][cpp11]           | ![][notyet]                       |
| erase_if(ss::unordered_multiset)             | ![][cpp20]           | ![][notyet]                       |
| **Range access**                             |                      |                                   |
| begin <br/>cbegin                            | ![][cpp11] <br/>![][cpp14] | ![][notyet]                       |
| end <br/>cend                                | ![][cpp11] <br/>![][cpp14] | ![][notyet]                       |
| rbegin <br/>crbegin                          | ![][cpp14]           | ![][notyet]                       |
| rend <br/>crend                              | ![][cpp14]           | ![][notyet]                       |
| size <br/>ssize                              | ![][cpp17] <br/>![][cpp20] | ![][notyet]                       |
| empty                                        | ![][cpp17]           | ![][notyet]                       |
| data                                         | ![][cpp17]           | ![][notyet]                       |


<!--
	C++11: 5	| 0
	C++14: 2	| 0
	C++17: 2	| 0
	C++20: 3	| 0

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
