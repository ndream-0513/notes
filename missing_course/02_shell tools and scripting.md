### Shell Scripting

- assign variables：`foo=bar`；access the value of the variable with `$foo`；

  >`foo=bar`$\neq$`foo = bar`, first is assign var, last is excuting foo with arguments `=` and `bar`;
  >
  >In general, in shell scripts the space character will perform argument splitting;

- Strings delimited with `'` are literal strings and will not substitute variable values whereas `"` delimited strings will.

  ```bash
  foo=bar
  echo "$foo"
  # prints bar
  echo '$foo'
  # prints $foo
  ```

- bash supports control flow techniques including `if`, `case`, `while` and `for`. Similarly, `bash` has functions that take arguments and can operate with them. Here is an example of a function that creates a directory and `cd` into it.

  ```bash
  mcd () {
      mkdir -p "$1"
      cd "$1"
  }
  ```

  > $1是脚本/函数的第一个参数；bash使用一系列特殊的变量来指代参数、错误码和其它相关的变量，以下是一些常用的特殊变量的含义：
  >
  > - `$0` - Name of the script
  >
  > - `$1` to `$9` - Arguments to the script. `$1` is the first argument and so on.
  > - `$@` - All the arguments
  > - `$#` - Number of arguments
  > - `$?` - Return code of the previous command
  > - `$$` - Process identification number (PID) for the current script
  > - `!!` - Entire last command, including arguments. A common pattern is to execute a command only for it to fail due to missing permissions; you can quickly re-execute the command with sudo by doing `sudo !!`
  > - `$_` - Last argument from the last command. If you are in an interactive shell, you can also quickly get this value by typing `Esc` followed by `.` or `Alt+.`

- Commands will often return output using `STDOUT`, errors through `STDERR`. A value of 0 usually means everything went OK; anything different from 0 means an error occurred.

