import src.core as core
from src.core import Record, RecordItem


def test_core_RecordItem():
  item = RecordItem(1, 'Alice', 100)
  assert item.ID == 1
  assert item.Name == 'Alice'
  assert item.Score == 100
  assert item() == '1,Alice,100'
  return


def test_str2RecordItem():
  item = core.str2RecordItem('1,Alice,100')
  assert item.ID == 1
  assert item.Name == 'Alice'
  assert item.Score == 100
  assert item() == '1,Alice,100'
  return


def test_getAvgScore():
  record = [
    RecordItem(1, 'Alice', 100),
    RecordItem(1, 'Alice', 90),
    RecordItem(1, 'Alice', 80),
  ]
  avg = core.getAvgScore(record)
  assert avg.ID == 1
  assert avg.Name == 'Alice'
  assert avg.Score == 90
  return


def test_core_Record_1():
  record = Record()
  assert len(record) == 0

  record.append(RecordItem(1, 'Alice', 100))
  record.append(RecordItem(2, 'Bob', 90))
  record.append(RecordItem(3, 'Charlie', 90))

  assert len(record) == 3
  assert str(record) == 'ID,Name,Score\n1,Alice,100\n2,Bob,90\n3,Charlie,90'

  assert record.query(1)[0].Name == 'Alice'
  assert record.query('Bob')[0].ID == 2

  record_with_list = Record([RecordItem(1, 'Alice', 100), RecordItem(2, 'Bob', 90), RecordItem(3, 'Charlie', 90)])
  assert len(record_with_list) == 3
  return


def test_core_Record_2():
  z = Record()
  z.clear()
  z.append(RecordItem(1, 'Alice', 100))
  z.append(RecordItem(2, 'Bob', 90))
  z.append(RecordItem(3, 'Charlie', 90))
  z.append(RecordItem(3, 'Charlie', 90))

  assert z.queryAll() == [
    [z.data[0]],
    [z.data[1]],
    [z.data[2], z.data[3]],
  ]

  assert z.getIDs() == [1, 2, 3]

  assert z.getNames() == ['Alice', 'Bob', 'Charlie']
  return


def test_str2Record():
  record = core.str2Record('ID,Name,Score\n1,Alice,100\n2,Bob,90\n3,Charlie,90\n')
  assert len(record) == 3
  assert record.query(1)[0].Name == 'Alice'
  assert record.query('Bob')[0].ID == 2

  return


def test_getRankedRecord():
  z = Record()
  z.append(RecordItem(1, 'Alice', 100))
  z.append(RecordItem(2, 'Bob', 90))
  z.append(RecordItem(3, 'Charlie', 90))
  z.append(RecordItem(3, 'Charlie', 90))

  res = core.getRankedRecord(z)

  assert res[0].ID == 1
  assert res[0].Name == 'Alice'
  assert res[0].Score == 100
  return


def test_printRankedRecord():
  record = Record()
  record.append(RecordItem(1, 'Alice', 100))
  record.append(RecordItem(2, 'Bob', 90))
  record.append(RecordItem(3, 'Charlie', 90))
  record.append(RecordItem(3, 'Charlie', 90))

  res = core.printRankedRecord(record)

  assert '\n'.join(res) == 'Rank,ID,Name,Average Score\n第1名,1,Alice,100.0\n第2名,2,Bob,90.0\n第2名,3,Charlie,90.0'
  return
