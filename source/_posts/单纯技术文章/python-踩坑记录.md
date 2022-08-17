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

### airtest

