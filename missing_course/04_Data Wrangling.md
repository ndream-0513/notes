这一节中使用linux中的日志文件作为wrangling的数据，下面是一个例子：

`journalctl | grep -i intel`：finds all system log entries that mention Intel (case insensitive)

`ssh myserver journalctl | grep sshd`：登录远程服务器，在远程服务器上执行`journalctl`通过管道传输到本地，相当于`ssh myserver`，然后在服务器上执行`journalctl | grep sshd`输出内容，退出服务器

`ssh myserver 'journalctl | grep sshd | grep "Disconnected from"' | less`：单引号中的内容是在远程服务器上执行的命令

`ssh root_hx journalctl | grep sshd | grep "Disconnected from" | sed 's/.*Disconnected from //'`：`s`是sed中最常用的命令，格式为`s/REGEX/SUBTITUTION/`，`REGEX`为正则表达式，`SUBTITUTION`用来替换文本



### Regular expressions

