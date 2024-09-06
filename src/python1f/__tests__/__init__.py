def snapshot(*args, target='', **kwargs) -> None:
  filename = f'__tests__/__snapshots__/{target}.snap'
  with open(filename, 'a') as f:
    print(*args, file=f, **kwargs)
    pass
  return
