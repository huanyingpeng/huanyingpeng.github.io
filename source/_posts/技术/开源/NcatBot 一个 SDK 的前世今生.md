---
title: NcatBot 一个 SDK 的前世今生
date: 2025-02-12 16:24:19
tags:
- Python
- NcatBot
- 开源
categories:
- 技术
---

[NcatBot](https://github.com/liyihao1110/ncatbot) 是一个用于 QQ-Bot 开发的 Python SDK.

NcaBot 相比其它框架，拥有以下优势：

1. 社区活跃，**文档完善**。
2. 轻量框架，开发简单。
3. 提供一键部署方案，快速分发。

### 关于开发者们

- `彭彭`：我，不是全能猫娘，[huan-yp](https://github.com/huan-yp)。
- `周周`：USTC 少年班某大佬，[Isaaczhr](https://github.com/Isaaczhr)。
- `伊伊`：高中生，[zxxhz](https://github.com/zxxhz)。
- `鱼鱼`：在校大学生，[Fish-LP](https://github.com/Fish-LP)。
- `蝶蝶`：神秘大佬，没找到链接。
- `饭饭`：咕咕咕，[Qi-Cao](https://github.com/Qi-Cao)
- `木子`：群主，项目发起者，华侨大学机械专业研究生，[liyihao1110](https://github.com/liyihao1110)。

### 前情提要

AI 大作业做了个 AI Agent 叫小妍，后面 KWS 授权过期了就用不了了，打算移植到 QQ 上。

Mirai 在 24 年的时候尸体已经凉透了，之前费了老大功夫写的 Qbot 插件 Luling-AI 也用不了了，打算换个新的，继承 Luling 的名字。

了解到 napcat。

TS/JS 这块不熟，找 SDK，恰好有个 Python SDK 叫 NcatBot，就用它了。

然后发现这个 SDK 是个新手做的，后面交了两个 PR，进群被作者 PUA 然后套牢了。

我经验比较丰富，莫名其妙就给我接手了 V1.0.1 版本。

### 初步规范化

首先是代码格式统一，`pre-commit` 全家桶走起。

然后我发现 NcatBot 的开发团队非常活跃，一个 36stars 的项目有 5 个活跃开发者，然后 `pre-commit` 的时候遇到了一些问题（我是直接抄的原来项目的文件），然后几个人商量着解决了。

SDK 嘛，得走标准化发布，于是考虑配置了 PYPI 发布流程，很搞的一件事就是木子把 secret 变量名字搞错了，然后我在配置，他谈恋爱去了，折腾了一个小时，然后配完了 PYPI 发布。

接着是文档，TM 的 NcatBot 更新太快了，文档写不了一点，然后消息构造留了一坨屎山，我们一致决定先把屎山搞定。

### MessageChain

MessageChain 是模仿 Mirai 做的，这块是伊伊在负责，做挺好的，就是没考虑到发送 "本地图片" 时，ncatbot 和 napcat 的路径不同问题。

本地强转 base64 大法搞定的。

然后为这件事我还去 napcat 上扔了 Issue，因为他们的 http 发图片只支持单纯 .jpg, .png 这些，svg 这种支持不了。

后面了解到是 Not Planed，给文档交了个 PR 说不支持，现在还没合。

### 异步

本项目最大的梗，以下是 DeepSeek 的吐槽。

> 卧槽哥们儿你们这代码写得跟tm便秘似的！口口声声说异步操作，结果每个函数都无脑await串行执行，协程全他妈串成糖葫芦了，这跟同步有鸡毛区别？还舔着脸说用了websockets才用异步，合着异步库当摆设用是吧？就这水平还搞并发呢，隔壁老太太拄拐杖散步都比这代码跑得快！知不知道啥叫事件循环啊？协程全堵在await上跟早高峰地铁似的，这破玩意儿上线怕不是要卡成PPT！赶紧把键盘上那个await键抠了吧，写尼玛的异步代码，直接上同步不香吗？白瞎了websockets这库！

木子不是专业人员，代码基本 AI 写的，然后为了用 websockets，所有函数都写成了异步，但是事件循环什么的根本没有，然后线程安全一团糟。

我写着写着发现：woc，这 TM 啥异步啊，不是个同步吗？

后面木子补了异步的东西，把这玩意改成了真异步。

改成异步之后出了好些 [bug](https://github.com/liyihao1110/ncatbot/discussions/46)。

### 插件

#### 插里面还是插外面



### 一键部署

### 某些技术问题

#### cpp 程序乱码

代码都是 UTF-8 编码， Winows 是 GBK，导致乱码问题，搜了一堆解决不了，最后发现只需要在 main 函数最前面加上：

```cpp
#ifdef _WIN32
SetConsoleOutputCP(65001); // 设置控制台输出编码为 UTF-8
#endif
```

就搞定了，如此简单。

#### github webhook

服务器端接收到的是乱码，类似：

```
140.82.115.249 - - [13/Feb/2025 23:13:19] code 400, message Bad request version ('À\\x13À')
140.82.115.249 - - [13/Feb/2025 23:13:19] "\x16\x03\x01\x05¨\x01\x00\x05¤\x03\x03\x140@-SI\x94µ±èÐÆµÜ¿ôÚ{Å@\x8c·õü\x95\x87üá\x07f\x81ó ³7T¢9¨ê\x08\x01±Æ°]tb£#-0ª8I\x0bP\x94óÐ'öFc®\x00\x1aÀ+À/À,À0Ì©Ì¨À\x09À\x13À" 400 -
```

检查 webhook 设置的 URL 是不是 https，如果服务器没有额外配置 https，那得改成 http 协议。

### 未完待续...





