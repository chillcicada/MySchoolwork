/**
 * @file LspUri.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-26
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef LSP_URI_H
#define LSP_URI_H

#include <nlohmann/json.hpp>

#include <cstddef>
#include <cstring>
#include <regex>
#include <string>

using json = nlohmann::json;

/**
 * @brief A wrapper for string, which is used to represent a string without
 *        owning the memory.
 *
 */
class string_ref {
public:
  static const size_t npos = ~size_t(0);
  using iterator = const char *;
  using const_iterator = const char *;
  using size_type = size_t;

private:
  const char *ref_ = nullptr;
  size_t length_ = 0;

public:
  constexpr string_ref() : ref_(nullptr), length_(0) {}
  constexpr string_ref(std::nullptr_t) : ref_(nullptr), length_(0) {}
  constexpr string_ref(const char *ref, size_t length)
      : ref_(ref), length_(length) {}
  string_ref(const char *ref) : ref_(ref), length_(std::strlen(ref)) {}
  string_ref(const std::string &string)
      : ref_(string.c_str()), length_(string.length()) {}
  inline operator const char *() const { return ref_; }
  inline std::string str() const { return std::string(ref_, length_); }
  inline bool operator==(const string_ref &ref) const {
    return length_ == ref.length_ && strcmp(ref_, ref.ref_) == 0;
  }
  inline bool operator==(const char *ref) const {
    return strcmp(ref_, ref) == 0;
  }
  inline bool operator>(const string_ref &ref) const {
    return length_ > ref.length_;
  }
  inline bool operator<(const string_ref &ref) const {
    return length_ < ref.length_;
  }
  inline const char *c_str() const { return ref_; }
  inline bool empty() const { return length_ == 0; }
  iterator begin() const { return ref_; }
  iterator end() const { return ref_ + length_; }
  inline const char *data() const { return ref_; }
  inline size_t size() const { return length_; }
  inline size_t length() const { return length_; }
  char front() const { return ref_[0]; }
  char back() const { return ref_[length_ - 1]; }
  char operator[](size_t index) const { return ref_[index]; }
};
template <typename T> class option {
public:
  T fStorage = T();
  bool fHas = false;
  constexpr option() = default;
  option(const T &y) : fStorage(y), fHas(true) {}
  option(T &&y) : fStorage(std::move(y)), fHas(true) {}
  option &operator=(T &&v) {
    fStorage = std::move(v);
    fHas = true;
    return *this;
  }
  option &operator=(const T &v) {
    fStorage = v;
    fHas = true;
    return *this;
  }
  const T *ptr() const { return &fStorage; }
  T *ptr() { return &fStorage; }
  const T &value() const { return fStorage; }
  T &value() { return fStorage; }
  bool has() const { return fHas; }
  const T *operator->() const { return ptr(); }
  T *operator->() { return ptr(); }
  const T &operator*() const { return value(); }
  T &operator*() { return value(); }
  explicit operator bool() const { return fHas; }
};

template <typename T> void to_json(json &j, const option<T> &opt) {
  if (opt.has()) {
    j = opt.value();
  } else {
    j = nullptr;
  }
}

template <typename T> void from_json(const json &j, option<T> &opt) {
  if (j.is_null()) {
    opt = option<T>();
  } else {
    opt = option<T>(j.get<T>());
  }
}

inline uint8_t FromHex(const char digit) {
  if (digit >= '0' && digit <= '9')
    return digit - '0';
  if (digit >= 'a' && digit <= 'f')
    return digit - 'a' + 10;
  if (digit >= 'A' && digit <= 'F')
    return digit - 'A' + 10;
  return 0;
}
inline uint8_t FromHex(const char n1, const char n2) {
  return (FromHex(n1) << 4) + FromHex(n2);
}

