//
// Created by YongGyu Lee on 2021/11/13.
//

#include <cmath>

#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <filesystem>
#include <numeric>

#include "ss/optional.h"
#include "ss/type_traits.h"
#include "ss/utility.h"

#include "libxml2/libxml/HTMLparser.h"
#include "libxml2/libxml/xpath.h"

#include "curlpp.hpp"

#define CHAIN_1(a) a
#define CHAIN_2(a,b) CHAIN_1(a) && a->b
#define CHAIN_3(a,b,c) CHAIN_2(a,b) && a->b->c
#define CHAIN_4(a,b,c,d) CHAIN_3(a,b,c) && a->b->c->d
#define CHAIN_5(a,b,c,d,e) CHAIN_4(a,b,c,d) && a->b->c->d->e
#define CHAIN_6(a,b,c,d,e,f) CHAIN_5(a,b,c,d,e) && a->b->c->d->e->f
#define CHAIN_7(a,b,c,d,e,f,g) CHAIN_6(a,b,c,d,e,f) && a->b->c->d->e->f->g
#define CHAIN_8(a,b,c,d,e,f,g,h) CHAIN_7(a,b,c,d,e,f,g) && a->b->c->d->e->f->g->h
#define CHAIN_9(a,b,c,d,e,f,g,h,i) CHAIN_8(a,b,c,d,e,f,g,h) && a->b->c->d->e->f->g->h->i

#define CHAIN_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,N,...) CHAIN_##N

#define IF_CHAIN(...) if (CHAIN_N(__VA_ARGS__,9,8,7,6,5,4,3,2,1)(__VA_ARGS__))

template<typename T>
class span {
 public:
  constexpr span(T* ptr, size_t n) : ptr(ptr), n(n) {}

  LSD_NODISCARD constexpr T* begin() { return ptr; }
  LSD_NODISCARD constexpr const T* begin() const { return ptr; }
  LSD_NODISCARD constexpr const T* cbegin() const { return ptr; }

  LSD_NODISCARD constexpr T* end() { return ptr + n; }
  LSD_NODISCARD constexpr const T* end() const { return ptr + n; }
  LSD_NODISCARD constexpr const T* cend() const { return ptr + n; }

  LSD_NODISCARD constexpr size_t size() const { return n; }

  LSD_NODISCARD constexpr bool empty() const { return ptr == nullptr || n == 0; }

  LSD_NODISCARD constexpr explicit operator bool() const { return ptr != nullptr && n != 0; }

  LSD_NODISCARD constexpr T& operator[](size_t i) { return ptr[i]; }
  LSD_NODISCARD constexpr const T& operator[](size_t i) const { return ptr[i]; }

 private:
  T* ptr;
  size_t n;
};

template<typename T>
span(T*, size_t) -> span<T>;

using xstring = std::basic_string<xmlChar>;

const xmlChar* operator""_xstr(const char* s, size_t n) {
  return reinterpret_cast<const xmlChar*>(s);
}

// NOTE: this returns unique_ptr. Aware of temporary.
std::unique_ptr<xmlXPathObject, decltype(&xmlXPathFreeObject)>
xpathSearch(xmlDocPtr doc, const xmlChar *xpath){

  xmlXPathContextPtr context;
  xmlXPathObjectPtr result;

  context = xmlXPathNewContext(doc);
  if (context == NULL) {
    fprintf(stderr, "Error in xmlXPathNewContext\n");
    return {nullptr, xmlXPathFreeObject};
  }
  result = xmlXPathEvalExpression(xpath, context);
  xmlXPathFreeContext(context);
  if (result == NULL) {
    fprintf(stderr, "Error in xmlXPathEvalExpression\n");
    return {nullptr, xmlXPathFreeObject};
  }
  if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
    xmlXPathFreeObject(result);
    return {nullptr, xmlXPathFreeObject};
  }
  return {result, xmlXPathFreeObject};
}

auto xpathSearch(xmlDocPtr doc, const std::string& xpath) {
  return xpathSearch(doc, reinterpret_cast<const xmlChar *>(xpath.c_str()));
}

auto xpathSearch(xmlNodePtr doc, const std::string& xpath) {
  return xpathSearch(reinterpret_cast<xmlDocPtr>(doc), reinterpret_cast<const xmlChar *>(xpath.c_str()));
}

void xmlErrorHandler(void *ctx, const char* msg, ...){
  std::cerr << "XML Error: " << ctx << " : " << msg << '\n';
}

