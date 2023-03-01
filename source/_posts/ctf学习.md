---
title: ctf学习
mathjax: true
date: 2023-02-13 15:13:41
tags:
categories:
---



## Web

### Basic Auth

Basic Auth 是一种在头部提供验证账户和密码的方式，具体的，需要在 headers 参数中加入 Authorization 字端，其值为 `[验证方式] [Base64 编码的账号和密码]`。

[参考](https://zh.wikipedia.org/wiki/HTTP%E5%9F%BA%E6%9C%AC%E8%AE%A4%E8%AF%81)

**部分验证会忽略 Base64 的 =，所以爆破前先检查真实方式是否有 =。**

### 数据泄露

通过爆破网站根目录下可能的备份文件获取网站文件目录结构和源码

通过访问 {源代码名}.bak 获取网页源码。

当开发人员在线上环境中使用 vim 编辑器，在使用过程中会留下 vim 编辑器缓存，当vim异常退出时，缓存会一直留在服务器上，引起网站源码泄露。
