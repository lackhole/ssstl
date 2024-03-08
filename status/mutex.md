## Header `<mutex>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/mutex)  
[Implementation](../include/lsd/mutex.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Classes**                                  |                      |                                   |
| mutex                                        | ![][cpp11]           | ![][notyet]                       |
| timed_mutex                                  | ![][cpp11]           | ![][notyet]                       |
| recursive_mutex                              | ![][cpp11]           | ![][notyet]                       |
| recursive_timed_mutex                        | ![][cpp11]           | ![][notyet]                       |
| lock_guard                                   | ![][cpp11]           | ![][notyet]                       |
| unique_lock                                  | ![][cpp11]           | ![][notyet]                       |
| scoped_lock                                  | ![][cpp17]           | ![][notyet]                       |
| defer_lock_t <br/>try_to_lock_t <br/>adopt_lock_t | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
| once_flag                                    | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Constants**                                |                      |                                   |
| defer_lock <br/>try_to_lock <br/>adopt_lock  | ![][cpp11] <br/>![][cpp11] <br/>![][cpp11] | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| try_lock                                     | ![][cpp11]           | ![][notyet]                       |
| lock                                         | ![][cpp11]           | ![][notyet]                       |
| call_once                                    | ![][cpp11]           | ![][notyet]                       |
| lsd::swap(lsd::unique_lock)                    | ![][cpp11]           | ![][notyet]                       |


<!--
	C++11: 11	| 0
	C++17: 1	| 0

	Total: 12	| 0-->

[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red
[legacy]: https://img.shields.io/badge/legacy-grey

[cppno11]: https://img.shields.io/badge/C%2B%2B-11-red
[cppno14]: https://img.shields.io/badge/C%2B%2B-14-red
[cppno17]: https://img.shields.io/badge/C%2B%2B-17-red
[cppno20]: https://img.shields.io/badge/C%2B%2B-20-red
[cppno23]: https://img.shields.io/badge/C%2B%2B-23-red
[cppno26]: https://img.shields.io/badge/C%2B%2B-23-red

[cpppt11]: https://img.shields.io/badge/C%2B%2B-11-blue
[cpppt14]: https://img.shields.io/badge/C%2B%2B-14-blue
[cpppt17]: https://img.shields.io/badge/C%2B%2B-17-blue
[cpppt20]: https://img.shields.io/badge/C%2B%2B-20-blue
[cpppt23]: https://img.shields.io/badge/C%2B%2B-23-blue
[cpppt26]: https://img.shields.io/badge/C%2B%2B-23-blue

[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green
[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green
[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green
[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green
[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green
