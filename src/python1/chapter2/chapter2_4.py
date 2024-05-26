# -*- coding: utf-8 -*-

# chapter2_4
cache = []


while True:
  temp = input()
  try:
    temp = float(temp)
    if temp == 0:
      result = sum(cache) / len(cache)
      print(f'the input is: {cache}')
      print(f'the result is: {result:.2f}')
      break
    cache.append(temp)
  except ValueError:
    result = sum([float(i) for i in temp.split()]) / (len(temp.split()) - 1)
    print(f'the input is: {temp}')
    print(f'the result is: {result:.2f}')
    break
