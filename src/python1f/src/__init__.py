from typing import Optional
from typing_extensions import Annotated

import typer

__version__ = '0.0.1'

App = typer.Typer()


def version_callback(value: bool):
  if value:
    print(f'CLI Version: {__version__}')
    raise typer.Exit()
  pass


@App.command()
def hello(name: Annotated[str, typer.Option('-n', '--name')] = None):
  """
  Test text.
  """
  if name:
    print(f'Hello {name}')
    raise typer.Exit()
  pass


@App.callback(invoke_without_command=True)
def main(
  version: Annotated[Optional[bool], typer.Option('-v', '--version', callback=version_callback)] = None,
) -> None:
  __doc__ = """💕 Welcome to this cli app! 💕
🚀 run `--help` to see available commands. 🚀"""
  print(__doc__)
  pass


if __name__ == '__main__':
  App()
