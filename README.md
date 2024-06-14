<div align="center">
  
# SSSTL
SS Standard Template Library  
Focusing on implementing high C++ features for low C++(i.e. You can use `ss::optional<T>` in C++11)  
*Note: This is personal project*

# Build Status
[![g++](https://github.com/lackhole/ssstl/actions/workflows/gcc.yml/badge.svg)](https://github.com/lackhole/ssstl/actions/workflows/gcc.yml)
[![clang++](https://github.com/lackhole/ssstl/actions/workflows/clang.yml/badge.svg)](https://github.com/lackhole/ssstl/actions/workflows/clang.yml)
[![MSVC](https://github.com/lackhole/ssstl/actions/workflows/msvc.yml/badge.svg)](https://github.com/lackhole/ssstl/actions/workflows/msvc.yml)
[![Emscripten](https://github.com/lackhole/ssstl/actions/workflows/emscripten.yml/badge.svg)](https://github.com/lackhole/ssstl/actions/workflows/emscripten.yml)
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
* ![](https://img.shields.io/badge/C++X-100%25-brightgreen): Implemented features of `C++ X` using `C++ Y`(`Y <= X`).
* ![](https://img.shields.io/badge/C++N-X%25-green)
  ![](https://img.shields.io/badge/C++N-X%25-yellowgreen)
  ![](https://img.shields.io/badge/C++N-X%25-yellow)
  ![](https://img.shields.io/badge/C++N-X%25-orange)
  ![](https://img.shields.io/badge/C++N-X%25-red): 
  Implementation in progress.

| Concepts library                              | Feature status      | Notes            |
|-----------------------------------------------|---------------------|------------------|
| [concepts](status/concepts.md)                | ![][cpp20]![][p007] |                  |

| Coroutines library                            | Feature status                                                        | Notes            |
|-----------------------------------------------|-----------------------------------------------------------------------|------------------|
| coroutine                                     | ![][cpp20]![][p000]                                                         |                  |

| Utilities library                              | Feature status                                                                                      | Notes |
|------------------------------------------------|-----------------------------------------------------------------------------------------------------|-------|
| [typeinfo](status/typeinfo.md)                 | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000]                     |       |
| [typeindex](status/typeindex.md)               | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000]                     |       |
| [type_traits](status/type_traits.md)           | ![][cpp11]![][p100] ![][cpp14]![][p100] ![][cpp17]![][p100] ![][cpp20]![][p064]                     |       |
| [bitset](status/bitset.md)                     | ![][cpp11]![][p075]                                                                                 |       |
| [functional](status/functional.md)             | ![][cpp11]![][p066] ![][cpp14]![][p100] ![][cpp17]![][p020] ![][cpp20]![][p000] ![][cpp23]![][p100] |       |
| [utility](status/utility.md)                   | ![][cpp11]![][p100] ![][cpp14]![][p100] ![][cpp17]![][p100] ![][cpp20]![][p096]                     |       |
| [chrono](status/chrono.md)                     | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000]                     |       |
| [initializer_list](status/initializer_list.md) | ![][cpp11]![][p100]                                                                                 |       |
| [tuple](status/tuple.md)                       | ![][cpp11]![][p075] ![][cpp14]![][p100] ![][cpp17]![][p100] ![][cpp20]![][p000]                     |       |
| [any](status/any.md)                           | ![][cpp17]![][p000] ![][cpp20]![][p000]                                                             |       |
| [optional](status/optional.md)                 | ![][cpp17]![][p100] ![][cpp20]![][p000]                                                             |       |
| [variant](status/variant.md)                   | ![][cpp17]![][p000] ![][cpp20]![][p000]                                                             |       |
| [compare](status/compare.md)                   | ![][unknown_]                                                                                       |       |
| [version](status/version.md)                   | ![][unknown_]                                                                                       |       |
| [source_location](status/source_location.md)   | ![][impossib]                                                                                       |       |
| [stacktrace](status/stacktrace.md)             | ![][impossib]                                                                                       |       |
| [stacktrace](status/stacktrace.md)             | ![][impossib]                                                                                       |       |


| Dynamic memory management                      | Feature status                                                        | Notes            |
|------------------------------------------------|-----------------------------------------------------------------------|------------------|
| [new](status/new.md)                           | ![][unknown_]                                                         |                  |
| [memory](status/memory.md)                     | ![][cpp11024] ![][cpp14]![][p100] ![][cpp17]![][p000] ![][cpp20]![][p000] ![][cpp23033] |                  |
| [scoped_allocator](status/scoped_allocator.md) | ![][unknown_]                                                         |                  |
| [memory_resource](status/memory_resource.md)   | ![][unknown_]                                                         |                  |


| Numeric limits             | Feature status                                                        | Notes            |
|----------------------------|-----------------------------------------------------------------------|------------------|
| [limits](status/limits.md) | ![][unknown_]                                                         |                  |

| Error handling                         | Feature status      | Notes            |
|----------------------------------------|---------------------|------------------|
| [exception](status/exception.md)       | ![][cpp11]![][p007] |                  |
| [stdexcept](status/stdexcept.md)       | ![][cpp11]![][p100] |                  |
| [system_error](status/system_error.md) | ![][unknown_]       |                  |
| [cerrno](status/cerrno.md)             | ![][unknown_]       |                  |

| Strings library                      | Feature status                                                                  | Notes |
|--------------------------------------|---------------------------------------------------------------------------------|-------|
| [string](status/string.md)           | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [string_view](status/string_view.md) | ![][cpp17]![][p000] ![][cpp20]![][p000]                                         |       |
| [charconv](status/charconv.md)       | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [format](status/format.md)           | ![][cpp20]![][p000]                                                             |       |

| Containers library                       | Feature status                                                                  | Notes |
|------------------------------------------|---------------------------------------------------------------------------------|-------|
| [array](status/array.md)                 | ![][cpp11]![][p100] ![][cpp14]![][p100] ![][cpp17]![][p100] ![][cpp20]![][p050] |       |
| [vector](status/vector.md)               | ![][cpp11]![][p017] ![][cpp20]![][p000]                                         |       |
| [deque](status/deque.md)                 | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [list](status/list.md)                   | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [forward_list](status/forward_list.md)   | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [set](status/set.md)                     | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [map](status/map.md)                     | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [unordered_set](status/unordered_set.md) | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [unordered_map](status/unordered_map.md) | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [stack](status/stack.md)                 | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [queue](status/queue.md)                 | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [span](status/span.md)                   | ![][cpp20]![][p000]                                                             |       |

| Iterators library              | Feature status                                                                  | Notes |
|--------------------------------|---------------------------------------------------------------------------------|-------|
| [iterator](status/iterator.md) | ![][cpp11]![][p038] ![][cpp14]![][p100] ![][cpp17]![][p100] ![][cpp20]![][p006] |       |

| Ranges library                                | Feature status                                                        | Notes            |
|-----------------------------------------------|-----------------------------------------------------------------------|------------------|
| [ranges](status/ranges.md)                    | ![][cpp20]![][p000]                                                         |                  |

| Algorithms library               | Feature status                                              | Notes |
|----------------------------------|-------------------------------------------------------------|-------|
| [algorithm](status/algorithm.md) | ![][cpp11]![][p015] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [execution](status/execution.md) | ![][unknown_]                                               |       |

| Numerics library               | Feature status                                                                  | Notes |
|--------------------------------|---------------------------------------------------------------------------------|-------|
| [complex](status/complex.md)   | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [valarray](status/valarray.md) | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [random](status/random.md)     | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [numeric](status/numeric.md)   | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [ratio](status/ratio.md)       | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |
| [bit](status/bit.md)           | ![][unknown_]                                                                   |       |
| [numbers](status/numbers.md)   | ![][cpp20]![][p000]                                                             |       |

| Localization library         | Feature status                                                        | Notes            |
|------------------------------|-----------------------------------------------------------------------|------------------|
| [locale](status/locale.md)   | ![][unknown_]                                                         |                  |
| [codecvt](status/codecvt.md) | ![][deprecat]                                                         |                  |

| Input/Output library               | Feature status                                                        | Notes            |
|------------------------------------|-----------------------------------------------------------------------|------------------|
| [iosfwd](status/iosfwd.md)         | ![][unknown_]                                                         |                  |
| [ios](status/ios.md)               | ![][unknown_]                                                         |                  |
| [istream](status/istream.md)       | ![][unknown_]                                                         |                  |
| [ostream](status/ostream.md)       | ![][unknown_]                                                         |                  |
| [iostream](status/iostream.md)     | ![][unknown_]                                                         |                  |
| [fstream](status/fstream.md)       | ![][unknown_]                                                         |                  |
| [sstream](status/sstream.md)       | ![][unknown_]                                                         |                  |
| [syncstream](status/syncstream.md) | ![][unknown_]                                                         |                  |
| [spanstream](status/spanstream.md) | ![][unknown_]                                                         |                  |
| [strstream](status/strstream.md)   | ![][deprecat]                                                         |                  |
| [iomanip](status/iomanip.md)       | ![][unknown_]                                                         |                  |
| [streambuf](status/streambuf.md)   | ![][unknown_]                                                         |                  |

| Filesystem library                 | Feature status                                                        | Notes            |
|------------------------------------|-----------------------------------------------------------------------|------------------|
| [filesystem](status/filesystem.md) | ![][impossib]                                                         |                  |

| Regular Expression library | Feature status                                                                  | Notes |
|----------------------------|---------------------------------------------------------------------------------|-------|
| [regex](status/regex.md)   | ![][cpp11]![][p000] ![][cpp14]![][p000] ![][cpp17]![][p000] ![][cpp20]![][p000] |       |

| Atomic Operations library  | Feature status                                                        | Notes            |
|----------------------------|-----------------------------------------------------------------------|------------------|
| [atomic](status/atomic.md) |  ![][unknown_]                                                        |                  |

| Thread support library                             | Feature status                                                        | Notes            |
|----------------------------------------------------|-----------------------------------------------------------------------|------------------|
| [thread](status/thread.md)                         |  ![][unknown_]                                                        |                  |
| [stop_token](status/stop_token.md)                 |  ![][unknown_]                                                        |                  |
| [mutex](status/mutex.md)                           |  ![][unknown_]                                                        |                  |
| [shared_mutex](status/shared_mutex.md)             |  ![][unknown_]                                                        |                  |
| [future](status/future.md)                         |  ![][unknown_]                                                        |                  |
| [condition_variable](status/condition_variable.md) |  ![][unknown_]                                                        |                  |
| [semaphore](status/semaphore.md)                   |  ![][unknown_]                                                        |                  |
| [latch](status/latch.md)                           |  ![][unknown_]                                                        |                  |
| [barrier](status/barrier.md)                       |  ![][unknown_]                                                        |                  |


[impossib]: https://img.shields.io/badge/not_possible-grey
[unknown_]: https://img.shields.io/badge/unknown-grey
[deprecat]: https://img.shields.io/badge/deprecated-grey

[legacy]: https://img.shields.io/badge/legacy-555555
[cpp11]: https://img.shields.io/badge/C++11-555555
[cpp14]: https://img.shields.io/badge/C++14-555555
[cpp17]: https://img.shields.io/badge/C++17-555555
[cpp20]: https://img.shields.io/badge/C++20-555555
[cpp23]: https://img.shields.io/badge/C++23-555555
[cpp26]: https://img.shields.io/badge/C++26-555555

[p000]: https://img.shields.io/badge/0%25-red
[p001]: https://img.shields.io/badge/1%25-orange
[p002]: https://img.shields.io/badge/2%25-orange
[p003]: https://img.shields.io/badge/3%25-orange
[p004]: https://img.shields.io/badge/4%25-orange
[p005]: https://img.shields.io/badge/5%25-orange
[p006]: https://img.shields.io/badge/6%25-orange
[p007]: https://img.shields.io/badge/7%25-orange
[p008]: https://img.shields.io/badge/8%25-orange
[p009]: https://img.shields.io/badge/9%25-orange
[p010]: https://img.shields.io/badge/10%25-orange
[p011]: https://img.shields.io/badge/11%25-orange
[p012]: https://img.shields.io/badge/12%25-orange
[p013]: https://img.shields.io/badge/13%25-orange
[p014]: https://img.shields.io/badge/14%25-orange
[p015]: https://img.shields.io/badge/15%25-orange
[p016]: https://img.shields.io/badge/16%25-orange
[p017]: https://img.shields.io/badge/17%25-orange
[p018]: https://img.shields.io/badge/18%25-orange
[p019]: https://img.shields.io/badge/19%25-orange
[p020]: https://img.shields.io/badge/20%25-orange
[p021]: https://img.shields.io/badge/21%25-orange
[p022]: https://img.shields.io/badge/22%25-orange
[p023]: https://img.shields.io/badge/23%25-orange
[p024]: https://img.shields.io/badge/24%25-orange
[p025]: https://img.shields.io/badge/25%25-yellow
[p026]: https://img.shields.io/badge/26%25-yellow
[p027]: https://img.shields.io/badge/27%25-yellow
[p028]: https://img.shields.io/badge/28%25-yellow
[p029]: https://img.shields.io/badge/29%25-yellow
[p030]: https://img.shields.io/badge/30%25-yellow
[p031]: https://img.shields.io/badge/31%25-yellow
[p032]: https://img.shields.io/badge/32%25-yellow
[p033]: https://img.shields.io/badge/33%25-yellow
[p034]: https://img.shields.io/badge/34%25-yellow
[p035]: https://img.shields.io/badge/35%25-yellow
[p036]: https://img.shields.io/badge/36%25-yellow
[p037]: https://img.shields.io/badge/37%25-yellow
[p038]: https://img.shields.io/badge/38%25-yellow
[p039]: https://img.shields.io/badge/39%25-yellow
[p040]: https://img.shields.io/badge/40%25-yellow
[p041]: https://img.shields.io/badge/41%25-yellow
[p042]: https://img.shields.io/badge/42%25-yellow
[p043]: https://img.shields.io/badge/43%25-yellow
[p044]: https://img.shields.io/badge/44%25-yellow
[p045]: https://img.shields.io/badge/45%25-yellow
[p046]: https://img.shields.io/badge/46%25-yellow
[p047]: https://img.shields.io/badge/47%25-yellow
[p048]: https://img.shields.io/badge/48%25-yellow
[p049]: https://img.shields.io/badge/49%25-yellow
[p050]: https://img.shields.io/badge/50%25-yellowgreen
[p051]: https://img.shields.io/badge/51%25-yellowgreen
[p052]: https://img.shields.io/badge/52%25-yellowgreen
[p053]: https://img.shields.io/badge/53%25-yellowgreen
[p054]: https://img.shields.io/badge/54%25-yellowgreen
[p055]: https://img.shields.io/badge/55%25-yellowgreen
[p056]: https://img.shields.io/badge/56%25-yellowgreen
[p057]: https://img.shields.io/badge/57%25-yellowgreen
[p058]: https://img.shields.io/badge/58%25-yellowgreen
[p059]: https://img.shields.io/badge/59%25-yellowgreen
[p060]: https://img.shields.io/badge/60%25-yellowgreen
[p061]: https://img.shields.io/badge/61%25-yellowgreen
[p062]: https://img.shields.io/badge/62%25-yellowgreen
[p063]: https://img.shields.io/badge/63%25-yellowgreen
[p064]: https://img.shields.io/badge/64%25-yellowgreen
[p065]: https://img.shields.io/badge/65%25-yellowgreen
[p066]: https://img.shields.io/badge/66%25-yellowgreen
[p067]: https://img.shields.io/badge/67%25-yellowgreen
[p068]: https://img.shields.io/badge/68%25-yellowgreen
[p069]: https://img.shields.io/badge/69%25-yellowgreen
[p070]: https://img.shields.io/badge/70%25-yellowgreen
[p071]: https://img.shields.io/badge/71%25-yellowgreen
[p072]: https://img.shields.io/badge/72%25-yellowgreen
[p073]: https://img.shields.io/badge/73%25-yellowgreen
[p074]: https://img.shields.io/badge/74%25-yellowgreen
[p075]: https://img.shields.io/badge/75%25-green
[p076]: https://img.shields.io/badge/76%25-green
[p077]: https://img.shields.io/badge/77%25-green
[p078]: https://img.shields.io/badge/78%25-green
[p079]: https://img.shields.io/badge/79%25-green
[p080]: https://img.shields.io/badge/80%25-green
[p081]: https://img.shields.io/badge/81%25-green
[p082]: https://img.shields.io/badge/82%25-green
[p083]: https://img.shields.io/badge/83%25-green
[p084]: https://img.shields.io/badge/84%25-green
[p085]: https://img.shields.io/badge/85%25-green
[p086]: https://img.shields.io/badge/86%25-green
[p087]: https://img.shields.io/badge/87%25-green
[p088]: https://img.shields.io/badge/88%25-green
[p089]: https://img.shields.io/badge/89%25-green
[p090]: https://img.shields.io/badge/90%25-green
[p091]: https://img.shields.io/badge/91%25-green
[p092]: https://img.shields.io/badge/92%25-green
[p093]: https://img.shields.io/badge/93%25-green
[p094]: https://img.shields.io/badge/94%25-green
[p095]: https://img.shields.io/badge/95%25-green
[p096]: https://img.shields.io/badge/96%25-green
[p097]: https://img.shields.io/badge/97%25-green
[p098]: https://img.shields.io/badge/98%25-green
[p099]: https://img.shields.io/badge/99%25-green
[p100]: https://img.shields.io/badge/100%25-brightgreen
