#!/usr/bin/env python
# -*- coding: utf-8 -*-
import typer

from sys import version_info
from colorama import Fore
from typing import Optional
from typing_extensions import Annotated

import src.core as core

from src.fs import FS
from src.log import info, warn, error, debug
from src.gen import IssuesGenerator
from src.utils import YN2Bool, parseInput

__version__ = '0.0.1'

App = typer.Typer()


def version_callback(value: bool):
  if value:
    debug('CLI Version:', __version__)

    raise typer.Exit()
  return


@App.command()
def start():
  """
  start the app.
  """

  if version_info.major < 3 or version_info.minor < 8:
    warn(f'[Hint] You are using python {version_info.major}.{version_info.minor}.')
    warn('I have only tested this on python 3.8+, please consider upgrading.')
    warn('If you encounter any issues, please report them at 2210227279@qq.com')
    pass

  __guide__ = """Welcome to the app! 🎉
Type the following command to interact with the app:
  * [0/E] Exit and logout the app
  * [1/S] Start test
  * [2/F] Find record
  * [3/H/Default] Show help
  * [4/L] Login / Register
  * [5/Q] Logout if you won't to quit the app
"""

  info('Starting the app...')

  print('Loading data...')
  fs = FS()

  rawData = fs.load()

  if rawData == '' or rawData == 'ID,Name,Score\n':
    warn('No record found. Initializing...')
    data = core.Record()
    pass
  else:
    debug('Record found. Loading...')
    try:
      data = core.str2Record(rawData)
      info('Record loaded.')
    except ValueError:
      warn('Invalid record found. Initializing...')
      fs.clear()
      data = core.Record()
    pass

  info(__guide__)

  currentName: str | None = None
  currentID: int | None = None

  while True:
    c = input('Type a command: ').lower().strip()

    if c in ['0', 'e', 'exit']:  # match case is only available in python 3.10+, :/
      fs.save(str(data))
      break
    elif c in ['1', 's']:  # Start test
      if currentName is None or currentID is None:
        error('Please login first.')
        continue

      print()  # Add a blank line
      info('Starting the test...')
      debug('=' * 50)

      issues = IssuesGenerator()  # ! Change the number of questions here

      for index, item in enumerate(issues):
        info(f'Question {index + 1:<2}: {item()}')
        raw = input('Type your answer: ')
        recv = parseInput(raw)
        while recv is None:
          error(f'Invalid input {Fore.GREEN}"{raw}"')
          raw = input('Type your answer: ')
          recv = parseInput(raw)
          pass
        item.setRecv(recv)

        info(f'Your answer: {item()}')
        yn = input('Are you confirm of your answer [y/N] (default: y): ')
        while not YN2Bool(yn):
          raw = input('Type your answer: ')
          recv = parseInput(raw)
          while recv is None:
            error(f'Invalid input {Fore.GREEN}"{raw}"')
            raw = input('Type your answer: ')
            recv = parseInput(raw)
          pass
          item.setRecv(recv)

          info(f'Your answer: {item()}')
          yn = input('Are you confirm of your answer [y/N] (default: y): ')
          pass

        item.submit()
        debug('=' * 50)
        pass

      info('Test finished.')
      data.append(core.RecordItem(currentID, currentName, issues.getScores()))
      print()  # Add a blank line

      pass
    elif c in ['2', 'f']:  # Find record
      __find_guide__ = """Find record by:
  * [0/E] Exit
  * [1/N] Name
  * [2/I] ID
  * [3/H/Default] Help
  * [4/L] List all records
  * [5/A] List all records by average score
"""
      debug(__find_guide__)

      while True:
        c = input('Type a query command: ').lower().strip()

        if c in ['0', 'e', 'exit']:
          break
        elif c in ['1', 'n']:
          name = input('Type the name: ')
          items = data.query(name)
          if len(items) == 0:
            warn(f'No record found for {name}.')
            continue

          for item in items:
            info(item)
            pass
          pass
        elif c in ['2', 'i']:
          try:
            ID = int(input('Type the ID: '))
          except ValueError:
            error('Invalid input.')
            continue

          items = data.query(ID)
          if len(items) == 0:
            warn(f'No record found for {ID}.')
            continue
          pass
        elif c in ['3', 'h', '']:
          info(__find_guide__)
          pass
        elif c in ['4', 'l']:
          if len(data) == 0:
            warn('No record found.')
            continue
          for item in data:
            info(item())
            pass
          pass
        elif c in ['5', 'a']:
          ctx = core.printRankedRecord(data)
          for item in ctx:
            info(item)
            pass
        else:
          error(f'Invalid query command {Fore.GREEN}"{c}"')
          warn('Invalid command, please check the guide:')
          debug(__find_guide__)
          pass
      pass
    elif c in ['3', 'h', '']:  # Help
      info(__guide__)
      pass
    elif c in ['4', 'l']:  # Login
      if currentName is not None:
        warn('You are already logged in.')
        warn('If you want to login as another user, please logout first.')
        continue

      currentName = input('Type your name: ')

      if currentName in data.getNames():
        currentID = data.query(currentName)[0].ID
        pass
      else:
        warn('User not found, initializing...')
        currentID = data.getIDs()[-1] + 1 if len(data.getIDs()) > 0 else 100001
        info(f'Your ID is {currentID}.')
        pass

      info(f'Welcome, {currentName}!')
      pass
    elif c in ['5', 'q']:  # Logout
      if currentName is None:
        warn('You are not logged in.')
        continue

      info(f'Goodbye, {currentName}!')
      currentName = None
      currentID = None
      pass
    else:
      error(f'Invalid command {Fore.GREEN}"{c}"')
      warn('please check the guide:')
      debug(__guide__)
      pass

  return


@App.callback(invoke_without_command=True)
def main(
  version: Annotated[Optional[bool], typer.Option('-v', '--version', callback=version_callback)] = None,
) -> None:
  __doc__ = """💕 Welcome to this cli app! 💕
🚀 run `--help` to see available commands. 🚀
"""

  info(__doc__)
  return


if __name__ == '__main__':
  App()
  pass
