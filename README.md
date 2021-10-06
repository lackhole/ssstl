<div align="center">
  
# SSSTL
SS Standard Template Library  
Focusing on implementing high C++ features for low C++(i.e. You can use `ss::optional<T>` in C++11)
  
# Build Status
[![g++](https://github.com/lackhole/ssstl/actions/workflows/gcc.yml/badge.svg)](https://github.com/lackhole/ssstl/actions/workflows/gcc.yml)
[![clang++](https://github.com/lackhole/ssstl/actions/workflows/clang.yml/badge.svg)](https://github.com/lackhole/ssstl/actions/workflows/clang.yml)
[![MSVC](https://github.com/lackhole/ssstl/actions/workflows/msvc.yml/badge.svg)](https://github.com/lackhole/ssstl/actions/workflows/msvc.yml)
</div>

# Code Coverage

<!--- 
100%      : brightgreen
75% ~ 100%: green
50% ~ 75% : yellowgreen
25% ~ 50% : yellow
0% ~ 25%  : orange
0%        : red
--->

* ![](https://img.shields.io/badge/not_possible-grey): Impossible to implement with language itself.
* ![](https://img.shields.io/badge/C++N-100%25-brightgreen): Implemented `C++ standard` == `N` features in C++ N.
* ![](https://img.shields.io/badge/C++N-100%25-blue): Implemented `C++ standard` > `N` features in C++ N.
* ![](https://img.shields.io/badge/C++N-X%25-green)
  ![](https://img.shields.io/badge/C++N-X%25-yellowgreen)
  ![](https://img.shields.io/badge/C++N-X%25-yellow)
  ![](https://img.shields.io/badge/C++N-X%25-orange)
  ![](https://img.shields.io/badge/C++N-X%25-red): 
  Implementation in progress.

| Concepts library                              | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| [concepts](status/concepts.md)                | ![][cpp20007]                                           |

| Coroutines library                            | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| coroutine                                     | ![][cpp20000]                                           |

| Utilities library                             | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| cstdlib                                       | ![][impossib]                                           |
| csignal                                       | ![][impossib]                                           |
| csetjmp                                       | ![][impossib]                                           |
| cstdarg                                       | ![][impossib]                                           |
| typeinfo                                      | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| typeindex                                     | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| [type_traits](status/type_traits.md)          | ![][cpp11100] ![][cpp14100] ![][cpp17069] ![][cpp20064] |
| bitset                                        | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| [functional](status/functional.md)            | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| [utility](status/utility.md)                  | ![][cpp11100] ![][cpp14100] ![][cpp17100] ![][cpp20096] |
| chrono                                        | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| initializer_list                              | ![][impossib]                                           |
| tuple                                         | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| any                                           | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| [optional](status/optional.md)                | ![][cpp11300] ![][cpp14200] ![][cpp17100] ![][cpp20000] |
| variant                                       | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| compare                                       | ![][unknown_]                                           |
| version                                       | ![][unknown_]                                           |
| source_location                               | ![][impossib]                                           |
| stacktrace                                    | ![][impossib]                                           |
| stacktrace                                    | ![][impossib]                                           |


| Dynamic memory management                     | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| new                                           | ![][unknown_]                                           |
| memory                                        | ![][cpp11003] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| scoped_allocator                              | ![][unknown_]                                           |
| memory_resource                               | ![][unknown_]                                           |


| Numeric limits                                | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| climits                                       | ![][unknown_]                                           |
| cfloat                                        | ![][unknown_]                                           |
| cstdint                                       | ![][unknown_]                                           |
| cinttypes                                     | ![][unknown_]                                           |
| limits                                        | ![][unknown_]                                           |

| Error handling                                | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| exception                                     | ![][unknown_]                                           |
| stdexcept                                     | ![][unknown_]                                           |
| cassert                                       | ![][unknown_]                                           |
| system_error                                  | ![][unknown_]                                           |
| cerrno                                        | ![][unknown_]                                           |

| Strings library                               | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| cctype                                        | ![][unknown_]                                           |
| cwctype                                       | ![][unknown_]                                           |
| cstring                                       | ![][unknown_]                                           |
| cwchar                                        | ![][unknown_]                                           |
| cuchar                                        | ![][unknown_]                                           |
| string                                        | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| string_view                                   | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| charconv                                      | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| format                                        | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |

| Containers library                            | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| array                                         | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| vector                                        | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| deque                                         | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| list                                          | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| forward_list                                  | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| set                                           | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| map                                           | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| unordered_set                                 | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| unordered_map                                 | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| stack                                         | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| queue                                         | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| span                                          | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |

| Iterators library                             | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| [iterator](status/iterator.md)                | ![][cpp11007] ![][cpp14000] ![][cpp17000] ![][cpp20002] |

| Ranges library                                | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| [ranges](status/ranges.md)                    | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |

| Algorithms library                            | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| [algorithm](status/algorithm.md)              | ![][cpp11001] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| execution                                     | ![][unknown_]                                           |

| Numerics library                              | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| cmath                                         | ![][unknown_]                                           |
| complex                                       | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| valarray                                      | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| random                                        | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| numeric                                       | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| ratio                                         | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |
| cfenv                                         | ![][unknown_]                                           |
| bit                                           | ![][unknown_]                                           |
| numbers                                       | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |

| Localization library                          | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| locale                                        | ![][unknown_]                                           |
| clocale                                       | ![][unknown_]                                           |
| codecvt                                       | ![][deprecat]                                           |

| Input/Output library                          | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| iosfwd                                        | ![][unknown_]                                           |
| ios                                           | ![][unknown_]                                           |
| istream                                       | ![][unknown_]                                           |
| ostream                                       | ![][unknown_]                                           |
| iostream                                      | ![][unknown_]                                           |
| fstream                                       | ![][unknown_]                                           |
| sstream                                       | ![][unknown_]                                           |
| syncstream                                    | ![][unknown_]                                           |
| spanstream                                    | ![][unknown_]                                           |
| strstream                                     | ![][deprecat]                                           |
| iomanip                                       | ![][unknown_]                                           |
| streambuf                                     | ![][unknown_]                                           |
| cstdio                                        | ![][impossib]                                           |

| Filesystem library                            | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| filesystem                                    | ![][impossib]                                           |

| Regular Expression library                    | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| filesystem                                    | ![][cpp11000] ![][cpp14000] ![][cpp17000] ![][cpp20000] |

| Atomic Operations library                     | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| atomic                                        |  ![][unknown_]                                          |

| Thread support library                        | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| thread                                        |  ![][unknown_]                                          |
| stop_token                                    |  ![][unknown_]                                          |
| mutex                                         |  ![][unknown_]                                          |
| shared_mutex                                  |  ![][unknown_]                                          |
| future                                        |  ![][unknown_]                                          |
| condition_variable                            |  ![][unknown_]                                          |
| semaphore                                     |  ![][unknown_]                                          |
| latch                                         |  ![][unknown_]                                          |
| barrier                                       |  ![][unknown_]                                          |


[impossib]: https://img.shields.io/badge/not_possible-grey
[unknown_]: https://img.shields.io/badge/unknown-grey
[deprecat]: https://img.shields.io/badge/deprecated-grey

[cpp11000]: https://img.shields.io/badge/C++11-0%25-red
[cpp11001]: https://img.shields.io/badge/C++11-1%25-orange
[cpp11003]: https://img.shields.io/badge/C++11-3%25-orange
[cpp11007]: https://img.shields.io/badge/C++11-7%25-orange
[cpp11100]: https://img.shields.io/badge/C++11-100%25-brightgreen
[cpp11200]: https://img.shields.io/badge/C++11-100%25-blue
[cpp11300]: https://img.shields.io/badge/C++11-100%25-blue

[cpp14000]: https://img.shields.io/badge/C++14-0%25-red
[cpp14100]: https://img.shields.io/badge/C++14-100%25-brightgreen
[cpp14200]: https://img.shields.io/badge/C++14-100%25-blue

[cpp17000]: https://img.shields.io/badge/C++17-0%25-red
[cpp17069]: https://img.shields.io/badge/C++17-69%25-yellowgreen
[cpp17075]: https://img.shields.io/badge/C++17-75%25-green
[cpp17100]: https://img.shields.io/badge/C++17-100%25-brightgreen
[cpp17200]: https://img.shields.io/badge/C++17-100%25-blue

[cpp20000]: https://img.shields.io/badge/C++20-0%25-red
[cpp20002]: https://img.shields.io/badge/C++20-2%25-orange
[cpp20007]: https://img.shields.io/badge/C++20-7%25-orange
[cpp20064]: https://img.shields.io/badge/C++20-64%25-yellowgreen
[cpp20096]: https://img.shields.io/badge/C++20-96%25-green
[cpp20100]: https://img.shields.io/badge/C++20-100%25-brightgreen
[cpp20200]: https://img.shields.io/badge/C++20-100%25-blue

[cpp23000]: https://img.shields.io/badge/C++23-0%25-red
[cpp23100]: https://img.shields.io/badge/C++23-100%25-brightgreen
