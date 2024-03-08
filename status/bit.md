## Header `<bit>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/bit)  
[Implementation](../include/lsd/bit.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Types**                                    |                      |                                   |
| endian                                       | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| bit_cast                                     | ![][cpp20]           | ![][notyet]                       |
| byteswap                                     | ![][cpp23]           | ![][notyet]                       |
| has_single_bit                               | ![][cpp20]           | ![][notyet]                       |
| bit_ceil                                     | ![][cpp20]           | ![][notyet]                       |
| bit_floor                                    | ![][cpp20]           | ![][notyet]                       |
| bit_width                                    | ![][cpp20]           | ![][notyet]                       |
| rotl                                         | ![][cpp20]           | ![][notyet]                       |
| rotr                                         | ![][cpp20]           | ![][notyet]                       |
| countl_zero                                  | ![][cpp20]           | ![][notyet]                       |
| countl_one                                   | ![][cpp20]           | ![][notyet]                       |
| countr_zero                                  | ![][cpp20]           | ![][notyet]                       |
| countr_one                                   | ![][cpp20]           | ![][notyet]                       |
| popcount                                     | ![][cpp20]           | ![][notyet]                       |


<!--
	C++20: 13	| 0
	C++23: 1	| 0

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
