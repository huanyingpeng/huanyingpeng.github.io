---
title: STL 容器的一些澄清
mathjax: true
date: 2022-08-30 09:19:43
tags:
- STL
categories:
---

## map

本质上是 `set<pair<T1,T2>>`，见 `set`。

## set

### insert

可以插入一段区间，支持数组，同类型的 `set vector` 容器。

开 O2，$1$ 秒 $1.5\times 10^6$ 次操作。

如果接下来的一段插入有序，开 O2，$1$ 秒 $4.5\times 10^6$ 次，所以尽量排序后再插入。

### erase

开 O2，$1$ 秒 $1.5\times 10^6$ 次操作。

如果接下来的一段插入有序，开 O2，$1$ 秒 $4.5\times 10^6$ 次。

### 迭代器操作

开 O2，$1$ 秒 $10^7$。

### 遍历

```cpp
for(auto v:st)
for(auto it=st.begin();it!=st.end();it++)
```

以上两种均为 $O(n\log n)$

开 O2，$1$ 秒 $10^7$ 次操作。

## unordered_set

基础操作相比 `set` 快 $2$ 倍。

有序操作和 `set` 效率差不多。

## unoedered_map

本质上是 `unordered_set<pair<T1,T2>>`。



