# -*- coding: utf-8 -*-
from typing import List, Dict


class RecordItem:
  def __init__(self, ID: int, Name: str, Score: int | float) -> None:
    self.ID = ID
    self.Name = Name
    self.Score = Score
    return

  def __str__(self) -> str:
    return f'{self.ID},{self.Name},{self.Score}'

  def __repr__(self) -> str:
    return str(self)

  def __call__(self) -> str:
    return str(self)

  pass


def str2RecordItem(s: str) -> RecordItem:
  ID, Name, Score = s.split(',')
  return RecordItem(int(ID), Name, int(Score))


def getAvgScore(record: List[RecordItem]) -> RecordItem:
  """
  This requires a list of RecordItem with the same ID.
  """
  _id = record[0].ID
  if not all([item.ID == _id for item in record]):
    raise ValueError('The input list of RecordItem must have the same ID.')
  _name = record[0].Name
  avg_score = round(sum([item.Score for item in record]) / len(record), 2)
  return RecordItem(_id, _name, avg_score)


class Record:
  header = ['ID', 'Name', 'Score']

  def __init__(self, lt: List[RecordItem] = []) -> None:
    self.data: List[RecordItem] = lt
    return

  def append(self, item: RecordItem) -> None:
    self.data.append(item)
    return

  def remove(self, item: RecordItem) -> None:
    self.data.remove(item)
    return

  def __call__(self) -> List[RecordItem]:
    return self.data

  def __len__(self) -> int:
    return len(self.data)

  def __iter__(self):
    return iter(self.data)

  def __str__(self) -> str:
    return ','.join(self.header) + '\n' + '\n'.join([str(item) for item in self.data])

  def query(self, term: str | int) -> List[RecordItem]:
    if isinstance(term, int) or term.isdigit():
      return [item for item in self.data if item.ID == term]
    # isinstance(term, str)
    return [item for item in self.data if item.Name == term]

  def queryAll(self) -> List[List[RecordItem]]:
    ids = set([item.ID for item in self.data])
    return [[item for item in self.data if item.ID == _id] for _id in ids]

  def getIDs(self) -> List[int]:
    return sorted(list(set([item.ID for item in self.data])))

  def getNames(self) -> List[str]:
    return sorted(list(set([item.Name for item in self.data])))

  def clear(self) -> None:
    self.data.clear()
    return

  pass


def str2Record(s: str) -> Record:
  lines = s.strip().split('\n')
  data = [str2RecordItem(line) for line in lines[1:]]  # Skip the header
  return Record(data)


def getRankedRecord(record: Record) -> List[RecordItem]:
  data_section = record.queryAll()
  return sorted([getAvgScore(section) for section in data_section], key=lambda x: x.Score, reverse=True)


def printRankedRecord(record: Record) -> List[str]:
  sorted_record = getRankedRecord(record)
  res: List[str] = []

  header = ['Rank', 'ID', 'Name', 'Average Score']
  res.append(','.join(header))

  dict_record: Dict[int | float, List[RecordItem]] = {}

  for item in sorted_record:
    if item.Score not in dict_record:
      dict_record[item.Score] = [item]
      continue
    dict_record[item.Score].append(item)
    pass

  scores = sorted(dict_record.items(), key=lambda x: x[0], reverse=True)

  rank = 1

  for _, items in scores:
    length = len(items)
    for i in range(length):
      res.append(f'第{rank}名,{str(items[i])}')
      pass
    rank += length
    pass

  return res
