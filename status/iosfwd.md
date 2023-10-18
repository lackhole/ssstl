## Header `<iosfwd>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/iosfwd)  
[Implementation](../ss/include/ss/iosfwd.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Forward declarations**                     |                      |                                   |
| allocator                                    | ![][legacy]          | ![][notyet]                       |
| basic_ios                                    | ![][legacy]          | ![][notyet]                       |
| fpos                                         | ![][legacy]          | ![][notyet]                       |
| basic_streambuf                              | ![][legacy]          | ![][notyet]                       |
| basic_ostream                                | ![][legacy]          | ![][notyet]                       |
| basic_istream                                | ![][legacy]          | ![][notyet]                       |
| basic_iostream                               | ![][legacy]          | ![][notyet]                       |
| basic_filebuf                                | ![][legacy]          | ![][notyet]                       |
| basic_ifstream                               | ![][legacy]          | ![][notyet]                       |
| basic_ofstream                               | ![][legacy]          | ![][notyet]                       |
| basic_fstream                                | ![][legacy]          | ![][notyet]                       |
| basic_stringbuf                              | ![][legacy]          | ![][notyet]                       |
| basic_istringstream                          | ![][legacy]          | ![][notyet]                       |
| basic_ostringstream                          | ![][legacy]          | ![][notyet]                       |
| basic_stringstream                           | ![][legacy]          | ![][notyet]                       |
| basic_syncbuf                                | ![][cpp20]           | ![][notyet]                       |
| basic_osyncstream                            | ![][cpp20]           | ![][notyet]                       |
| basic_spanbuf                                | ![][cpp23]           | ![][notyet]                       |
| basic_ispanstream                            | ![][cpp23]           | ![][notyet]                       |
| basic_ospanstream                            | ![][cpp23]           | ![][notyet]                       |
| basic_spanstream                             | ![][cpp23]           | ![][notyet]                       |
| ~~strstreambuf~~                             | ![][legacy]          | Deprecated in C++98               |
| ~~istrstream~~                               | ![][legacy]          | Deprecated in C++98               |
| ~~ostrstream~~                               | ![][legacy]          | Deprecated in C++98               |
| ~~strstream~~                                | ![][legacy]          | Deprecated in C++98               |


<!--
	C++11: 15	| 0
	C++20: 2	| 0
	C++23: 4	| 0

	Total: 21	| 0-->

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
