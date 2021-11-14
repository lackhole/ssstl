cmake_minimum_required(VERSION 3.17)
project(docs)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(LibXml2 REQUIRED)

include_directories(${CURL_INCLUDE_DIR} ${LIBXML2_INCLUDE_DIR})

add_executable(docs make_doc.cc curlpp.cpp)

target_link_libraries(docs ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES} ss)