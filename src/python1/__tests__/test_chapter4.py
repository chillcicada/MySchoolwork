from chapter4.chapter4_1 import is_word_palindrome
from chapter4.chapter4_2 import getDay, getDays, printMonth, printYear
from chapter4.chapter4_3 import printMonth2File, printYear2File
from chapter4.chapter4_4 import (
  parseMonth,
  printSeason,
  printYearWithSeasons,
  printSeason2File,
  printYearWithSeasons2File,
)


def test_is_word_palindrome():
  assert is_word_palindrome('你好qaq')
  assert is_word_palindrome('这z是z测z试')
  assert is_word_palindrome('a🥳w🥳a')
  assert is_word_palindrome('wo我ui是hv回wf文 文fw回vh是iu我ow')
  assert is_word_palindrome('z,z')
  assert is_word_palindrome('aba')

  assert not is_word_palindrome('abc')
  assert not is_word_palindrome('wa a ame')
  assert not is_word_palindrome('🤣🤣aww')
  pass


def test_is_word_palindrome_empty():
  assert is_word_palindrome('')
  pass


def test_is_word_palindrome_with_file():
  with open('chapter4/test_chapter4_1_true.txt', 'r', encoding='utf-8') as f:
    for line in f:
      if line.strip() == '':
        continue
      assert is_word_palindrome(line.strip())
      pass
    pass

  with open('chapter4/test_chapter4_1_false.txt', 'r', encoding='utf-8') as f:
    for line in f:
      if line.strip() == '':
        continue
      assert not is_word_palindrome(line.strip())
      pass
    pass
  pass


def test_getDay():
  assert getDay(2024, 1) == 1
  assert getDay(2024, 6) == 6
  assert getDay(2024, 6, 2) == 0
  assert getDay(2024, 6, 3) == 1
  pass


def test_getDays():
  assert getDays(2024, 1) == 31
  assert getDays(2024, 2) == 29
  assert getDays(2024, 6) == 30
  pass


def test_printMonth():
  print()  # print a blank line here
  printMonth(2024, 1)
  printMonth(2024, 6)
  printMonth(2024, 12)
  pass


def test_printYear():
  print()  # print a blank line here
  printYear(2024)
  pass


def test_printMonth2File():
  printMonth2File(2024, 1, '__tests__/__snapshots__/test_chapter4_2_month1.snap')
  printMonth2File(2024, 6, '__tests__/__snapshots__/test_chapter4_2_month6.snap')
  printMonth2File(2024, 12, '__tests__/__snapshots__/test_chapter4_2_month12.snap')
  pass


def test_printYear2File():
  printYear2File(2024, '__tests__/__snapshots__/test_chapter4_2_year2024.snap')
  pass


def test_parseMonth():
  assert parseMonth(2024, 1) == [
    '      1   2   3   4   5   6',
    '  7   8   9  10  11  12  13',
    ' 14  15  16  17  18  19  20',
    ' 21  22  23  24  25  26  27',
    ' 28  29  30  31            ',
  ]
  assert parseMonth(2024, 6) == [
    '                          1',
    '  2   3   4   5   6   7   8',
    '  9  10  11  12  13  14  15',
    ' 16  17  18  19  20  21  22',
    ' 23  24  25  26  27  28  29',
    ' 30                        ',
  ]
  assert parseMonth(2024, 12) == [
    '  1   2   3   4   5   6   7',
    '  8   9  10  11  12  13  14',
    ' 15  16  17  18  19  20  21',
    ' 22  23  24  25  26  27  28',
    ' 29  30  31                ',
  ]
  pass


def test_printSeason():
  print()  # print a blank line here
  printSeason(2024, 1)
  printSeason(2024, 2)
  printSeason(2024, 3)
  printSeason(2024, 4)
  pass


def test_printYearWithSeasons():
  print()  # print a blank line here
  printYearWithSeasons(2024)
  pass


def test_printSeason2File():
  printSeason2File(2024, 1, '__tests__/__snapshots__/test_chapter4_4_season1.snap')
  printSeason2File(2024, 2, '__tests__/__snapshots__/test_chapter4_4_season2.snap')
  printSeason2File(2024, 3, '__tests__/__snapshots__/test_chapter4_4_season3.snap')
  printSeason2File(2024, 4, '__tests__/__snapshots__/test_chapter4_4_season4.snap')
  pass


def test_printYearWithSeasons2File():
  printYearWithSeasons2File(2024, '__tests__/__snapshots__/test_chapter4_4_year2024.snap')
  pass
