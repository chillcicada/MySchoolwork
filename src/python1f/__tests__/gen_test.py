import src.gen as gen
from . import snapshot


def test_gen_check():
  assert gen.check(0)
  assert gen.check(99)
  assert not gen.check(-1)
  assert not gen.check(100)
  return


def test_gen_rand():
  snapshot(gen.rand(), target='gen_rand')
  snapshot(gen.rand(1), target='gen_rand')
  snapshot(gen.rand(3), target='gen_rand')
  snapshot(gen.rand(5, 10, 20), target='gen_rand')
  snapshot(gen.rand(10, 20, 30), target='gen_rand')
  return


def test_gen_IssueItem():
  item = gen.IssueItem(1, 2, '×')
  assert item.a == 1
  assert item.b == 2
  assert item.method == '×'
  assert item.result == 2
  assert item() == ' 1 ×  2 = ??'
  assert item.recv is None
  assert not item.isSubmitted
  assert not item.isCorrect

  item.setRecv(2)
  assert item.recv == 2
  assert item() == ' 1 ×  2 =  2'
  assert not item.isSubmitted
  assert not item.isCorrect

  item.submit()
  assert item() == ' 1 ×  2 =  2 (✓)'
  assert item.isSubmitted
  assert item.isCorrect
  return


def test_gen_IssueItem_snapshot():
  for _ in range(20):
    item = gen.IssueItem()
    snapshot(item(), target='gen_IssueItem')
  return


def test_gen_IssuesGenerator():
  issues = gen.IssuesGenerator(3)
  assert len(issues) == 3
  assert not issues.isCompleted
  assert all([isinstance(item, gen.IssueItem) for item in issues.issues])

  for item in issues.issues:
    assert not item.isSubmitted
    assert not item.isCorrect
    assert item.recv is None

  issues[0].setRecv(1)
  issues[0].submit()

  issues[1].setRecv(2)
  issues[1].submit()

  issues[2].setRecv(3)
  issues[2].submit()

  assert all([item.isSubmitted for item in issues.issues])

  issues.checkSubmit()
  assert issues.isCompleted
  return
