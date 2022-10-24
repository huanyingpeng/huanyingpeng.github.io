---
title: python 踩坑记录
mathjax: true
date: 2022-07-12 16:28:24
tags:
- 踩坑记录
- python
categories:
- 技术
- 踩坑记录
---

### pip 和包

- 用 pip 安装包时，windows 会出各种各样的问题，请关闭代理并使用国内源安装
- 将所有包放在系统 python 中是一个坏习惯，python 各种包的有复杂的版本依赖关系，请使用 anaconda 或者 virtualenv 等包管理器。
- 如果你没有 `install` 一个包，那么只能在包的父目录下直接 `import` 它，其它位置不能引入，如果 `install` 了，那么你在该环境中任何位置都可以用了，相当于加入了 `sys.path`。

### airtest

### import

正常情况下，一个项目中，同一文件被引用两次，那么只会在第一次执行。

但是如果你乱改 `sys.path`，然后在 `__init__.py` 里直接用 `import xxx` 引入，然后再在外面乱引入，就有可能被引入多次。

