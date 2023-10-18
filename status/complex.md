## Header `<complex>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/complex)  
[Implementation](../ss/include/ss/complex.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| complex                                      | ![][legacy]          | ![][notyet]                       |
| **Operations**                               |                      |                                   |
| operator+ <br/>operator-                     | ![][legacy]          | ![][notyet]                       |
| operator+ <br/>operator- <br/>operator* <br/>operator/ | ![][legacy]          | ![][notyet]                       |
| operator== <br/>~~operator!=~~               | ![][legacy] <br/>![][legacy] | ![][notyet]                       |
| operator\<\< <br/>operator>>                 | ![][legacy]          | ![][notyet]                       |
| real                                         | ![][legacy]          | ![][notyet]                       |
| imag                                         | ![][legacy]          | ![][notyet]                       |
| abs(ss::complex)                             | ![][legacy]          | ![][notyet]                       |
| arg                                          | ![][legacy]          | ![][notyet]                       |
| norm                                         | ![][legacy]          | ![][notyet]                       |
| conj                                         | ![][legacy]          | ![][notyet]                       |
| proj                                         | ![][cpp11]           | ![][notyet]                       |
| polar                                        | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Exponential functions**                    |                      |                                   |
| exp(ss::complex)                             | ![][legacy]          | ![][notyet]                       |
| log(ss::complex)                             | ![][legacy]          | ![][notyet]                       |
| log10(ss::complex)                           | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Power functions**                          |                      |                                   |
| pow(ss::complex)                             | ![][legacy]          | ![][notyet]                       |
| sqrt(ss::complex)                            | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Trigonometric functions**                  |                      |                                   |
| sin(ss::complex)                             | ![][legacy]          | ![][notyet]                       |
| cos(ss::complex)                             | ![][legacy]          | ![][notyet]                       |
| tan(ss::complex)                             | ![][legacy]          | ![][notyet]                       |
| asin(ss::complex)                            | ![][cpp11]           | ![][notyet]                       |
| acos(ss::complex)                            | ![][cpp11]           | ![][notyet]                       |
| atan(ss::complex)                            | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Hyperbolic functions**                     |                      |                                   |
| sinh(ss::complex)                            | ![][legacy]          | ![][notyet]                       |
| cosh(ss::complex)                            | ![][legacy]          | ![][notyet]                       |
| tanh(ss::complex)                            | ![][legacy]          | ![][notyet]                       |
| asinh(ss::complex)                           | ![][cpp11]           | ![][notyet]                       |
| acosh(ss::complex)                           | ![][cpp11]           | ![][notyet]                       |
| atanh(ss::complex)                           | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Literals**                                 |                      |                                   |
| operator""if <br/>operator""i <br/>operator""il | ![][cpp14]           | ![][notyet]                       |


<!--
	C++11: 29	| 0
	C++14: 1	| 0

	Total: 30	| 0-->

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