xstring PrettyString(const xmlChar* str) {
  xstring result;

  // TODO: optimize
  for (const auto c : span(str, xmlStrlen(str))) {
    switch (c) {
      case '\n':
      case '\t':
      break;

      case (xmlChar)' ':
        if (!result.empty() && result.back() != (xmlChar)' ')
          result += c;
        break;

      default:
        result += c;
    }
  }

  while (!result.empty() && result.back() == (xmlChar)' ')
    result.pop_back();

  return result;
}

auto make_span(xmlXPathObjectPtr obj) {
  return span(obj->nodesetval->nodeTab, obj->nodesetval->nodeNr);
}

enum Version {
  kVersionMixed = -1,
  kVersionUnknown = -2,
  kVersion98 = 98,
  kVersionLegacy = kVersion98,
  kVersion11 = 11,
  kVersion14 = 14,
  kVersion17 = 17,
  kVersion20 = 20,
  kVersion23 = 23,
};

enum MarkType {
  kMarkVersion,
  kMarkDeprecated,
  kMarkRemoved,
};

lsd::optional<std::string> GetPage(const char* url) {
  std::string response;

  Curlpp curlpp;
  std::clog << "Requesting " << url << "..." << std::endl;
  if (!curlpp.init() || !curlpp.request(url))
    return {};

  std::clog << "Got " << curlpp.bufferSize() << "bytes" << std::endl;

  response.resize(curlpp.bufferSize());
  curlpp.get(const_cast<char *>(response.data()), response.size());

  if (response.empty())
    return {};
  return response;
}

std::unordered_map<const xmlChar*, xmlChar*>
getAttributes(xmlNodePtr node) {
  std::unordered_map<const xmlChar*, xmlChar*> attributes;
  for (auto attr = node->properties; attr; attr = attr->next) {
    const auto name = attr->name;
    xmlChar* value = nullptr;

    IF_CHAIN(attr, children, content) {
      value = attr->children->content;
    }

    attributes.emplace(name, value);
  }

  return attributes;
}

enum TRType {
  kTypeCategory,
  kTypeFeature,
  kTypeAdditionalDesc,
  kTypeUnknown,
};

TRType GetTRType(xmlNodePtr node) {
  const auto attributes = getAttributes(node);
  if (attributes.empty())
    return kTypeCategory;

  for (const auto attr : attributes) {
    if (xmlUTF8Charcmp(attr.first, (const xmlChar*)"class") == 0) {
      if (xmlUTF8Charcmp(attr.second, (const xmlChar*)"t-dsc") == 0) {
        if (xmlUTF8Charcmp(attr.second + 5, (const xmlChar*)"-header") == 0)
          return kTypeAdditionalDesc;
        return kTypeFeature;
      }
    }
  }

  return kTypeUnknown;
}

struct Feature {
  std::vector<lsd::pair<xmlChar, xstring>> category;
  int order = 0;

  std::vector<xstring> names;
  std::string description;

  std::vector<lsd::optional<lsd::pair<MarkType, int>>> t_mark;
//  int first_version = kVersionLegacy;
//  std::vector<lsd::optional<int>> deprecated_after;
//  std::vector<lsd::optional<int>> removed_after;

  lsd::optional<xstring> additional_description;
};

int ExtractCppVersion(const xmlChar* str) {
  const auto pos = xmlStrstr(str, "C++"_xstr);
  const auto len = xmlStrlen(str);

  if (pos == nullptr || len < 5)
    return kVersionUnknown;


  xstring num_str(pos + 3, pos + 5);
  const auto version = xmlXPathCastStringToNumber(num_str.data());
  if (std::isnan(version)) {
    std::cerr << "Failed to decode C++ version: " << str << '\n';
  }

  return static_cast<int>(std::lround(version + 0.1));
}

xstring replace_xstring(const xstring& str, const std::string& e, const std::string& fmt) {
  std::string temp(str.begin(), str.end());
  // TODO: Optimize
  temp = std::regex_replace(temp, std::regex(e), fmt);
  return {temp.begin(), temp.end()};
}

std::vector<xstring> GetFeatureName(xmlNodePtr node) {
  static constexpr const auto xpath =
      "//span[@class='t-lines']//span[not(@class)]/text()";

  const auto text = xpathSearch(node, xpath);
  const auto span = make_span(text.get());

  if (xmlStrcmp(span[0]->content, "std::swap"_xstr) == 0)
    bool debug = true;

  std::vector<xstring> result;
  result.reserve(span.size());
  xstring temp;

  for (const auto item : span) {
    temp = item->content;
    IF_CHAIN(item, next, children, content) {
      temp += item->next->children->content;
    }
    result.emplace_back(replace_xstring(temp, "std::", "lsd::"));
  }

  return result;
}

