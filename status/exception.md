## Header `<exception>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/exception)  
[Implementation](../ss/include/ss/exception.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Types**                                    |                      |                                   |
| exception                                    | ![][legacy]          | ![][notyet]                       |
| nested_exception                             | ![][cpp11]           | ![][notyet]                       |
| bad_exception                                | ![][legacy]          | ![][notyet]                       |
| ~~unexpected_handler~~                       | ![][legacy]          | Removed in C++17                  |
| terminate_handler                            | ![][legacy]          | ![][notyet]                       |
| exception_ptr                                | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| ~~unexpected~~                               | ![][legacy]          | Removed in C++17                  |
| ~~uncaught_exception~~ <br/>uncaught_exceptions | ![][legacy] <br/>![][cpp17] | ![][notyet]                       |
| make_exception_ptr                           | ![][cpp11]           | ![][notyet]                       |
| current_exception                            | ![][cpp11]           | ![][notyet]                       |
| rethrow_exception                            | ![][cpp11]           | ![][notyet]                       |
| throw_with_nested                            | ![][cpp11]           | ![][notyet]                       |
| rethrow_if_nested                            | ![][cpp11]           | ![][notyet]                       |
| terminate                                    | ![][legacy]          | ![][notyet]                       |
| get_terminate                                | ![][cpp11]           | ![][notyet]                       |
| set_terminate                                | ![][legacy]          | ![][notyet]                       |
| ~~get_unexpected~~                           | ![][cpp11]           | Removed in C++17                  |
| ~~set_unexpected~~                           | ![][legacy]          | Removed in C++17                  |


<!--
	C++11: 13	| 0

	Total: 13	| 0-->

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
