---
title: Hexo-NexT 安装踩坑记录
mathjax: true
date: 2022-07-12 16:22:10
categories:
- 技术
---
## 博客部署

[参考](https://zhuanlan.zhihu.com/p/618864711)

### 环境

#### 基础

- git
- nodejs && npm

#### 开工作目录

```bash
npm install hexo-cli -g
hexo init blog
cd blog
npm install
hexo server
```

**工作目录**是 `blog`，记住，这很重要，文件名默认为相对工作目录的名字。

#### 本地预览

工作目录下：

```bash
hexo g && hexo s
```

`localhost:4000` 上看。

#### 开 GitHub Pages 仓库

每个账号只能开一个，仓库名 `username.github.io`。

#### 配源码分支

创仓库的时候把 main 弄下来，源码（不含 public）放这里，免得被覆盖。

#### 自动部署

工作目录下安自动部署工具。

```bash
npm install hexo-deployer-git --save
```

`_config.yml` 末尾加上（记得照着用户名改动）：

```yaml
deploy:
  type: git
  repo: https://github.com/username/username.github.io.git
  branch: master
  # message: Site updated: {{ now('YYYY-MM-DD HH:mm:ss') }})
```

部署：

```bash
hexo clean && hexo g && hexo d
```

### metadata

搜 `_config.yml` 相关配置项：

```yaml
title: 幻影彭的彩虹
subtitle: '记录青春的扇区'
description: ''
keywords: '算法竞赛, 自动化测试, 工程技术, Python'
author: huan-yp
language: zh-CN # 必须改

url: http://huanyp.cn
```

### 主题

#### 安主题（next）

工作目录下：

```bash
git clone https://github.com/next-theme/hexo-theme-next themes/next
```

#### 写上要用这个主题

`_config.yml` 里，找到 `theme`，写上 `next`

### next

我用 next 主题。

#### menu

配置菜单。

````yaml
menu:
  home: / || fa fa-home
  about: /about/ || fa fa-user
  tags: /tags/ || fa fa-tags
  categories: /categories/ || fa fa-th
  archives: /archives/ || fa fa-archive
  # schedule: /schedule/ || fa fa-calendar
  sitemap: /sitemap.xml || fa fa-sitemap
  commonweal: /404/ || fa fa-heartbeat
````

#### scheme

在 `themes/next/_config.yml` 调 scheme，传统的应该选 `Gemini`。

```yaml
# Schemes
# scheme: Muse
# scheme: Mist
# scheme: Pisces
scheme: Gemini
```

#### dark

应该没有人喜欢 light，所以调成 dark。

在 `themes/next/_config.yml` 调 darkmode。

```
darkmode: true
```

### 背景

一般要加个背景图片什么的

#### 准备 source 图片

图片放到 `themes/next/source/image/background.jpg` 里。

#### 改 style

找到 `themes\next\source\css\_schemes\Gemini\index.styl`，加上：

```css
body {
    background:url(/images/background-now.jpg);
    background-repeat: no-repeat;
    background-attachment:fixed; //不重复
    background-size: cover;      //填充
    background-position:50% 50%;
}


// 博客内容透明化
// 文章内容的透明度设置
.content-wrap {
  opacity: 0.7;
}


// 侧边框的透明度设置
.sidebar {
  opacity: 0.7;
}

// 菜单栏的透明度设置
.header-inner {
  background: rgba(255, 255, 255, 0.8);
}

// 搜索框（local-search）的透明度设置
.popup {
  opacity: 0.7;
}

//博客内容透明化

:root {
  --content-bg-color: rgba(255, 255, 255, 0.8);
}

```

那个 [0, 1] 的参数是透明度，自己估摸着调。

### 友情链接

#### menu 加 link

```yaml
menu:
  友情链接: /links/ || fa fa-link
```

写中文就行。

#### 内联 html

新建 `source/links/index.md`，写入：

```markdown
{% raw %}
<div class="post-body">
   <div id="links">
      <style>
         .links-content{
         margin-top:1rem;
         }
         .link-navigation::after {
         content: " ";
         display: block;
         clear: both;
         }
         .card {
         width: 45%;
         font-size: 1rem;
         padding: 10px 20px;
         border-radius: 4px;
         transition-duration: 0.15s;
         margin-bottom: 1rem;
         display:flex;
         }
         .card:nth-child(odd) {
         float: left;
         }
         .card:nth-child(even) {
         float: right;
         }
         .card:hover {
         transform: scale(1.1);
         box-shadow: 0 2px 6px 0 rgba(0, 0, 0, 0.12), 0 0 6px 0 rgba(0, 0, 0, 0.04);
         }
         .card a {
         border:none;
         }
         .card .ava {
         width: 3rem!important;
         height: 3rem!important;
         margin:0!important;
         margin-right: 1em!important;
         border-radius:4px;
         }
         .card .card-header {
         font-style: italic;
         overflow: hidden;
         width: 100%;
         }
         .card .card-header a {
         font-style: normal;
         color: #2bbc8a;
         font-weight: bold;
         text-decoration: none;
         }
         .card .card-header a:hover {
         color: #d480aa;
         text-decoration: none;
         }
         .card .card-header .info {
         font-style:normal;
         color:#a3a3a3;
         font-size:14px;
         min-width: 0;
         overflow: hidden;
         white-space: nowrap;
         }
      </style>
      <div class="links-content">
         <div class="link-navigation">
            <div class="card">
               <img class="ava" src="博客图标" />
               <div class="card-header">
                  <div>
                     <a href="博客链接">博客名字</a>
                  </div>
                  <div class="info">博客简介</div>
               </div>
            </div>
            <div class="card">
               <img class="ava" src="博客图标" />
               <div class="card-header">
                  <div>
                     <a href="博客链接">博客名字</a>
                  </div>
                  <div class="info">博客简介</div>
               </div>
            </div>
         </div>
      </div>
   </div>
</div>
{% endraw %}
```

要加的时候在这复制 html 就行。

### 杂项

#### 置顶文章

工作目录下执行：

```bash
npm uninstall --save hexo-generator-index
npm install --save hexo-generator-index-pin-top
```

metadata 部分写：

```markdown
---
title: Title
top: true
---
```

即可置顶。

### 插件

#### 搜索插件

工作目录下：

```bash
npm install hexo-generator-searchdb
```

主题配置 `themes/next/_config.yml` 下：

```yaml
local_search:
  enable: true
  # Show top n results per article, show all results by setting to -1
  top_n_per_article: 2
  # Unescape html strings to the readable one.
  unescape: false
  # Preload the search data when the page loads.
  preload: false
```

#### 数学插件

一般用 Mathjax。

先安装 [Pandoc](https://pandoc.org/installing.html)，这个要改系统路径，需要重启终端。

工作目录下执行：

```
npm uninstall hexo-renderer-marked
npm install hexo-renderer-pandoc
```

改 `themes/next/_config.yml` 的 math 配置：

```yaml
math:
  mathjax:
    enable: true
    # Available values: none | ams | all
    tags: all
```

每篇文档的 metadata 部分要写启用 Mathjax：

```markdown
---
title: Hello World
mathjax: true
---
```

参考资料：[Next 官方有关文档](https://github.com/theme-next/hexo-theme-next/blob/master/docs/zh-CN/MATH.md)。

### 常用命令

- `hexo g` : 生成
- `hexo s` : 本地部署
- `hexo d` : 远端部署


### 网络相关

#### CNAME

CNAME 文件部署时被覆盖

[解决方式](http://eronana.github.io/2014/11/07/Hexo%E9%83%A8%E7%BD%B2%E5%90%8ECNAME%E8%A2%AB%E8%A6%86%E7%9B%96%E7%9A%84%E8%A7%A3%E5%86%B3%E6%96%B9%E6%B3%95/)

将 `CNAME` 放入 `./source`，即存在 `./source/CNAME` 文件。

#### SEO

在 `google search console` 申请抓取的时候，一定要看清楚是不是 `https` 协议，如果部署在 `github` 上，可能会强制 `https`，导致抓取出现**重定向错误。**如果出现了这个错误，有可能是没用 `https` 协议。
