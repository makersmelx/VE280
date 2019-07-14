## 配置
```
chmod 777 app.sh
chmod 777 diff.sh
```
出现问题前头加sudo


## 用法
```
usage ./app [username] [execute program] [human vs human input dir] [human myOpic input dir]
usage ./diff.sh [use1] [user2]
```

## 结果
有不一样的就会在diff_detail输出一个diff -y的细节
一样就没输出，linux经典逻辑