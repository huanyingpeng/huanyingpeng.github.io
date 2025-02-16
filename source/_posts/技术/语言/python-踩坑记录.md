---
title: python 踩坑记录
mathjax: true
date: 2022-07-12 16:28:24
tags:
- python
categories:
- 技术
---

### pip 和包

- 用 pip 安装包时，windows 会出各种各样的问题，请关闭代理并使用国内源安装
- 将所有包放在系统 python 中是一个坏习惯，python 各种包的有复杂的版本依赖关系，请使用 anaconda 或者 virtualenv 等包管理器。
- 如果你没有 `install` 一个包，那么只能在包的父目录下直接 `import` 它，其它位置不能引入，如果 `install` 了，那么你在该环境中任何位置都可以用了，相当于加入了 `sys.path`。

### airtest

### import

正常情况下，一个项目中，同一文件被引用两次，那么只会在第一次执行。

但是如果你乱改 `sys.path`，然后在 `__init__.py` 里直接用 `import xxx` 引入，然后再在外面乱引入，就有可能被引入多次。

### 关于 Request 这一类网络请求函数

Python 的 Requests 包对请求做了一些包装，但是 NodeJS的 Request 没有这种包装。

因此可能会引发一些 403 问题（比如 Python 的 Requests 可以正常用但 NodeJS 的 Request 不行），可以输出一下它们的 headers 看看最终发出的请求长什么样子。

这是 Python。

```yaml
{
	'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Safari/537.36', 
	'Accept-Encoding': 'gzip, deflate', 
	'Accept': '*/*', 
	'Connection': 'keep-alive'
}
```

这是 JS。

```yaml
{
  'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Safari/537.36'
}
```

headers:

```yaml
headers = {
	'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Safari/537.36',
}
```

nodejs 的 request 由于太过常用，已经被一些服务器加入了黑名单，方式是通过建立 https 时的一些 ciphers 来判别是否属于爬虫，容易发生 403。

[参考资料](https://pixeljets.com/blog/bypass-cloudflare/)

