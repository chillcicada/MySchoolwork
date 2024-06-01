# -*- coding: utf-8 -*-
from re import findall


def is_word_palindrome(word: str) -> bool:
  word = ''.join(findall(r'[a-zA-Z]', word))
  return word == word[::-1]
