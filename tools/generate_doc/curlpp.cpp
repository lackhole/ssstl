//
// Created by YongGyu Lee on 2020/12/23.
//

#include "curlpp.hpp"
#include <curl/curl.h>
#include <string>

static int writer(char *data, size_t size, size_t nmemb,
           std::string *writerData)
{
  if(writerData == NULL)
    return 0;

  writerData->append(data, size*nmemb);

  return size * nmemb;
}


/** Impl **/

class Curlpp::Impl {
 public:
  Impl() = default;
  ~Impl();

  bool init();

  bool request(const char* url);

  void copyTo(char *dst, std::uint_fast32_t n = -1) const;

  std::uint_fast32_t bufferSize() const;

 private:

  std::string buffer;
  char errorbuffer[CURL_ERROR_SIZE];
  CURL *conn = NULL;
  CURLcode code;
};

bool Curlpp::Impl::init() {
  curl_global_init(CURL_GLOBAL_DEFAULT);

  conn = curl_easy_init();

  if(conn == NULL) {
    fprintf(stderr, "Failed to create CURL connection\n");
    return false;
  }

  code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorbuffer);
  if(code != CURLE_OK) {
    fprintf(stderr, "Failed to set error buffer [%d]\n", code);
    return false;
  }

  code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
  if(code != CURLE_OK) {
    fprintf(stderr, "Failed to set redirect option [%s]\n", errorbuffer);
    return false;
  }

  code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
  if(code != CURLE_OK) {
    fprintf(stderr, "Failed to set writer [%s]\n", errorbuffer);
    return false;
  }

  code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &buffer);
  if(code != CURLE_OK) {
    fprintf(stderr, "Failed to set write data [%s]\n", errorbuffer);
    return false;
  }

  return true;
}

bool Curlpp::Impl::request(const char *url) {
  if (conn == NULL) {
    fprintf(stderr, "CURL connection is not initialized\n");
    return false;
  }

  code = curl_easy_setopt(conn, CURLOPT_URL, url);
  if(code != CURLE_OK) {
    fprintf(stderr, "Failed to set URL [%s]\n", errorbuffer);
    return false;
  }


  code = curl_easy_perform(conn);
  curl_easy_cleanup(conn);
  conn = NULL;

  if(code != CURLE_OK) {
    fprintf(stderr, "Failed to get '%s' [%s]\n", url, errorbuffer);
    return false;
  }

  return true;
}

Curlpp::Impl::~Impl() {
  if (conn != NULL)
    curl_easy_cleanup(conn);
}

void Curlpp::Impl::copyTo(char *dst, std::uint_fast32_t n) const {
  strncpy(dst, buffer.c_str(), std::min<std::uint_fast32_t>(buffer.size(), n));
}

std::uint_fast32_t Curlpp::Impl::bufferSize() const {
  return buffer.size();
}

/** API **/

Curlpp::Curlpp() {
  pImpl = new Impl();
}
Curlpp::~Curlpp() {
  delete pImpl;
}

bool Curlpp::request(const char *url) {
  return pImpl->request(url);
}
void Curlpp::get(char *buffer, std::uint_fast32_t max_size) const {
  return pImpl->copyTo(buffer, max_size);
}

std::uint_fast32_t Curlpp::bufferSize() const {
  return pImpl->bufferSize();
}
bool Curlpp::init() {
  return pImpl->init();
}
