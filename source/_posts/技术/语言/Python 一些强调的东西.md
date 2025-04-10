---
title: Python 一些强调的东西
mathjax: true
date: 2022-07-12 16:28:24
tags:
- Python
- 网络
categories:
- 技术
---

## pip 和包

### 网络问题

GFW 会墙掉默认的 pip 源, 所以请使用国内源.

**不建议使用代理连接国外源.**

使用国内源时一些注意事项:

- **彻底关闭代理软件**(退出软件, 关 System Proxy 没用), 并检查系统代理设置, 确认没有设置代理端口.
	由它引起的报错:
	
	- SSL 错误(报错大概长下面这样), 国内源不允许代理连接, 用的 TLS 方式, 代理的 SSL 证书通不过验证.
	
	```shell
	WARNING: Retrying (Retry(total=4, connect=None, read=None, redirect=None, status=None)) after connection broken by 'SSLError(SSLEOFError(8, '[SSL: UNEXPECTED_EOF_WHILE_READING] EOF occurred in violation of protocol (_ssl.c:1000)'))': /simple/proxyscrape/
	```
	- Proxy 连接错误(报错大概长下面这样). 原因是命令行代理没有配置好, 但是 pip 检测到了系统有代理尝试使用.
	
	```shell
	WARNING: Retrying (Retry(total=4, connect=None, read=None, redirect=None, status=None)) after connection broken by 'ProxyError('Cannot connect to proxy.', timeout('_ssl.c:1091: The handshake operation timed out'))': /simple/pandas/
	```
- 清华源同步很慢, 速度不稳定, 建议使用阿里云源, 命令行执行(永久设置):

    ```shell
    pip config set global.index-url https://mirrors.aliyun.com/pypi/simple/
    pip config set global.trusted-host mirrors.aliyun.com
    ```
- 检查全局源设置:
 
  ```shell
	pip config list
  ```
  输出应该是:
  ```shell
	global.index-url='https://mirrors.aliyun.com/pypi/simple'
	install.trusted-host='mirrors.aliyun.com'
  ```


### 虚拟环境

Python 包各种包的有复杂的版本依赖关系, 把所有包装在一起不可取.

建议安装个 anaconda 创建虚拟环境, 然后在虚拟环境里安装包.

anaconda [安装教程](https://zhuanlan.zhihu.com/p/75717350?utm_source=wechat_session&utm_medium=social&utm_oi=940926592332066816).

额外提几个注意:

- 安装 conda 前, 应该**彻底卸载**之前安装的 Python, 直接用卸载功能不会删除 pip 相关的包, 正确的卸载方式:
  
  1. 找到并记住安装路径.
  
  2. 用卸载程序(就是安装包)卸载.
  
  3. 彻底删除安装路径.

- 第一次安装 conda 完成后, 必须在终端执行 `conda init` 命令使 conda 生效. 

### 局部环境

虚拟环境本质上就是建立了若干个局部环境, 并使用一个全局的管理工具来管理这些局部环境.

所以也可以直接建立局部环境, Python 的标准库有个 venv, 就是用局部环境来做虚拟环境的.

局部环境也可以用安装包安装, **不要勾选添加系统路径**, 然后自定义安装路径就能安装 Windows 的 Python 局部环境.

Linux 下安装 Python 局部环境

用局部环境的路径去运行 pip, Python 时, 所有操作都会在这个局部环境里执行, 与全局环境无关.

理论上这个东西在制作傻瓜式软件的时候有一定作用, 但根据我的经验, 虽然可能全国有 1% 的人会 Python, 但全国只有 0.1% 的人能够正确安装小众的 Python 第三方库, 所以还是很有用的.

~~上周见到两个 conda 装了不 init 的胎神.~~

## import

### __name__

`__name__` 是 Python 的一个内置变量, 用于判断当前文件是否被**直接运行**.

用 `python xxx.py` 直接运行, `__name__` 为 "__main__".

用 `python -m xxx` 间接运行, `__name__` 为**模块名**.

### import 包时的执行逻辑

用 import 或者 from 导入模块时, 对应模块代码会被原封不动的全部执行一遍, 执行时, 被 import 的代码中 `__name__` 为 **模块名**.

### import 寻找顺序

有一个 `sys.path` 变量, 里面存着一些路径, 用于寻找模块. 这玩意是个列表, 从前往后依次寻找, 找到就开始导入, 顺序大概这样:
1. 在工作目录下寻找(绝对或相对导入).
2. 在 `site-packages` 目录下寻找(仅绝对导入).

### 莫名其妙的 id 不一致问题

有时候, 你手动加了 `sys.path` 后, 导入时全局变量可能会出现 id 不一致的问题, 讲下原因:

- ma 模块假设在 `module/ma.py` 里.

- `a.py` 代码用 `module.ma` 导入了 `ma` 模块的一个全局变量 `g`.
  
- 往 `sys.path` 里加了 `module` 这个目录. 
  
- `module/b.py` 代码中用 `ma` 导入了 `ma` 模块的全局变量 `g`.
  
- `a.py` 和 `b.py` 里 `g` 的 id 不一致.
  
所以别问为啥全局变量修改无效了.

从不同目录下(`sys.path`值不同)导入同一个文件时, 被导入的模块代码有不同的 id, 所以里面的东西也有两份.

**无特殊需求, 只建议项目使用绝对导入.**

### import 的代码到底执行了几遍

用同一个 `sys.path` 量导入的模块代码只会执行一遍, 第一次执行后被加进 cache 里了, 第二次 import 时发现 cache 里有就直接用 cache 里的了, 不执行第二次.

## PYPI

PYPI 打包发布的时候, 如果文件夹没有 `__init__.py` 文件, 那么这个文件夹会扔掉打包不进去.

## 关于 Request 这一类网络请求函数

### Requests 库的 POST 相关

- requests 的 post 方法有点坑，目前主流数据提交方式都是 json，所以一般用 json 这个可选参数传参，data 传参可能会因为格式问题导致请求失败。
- 需要**显式指定协议**，直接写 `example.com` 会报错。

```python
import requests

requests.post("http://example.com", json={
    "token": "xxx",
    "value": "yyy"
})
```


Request 爬虫的时代已经过去了, 现在用 selenium 吧.

当然如果直接最简单的 Request 没出问题也不妨试试.
