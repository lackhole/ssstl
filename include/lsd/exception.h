//
// Created by cosge on 2023-10-29.
//

#ifndef LSD_EXCEPTION_H_
#define LSD_EXCEPTION_H_

#include <cstring>

#include "lsd/string.h"

namespace lsd {

class exception {
  struct ExceptionData {
    char* message = nullptr;
  };

  static void CopyExceptionData(ExceptionData& dst, const ExceptionData& src) {
    if (src.message == nullptr) {
      dst.message = nullptr;
      return;
    }

    const auto len = std::strlen(src.message);
    dst.message = new char[len + 1];
    if (dst.message == nullptr)
      return;

    std::memcpy(dst.message, src.message, sizeof(char) * len);
    dst.message[len] = '\0';
  }

  static void DestroyExceptionData(ExceptionData& data) {
    delete[] data.message;
  }

 public:
  exception() noexcept = default;
  exception(const exception& other) noexcept {
    CopyExceptionData(data_, other.data_);
  }

  virtual ~exception() {
    DestroyExceptionData(data_);
  }

  exception& operator=(const exception& other) noexcept {
    DestroyExceptionData(data_);
    CopyExceptionData(data_, other.data_);

    return *this;
  }

  virtual const char* what() const noexcept {
    return data_.message ? data_.message : "Unknown exception";
  }

 protected:
  explicit exception(const string& what_arg) {
    data_.message = new char[what_arg.size() + 1];
    if (data_.message != nullptr)
      what_arg.copy(data_.message, what_arg.size());
  }

  explicit exception(const char* what_arg) {
    ExceptionData view;
    view.message = const_cast<char*>(what_arg);
    CopyExceptionData(data_, view);
  }

 private:
  ExceptionData data_;
};

} // namespace lsd

#endif // LSD_EXCEPTION_H_
