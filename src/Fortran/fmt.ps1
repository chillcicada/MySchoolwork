Get-ChildItem -Path . -Recurse -Filter *.F90 |
  ForEach-Object {
    fprettify $_.FullName
  }
