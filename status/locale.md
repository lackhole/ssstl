## Header `<locale>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/locale)  
[Implementation](../include/lsd/locale.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Classes**                                  |                      |                                   |
| locale                                       | ![][legacy]          | ![][notyet]                       |
| **String and stream conversions**            |                      |                                   |
| ~~wstring_convert~~                          | ![][cpp11]           | Deprecated in C++17               |
| ~~wbuffer_convert~~                          | ![][cpp11]           | Deprecated in C++17               |
| **Facet category base classes**              |                      |                                   |
| ctype_base                                   | ![][legacy]          | ![][notyet]                       |
| codecvt_base                                 | ![][legacy]          | ![][notyet]                       |
| messages_base                                | ![][legacy]          | ![][notyet]                       |
| time_base                                    | ![][legacy]          | ![][notyet]                       |
| money_base                                   | ![][legacy]          | ![][notyet]                       |
| **Facet categories**                         |                      |                                   |
| ctype                                        | ![][legacy]          | ![][notyet]                       |
| ctype\<char>                                 | ![][legacy]          | ![][notyet]                       |
| codecvt                                      | ![][legacy]          | ![][notyet]                       |
| collate                                      | ![][legacy]          | ![][notyet]                       |
| messages                                     | ![][legacy]          | ![][notyet]                       |
| time_get                                     | ![][legacy]          | ![][notyet]                       |
| time_put                                     | ![][legacy]          | ![][notyet]                       |
| num_get                                      | ![][legacy]          | ![][notyet]                       |
| num_put                                      | ![][legacy]          | ![][notyet]                       |
| numpunct                                     | ![][legacy]          | ![][notyet]                       |
| money_get                                    | ![][legacy]          | ![][notyet]                       |
| money_put                                    | ![][legacy]          | ![][notyet]                       |
| moneypunct                                   | ![][legacy]          | ![][notyet]                       |
| **Locale-specific facet categories**         |                      |                                   |
| ctype_byname                                 | ![][legacy]          | ![][notyet]                       |
| codecvt_byname                               | ![][legacy]          | ![][notyet]                       |
| messages_byname                              | ![][legacy]          | ![][notyet]                       |
| collate_byname                               | ![][legacy]          | ![][notyet]                       |
| time_get_byname                              | ![][legacy]          | ![][notyet]                       |
| time_put_byname                              | ![][legacy]          | ![][notyet]                       |
| numpunct_byname                              | ![][legacy]          | ![][notyet]                       |
| moneypunct_byname                            | ![][legacy]          | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| **Locales and facets**                       |                      |                                   |
| use_facet                                    | ![][legacy]          | ![][notyet]                       |
| has_facet                                    | ![][legacy]          | ![][notyet]                       |
| **Character classification**                 |                      |                                   |
| isspace(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| isblank(lsd::locale)                          | ![][cpp11]           | ![][notyet]                       |
| iscntrl(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| isupper(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| islower(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| isalpha(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| isdigit(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| ispunct(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| isxdigit(lsd::locale)                         | ![][legacy]          | ![][notyet]                       |
| isalnum(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| isprint(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| isgraph(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| **Character conversions**                    |                      |                                   |
| toupper(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |
| tolower(lsd::locale)                          | ![][legacy]          | ![][notyet]                       |


<!--
	C++11: 43	| 0

	Total: 43	| 0-->

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
