# -*- coding: utf-8 -*-
import platform
from colorama import Fore, Style

if platform.system() == 'Windows':
  from colorama import just_fix_windows_console

  just_fix_windows_console()
  pass


def info(*msg, **kwargs):
  print(Fore.GREEN, end='')
  print(*msg, **kwargs, end='')
  print(Style.RESET_ALL)
  return


def warn(*msg, **kwargs):
  print(Fore.YELLOW, end='')
  print(*msg, **kwargs, end='')
  print(Style.RESET_ALL)
  return


def error(*msg, **kwargs):
  print(Fore.RED, end='')
  print(*msg, **kwargs, end='')
  print(Style.RESET_ALL)
  return


def debug(*msg, **kwargs):
  print(Fore.CYAN, end='')
  print(*msg, **kwargs, end='')
  print(Style.RESET_ALL)
  return
