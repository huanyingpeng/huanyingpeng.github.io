---
title: 折腾 vmware
date: 2025-03-01 16:30:00
tags: 
- 虚拟化
categories:
- 技术
---

折腾 vmware

ubuntu24.04 环境。

### config apt source

打开 `/etc/apt/source.list.d/ubuntu.sources`，在 `URIs` 一项中，`http://archive.ub....` 前面加上 `.cn`，也就是 `https://cn.archive.ub....`。

第二项那个 `security` 不用改。

### vmware tools

```
sudo su
apt-get update
apt-get install open-vm-tools
apt-get install open-vm-tools-desktop
reboot
```

### 共享文件夹

开共享后, 客户机共享文件夹目录: `/mnt/hgfs/`

### 重安装的网络问题

重新安装 vmware 时，可能会遇到以下问题：

- 安装程序在 "配置网络驱动" 时卡死
- 安装后客户机死活连不上网。

这是由于卸载时没有删除注册表导致的，解决方案（[参考](https://blog.csdn.net/weixin_44188424/article/details/123402985)）如下：

- 在下载的软件中翻一翻，找到 "注册表"
- 一键扫描然后修复。
- vmware 点 "编辑"，"虚拟网络编辑器"，还原默认设置。

### 输入法

百度输入法很靠谱，它甚至附带了安装说明。

[百度输入法](https://srf.baidu.com/site/guanwang_linux/index.html)

