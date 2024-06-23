from chapter5.chapter5_1 import filter_chars
from chapter5.chapter5_2 import calc, calc_2, mock
from chapter5.chapter5_3 import calcRPN, gen, genRPNs, judge24
from chapter5.chapter5_4 import Cards, divide


def test_filter_chars():
  assert filter_chars('a1b2c3') == 'abc'
  assert filter_chars('a1b2c3!@#') == 'abc'
  assert filter_chars('a1b2c3!@#🤣🤣') == 'abc'
  assert filter_chars('你好qaq') == 'qaq'
  pass


def test_mock():
  assert mock(1, 2, '+') == 3
  assert mock(1, 2, '-') == -1
  assert mock(1, 2, '*') == 2
  assert mock(1, 2, '/') == 0.5
  pass


def test_calc():
  assert calc('1 + 2') == 3
  assert calc('1 + 2 * 3') == 7
  assert calc('1 + 2 * 3 - 4') == 3
  pass


def test_calc_2():
  assert calc_2('1 + 2') == 3
  assert calc_2('1 + 2 * 3') == 7
  assert calc_2('1+2*3-4') == 3
  pass


def test_gen():
  assert len(gen()) == 4

  print()  # print a blank line here
  print(*gen())

  with open('__tests__/__snapshots__/test_chapter5_3_gen.snap', 'w') as f:
    for _ in range(10):
      print(*gen(), file=f)
      pass
    pass
  pass


def test_calcRPN():
  assert calcRPN([1, 2, '+', 3, '*']) == 9
  assert calcRPN([1, 2, '+', 3, '*', 4, '-']) == 5
  pass


def test_genRPNs():
  assert len(genRPNs([1, 2, 3, 4])) == 320

  with open('__tests__/__snapshots__/test_chapter5_3_genRPNs.snap', 'w') as f:
    for item in genRPNs([1, 2, 3, 4]):
      print(item, file=f)
      pass
    pass
  pass


def test_judge24():
  assert judge24([1, 2, 3, 7])
  assert judge24([1, 2, 3, 4])
  assert judge24([1, 2, 3, 5])

  assert not judge24([1, 1, 1, 1])
  assert not judge24([1, 1, 1, 2])

  with open('__tests__/__snapshots__/test_chapter5_3_judge24.snap', 'w') as f:
    for _ in range(10):
      nums = gen()
      print(nums, judge24(nums), file=f)
      pass
    pass
  pass


def test_divide():
  assert divide([1, 2, 3, 4, 5, 6, 7, 8], 4) == [[1, 2], [3, 4], [5, 6], [7, 8]]
  assert divide([1, 2, 3, 4, 5, 6, 7, 8, 9], 3) == [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
  assert divide([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 3) == [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
  assert divide([1, 2, 3, 4, 5, 6, 7, 8], 3) == [[1, 2, 3], [4, 5, 6], [7, 8]]

  assert divide([(1, 1), (2, 2), (3, 3), (4, 4), (5, 5), (6, 6), (7, 7), (8, 8)], 4) == [
    [(1, 1), (2, 2)],
    [(3, 3), (4, 4)],
    [(5, 5), (6, 6)],
    [(7, 7), (8, 8)],
  ]
  pass


def test_Cards():
  cards = Cards()

  assert cards.length == 13

  print()  # print a blank line here
  print('Hand:', cards.hand)
  print('Total Point:', cards())

  with open('__tests__/__snapshots__/test_chapter5_4_cards.snap', 'w') as f:
    print('Hand:', cards.hand, file=f)
    print('Total Point:', cards(), file=f)
    pass

  pass
