## Topic 1: The Shell(bash)

### Using the shell

```
missing:~$ 
```

- `missing`：机器名；	`~`：当前工作目录；	
- `$`：当前用户不是root用户，在其后可以输入命令，最基本的命令是执行程序；

```
missing:~$ date
Fri 10 Jan 2020 11:49:31 AM EST
missing:~$ 
```

- 输入date命令，执行date程序，执行完之后，shell等待下一条命令的输入；

```
missing:~$ echo hello
hello
missing:~$ 
```

- 输入echo命令及参数，执行echo程序，执行完之后，shell等待下一条命令的输入；

- shell是如何解析带参数的命令的？

  > The shell parses the command by splitting it by whitespace, and then runs the program indicated by the first word, supplying each subsequent word as an argument that the program can access.

- 参数中带空格如何处理？

  > you can either quote the argument with `'` or `"` (`"My Photos"`), or escape just the relevant characters with `\` (`My\ Photos`).

- shell是如何找到date/echo程序的？

  > shell执行echo命令时，在$PATH的以 : 分隔的文件夹列表中搜索程序，找到后执行程序；
  >
  > 可以通过which找到程序在哪个文件夹下，绕过$PATH直接通过程序所在位置执行程序；

```
missing:~$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
missing:~$ which echo
/bin/echo
missing:~$ /bin/echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
```

### Navigating in the shell

- A path on the shell is a delimited list of directories；

- linux和macOS中用`/`进行分隔、windows中用`\`进行分隔，linux和macOS的根目录为`/`、windows中每个磁盘都有一个根目录(e.g. `C:\`)

- 绝对路径：以根目录起始；相对路径：相对于当前工作目录的路径

- 常用的和目录有关的bash命令：

  - `pwd`：查看当前工作目录的绝对路径；

  - `cd <directory_path>`：打开目录；directory_path可以是相对路径也可以是绝对路径；

  - `.`表示当前目录；`..`表示当前目录的父目录；

    > 注意`cd /home`和`cd ./home`的区别

```
missing:/home/acs$ ls
home
missing:/home/acs$ pwd
/home/acs
missing:/home/acs$ cd ./home
missing:/home/acs/home$ cd /home
missing:/home$ cd ..
missing:/$
```



- when we run a program, it will operate in the current directory unless we tell it otherwise.

```
missing:~$ ls
missing:~$ ls /
bin dev home lib32 ...
```

- Most commands accept flags and options (flags with values) that start with `-` to modify their behavior；
- Usually, running a program with the `-h` or `--help` flag will print some help text that tells you what flags and options are available.

```
missing:~$ ls -l /home
drwxr-xr-x 1 missing  users  4096 Jun 15  2019 missing
missing:~$ ls --help
Usage: ls [OPTION]... [FILE]...
List information about the FILEs (the current directory by default).
Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.
......
```

- `ls -l [directory_path]`：提供某路径下的文件或文件夹的具体信息；例如上例中，`d`表示`missing`是一个目录；后面的三组`rwx`分别表示文件所有者、用户组和所有人对这个文件所拥有的权限；`-`表示没有分配权限；`w`可以对文件内容进行修改、可以在文件夹内创建和删除文件夹/文件；`x`要想进入一个目录，用户则必须对这个文件夹具有`x`权限；`r`要想知道文件夹的内容，用户则必须对这个文件夹具有`r`权限；



### Connecting programs

- In the shell, programs have two primary “streams” associated with them: their input stream and their output stream. Normally, a program’s input and output are both your terminal. However, we can also rewire those streams!

-  The simplest form of redirection is `< file` and `> file`. These let you rewire the input and output streams of a program to a file respectively:

  ```
  missing:~$ echo hello > hello.txt
  missing:~$ cat hello.txt
  hello
  missing:~$ cat < hello.txt
  hello
  missing:~$ cat < hello.txt > hello2.txt
  missing:~$ cat hello2.txt
  hello
  ```

  > cat < hello.txt和cat hello.txt的区别：输出结果相同，都为hello，但是输入数据的来源不同，前者是将txt的内容重定向为标准输入，然后再传递给cat命令；后者是直接将txt的内容作为标准输入传递给cat

- You can also use `>>` to **append** to a file. Where this kind of input/output redirection really shines is in the use of *pipes*. The `|` operator lets you “chain” programs such that the output of one is the input of another:

  ```
  missing:~$ ls -l / | tail -n1
  drwxr-xr-x 1 root  root  4096 Jun 20  2019 var
  missing:~$ curl --head --silent google.com | grep --ignore-case content-length | cut --delimiter=' ' -f2
  219
  ```



### A versatile and powerful tool

- 在一个Unix-like系统中，root用户对任意文件都有所有的权限，一般不直接使用root登录系统进行使用(怕出现错误)，而是作为普通用户进行登录，使用`sudo`命令来申请root权限，例如，`sudo ls`使用root权限执行`ls`命令；
- `/sys`下的文件只有用root权限才能进行修改，下面是修改`/sys`文件易出现的一个错误；

```
$ cd /sys/class/backlight/thinkpad_screen
$ sudo echo 3 > brightness
An error occurred while redirecting file 'brightness'
open: Permission denied
```

>Operations like `|`, `>`, and `<` are done *by the shell*, not by the individual program. In the case above, the *shell* (which is authenticated just as your user) tries to open the brightness file for writing, before setting that as `sudo echo`’s output, but is prevented from doing so since the shell does not run as root. Using this knowledge, we can work around this:

```
echo 3 | sudo tee brightness
```

- `tee [OPTION]...[FILE]...` ：Copy standard input to each FILE, and also to standard output.







