# hw7

```bash
#!/bin/bash

targetFolder='/tmp'

if [ ! -e $targetFolder ]; then
  sudo mkdir $targetFolder
fi

for ((i = 1; i <= 3; i++))
do
  if [ ! -e "$targetFolder/dir$i" ]; then
    sudo mkdir $targetFolder/dir$i
  fi
done

cd /tmp/

if [ -e '/etc/pam.d/' ]; then
  cp -r /etc/pam.d/ ./test/ && chmod 750 -R test/
fi

# 鉴于 /etc/pam.d/ 文件夹下没有嵌套文件夹，因而不做文件类型判断
for file in `ls -l ./test/ | awk '{if($5>100) {print $9}}'`
do
  mv ./test/$file ./dir1
done
```
