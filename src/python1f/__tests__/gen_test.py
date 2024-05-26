import src.gen as gen


def test_gen_check():
  assert gen.check(0)
  assert gen.check(99)
  assert not gen.check(-1)
  assert not gen.check(100)
  pass
