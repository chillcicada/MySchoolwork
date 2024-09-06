import src.utils as utils


def test_utils_YN2Bool():
  assert utils.YN2Bool('Y')
  assert utils.YN2Bool('y')
  assert utils.YN2Bool('')

  assert utils.YN2Bool('  Y  ')
  assert utils.YN2Bool('  y  ')
  assert utils.YN2Bool('     ')

  assert not utils.YN2Bool('N')
  assert not utils.YN2Bool('n')

  assert not utils.YN2Bool('A')
  assert not utils.YN2Bool('a')
  return


def test_utils_parseInput():
  assert utils.parseInput('1') == 1
  assert utils.parseInput(' 1 ') == 1
  assert utils.parseInput(' 1 2 ') is None
  assert utils.parseInput('a') is None
  return
