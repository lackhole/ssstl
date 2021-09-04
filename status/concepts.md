## Header `<algorithm>` implementation status

[Reference](https://en.cppreference.com/w/cpp/header/concepts)  
[Implementation](../ss/include/ss/concepts.h)

* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL
* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N
* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N
* ![][notyet]: Not yet implemented


| C++ 20 Features                  | Implemented in          |
|----------------------------------|:-----------------------:|
| **Concepts**                     |                         |
| **Core language concepts**       |                         |
|same_as                           | ![][cpp20]              |
|derived_from                      | ![][cpp20]              |
|convertible_to                    | ![][notyet]             |
|common_reference_with             | ![][notyet]             |
|common_with                       | ![][notyet]             |
|integral                          | ![][notyet]             |
|signed_integral                   | ![][notyet]             |
|unsigned_integral                 | ![][notyet]             |
|floating_point                    | ![][notyet]             |
|assignable_from                   | ![][notyet]             |
|swappable                         | ![][notyet]             |
|swappable_with                    | ![][notyet]             |
|destructible                      | ![][notyet]             |
|constructible_from                | ![][notyet]             |
|default_initializable             | ![][notyet]             |
|move_constructible                | ![][notyet]             |
|copy_constructible                | ![][notyet]             |
| **Comparison concepts**          |                         |                    
|equality_comparable               | ![][notyet]             |                    
|equality_comparable_with          | ![][notyet]             |                        
|totally_ordered                   | ![][notyet]             |                
|totally_ordered_with              | ![][notyet]             |                    
| **Object concepts**              |                         |                
|movable                           | ![][notyet]             |        
|copyable                          | ![][notyet]             |        
|semiregular                       | ![][notyet]             |            
|regular                           | ![][notyet]             |        
| **Callable concepts**            |                         |                
|invocable                         | ![][notyet]             |        
|regular_invocable                 | ![][notyet]             |                
|predicate                         | ![][notyet]             |        
|relation                          | ![][notyet]             |        
|equivalence_relation              | ![][notyet]             |                    
|strict_weak_order                 | ![][notyet]             |                
|                                  |                         |                            
| **Customization point objects**  |                         |                            
|ranges::swap                      | ![][notyet]             |    


[notyet]: https://img.shields.io/badge/Not_yet-orange
[removed]: https://img.shields.io/badge/Removed-red

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
