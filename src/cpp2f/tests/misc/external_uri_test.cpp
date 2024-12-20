/**
 * @file external_uri_test.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-20
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include <utest.h>

#include "EditorUtils.h"

UTEST(utils, uriForFile) {
  auto uri1 = util::uriForFile(
      "D:/Desktop/Projects/qode/build/windows/x64/release/main.cpp");
  EXPECT_TRUE(
      uri1.str() ==
      "file:///D:/Desktop/Projects/qode/build/windows/x64/release/main.cpp");

  auto uri2 = util::uriForFile("main.cpp");
  EXPECT_TRUE(
      uri2.str() ==
      "file:///D:/Desktop/Projects/qode/build/windows/x64/release/main.cpp");

  auto uri3 = util::uriForFile("D:/Desktop/Projects/qode/src/main.cpp");
  EXPECT_TRUE(uri3.str() == "file:///D:/Desktop/Projects/qode/src/main.cpp");
}
