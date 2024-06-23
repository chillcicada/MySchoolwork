# -*- coding: utf-8 -*-
from random import shuffle
from typing import List


def divide(lt: List, n: int) -> List[List]:
  """将一个数组尽量均分成 n 个子数组，溢出的部分将分配到前面的子数组中"""
  k, m = divmod(len(lt), n)
  return [lt[i * k + min(i, m) : (i + 1) * k + min(i + 1, m)] for i in range(n)]


class Cards:
  # 定义一副牌及所有牌的功能
  CARD_RANK = ['2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A']
  CARD_SUIT = ['C', 'D', 'H', 'S']
  CARD_POINT = {'A': 4, 'K': 3, 'Q': 2, 'J': 1}
  BRIDGE_STATUS = ['NT', 'p']  # 由于我不熟悉桥牌，此处没有给出根据桥牌规则的具体实现

  def __init__(self, n=4) -> None:
    # 定义牌组
    self.CARD_DECK = [(rank, suit) for rank in self.CARD_RANK for suit in self.CARD_SUIT]

    # 洗牌
    shuffle(self.CARD_DECK)

    # 发牌
    self.hands = divide(self.CARD_DECK, n)

    # 这里默认取第一组作为手牌
    self.hand = self.hands[0]
    self.length = len(self.hand)

    self.point = 0
    self.table = None
    return

  def getHand(self):
    """此处手牌会以元组的形式返回，元组的第一个元素是牌面，第二个元素是花色"""
    return self.hand

  def getPoint(self, card: str) -> int:
    """根据牌面计算一张牌的牌点"""
    return self.CARD_POINT.get(card, 0)

  def getTotalPoint(self):
    """计算手牌的总牌点"""
    self.point = sum([self.getPoint(card[0]) for card in self.hand])
    return self.point

  def getAllTotalPoint(self):
    """返回所有牌组的各自总牌点"""
    self.table = [sum([self.getPoint(card[0]) for card in hand]) for hand in self.hands]
    return self.table

  def __call__(self):
    """便于调用，计算手牌的总牌点"""
    return self.getTotalPoint()

  pass


def main() -> None:
  cards = Cards()

  print('Hand:', cards.hands)
  print('Total Point:', cards())
  return
