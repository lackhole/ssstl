//
// Created by YongGyu Lee on 2020/12/23.
//

#ifndef CURLPP_H_
#define CURLPP_H_

#include <cstdint>

class Curlpp {
 public:
  Curlpp();
  ~Curlpp();

  bool init();

  bool request(const char* url);

  void get(char* buffer, std::uint_fast32_t max_size) const;

  std::uint_fast32_t bufferSize() const;

 private:
  class Impl;
  Impl* pImpl;
};

#endif // CURLPP_H_
