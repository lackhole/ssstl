## Header `<filesystem>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/filesystem)  
[Implementation](../ss/include/ss/filesystem.h)

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
| path                                         | ![][cpp17]           | ![][notyet]                       |
| filesystem_error                             | ![][cpp17]           | ![][notyet]                       |
| directory_entry                              | ![][cpp17]           | ![][notyet]                       |
| directory_iterator                           | ![][cpp17]           | ![][notyet]                       |
| recursive_directory_iterator                 | ![][cpp17]           | ![][notyet]                       |
| file_status                                  | ![][cpp17]           | ![][notyet]                       |
| space_info                                   | ![][cpp17]           | ![][notyet]                       |
| file_type                                    | ![][cpp17]           | ![][notyet]                       |
| perms                                        | ![][cpp17]           | ![][notyet]                       |
| perm_options                                 | ![][cpp17]           | ![][notyet]                       |
| copy_options                                 | ![][cpp17]           | ![][notyet]                       |
| directory_options                            | ![][cpp17]           | ![][notyet]                       |
| file_time_type                               | ![][cpp17]           | ![][notyet]                       |
| ss::hash\<ss::filesystem::path>              | ![][cpp17]           | ![][notyet]                       |
| **Forward declarations**                     |                      |                                   |
| hash                                         | ![][cpp11]           | ![][notyet]                       |
|                                              |                      |                                   |
| **Functions**                                |                      |                                   |
| ~~u8path~~                                   | ![][cpp17]           | Deprecated in C++20               |
| absolute                                     | ![][cpp17]           | ![][notyet]                       |
| canonical <br/>weakly_canonical              | ![][cpp17]           | ![][notyet]                       |
| relative <br/>proximate                      | ![][cpp17]           | ![][notyet]                       |
| copy                                         | ![][cpp17]           | ![][notyet]                       |
| copy_file                                    | ![][cpp17]           | ![][notyet]                       |
| copy_symlink                                 | ![][cpp17]           | ![][notyet]                       |
| create_directory <br/>create_directories     | ![][cpp17] <br/>![][cpp17] | ![][notyet]                       |
| create_hard_link                             | ![][cpp17]           | ![][notyet]                       |
| create_symlink <br/>create_directory_symlink | ![][cpp17] <br/>![][cpp17] | ![][notyet]                       |
| current_path                                 | ![][cpp17]           | ![][notyet]                       |
| exists                                       | ![][cpp17]           | ![][notyet]                       |
| equivalent                                   | ![][cpp17]           | ![][notyet]                       |
| file_size                                    | ![][cpp17]           | ![][notyet]                       |
| hard_link_count                              | ![][cpp17]           | ![][notyet]                       |
| last_write_time                              | ![][cpp17]           | ![][notyet]                       |
| permissions                                  | ![][cpp17]           | ![][notyet]                       |
| read_symlink                                 | ![][cpp17]           | ![][notyet]                       |
| remove <br/>remove_all                       | ![][cpp17] <br/>![][cpp17] | ![][notyet]                       |
| rename                                       | ![][cpp17]           | ![][notyet]                       |
| resize_file                                  | ![][cpp17]           | ![][notyet]                       |
| space                                        | ![][cpp17]           | ![][notyet]                       |
| status <br/>symlink_status                   | ![][cpp17] <br/>![][cpp17] | ![][notyet]                       |
| temp_directory_path                          | ![][cpp17]           | ![][notyet]                       |
| **File types**                               |                      |                                   |
| is_block_file                                | ![][cpp17]           | ![][notyet]                       |
| is_character_file                            | ![][cpp17]           | ![][notyet]                       |
| is_directory                                 | ![][cpp17]           | ![][notyet]                       |
| is_empty                                     | ![][cpp17]           | ![][notyet]                       |
| is_fifo                                      | ![][cpp17]           | ![][notyet]                       |
| is_other                                     | ![][cpp17]           | ![][notyet]                       |
| is_regular_file                              | ![][cpp17]           | ![][notyet]                       |
| is_socket                                    | ![][cpp17]           | ![][notyet]                       |
| is_symlink                                   | ![][cpp17]           | ![][notyet]                       |
| status_known                                 | ![][cpp17]           | ![][notyet]                       |


<!--
	C++11: 1	| 0
	C++17: 43	| 0
	C++20: 1	| 0

	Total: 45	| 0-->

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
