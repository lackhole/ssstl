## Header `<chrono>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/chrono)  
[Implementation](../include/lsd/chrono.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented

| Features                                     | Standard             | Implemented in                    |
|----------------------------------------------|:--------------------:|:---------------------------------:|
| **Includes**                                 |                      |                                   |
| \<compare>                                   | ![][cpp20]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Classes**                                  |                      |                                   |
| **Duration**                                 |                      |                                   |
| duration                                     | ![][cpp11]           | ![][notyet]                       |
| treat_as_floating_point                      | ![][cpp11]           | ![][notyet]                       |
| duration_values                              | ![][cpp11]           | ![][notyet]                       |
| **Time point**                               |                      |                                   |
| time_point                                   | ![][cpp11]           | ![][notyet]                       |
| clock_time_conversion                        | ![][cpp20]           | ![][notyet]                       |
| **Clocks**                                   |                      |                                   |
| is_clock <br/>is_clock_v                     | ![][cpp20]           | ![][notyet]                       |
| system_clock                                 | ![][cpp11]           | ![][notyet]                       |
| steady_clock                                 | ![][cpp11]           | ![][notyet]                       |
| high_resolution_clock                        | ![][cpp11]           | ![][notyet]                       |
| utc_clock                                    | ![][cpp20]           | ![][notyet]                       |
| tai_clock                                    | ![][cpp20]           | ![][notyet]                       |
| gps_clock                                    | ![][cpp20]           | ![][notyet]                       |
| file_clock                                   | ![][cpp20]           | ![][notyet]                       |
| local_t                                      | ![][cpp20]           | ![][notyet]                       |
| **Calendar**                                 |                      |                                   |
| last_spec                                    | ![][cpp20]           | ![][notyet]                       |
| day                                          | ![][cpp20]           | ![][notyet]                       |
| month                                        | ![][cpp20]           | ![][notyet]                       |
| year                                         | ![][cpp20]           | ![][notyet]                       |
| weekday                                      | ![][cpp20]           | ![][notyet]                       |
| weekday_indexed                              | ![][cpp20]           | ![][notyet]                       |
| weekday_last                                 | ![][cpp20]           | ![][notyet]                       |
| month_day                                    | ![][cpp20]           | ![][notyet]                       |
| month_day_last                               | ![][cpp20]           | ![][notyet]                       |
| month_weekday                                | ![][cpp20]           | ![][notyet]                       |
| month_weekday_last                           | ![][cpp20]           | ![][notyet]                       |
| year_month                                   | ![][cpp20]           | ![][notyet]                       |
| year_month_day                               | ![][cpp20]           | ![][notyet]                       |
| year_month_day_last                          | ![][cpp20]           | ![][notyet]                       |
| year_month_weekday                           | ![][cpp20]           | ![][notyet]                       |
| year_month_weekday_last                      | ![][cpp20]           | ![][notyet]                       |
| **Time of day**                              |                      |                                   |
| hh_mm_ss                                     | ![][cpp20]           | ![][notyet]                       |
| **Time zone**                                |                      |                                   |
| tzdb                                         | ![][cpp20]           | ![][notyet]                       |
| tzdb_list                                    | ![][cpp20]           | ![][notyet]                       |
| time_zone                                    | ![][cpp20]           | ![][notyet]                       |
| sys_info                                     | ![][cpp20]           | ![][notyet]                       |
| local_info                                   | ![][cpp20]           | ![][notyet]                       |
| choose                                       | ![][cpp20]           | ![][notyet]                       |
| zoned_traits                                 | ![][cpp20]           | ![][notyet]                       |
| zoned_time                                   | ![][cpp20]           | ![][notyet]                       |
| time_zone_link                               | ![][cpp20]           | ![][notyet]                       |
| nonexistent_local_time                       | ![][cpp20]           | ![][notyet]                       |
| ambiguous_local_time                         | ![][cpp20]           | ![][notyet]                       |
| **Leap second**                              |                      |                                   |
| leap_second                                  | ![][cpp20]           | ![][notyet]                       |
| leap_second_info                             | ![][cpp20]           | ![][notyet]                       |
| **Specializations**                          |                      |                                   |
| lsd::common_type\<lsd::chrono::duration>       | ![][cpp11]           | ![][notyet]                       |
| lsd::common_type\<lsd::chrono::time_point>     | ![][cpp11]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::duration>         | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::sys_time>         | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::utc_time>         | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::tai_time>         | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::gps_time>         | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::file_time>        | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::local_time>       | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::day>              | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::month>            | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::year>             | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::weekday>          | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::weekday_indexed>  | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::weekday_last>     | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::month_day>        | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::month_day_last>   | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::month_weekday>    | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::month_weekday_last> | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::year_month>       | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::year_month_day>   | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::year_month_day_last> | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::year_month_weekday> | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::year_month_weekday_last> | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::hh_mm_ss>         | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::sys_info>         | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::local_info>       | ![][cpp20]           | ![][notyet]                       |
| lsd::formatter\<lsd::chrono::zoned_time>       | ![][cpp20]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::duration>              | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::time_point>            | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::day>                   | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::month>                 | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::year>                  | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::weekday>               | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::weekday_indexed>       | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::weekday_last>          | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::month_day>             | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::month_day_last>        | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::month_weekday>         | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::month_weekday_last>    | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::year_month>            | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::year_month_day>        | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::year_month_day_last>   | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::year_month_weekday>    | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::year_month_weekday_last> | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::zoned_time>            | ![][cpp26]           | ![][notyet]                       |
| lsd::hash\<lsd::chrono::leap_second>           | ![][cpp26]           | ![][notyet]                       |
| **Forward declarations**                     |                      |                                   |
| hash                                         | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| **Duration**                                 |                      |                                   |
| operator+ <br/>operator- <br/>operator* <br/>operator/ <br/>operator% | ![][cpp11]           | ![][notyet]                       |
| operator== <br/>~~operator!=~~ <br/>operator\< <br/>operator\<= <br/>operator> <br/>operator>= <br/>operator\<=> | ![][cpp11] <br/>![][legacy] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp20] | ![][notyet]                       |
| duration_cast                                | ![][cpp11]           | ![][notyet]                       |
| floor(lsd::chrono::duration)                  | ![][cpp17]           | ![][notyet]                       |
| ceil(lsd::chrono::duration)                   | ![][cpp17]           | ![][notyet]                       |
| round(lsd::chrono::duration)                  | ![][cpp17]           | ![][notyet]                       |
| abs(lsd::chrono::duration)                    | ![][cpp17]           | ![][notyet]                       |
| **Time point**                               |                      |                                   |
| operator+ <br/>operator-                     | ![][cpp11]           | ![][notyet]                       |
| operator== <br/>~~operator!=~~ <br/>operator\< <br/>operator\<= <br/>operator> <br/>operator>= <br/>operator\<=> | ![][cpp11] <br/>![][legacy] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp11] <br/>![][cpp20] | ![][notyet]                       |
| time_point_cast                              | ![][cpp11]           | ![][notyet]                       |
| floor(lsd::chrono::time_point)                | ![][cpp17]           | ![][notyet]                       |
| ceil(lsd::chrono::time_point)                 | ![][cpp17]           | ![][notyet]                       |
| round(lsd::chrono::time_point)                | ![][cpp17]           | ![][notyet]                       |
| from_stream(lsd::chrono::sys_time)            | ![][cpp20]           | ![][notyet]                       |
| from_stream(lsd::chrono::utc_time)            | ![][cpp20]           | ![][notyet]                       |
| from_stream(lsd::chrono::tai_time)            | ![][cpp20]           | ![][notyet]                       |
| from_stream(lsd::chrono::gps_time)            | ![][cpp20]           | ![][notyet]                       |
| from_stream(lsd::chrono::file_time)           | ![][cpp20]           | ![][notyet]                       |
| from_stream(lsd::chrono::local_time)          | ![][cpp20]           | ![][notyet]                       |
| clock_cast                                   | ![][cpp20]           | ![][notyet]                       |
| **Calendar**                                 |                      |                                   |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator==                                   | ![][cpp20]           | ![][notyet]                       |
| operator==                                   | ![][cpp20]           | ![][notyet]                       |
| operator==                                   | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator==                                   | ![][cpp20]           | ![][notyet]                       |
| operator==                                   | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator==                                   | ![][cpp20]           | ![][notyet]                       |
| operator==                                   | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator+ <br/>operator-                     | ![][cpp20]           | ![][notyet]                       |
| operator/                                    | ![][cpp20]           | ![][notyet]                       |
| **Time of day**                              |                      |                                   |
| is_am <br/>is_pm <br/>make12 <br/>make24     | ![][cpp20]           | ![][notyet]                       |
| **Time zone**                                |                      |                                   |
| get_tzdb <br/>get_tzdb_list <br/>reload_tzdb <br/>remote_version | ![][cpp20]           | ![][notyet]                       |
| locate_zone                                  | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| operator==                                   | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\<=>                 | ![][cpp20]           | ![][notyet]                       |
| **Leap second**                              |                      |                                   |
| get_leap_second_info                         | ![][cpp20]           | ![][notyet]                       |
| operator== <br/>operator\< <br/>operator\<= <br/>operator> <br/>operator>= <br/>operator\<=> | ![][cpp20]           | ![][notyet]                       |
| **I/O**                                      |                      |                                   |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<(lsd::chrono::sys_time)           | ![][cpp20]           | ![][notyet]                       |
| operator\<\<(lsd::chrono::utc_time)           | ![][cpp20]           | ![][notyet]                       |
| operator\<\<(lsd::chrono::tai_time)           | ![][cpp20]           | ![][notyet]                       |
| operator\<\<(lsd::chrono::gps_time)           | ![][cpp20]           | ![][notyet]                       |
| operator\<\<(lsd::chrono::file_time)          | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| operator\<\<                                 | ![][cpp20]           | ![][notyet]                       |
| from_stream                                  | ![][cpp20]           | ![][notyet]                       |
| from_stream                                  | ![][cpp20]           | ![][notyet]                       |
| from_stream                                  | ![][cpp20]           | ![][notyet]                       |
| from_stream                                  | ![][cpp20]           | ![][notyet]                       |
| from_stream                                  | ![][cpp20]           | ![][notyet]                       |
| from_stream                                  | ![][cpp20]           | ![][notyet]                       |
| from_stream                                  | ![][cpp20]           | ![][notyet]                       |
| parse                                        | ![][cpp20]           | ![][notyet]                       |
| **Literals**                                 |                      |                                   |
| operator""h                                  | ![][cpp14]           | ![][notyet]                       |
| operator""min                                | ![][cpp14]           | ![][notyet]                       |
| operator""s                                  | ![][cpp14]           | ![][notyet]                       |
| operator""ms                                 | ![][cpp14]           | ![][notyet]                       |
| operator""us                                 | ![][cpp14]           | ![][notyet]                       |
| operator""ns                                 | ![][cpp14]           | ![][notyet]                       |
| operator""d                                  | ![][cpp20]           | ![][notyet]                       |
| operator""y                                  | ![][cpp20]           | ![][notyet]                       |


<!--
	C++11: 14	| 0
	C++14: 6	| 0
	C++17: 7	| 0
	C++20: 139	| 0
	C++26: 19	| 0

	Total: 185	| 0-->

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
