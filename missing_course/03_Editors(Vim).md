### Philosophy of Vim

Vim’s design is based on the idea that a lot of programmer time is spent reading, navigating, and making small edits, as opposed to writing long streams of text. For this reason, Vim has multiple operating modes.

- **Normal**: for moving around a file and making edits（default）
- **Insert**: for inserting text（`i`/`a`）
- **Replace**: for replacing text（`R`）
- **Visual** (plain, line, or block): for selecting blocks of text（plain`v`、line`V`、block`<C-v>/Ctrl-V/^V`）
- **Command-line**: for running a command（`:`）

You change modes by pressing `<ESC>` (the escape key) to switch from any mode back to Normal mode. You use the `<ESC>` key a lot when using Vim: consider remapping Caps Lock to Escape； 



### Basics

Vim maintains a set of open files, called “buffers”. A Vim session has a number of tabs, each of which has a number of windows (split panes). Each window shows a single buffer. Unlike other programs you are familiar with, like web browsers, there is not a 1-to-1 correspondence between buffers and windows; windows are merely views. A given buffer may be open in *multiple* windows, even within the same tab. This can be quite handy, for example, to view two different parts of a file at the same time.

> `:split`上下split window；`:vsplit`左右split window
>
> `vim -o file1 file2`同时打开多个文件，上下分开，-O，左右分开
>
> `Ctrl F` scroll the window forward；`Ctrl B` scroll the window backward；
>
> `Ctrl n` create a brand new window with a new file，`Ctrl + N` create a new split window vertically（未成功使用过）
>
> Switching Between Split Windows in Vim：Ctrl W + k/j/h/l(vim movement key commands)
>
> Opening Terminal Windows in Vim：`:!ls`在当前目录执行ls，`:terminal`在vim中新增一个shell窗口，可以在该窗口中输入exit关闭窗口
>
> Resizing Split Windows in Vim：`Ctrl + W + Plus`、`Ctrl + W + Minus`，You can also specify the size of a window ahead of time by prefixing the `:split` command with the number of lines you want the window to be.

#### Quitting and Help in Vim

- `:q` quit (close window)

- `:w` save (“write”)

- `:wq` save and quit

- `:e {name of file}` open file for editing

- `:ls` show open buffers

- `:help {topic}` open help
  - `:help :w` opens help for the `:w` command
  - `:help w` opens help for the `w` movement

#### Movement in Vim

- Basic movement: `hjkl` (left, down, up, right)

- Words: `w` (beginning of next word), `b` (beginning of previous word), `e` (end of next word), `ge`(end of previous word)

- Lines: `0` (beginning of line), `^` (first non-blank character), `$` (end of line)

- Screen: `H` (top of screen), `M` (middle of screen), `L` (bottom of screen)

- Scroll: `Ctrl-u` (up), `Ctrl-d` (down)

- File: `gg` (beginning of file), `G` (end of file)，`ggyG`全部复制，`ggdG`全部删除

- Line numbers: `:{number}<CR>` or `{number}G` (line {number})

- Misc: `%` (corresponding item)

- Find: `f{character}`, `t{character}`, `F{character}`, `T{character}`
  - find/to forward/backward {character} on the current line
  - `,` / `;` for navigating matches
  
- Search: `/{regex}`, `n` / `N` for navigating matches

  > 清除搜索之后的高亮：`:noh`、`set nohlsear

#### Selection

Visual modes: Visual: `v`; Visual Line: `V`; Visual Block: `Ctrl-V`，Can use movement keys to make selection.



#### Edits

- `i` enter Insert mode
  - but for manipulating/deleting text, want to use something more than backspace
- `o` / `O` insert line below / above
- `d{motion}`delete {motion}
  - e.g. `dw` is delete word, `d$` is delete to end of line, `d0` is delete to beginning of line
- `c{motion}`change {motion}
  - e.g. `cw` is change word
  - like `d{motion}` followed by `i`
- `x` delete character (equal do `dl`)
- `s` substitute character (equal to `cl`)
- Visual mode + manipulation
  - select text, `d` to delete it or `c` to change it
- `u` to undo, `<C-r>` to redo
- `y` to copy / “yank” (some other commands like `d` also copy)
- `p` to paste
- Lots more to learn: e.g. `~` flips the case of a character(大小写转换)

#### Counts

- `3w` move 3 words forward
- `5j` move 5 lines down
- `7dw` delete 7 words

#### Modifiers

You can use modifiers to change the meaning of a noun. Some modifiers are `i`, which means “inner” or “inside”, and `a`, which means “around”.

- `ci(` change the contents inside the current pair of parentheses（这个没有效果**？？？**）
- `ci[` change the contents inside the current pair of square brackets
- `da'` delete a single-quoted string, including the surrounding single quotes



### Customizing Vim

Vim is heavily customizable, and it’s worth spending time exploring customization options. You can look at people’s dotfiles on GitHub for inspiration, for example, your instructors’ Vim configs ([Anish](https://github.com/anishathalye/dotfiles/blob/master/vimrc), [Jon](https://github.com/jonhoo/configs/blob/master/editor/.config/nvim/init.vim) (uses [neovim](https://neovim.io/)), [Jose](https://github.com/JJGO/dotfiles/blob/master/vim/.vimrc)). There are lots of good blog posts on this topic too. Try not to copy-and-paste people’s full configuration, but read it, understand it, and take what you need.



### Extending Vim

There are tons of plugins for extending Vim. Contrary to outdated advice that you might find on the internet, you do *not* need to use a plugin manager for Vim (since Vim 8.0). Instead, you can use the built-in package management system. Simply create the directory `~/.vim/pack/vendor/start/`, and put plugins in there (e.g. via `git clone`).

Here are some of our favorite plugins:

- [ctrlp.vim](https://github.com/ctrlpvim/ctrlp.vim): fuzzy file finder
- [ack.vim](https://github.com/mileszs/ack.vim): code search
- [nerdtree](https://github.com/scrooloose/nerdtree): file explorer
- [vim-easymotion](https://github.com/easymotion/vim-easymotion): magic motions

We’re trying to avoid giving an overwhelmingly long list of plugins here. You can check out the instructors’ dotfiles ([Anish](https://github.com/anishathalye/dotfiles), [Jon](https://github.com/jonhoo/configs), [Jose](https://github.com/JJGO/dotfiles)) to see what other plugins we use. Check out [Vim Awesome](https://vimawesome.com/) for more awesome Vim plugins. There are also tons of blog posts on this topic: just search for “best Vim plugins”.



### Advanced Vim

Search and replace、Multiple windows(`:sp`/`:vsp`、Marcros(宏命令)



### Resources

- `vimtutor` is a tutorial that comes installed with Vim - if Vim is installed, you should be able to run `vimtutor` from your shell
- [Vim Adventures](https://vim-adventures.com/) is a game to learn Vim
- [Vim Tips Wiki](http://vim.wikia.com/wiki/Vim_Tips_Wiki)
- [Vim Advent Calendar](https://vimways.org/2019/) has various Vim tips
- [Vim Golf](http://www.vimgolf.com/) is [code golf](https://en.wikipedia.org/wiki/Code_golf), but where the programming language is Vim’s UI
- [Vi/Vim Stack Exchange](https://vi.stackexchange.com/)
- [Vim Screencasts](http://vimcasts.org/)
- [Practical Vim](https://pragprog.com/titles/dnvim2/) (book)