int GetVersion(xmlNodePtr node) {
  static constexpr const auto xpath =
    "//div[@class='t-dsc-member-div']//span[contains(@class,'t-since-cxx')]/text()";

  const auto text = xpathSearch(node, xpath);
  if (!text)
    return kVersionLegacy; // ?

  const auto str = make_span(text.get())[0]->content;
  return ExtractCppVersion(str);
}

std::vector<lsd::optional<int>> GetDeprecatedVersion(xmlNodePtr node) {
  static constexpr const auto xpath1 =
    "//div[@class='t-dsc-member-div']//span[@class='t-lines']";
  static constexpr const auto xpath2 =
    "//span[@class='t-mark']/text()";

  std::vector<lsd::optional<int>> result;
  const auto lists = xpathSearch(node, xpath1);

  for (const auto& s : make_span(lists.get())) {
    const auto text = xpathSearch(s, xpath2);
    if (!text) {
      result.emplace_back(lsd::nullopt);
    } else {
      const auto str = make_span(text.get())[0]->content;
      result.emplace_back(ExtractCppVersion(str));
    }
  }

  return result;
}

std::vector<lsd::optional<int>> GetRemovedVersion(xmlNodePtr node) {
  static constexpr const auto xpath1 =
    "//div[@class='t-dsc-member-div']//span[@class='t-lines']";
  static constexpr const auto xpath2 =
    "//span[contains(@class,'t-until-cxx')]/text()";

  std::vector<lsd::optional<int>> result;
  const auto lists = xpathSearch(node, xpath1);

  for (const auto& s : make_span(lists.get())) {
    const auto text = xpathSearch(s, xpath2);
    if (!text) {
      result.emplace_back(lsd::nullopt);
    } else {
      const auto str = make_span(text.get())[0]->content;
      result.emplace_back(ExtractCppVersion(str));
    }
  }

  return result;
}

std::vector<lsd::optional<lsd::pair<MarkType, int>>> GetMarks(xmlNodePtr node, bool multiple) {
  static constexpr const auto xpath1 =
    "/div/span[@class='t-lines']/span";

  static constexpr const auto xpath_version = "//span[contains(@class,'t-since-cxx')]/text()";
  static constexpr const auto xpath_deprecated = "//span[@class='t-mark' or contains(@class, 't-deprecated-')]/text()";
  static constexpr const auto xpath_removed = "//span[contains(@class,'t-until-cxx')]/text()";

  std::vector<lsd::optional<lsd::pair<MarkType, int>>> result;

  if (multiple) {
    const auto spans = xpathSearch(node, xpath1);
    if (!spans)
      return {lsd::make_pair(kMarkVersion, kVersionLegacy)};

    //FIXME: attach marks to each names
    for (const auto& s: make_span(spans.get())) {
      bool all_no = true;
      if (const auto removed = xpathSearch(s, xpath_removed)) {
        const auto str = make_span(removed.get())[0]->content;
        result.emplace_back(lsd::in_place,kMarkRemoved, ExtractCppVersion(str));
        all_no = false;
      } else if (const auto deprecated = xpathSearch(s, xpath_deprecated)) {
        const auto str = make_span(deprecated.get())[0]->content;
        if (const auto version = ExtractCppVersion(str); version != kVersionUnknown)
          result.emplace_back(lsd::in_place,kMarkDeprecated, ExtractCppVersion(str));
        all_no = false;
      } else if (const auto versions = xpathSearch(s, xpath_version)) {
        const auto str = make_span(versions.get())[0]->content;
        result.emplace_back(lsd::in_place, kMarkVersion, ExtractCppVersion(str));
      } else {
        result.emplace_back(lsd::in_place, kMarkVersion, kVersionLegacy);
      }
    }
  } else {
    if (const auto version = xpathSearch(node, xpath_version); version) {
      const auto str = make_span(version.get())[0]->content;
      result.emplace_back(lsd::in_place, kMarkVersion, ExtractCppVersion(str));
    }

    if (const auto deprecated = xpathSearch(node, xpath_deprecated); deprecated) {
      const auto str = make_span(deprecated.get())[0]->content;
      if (const auto version = ExtractCppVersion(str); version != kVersionUnknown)
        result.emplace_back(lsd::in_place, kMarkDeprecated, ExtractCppVersion(str));
    }
    if (const auto removed = xpathSearch(node, xpath_removed); removed) {
      const auto str = make_span(removed.get())[0]->content;
      result.emplace_back(lsd::in_place, kMarkRemoved, ExtractCppVersion(str));
    }
  }

  return result;
}

