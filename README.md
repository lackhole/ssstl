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
| concepts                                      | ![](https://img.shields.io/badge/C++20-0%25-red)        |

| Coroutines library                            | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| coroutine                                     | ![](https://img.shields.io/badge/C++20-0%25-red)        |

| Utilities library                             | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| cstdlib                                       | ![](https://img.shields.io/badge/not_possible-grey)     |
| csignal                                       | ![](https://img.shields.io/badge/not_possible-grey)     |
| csetjmp                                       | ![](https://img.shields.io/badge/not_possible-grey)     |
| cstdarg                                       | ![](https://img.shields.io/badge/not_possible-grey)     |
| typeinfo                                      | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| typeindex                                     | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| [type_traits](status/type_traits.md)          | ![](https://img.shields.io/badge/C++11-100%25-brightgreen) ![](https://img.shields.io/badge/C++14-100%25-brightgreen) ![](https://img.shields.io/badge/C++17-69%25-yellowgreen) ![](https://img.shields.io/badge/C++20-64%25-yellowgreen) |
| bitset                                        | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| functional                                    | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| [utility](status/utility.md)                  | ![](https://img.shields.io/badge/C++11-18%25-orange)       ![](https://img.shields.io/badge/C++14-0%25-red)           ![](https://img.shields.io/badge/C++17-75%25-green)       ![](https://img.shields.io/badge/C++20-0%25-red)          |
| chrono                                        | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| initializer_list                              | ![](https://img.shields.io/badge/not_possible-grey)     |
| tuple                                         | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| any                                           | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| [optional](status/optional.md)                | ![](https://img.shields.io/badge/C++11-100%25-blue)        ![](https://img.shields.io/badge/C++14-100%25-blue)        ![](https://img.shields.io/badge/C++17-100%25-green)      ![](https://img.shields.io/badge/C++20-0%25-red)          |
| variant                                       | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| compare                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| version                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| source_location                               | ![](https://img.shields.io/badge/not_possible-grey)     |
| stacktrace                                    | ![](https://img.shields.io/badge/not_possible-grey)     |
| stacktrace                                    | ![](https://img.shields.io/badge/not_possible-grey)     |


| Dynamic memory management                     | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| new                                           | ![](https://img.shields.io/badge/unknown-grey)          |
| memory                                        | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| scoped_allocator                              | ![](https://img.shields.io/badge/unknown-grey)          |
| memory_resource                               | ![](https://img.shields.io/badge/unknown-grey)          |


| Numeric limits                                | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| climits                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| cfloat                                        | ![](https://img.shields.io/badge/unknown-grey)          |
| cstdint                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| cinttypes                                     | ![](https://img.shields.io/badge/unknown-grey)          |
| limits                                        | ![](https://img.shields.io/badge/unknown-grey)          |

| Error handling                                | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| exception                                     | ![](https://img.shields.io/badge/unknown-grey)          |
| stdexcept                                     | ![](https://img.shields.io/badge/unknown-grey)          |
| cassert                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| system_error                                  | ![](https://img.shields.io/badge/unknown-grey)          |
| cerrno                                        | ![](https://img.shields.io/badge/unknown-grey)          |

| Strings library                               | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| cctype                                        | ![](https://img.shields.io/badge/unknown-grey)          |
| cwctype                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| cstring                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| cwchar                                        | ![](https://img.shields.io/badge/unknown-grey)          |
| cuchar                                        | ![](https://img.shields.io/badge/unknown-grey)          |
| string                                        | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| string_view                                   | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| charconv                                      | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| format                                        | ![](https://img.shields.io/badge/coverage-0%25-red)     |

| Containers library                            | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| array                                         | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| vector                                        | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| deque                                         | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| list                                          | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| forward_list                                  | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| set                                           | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| map                                           | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| unordered_set                                 | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| unordered_map                                 | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| stack                                         | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| queue                                         | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| span                                          | ![](https://img.shields.io/badge/coverage-0%25-red)     |

| Iterators library                             | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| [iterator](status/iterator.md)                | ![](https://img.shields.io/badge/C++11-7%25-orange)        ![](https://img.shields.io/badge/C++14-0%25-red)           ![](https://img.shields.io/badge/C++17-0%25-red)             ![](https://img.shields.io/badge/C++20-2%25-orange)    |

| Ranges library                                | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| ranges                                        | ![](https://img.shields.io/badge/coverage-0%25-red)     |

| Algorithms library                            | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| [algorithm](status/algorithm.md)              | ![](https://img.shields.io/badge/C++11-1%25-orange)        ![](https://img.shields.io/badge/C++14-0%25-red)           ![](https://img.shields.io/badge/C++17-0%25-red)             ![](https://img.shields.io/badge/C++20-0%25-red)       |
| execution                                     | ![](https://img.shields.io/badge/unknown-grey)          |

| Numerics library                              | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| cmath                                         | ![](https://img.shields.io/badge/unknown-grey)          |
| complex                                       | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| valarray                                      | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| random                                        | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| numeric                                       | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| ratio                                         | ![](https://img.shields.io/badge/coverage-0%25-red)     |
| cfenv                                         | ![](https://img.shields.io/badge/unknown-grey)          |
| bit                                           | ![](https://img.shields.io/badge/unknown-grey)          |
| numbers                                       | ![](https://img.shields.io/badge/coverage-0%25-red)     |

| Localization library                          | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| locale                                        | ![](https://img.shields.io/badge/unknown-grey)          |
| clocale                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| codecvt                                       | ![](https://img.shields.io/badge/deprecated-grey)       |

| Input/Output library                          | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| iosfwd                                        | ![](https://img.shields.io/badge/unknown-grey)          |
| ios                                           | ![](https://img.shields.io/badge/unknown-grey)          |
| istream                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| ostream                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| iostream                                      | ![](https://img.shields.io/badge/unknown-grey)          |
| fstream                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| sstream                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| syncstream                                    | ![](https://img.shields.io/badge/unknown-grey)          |
| spanstream                                    | ![](https://img.shields.io/badge/unknown-grey)          |
| strstream                                     | ![](https://img.shields.io/badge/deprecated-grey)       |
| iomanip                                       | ![](https://img.shields.io/badge/unknown-grey)          |
| streambuf                                     | ![](https://img.shields.io/badge/unknown-grey)          |
| cstdio                                        | ![](https://img.shields.io/badge/not_possible-grey)     |

| Filesystem library                            | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| filesystem                                    | ![](https://img.shields.io/badge/not_possible-grey)     |

| Regular Expression library                    | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| filesystem                                    | ![](https://img.shields.io/badge/coverage-0%25-red)     |

| Atomic Operations library                     | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| atomic                                        |  ![](https://img.shields.io/badge/unknown-grey)         |

| Thread support library                        | Feature status                                          |
|-----------------------------------------------|---------------------------------------------------------|
| thread                                        |  ![](https://img.shields.io/badge/unknown-grey)         |
| stop_token                                    |  ![](https://img.shields.io/badge/unknown-grey)         |
| mutex                                         |  ![](https://img.shields.io/badge/unknown-grey)         |
| shared_mutex                                  |  ![](https://img.shields.io/badge/unknown-grey)         |
| future                                        |  ![](https://img.shields.io/badge/unknown-grey)         |
| condition_variable                            |  ![](https://img.shields.io/badge/unknown-grey)         |
| semaphore                                     |  ![](https://img.shields.io/badge/unknown-grey)         |
| latch                                         |  ![](https://img.shields.io/badge/unknown-grey)         |
| barrier                                       |  ![](https://img.shields.io/badge/unknown-grey)         |
