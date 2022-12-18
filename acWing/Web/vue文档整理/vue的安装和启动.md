---
title: vue的安装和启动
date: 2022-11-14 22:54:37
tags: 工具
---

#### 1. 安装`nodejs`

- 在官网下载安装包，按照默认选项安装，安装`nodejs` 安装完毕后，用管理员启动`cmd`，`nodejs`的安装目录在`D:\nodejs\nodejs`

  1. 检查
     `node -v`
     `npm -v`

  2. 创建两个目录：
     `D:\nodejs\nodejs\node_cache`
     `D:\nodejs\nodejs\node_global`

  3. 设置`global cache`路径
     `npm config set prefix "D:\nodejs\nodejs\node_global"`
     `npm config set cache "D:\nodejs\nodejs\node_cache"`

  4. 修改用户的环境变量
     `Path`中添加`D:\nodejs\nodejs\node_global`

  5. 修改系统变量
     添加：`NODE_PATH`、`D:\nodejs\nodejs\node_global\node_modules`
     添加：`Path`  `D:\nodejs\nodejs\node_global` `D:\nodejs\nodejs`

  6. 修改镜像
     `npm config get registry`
     `npm config set registry https://registry.npm.taobao.org/`
     `npm config get registry`
     `npm install -g cnpm --registry=https://registry.npm.taobao.org`

#### 2. 安装vue

- 安装：`cnpm install -g @vue/cli`
- 启动：`vue ui`

#### 3. 常见问题及建议

使用建议：使用`vue ui`时，建议从存放`vue`项目的文件夹打开，也就是先管理员打开终端，然后终端`cd`到项目文件夹，然后再输入`vue ui`命令，不然有可能会出现项目管理一直在加载路径

常见问题1：`Windows`上运行`vue`，提示无法加载文件，表示用户权限不足。

解决方案：用管理员身份打开终端，输入`set-ExecutionPolicy RemoteSigned`，然后输入`y`

常见问题2：`vue`项目管理器一直都在加载的解决方法

解决方案：不用管理身份启动`powershell`，或使用上面的建议使用`vue ui`

#### 4. 仪表盘的使用

参考这个链接：[Vue3 v5.0.8——下载和安装过程 - AcWing](https://www.acwing.com/file_system/file/content/whole/index/content/6326802/)