std::vector<Feature> GetFeatures(const xmlChar* page, const char* encoding) {
  std::vector<Feature> result;
  std::vector<lsd::pair<xmlChar, xstring>> categories;
  xstring additional_desc;
  Feature feature;
  int order = 0;

  // parse string
  xmlSetGenericErrorFunc(NULL, xmlErrorHandler);

  using document_type = std::unique_ptr<lsd::remove_pointer_t<htmlDocPtr>, void(*)(htmlDocPtr)>;
  document_type doc = {htmlParseDoc(page, encoding), [](htmlDocPtr ptr) {
    xmlFreeDoc(ptr);
    xmlCleanupParser();
  }};


  if (!doc) {
    std::cerr << "Error while parsing html\n";
    return {};
  }

  auto trs = xpathSearch(doc.get(), "//table[@class='t-dsc-begin']/tr");
  for (auto node : make_span(trs.get())) {
    switch (GetTRType(node)) {
      case kTypeCategory: {
        const auto text = xpathSearch(node, "//span[@class='mw-headline']/text()");
        const auto span = make_span(text.get());
        const auto category = PrettyString(span[0]->content);
        const auto header = span[0]->parent->parent->name;
        const auto rank = header[1];

        while (!categories.empty() && rank <= categories.back().first)
          categories.pop_back();
        categories.emplace_back(rank, category);
        break;
      }

      case kTypeAdditionalDesc: {
        const auto text = xpathSearch(node, "//div//text()");
        additional_desc.clear();
        for (const auto node2 : make_span(text.get())) {
          additional_desc += node2->content;
        }
        feature.additional_description = replace_xstring(PrettyString(additional_desc.data()), "std::", "lsd::");
        break;
      }

      case kTypeFeature: {
        const auto member = xpathSearch(node, "//div[@class='t-dsc-member-div']");
        if (!member) {
          feature = Feature();
          std::cerr << "Failed to decode xpath " << __FILE__ << ", line " << __LINE__ << std::endl;
          break;
        }
        feature.names = GetFeatureName(make_span(member.get())[0]);

//        if (xmlStrstr(feature.names[0].data(), "atomic_is_lock_free"_xstr) != nullptr)
//          bool stop = true;

        feature.t_mark = GetMarks(make_span(member.get())[0], feature.names.size() > 1);
        feature.category = categories;
        feature.order = order++;

        result.emplace_back(lsd::move(feature));
        feature = Feature();
        break;
      }

      default:
        std::cerr << "Unknown type\n";
        std::terminate();
    }
  }

  return result;
}

enum DocumentType {
  kDocumentTypeDefault,
  kDocumentTypeAlignedVersion,
};

std::string CreateDocumentHeader(const std::string& title) {
  std::string header =
    "## Header `<" + title + ">` implementation status\n"
    "\n"
    "[Reference](https://en.cppreference.com/w/cpp/header/" + title + ")  \n"
    "[Implementation](../ss/include/ss/" + title + ".h)\n"
    "\n"
    "* ![](https://img.shields.io/badge/C%2B%2B-N-red): Cannot implement with language itself. Need compiler support. Used C++ N STL\n"
    "* ![](https://img.shields.io/badge/C%2B%2B-N-blue): Partially implemented with C++ N\n"
    "* ![](https://img.shields.io/badge/C%2B%2B-N-green): Fully implemented with C++ N\n"
    "* ![][notyet]: Not yet implemented\n\n";

  return header;
}

