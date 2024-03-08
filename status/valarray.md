## Header `<valarray>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/valarray)  
[Implementation](../include/lsd/valarray.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<initializer_list>                          | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| valarray                                     | ![][legacy]          | ![][notyet]                       |
| slice                                        | ![][legacy]          | ![][notyet]                       |
| slice_array                                  | ![][legacy]          | ![][notyet]                       |
| gslice                                       | ![][legacy]          | ![][notyet]                       |
| gslice_array                                 | ![][legacy]          | ![][notyet]                       |
| mask_array                                   | ![][legacy]          | ![][notyet]                       |
| indirect_array                               | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| **Operations**                               |                      |                                   |
| lsd::swap(lsd::valarray)                       | ![][cpp11]           | ![][notyet]                       |
| lsd::begin(lsd::valarray)                      | ![][cpp11]           | ![][notyet]                       |
| lsd::end(lsd::valarray)                        | ![][cpp11]           | ![][notyet]                       |
| operator+ <br/>operator- <br/>operator* <br/>operator/ <br/>operator% <br/>operator& <br/>operator| <br/>operator^ <br/>operator\<\< <br/>operator>> <br/>operator&& <br/>operator|| | ![][legacy]          | ![][notyet]                       |
| operator== <br/>operator!= <br/>operator\< <br/>operator\<= <br/>operator> <br/>operator>= | ![][legacy]          | ![][notyet]                       |
| abs(lsd::valarray)                            | ![][legacy]          | ![][notyet]                       |
| **Exponential functions**                    |                      |                                   |
| exp(lsd::valarray)                            | ![][legacy]          | ![][notyet]                       |
| log(lsd::valarray)                            | ![][legacy]          | ![][notyet]                       |
| log10(lsd::valarray)                          | ![][legacy]          | ![][notyet]                       |
| **Power functions**                          |                      |                                   |
| pow(lsd::valarray)                            | ![][legacy]          | ![][notyet]                       |
| sqrt(lsd::valarray)                           | ![][legacy]          | ![][notyet]                       |
| **Trigonometric functions**                  |                      |                                   |
| sin(lsd::valarray)                            | ![][legacy]          | ![][notyet]                       |
| cos(lsd::valarray)                            | ![][legacy]          | ![][notyet]                       |
| tan(lsd::valarray)                            | ![][legacy]          | ![][notyet]                       |
| asin(lsd::valarray)                           | ![][legacy]          | ![][notyet]                       |
| acos(lsd::valarray)                           | ![][legacy]          | ![][notyet]                       |
| atan(lsd::valarray)                           | ![][legacy]          | ![][notyet]                       |
| atan2(lsd::valarray)                          | ![][legacy]          | ![][notyet]                       |
| **Hyperbolic functions**                     |                      |                                   |
| sinh(lsd::valarray)                           | ![][legacy]          | ![][notyet]                       |
| cosh(lsd::valarray)                           | ![][legacy]          | ![][notyet]                       |
| tanh(lsd::valarray)                           | ![][legacy]          | ![][notyet]                       |


<!--
	C++11: 29	| 0

	Total: 29	| 0-->

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
