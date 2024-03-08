## Header `<new>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/new)  
[Implementation](../include/lsd/new.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Classes**                                  |                      |                                   |
| bad_alloc                                    | ![][legacy]          | ![][notyet]                       |
| bad_array_new_length                         | ![][cpp11]           | ![][notyet]                       |
| nothrow_t                                    | ![][legacy]          | ![][notyet]                       |
| align_val_t                                  | ![][cpp17]           | ![][notyet]                       |
| destroying_delete_t                          | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Types**                                    |                      |                                   |
| new_handler                                  | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Constants**                                |                      |                                   |
| nothrow                                      | ![][legacy]          | ![][notyet]                       |
| destroying_delete                            | ![][cpp20]           | ![][notyet]                       |
| hardware_destructive_interference_size <br/>hardware_constructive_interference_size | ![][cpp17]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| operator new <br/>operator new[]             | ![][legacy]          | ![][notyet]                       |
| operator delete <br/>operator delete[]       | ![][legacy]          | ![][notyet]                       |
| get_new_handler                              | ![][cpp11]           | ![][notyet]                       |
| set_new_handler                              | ![][legacy]          | ![][notyet]                       |
| launder                                      | ![][cpp17]           | ![][notyet]                       |


<!--
	C++11: 9	| 0
	C++17: 3	| 0
	C++20: 2	| 0

	Total: 14	| 0-->

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