std::string CreateDocumentFooter() {
  return "[notyet]: https://img.shields.io/badge/Not_yet-orange\n"
         "[removed]: https://img.shields.io/badge/Removed-red\n"
         "\n"
         "[cppno11]: https://img.shields.io/badge/C%2B%2B-11-red\n"
         "[cppno14]: https://img.shields.io/badge/C%2B%2B-14-red\n"
         "[cppno17]: https://img.shields.io/badge/C%2B%2B-17-red\n"
         "[cppno20]: https://img.shields.io/badge/C%2B%2B-20-red\n"
         "[cppno23]: https://img.shields.io/badge/C%2B%2B-23-red\n"
         "\n"
         "[cpppt11]: https://img.shields.io/badge/C%2B%2B-11-blue\n"
         "[cpppt14]: https://img.shields.io/badge/C%2B%2B-14-blue\n"
         "[cpppt17]: https://img.shields.io/badge/C%2B%2B-17-blue\n"
         "[cpppt20]: https://img.shields.io/badge/C%2B%2B-20-blue\n"
         "[cpppt23]: https://img.shields.io/badge/C%2B%2B-23-blue\n"
         "\n"
         "[cpp11]: https://img.shields.io/badge/C%2B%2B-11-green\n"
         "[cpp14]: https://img.shields.io/badge/C%2B%2B-14-green\n"
         "[cpp17]: https://img.shields.io/badge/C%2B%2B-17-green\n"
         "[cpp20]: https://img.shields.io/badge/C%2B%2B-20-green\n"
         "[cpp23]: https://img.shields.io/badge/C%2B%2B-23-green\n";
}

