Data Wrangling 数据整理，把数据整理成你想要的形式，在 linux 中，每次使用 `|`都是一次数据整理，比如`journalctl | grep -i intel`，虽然这条命令的意思是从系统日志中找出带有 intel 的行，但这也是一种数据整理，删除了一些冗余数据。

下面使用 linux 中的日志文件作为 wrangling 的数据，下面是几个例子：

- `ssh myserver journalctl | grep sshd`：登录远程服务器，在远程服务器上执行 `journalctl` ，通过 ssh 将数据传送到本地，然后通过 `|` 传给本地 `grep sshd` 进行处理；

- `ssh myserver 'journalctl | grep sshd | grep "Disconnected from"' | less`：
  - 单引号中的内容是在远程服务器上执行的命令。日志文件非常多，未经处理就通过 ssh 传输到本地有点浪费传输流量，可以在远程服务器上对数据进行整理后再传输到本地；
  - `less` 以阅读模式显示长文本；

- `ssh myserver journalctl | grep sshd | grep "Disconnected from" | sed 's/.*Disconnected from //'`
  - `sed`是 stream editor(流编辑器？) ，它基于 `ed`，你可以通过`sed`中的命令对文件进行修改，它的命令有很多，最常用的是 `s`(substitution, 替代)；
  - `s` 的格式 `s/REGEX/SUBTITUTION/`，`REGEX` 为正则表达式，`SUBTITUTION` 用来替换文本；
  - `sed 's/.*Disconnected from//'` 的意思为，将包括`Disconnected from `在内的之前的内容用空字符替代，即只保留`Disconnected from `后面内容；



### Regular expressions
参考网站：[regexone](https://regexone.com/)


