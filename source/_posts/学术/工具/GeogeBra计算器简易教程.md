---
title: GeogeBra计算器简易使用教程
mathjax: true
date: 2022-08-17 11:56:36
tags:
- 科普
- 数学
categories:
- 技术

---

## Geogebra 计算器简易教程

如果本文讲的不够精确，可以继续上网搜索教程。

### 格式

数学公式格式直接支持 `LaTex` 和 `wolframalpha` 提供的数学公式，也可以按照它的提示写。

乘方为 `^`，分式直接写 `/`。

内置 `ln sin cos` 等常用函数，写约定的函数名即可提示。

求导可以直接写 $f'$

积分输入 `integral`，会提示参数，默认对 $x$ 做不定积分。

![E1](https://raw.githubusercontent.com/huan-yp/image_space/master/202208171134545.png)

可以看到下面还有一些特殊函数的提示框，可以根据这个输入。

### 操作

一般只会用到 `Algebra` 区域的东西。

鼠标拖动可以调整坐标系显示区域，滚轮调整显示精度。

右下角的三个按钮中前两个可以起到滚轮的作用。

![E2](https://raw.githubusercontent.com/huan-yp/image_space/master/202208171134475.PNG)

`ctrl+z` 撤销上一步操作，`ctrl+y` 取消上一步撤销操作，一步操作的判定比较迷惑，你认为的多步操作可能被判定为一步。

### 设置

右上角有设置图标，见上图，点开后是是这样

![E3](https://raw.githubusercontent.com/huan-yp/image_space/master/202208171134442.PNG)

前三个全部默认勾上，不管，第五个 `Zoom to fit` 是自动调整的合适的大小，基本没用，点开第六个 `Settings`，主要用这个：

点进去之后只需要调 `Basic`，其它基本不用管。

![E4](https://raw.githubusercontent.com/huan-yp/image_space/master/202208171134810.PNG)

后面的基本不管，只需要调整 `Dimensions`，`x Min,x Max,y Min, y Max` 字面意义，显示的 $x,y$ 坐标的最大值和最小值，如果调整的话会自动调整下面的 `xAxis yAxis`，也就是 $x,y$ 坐标的比例，如果点了 `xAxis` 那个锁定小图标，那么调整 `x Min` 会自动调整其它两个值(`y Min,x Min`)以满足比例要求。

### 变量和函数设置

![E5](https://raw.githubusercontent.com/huan-yp/image_space/master/202208171134339.PNG)

红圈圈出来的可以设置函数和变量，函数左边那个带颜色的框框可以点，点了之后就不再显示图像，当然再点一次就显示。

函数的设置没啥说的，看变量。

变量的那个播放按钮按下后会动态改变变量值，所有相关函数都会同时改变。

**如果希望在函数中使用变量，一般先定义变量再写函数。**

变量的设置中可以调整范围。

![E6](https://raw.githubusercontent.com/huan-yp/image_space/master/202208171134005.PNG)

在 `Slider` 选项中调整，调整的时候，**上下界都调整好之后再按回车**。

[DEMO](https://www.geogebra.org/calculator/fgqtercd)