void MakeDocument(const std::vector<Feature>& features,
                  const std::string& title,
                  const std::string& dst,
                  DocumentType type = kDocumentTypeDefault) {
  std::ofstream ofs(dst);

  ofs << CreateDocumentHeader(title);

  std::map<int, int> version_count;

  if (type == kDocumentTypeDefault) {
    std::vector<xstring> categories;
    constexpr const int feature_width = 47;
    constexpr const int standard_width = 23;
    constexpr const int description_width = 37;

    const auto make_line = [=](const std::string& a="", const std::string& b="", const std::string& c="", int space = 1) {
      std::string result;
      result.reserve(feature_width + standard_width + description_width + 10);
      result += "|" + std::string(space, ' ') + a;
      result += std::string(std::max<int>(feature_width - 1 - space - a.size(), std::min(space, 1)), ' ');
      result += "|" + std::string(space, ' ') + b;
      result += std::string(std::max<int>(standard_width - 1 - space - b.size(), std::min(space, 1)), ' ');
      result += "|" + std::string(space, ' ') + c;
      result += std::string(std::max<int>(description_width - 2 - space - c.size(), std::min(space, 1)), ' ');
      result += "|\n";
      return result;
    };

    {
      ofs << make_line("Features", "Standard", "Implemented in");
      ofs << make_line(
          std::string(feature_width - 1, '-'),
          ':' + std::string(standard_width - 3, '-') + ':',
          ':' + std::string(description_width - 4, '-') + ':', 0);
    }

    for (const auto& feature : features) {
      { // Manage category changes
        std::vector<xstring> new_category;
        new_category.reserve(feature.category.size());
        for (const auto& c: feature.category)
          new_category.emplace_back(c.second);

        auto it1 = categories.begin();
        auto end1 = categories.end();
        auto it2 = new_category.begin();
        auto end2 = new_category.end();

        // Make empty line
        if (it1 != end1 && *it1 != *it2) {
          ofs << make_line();
        }

        // Write categories
        for (; it1 != end1 && it2 != end2; ++it1, ++it2) {
          if (*it1 == *it2)
            continue;
          std::string c(it2->begin(), it2->end());
          ofs << make_line("**" + c + "**");
        }

        while (it2 != end2) {
          std::string c(it2->begin(), it2->end());
          ofs << make_line("**" + c + "**", "", "");
          ++it2;
        }

        categories = new_category;
      }

      {
        auto begin = feature.names.begin();
        auto end = feature.names.end();
        bool all_deprecated = false;
        bool all_removed = false;
        int unused_version = 0;
        int min_version = 99;

        if (feature.names.size() == 1 || feature.t_mark.size() <= 1) {
          std::vector<std::string> names;
          std::vector<std::string> versions;

          for(auto it = begin; it != end; ++it) {
            std::string name(it->begin(), it->end());
            if (name == "pointer_safety")
              bool stop = true;
            name = std::regex_replace(name, std::regex("<"), "\\<");

            int version = kVersionUnknown;

            if (
              const auto p = std::find_if(feature.t_mark.begin(), feature.t_mark.end(), [](const auto& op) {
                return op && op->first != kMarkVersion;
              });
              p != feature.t_mark.end()) {
              name = "~~" + lsd::move(name) + "~~";
              unused_version = std::max(unused_version, p->value().second);
              if (const auto mark = p->value().first; mark == kMarkDeprecated)
                all_deprecated = true;
              else if (mark == kMarkRemoved)
                all_removed = true;
            }

            if (
              const auto p = std::find_if(feature.t_mark.begin(), feature.t_mark.end(), [](const auto& op) {
                return op && op->first == kMarkVersion;
              });
              p != feature.t_mark.end()) {
              version = p->value().second;
            }

            names.emplace_back(lsd::move(name));
            if (feature.t_mark.size() <= 1 && it != begin)
              continue;
            version = (version < kVersion11 || version == kVersionLegacy) ? kVersion11 : version;
            versions.emplace_back("![][cpp" + std::to_string(version) + "]");
            min_version = std::min(version, min_version);
          }

          std::string name_result = names[0];
          for (auto it = std::next(names.begin()); it != names.end(); ++it)
            name_result += " <br/>" + *it;

          std::string version_result = versions[0];
          for (auto it = std::next(versions.begin()); it != versions.end(); ++it)
            version_result += " <br/>" + *it;

          if (all_removed) {
            ofs << make_line(name_result, version_result, "Removed in C++" + std::to_string(unused_version));
          } else if (all_deprecated) {
            ofs << make_line(name_result, version_result, "Deprecated in C++" + std::to_string(unused_version));
          } else {
            ofs << make_line(name_result, version_result, "![][notyet]");
            version_count[min_version]++;
          }
        } else {
          std::vector<std::string> names;
          std::vector<std::string> versions;
          bool all_deprecated = true;
          bool all_removed = true;
          int unused_version = 0;

          auto mark_begin = feature.t_mark.begin();
          auto mark_end = feature.t_mark.end();

          auto mark_it = mark_begin;
          auto name_it = begin;

          for(; name_it != end; ++name_it, ++mark_it) {
            std::string name(name_it->begin(), name_it->end());

            name = std::regex_replace(name, std::regex("<"), "\\<");

            int version = kVersion11;
            const auto mark_type = mark_it->value().first;

            if (mark_type != kMarkVersion) {
              name = "~~" + lsd::move(name) + "~~";
              unused_version = std::max(unused_version, mark_it->value().second);
              if (mark_type == kMarkDeprecated)
                all_removed = false;
            } else {
              all_deprecated = false;
              all_removed = false;
              version = mark_it->value().second;
            }

            names.emplace_back(lsd::move(name));
            versions.emplace_back("![][cpp" + std::to_string(version < kVersion11 || version == kVersionLegacy ? kVersion11 : version) + "]");
          }

          std::string name_result = names[0];
          for (auto it = std::next(names.begin()); it != names.end(); ++it)
            name_result += " <br/>" + *it;

          std::string version_result = versions[0];
          for (auto it = std::next(versions.begin()); it != versions.end(); ++it)
            version_result += " <br/>" + *it;

          if (all_removed)
            ofs << make_line(name_result, version_result, "Removed in C++", unused_version);
          else if (all_deprecated)
            ofs << make_line(name_result, version_result, "Deprecated in C++", unused_version);
          else
            ofs << make_line(name_result, version_result, "![][notyet]");
        }


      }
    }
  }

  ofs << "\n\n"
      << "<!--\n";
  for (const auto& kv : version_count)
    ofs << "\tC++" << kv.first << ": " << kv.second << "\t| 0\n";
  ofs << "\n\tTotal: " << std::accumulate(version_count.begin(), version_count.end(), 0, [](int sum, const auto& elem) {
    return sum + elem.second;
  }) << "\t| 0";
  ofs << "-->\n";


  ofs << '\n' << CreateDocumentFooter();
  ofs.close();
}

int main(int argc, char* argv[]) {
  std::string pwd = __FILE__;
  pwd = pwd.substr(0, pwd.find_last_of('/'));

  std::string title = "chrono";
  if (argc >= 2) title = argv[1];

  std::string url = "https://en.cppreference.com/w/cpp/header/" + title;
  std::string dst = pwd + "/../../status/" + title + ".md";

  if (argc >= 3) url   = argv[2];
  if (argc >= 4) dst   = argv[3];

  const auto data = GetPage(url.data());
  if (!data)
    return EXIT_FAILURE;
  const auto& response = data.value();

  const auto features = GetFeatures(reinterpret_cast<const xmlChar *>(response.data()), "UTF-8");


  MakeDocument(features, title, dst);

  return EXIT_SUCCESS;
}
