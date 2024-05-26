# -*- coding: utf-8 -*-
from re import findall
import os
import sys
import zipfile
from pathlib import Path

from dotenv import load_dotenv

env_path = Path('.') / '.env'
load_dotenv(dotenv_path=env_path, verbose=True)

studentID = os.getenv('STUDENT_ID')
studentName = os.getenv('STUDENT_NAME')
studentEmail = os.getenv('STUDENT_EMAIL')

rank_dict = {
  '1': '一',
  '2': '二',
  '3': '三',
  '4': '四',
  '5': '五',
  '6': '六',
  '7': '七',
  '8': '八',
  '9': '九',
}
file_exclude = ['__pycache__', '.ipynb_checkpoints']


def zip_dir(folder_path, zip_path, rank):
  with zipfile.ZipFile(zip_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
    for root, _, files in os.walk(folder_path):
      for file in files:
        if any([exclude in root for exclude in file_exclude]):
          continue
        file_path = os.path.join(root, file)
        zipf.write(file_path, os.path.relpath(file_path, folder_path))
    test_file_path = os.path.join(os.path.join(os.getcwd(), '__tests__'), f'test_chapter{rank}.py')
    zipf.write(test_file_path, os.path.relpath(test_file_path, os.path.join(os.getcwd(), '__tests__')))


def main():
  zip_path = sys.argv[1]
  rank = findall(r'\d+', zip_path)[0]
  target_file_name = f'{studentID}_{studentName}_第{rank_dict[rank]}章作业.zip'
  target_path = os.path.join(os.path.join(os.getcwd(), '.dist'), target_file_name)
  zip_dir(zip_path, target_path, rank)


if __name__ == '__main__':
  main()
