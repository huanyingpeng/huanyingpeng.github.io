---
title: Hexo-NexT 安装踩坑记录
mathjax: true
date: 2022-07-12 16:22:10
tags:
- 踩坑记录
categories:
- 技术
- 踩坑记录
---

## Hexo-NexT 安装踩坑记录

### 背景图片设置

在 `.\themes\next\_config.yml` 设置好 `custom_file_path` 的 `style` 属性后，那个路径里面的 `/source/_data/styles.styl` 要建在根目录的 `source` 下而不是 `.\themes\next` 目录下的

### CNAME 文件部署时被覆盖

[解决方式](http://eronana.github.io/2014/11/07/Hexo%E9%83%A8%E7%BD%B2%E5%90%8ECNAME%E8%A2%AB%E8%A6%86%E7%9B%96%E7%9A%84%E8%A7%A3%E5%86%B3%E6%96%B9%E6%B3%95/)

将 `CNAME` 放入 `./source`，即存在 `./source/CNAME` 文件。