- Exit codes can be used to conditionally execute commands using `&&` (and operator) and `||` (or operator), both of which are [short-circuiting](https://en.wikipedia.org/wiki/Short-circuit_evaluation) operators. Commands can also be separated within the same line using a semicolon `;`.

  ```bash
  false || echo "Oops, fail"
  # Oops, fail
  
  true || echo "Will not be printed"
  #
  
  true && echo "Things went well"
  # Things went well
  
  false && echo "Will not be printed"
  #
  
  true ; echo "This will always run"
  # This will always run
  
  false ; echo "This will always run"
  # This will always run
  ```

- 另一个常见的用法是将命令的输出做为变量；`for file in $(ls)`，先执行`ls`，再将`ls`的结果进行遍历；

- A lesser known similar feature is *process substitution*, `<( CMD )` will execute `CMD` and place the output in a temporary file and substitute the `<()` with that file’s name.This is useful when commands expect values to be passed by file instead of by STDIN. 

  ```bash
  diff <(ls foo) <(ls bar) # show differences between files in dirs foo and bar
  ```

  ```bash
  # It will iterate through the arguments we provide, grep for the string foobar, and append it to the file as a comment if it’s not found.
  #!/bin/bash
  
  echo "Starting program at $(date)" # Date will be substituted
  
  echo "Running program $0 with $# arguments with pid $$"
  
  for file in "$@"; do
      grep foobar "$file" > /dev/null 2> /dev/null
      # When pattern is not found, grep has exit status 1
      # We redirect STDOUT and STDERR to a null register since we do not care about them
      # 2 is STDERR
      if [[ $? -ne 0 ]]; then
          echo "File $file does not have any foobar, adding one"
          echo "# foobar" >> "$file"
      fi
  done
  ```

  - When performing comparisons in bash, try to use double brackets `[[ ]]` in favor of simple brackets `[ ]`. Chances of making mistakes are lower although it won’t be portable to `sh`. A more detailed explanation can be found [here](http://mywiki.wooledge.org/BashFAQ/031).

- **shell globbing**：通过文件名扩展来扩展表达式，可以得到许多相似的参数

  - 通配符(Wildcards)：`?`可匹配一个字符，`*`可匹配任意个字符，例如有`foo`、`foo1`、`foo2`、`foo10`、`bar`这五个文件，使用`rm foo?`可以删除`foo1`和`foo2`文件，而使用`rm foo*`可以删除前四个文件；
  - `{}`(Curly braces)： Whenever you have a common substring in a series of commands, you can use curly braces for bash to expand this automatically.

  ```bash
  convert image.{png,jpg}
  # Will expand to
  convert image.png image.jpg
  
  cp /path/to/project/{foo,bar,baz}.sh /newpath
  # Will expand to
  cp /path/to/project/foo.sh /path/to/project/bar.sh /path/to/project/baz.sh /newpath
  
  # Globbing techniques can also be combined
  mv *{.py,.sh} folder
  # Will move all *.py and *.sh files
  
  
  mkdir foo bar
  # This creates files foo/a, foo/b, ... foo/h, bar/a, bar/b, ... bar/h
  touch {foo,bar}/{a..h}
  touch foo/x bar/y
  # Show differences between files in foo and bar
  diff <(ls foo) <(ls bar)
  # Outputs
  # < x
  # ---
  # > y
  ```

  > 可使用[shellcheck](https://github.com/koalaman/shellcheck)来检查sh/bash脚本中的错误

- shell函数和脚本之间的一些区别：（**有问题！！！**）

  - shell函数和shell使用相同的语言；脚本可以用任何语言进行编写(这也是脚本中为什么又shebang的原因)
  - shell函数在当前的shell环境中执行而脚本由它自己的程序执行；shell函数可以直接改变环境变量而脚本需要使用`export`才能进行改变；




### Shell Tools

### Finding how to use commands

- `-h`、`--help`、`man`
- 对于一些交互式的工具可以使用`:hlep`或`?`
- [TLDR pages](https://tldr.sh/)（比`manpages`更简洁更实用，有网页、有命令行...）

#### Finding files

- 所有的UNIX-like系统中都有`find`命令，它可以根据匹配规则递归的对文件进行搜索，以下是一些使用`find`的例子：

  ```bash
  # Find all directories named src
  find . -name src -type d
  # Find all python files that have a folder named test in their path
  find . -path '*/test/*.py' -type f
  # Find all files modified in the last day
  find . -mtime -1
  # Find all zip files with size in range 500k to 10M
  find . -size +500k -size -10M -name '*.tar.gz'
  ```

- 除了找文件，`find`还可以对文件进行操作

  ```bash
  # Delete all files with .tmp extension
  find . -name '*.tmp' -exec rm {} \;
  # Find all PNG files and convert them to JPG
  find . -name '*.png' -exec convert {} {}.jpg \;
  ```

- 可以通过`alias fd='find'`为`find`命令起别名，便于`find`命令的使用

- `locate`也可以查找文件，速度比`find`要快，但是很少使用`locate`，`locate`只能使用文件名进行搜索，而`find`可以根据各种属性进行搜索，例如，文件大小、修改时间或文件权限；In most systems, `updatedb` is updated daily via [`cron`](https://www.man7.org/linux/man-pages/man8/cron.8.html)(`locate`基于`updatedb`不知道这句话的意思是不是说`locate`的`updatedb`每天只更新一次)，`find`是实时的，更具时效性；

  

### Finding code

- 一般使用`grep`对文件中的内容进行搜索；

- `grep -C 5 [pattern] [file]`，输出匹配行的前五行和后五行；

- `grep -v [pattern] [file]`，输出不匹配的行；

- `grep -R [pattern] [directory]`，根据匹配规则递归搜索目录中的文件，无具体目录时默认为当前目录；

- [ack](https://github.com/beyondgrep/ack3), [ag](https://github.com/ggreer/the_silver_searcher) and [rg](https://github.com/BurntSushi/ripgrep)，`grep`的一些替代品，下面是`rg`命令的一些用法：

  ```bash
  # Find all python files where I used the requests library
  rg -t py 'import requests'
  # Find all files (including hidden files) without a shebang line
  rg -u --files-without-match "^#\!"
  # Find all matches of foo and print the following 5 lines
  rg foo -A 5
  # Print statistics of matches (# of matched lines and files )
  rg --stats PATTERN
  ```

  > 感觉第二个语句有问题，rg -u不能搜索隐藏文件中的内容，只有使用rg -uu才能搜索隐藏文件中的内容



### Finding shell commands

- 在shell中按向上的箭头可以得到曾经使用过的命令，每次显示一条；
- 在shell中输入`history`，以列表的形式显示近期使用过的命令；
- `Ctrl + R` + [fzf](https://github.com/junegunn/fzf/wiki/Configuring-shell-key-bindings#ctrl-r)，对使用过的命令进行模糊搜索，具体还不知道怎么使用（**？？？**）
- **history-based autosuggestions**，不知道怎么用，好像只有`zsh`才有（**？？？**）
- 可以修改`.bash_history`或`.zsh_history`文件来决定是否省略前导的空格；通过修改`.bashrc`的`HISTCONTROL=ignorespace`或`.zshrc`的`setopt HIST_IGNORE_SPACE`可以忽略输入的空格；



### Directory Navigation

- How do you go about quickly navigating directories? 
- writing shell aliases or creating symlinks with [ln -s](https://www.man7.org/linux/man-pages/man1/ln.1.html)；
- Finding frequent and/or recent files and directories can be done through tools like [`fasd`](https://github.com/clvv/fasd) and [`autojump`](https://github.com/wting/autojump)；
- More complex tools exist to quickly get an overview of a directory structure: [`tree`](https://linux.die.net/man/1/tree), [`broot`](https://github.com/Canop/broot) or even full fledged file managers like [`nnn`](https://github.com/jarun/nnn) or [`ranger`](https://github.com/ranger/ranger).

  

  