struct URIForFile {
  std::string file;
  static std::string UriEncode(string_ref ref) {
    static const char *hexs = "0123456789ABCDEF";
    static const char *symbol = "._-*/:";
    std::string result;
    for (uint8_t ch : ref) {
      if (ch == '\\') {
        ch = '/';
      }
      if (std::isalnum(ch) || strchr(symbol, ch)) {
        if (ch == '/' && result.back() == '/') {
          continue;
        }
        result += ch;
      } else if (ch == ' ') {
        result += '+';
      } else {
        result += '%';
        result += hexs[ch >> 4];
        result += hexs[ch & 0xF];
      }
    }
    return std::move(result);
  }
  explicit operator bool() const { return !file.empty(); }
  friend bool operator==(const URIForFile &LHS, const URIForFile &RHS) {
    return LHS.file == RHS.file;
  }
  friend bool operator!=(const URIForFile &LHS, const URIForFile &RHS) {
    return !(LHS == RHS);
  }
  friend bool operator<(const URIForFile &LHS, const URIForFile &RHS) {
    return LHS.file < RHS.file;
  }
  void from(string_ref path) { file = "file:///" + UriEncode(path); }
  explicit URIForFile(const char *str) : file(str) {}
  URIForFile() = default;
  inline std::string &str() { return file; }
};

class URI {
public:
  static std::string Encode(string_ref input) {
    static const char *hexs = "0123456789ABCDEF";
    static const char *unreserved = "-._~";
    std::string res;
    res.reserve(input.size());
    for (auto chr : input) {
      if (std::isalnum(chr) || std::strchr(unreserved, chr)) {
        res += chr;
      } else {
        res += '%';
        res += hexs[chr >> 4];
        res += hexs[chr & 0xF];
      }
    }
    return res;
  }
  static std::string Decode(string_ref input) {
    static const char *reserved = ":/?#[]@!$&'()*+,;=";
    std::string res;
    res.reserve(input.size());
    for (auto iter = input.begin(), end = input.end(); iter != end; ++iter) {
      if (*iter == '%') {
        const uint8_t n1 = (*(++iter));
        const uint8_t n2 = (*(++iter));
        res += static_cast<char>(FromHex(n1, n2));
      } else if (*iter == '+') {
        res += ' ';
      } else {
        res += *iter;
      }
    }
    return res;
  }

public:
  void parse(string_ref uri) {
    static const std::regex pattern{
        "^([a-zA-Z]+[\\w\\+\\-\\.]+)?(\\://)?" //< scheme
        "(([^:@]+)(\\:([^@]+))?@)?"            //< username && password
        "([^/:?#]+)?(\\:(\\d+))?"              //< hostname && port
        "([^?#]+)"                             //< path
        "(\\?([^#]*))?"                        //< query
        "(#(.*))?$"                            //< fragment
    };
    static std::cmatch parts;
    uri_ = Decode(uri);
    if (std::regex_match(uri_.c_str(), parts, pattern)) {
      path_ = string_ref(uri_.c_str() + parts.position(10), parts.length(10));
      scheme_ = parts.length(1) ? string_ref(uri_.c_str() + parts.position(1),
                                             parts.length(1))
                                : string_ref{};
      userinfo_ = parts.length(3) ? string_ref(uri_.data() + parts.position(3),
                                               parts.length(3))
                                  : string_ref{};
      host_ = parts.length(7)
                  ? string_ref(uri_.data() + parts.position(7), parts.length(7))
                  : string_ref{};
      port_ = parts.length(9)
                  ? string_ref(uri_.data() + parts.position(9), parts.length(9))
                  : string_ref{};
      query_ = parts.length(11) ? string_ref(uri_.data() + parts.position(11),
                                             parts.length(11))
                                : string_ref{};
      fragment_ =
          parts.length(13)
              ? string_ref(uri_.data() + parts.position(13), parts.length(13))
              : string_ref{};
    }
  }
  string_ref path() { return path_; }
  string_ref scheme() { return scheme_; }
  string_ref userinfo() { return userinfo_; }
  string_ref host() { return host_; }
  string_ref port() { return port_; }
  string_ref query() { return query_; }
  string_ref fragment() { return fragment_; }
  string_ref query(string_ref key) {

    std::regex regex("([a-zA-Z_]+)=");
    std::cmatch part;
    if (std::regex_match(uri_.c_str(), part, regex)) {
    }

    return {};
  }
  std::string uri() { return Encode(uri_); }

private:
  std::string uri_;
  string_ref path_;
  string_ref scheme_;
  string_ref userinfo_;
  string_ref host_;
  string_ref port_;
  string_ref query_;
  string_ref fragment_;
};

#endif // LSP_URI_H
