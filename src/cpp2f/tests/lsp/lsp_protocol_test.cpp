/**
 * @file lsp_protocol_test.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-26
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "LspProtocol.h"
#include <utest.h>

UTEST(lsp_protocol, position) {
  Position pos1;
  pos1.line = 1;
  pos1.character = 2;
  EXPECT_EQ(pos1.line, 1);
  EXPECT_EQ(pos1.character, 2);

  Position pos2;
  pos2.line = 1;
  pos2.character = 2;
  EXPECT_TRUE(pos1 == pos2);

  Position pos3 = {1, 3};
  EXPECT_TRUE(pos1 <= pos3);
}

UTEST(lsp_protocol, range) {
  Range rng1;
  rng1.start = {1, 2};
  rng1.end = {3, 4};
  EXPECT_EQ(rng1.start.line, 1);
  EXPECT_EQ(rng1.start.character, 2);
  EXPECT_EQ(rng1.end.line, 3);
  EXPECT_EQ(rng1.end.character, 4);

  Range rng2;
  rng2.start = {1, 2};
  rng2.end = {3, 4};
  EXPECT_TRUE(rng1 == rng2);

  Range rng3 = {{1, 2}, {3, 4}};
  EXPECT_TRUE(rng3.contains(rng1.start));
}
