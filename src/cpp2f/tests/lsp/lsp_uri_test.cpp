/**
 * @file lsp_uri_test.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-26
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "LspUri.h"
#include <string>
#include <utest.h>

UTEST(string_ref, base) {
  auto input = string_ref("file:///home/user/abc.cpp");
  auto output = "file:///home/user/abc.cpp";
  ASSERT_TRUE(input == output);
}

UTEST(lsp_uri, encode) {
  auto input1 = URIForFile::UriEncode("///home\\user/abc.cpp");
  auto output1 = std::string("/home/user/abc.cpp");
  ASSERT_TRUE(input1 == output1);

  auto input2 = URIForFile::UriEncode("///home\\user/abc.cpp ");
  auto output2 = std::string("/home/user/abc.cpp+");
  ASSERT_TRUE(input2 == output2);

  auto input3 = URIForFile::UriEncode("///home\\user/abc.cpp% ");
  auto output3 = std::string("/home/user/abc.cpp%25+");
  ASSERT_TRUE(input3 == output3);

  auto input4 = URIForFile::UriEncode("///home\\user/abc.cpp%25 ");
  auto output4 = std::string("/home/user/abc.cpp%2525+");
  ASSERT_TRUE(input4 == output4);

  auto input5 = URIForFile::UriEncode("C:\\Users\\user\\abc.cpp");
  auto output5 = std::string("C:/Users/user/abc.cpp");
  ASSERT_TRUE(input5 == output5);
}

UTEST(lsp_uri, from) {
  URIForFile uri1;
  uri1.from("/home\\user/abc.cpp");
  auto output1 = std::string("file:////home/user/abc.cpp");
  ASSERT_TRUE(uri1.str() == output1);

  URIForFile uri2;
  uri2.from("C:\\Users\\user\\abc.cpp");
  auto output2 = std::string("file:///C:/Users/user/abc.cpp");
  ASSERT_TRUE(uri2.str() == output2);

  URIForFile uri3;
  uri3.from("readme.md");
  auto output3 = std::string("file:///readme.md");
  ASSERT_TRUE(uri3.str() == output3);

  URIForFile uri4;
  uri4.from("./readme.md");
  auto output4 = std::string("file:///./readme.md");
  ASSERT_TRUE(uri4.str() == output4);
}

UTEST(uri, base) {
  URI uri;
  uri.parse("file:///home/user/abc.cpp");
  ASSERT_TRUE(uri.path() == "/home/user/abc.cpp");
}
