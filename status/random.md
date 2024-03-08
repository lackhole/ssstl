## Header `<random>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/random)  
[Implementation](../include/lsd/random.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<initializer_list>                          | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Concepts**                                 |                      |                                   |
| **Uniform random bit generator requirements** |                      |                                   |
| uniform_random_bit_generator                 | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| **Random number engines**                    |                      |                                   |
| linear_congruential_engine                   | ![][cpp11]           | ![][notyet]                       |
| mersenne_twister_engine                      | ![][cpp11]           | ![][notyet]                       |
| subtract_with_carry_engine                   | ![][cpp11]           | ![][notyet]                       |
| **Random number engine adaptors**            |                      |                                   |
| discard_block_engine                         | ![][cpp11]           | ![][notyet]                       |
| independent_bits_engine                      | ![][cpp11]           | ![][notyet]                       |
| shuffle_order_engine                         | ![][cpp11]           | ![][notyet]                       |
| **Non-deterministic random numbers**         |                      |                                   |
| random_device                                | ![][cpp11]           | ![][notyet]                       |
| **Uniform distributions**                    |                      |                                   |
| uniform_int_distribution                     | ![][cpp11]           | ![][notyet]                       |
| uniform_real_distribution                    | ![][cpp11]           | ![][notyet]                       |
| **Bernoulli distributions**                  |                      |                                   |
| bernoulli_distribution                       | ![][cpp11]           | ![][notyet]                       |
| binomial_distribution                        | ![][cpp11]           | ![][notyet]                       |
| negative_binomial_distribution               | ![][cpp11]           | ![][notyet]                       |
| geometric_distribution                       | ![][cpp11]           | ![][notyet]                       |
| **Poisson distributions**                    |                      |                                   |
| poisson_distribution                         | ![][cpp11]           | ![][notyet]                       |
| exponential_distribution                     | ![][cpp11]           | ![][notyet]                       |
| gamma_distribution                           | ![][cpp11]           | ![][notyet]                       |
| weibull_distribution                         | ![][cpp11]           | ![][notyet]                       |
| extreme_value_distribution                   | ![][cpp11]           | ![][notyet]                       |
| **Normal distributions**                     |                      |                                   |
| normal_distribution                          | ![][cpp11]           | ![][notyet]                       |
| lognormal_distribution                       | ![][cpp11]           | ![][notyet]                       |
| chi_squared_distribution                     | ![][cpp11]           | ![][notyet]                       |
| cauchy_distribution                          | ![][cpp11]           | ![][notyet]                       |
| fisher_f_distribution                        | ![][cpp11]           | ![][notyet]                       |
| student_t_distribution                       | ![][cpp11]           | ![][notyet]                       |
| **Sampling distributions**                   |                      |                                   |
| discrete_distribution                        | ![][cpp11]           | ![][notyet]                       |
| piecewise_constant_distribution              | ![][cpp11]           | ![][notyet]                       |
| piecewise_linear_distribution                | ![][cpp11]           | ![][notyet]                       |
| **Utilities**                                |                      |                                   |
| seed_seq                                     | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| generate_canonical                           | ![][cpp11]           | ![][notyet]                       |


<!--
	C++11: 30	| 0
	C++20: 1	| 0

	Total: 31	| 0-->

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
