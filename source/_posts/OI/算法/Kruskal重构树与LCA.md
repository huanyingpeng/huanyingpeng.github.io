---
title: CF1706小总结
mathjax: true
date: 2022-07-19 20:10:16
tags:
- 比赛总结
- LCA
categories:
- 总结
- 比赛总结
---

## CF1706 小总结

其实都会做，但是各种各样的原因导致了没在场上 AK

### ABC

A 题没考虑清楚就在写，WA 了一发样例，然后慢悠悠调好交上去过。

B 题愣了一会儿，弄了个伪 DP 上去，稍微有点磨蹭，但还好。

C 题做得无可挑剔。

### D

D 题先想到可以枚举一个端点，二分另一个，$O(n)$ check，但是发现枚举一个端点之后，可以快速计算另一个端点的最优值，得到一个 $O(n^2)$ 的枚举 max 的做法过了 D1，然后感觉其实只需要查 $[\lfloor\frac{\max a_i}{k}\rfloor,\lfloor\frac{\max a_i}{k}\rfloor+\sqrt N]$ 和 $\{\lfloor\frac{\max a_i}{x}\rfloor,x \le k\}$，写好交上去过了 Pretests，但是 FST 了。

后面想到其实对 min 分类限制更多。暴力算 $\min \lfloor \frac{a_i}{k_i}\rfloor\in [1,B]$，然后对于 $\min \lfloor \frac{a_i}{k_i}\rfloor\in(B,k]$，可以发现 $p_i\in [1,\lceil\frac{10^5}{B}\rceil]$，考虑维护 max 的变化，可以用一个 vector 记一下 $\lfloor\frac{a_i}{p_i}\rfloor$ 的所有可能，共 $n\times \lceil\frac{10^5}{B}\rceil$ 种，因此对于 $(B,k]$，$\lfloor\frac{a_i}{p_i}\rfloor$ 的变化总量是 $O(n\sqrt n)$ 的。

换一种思路考虑，还是枚举 $x$，令 $\lfloor\frac{a_i}{p_i}\rfloor\le x$，易知 $p_i\ge\lfloor\frac{a_i}{x+1}\rfloor+1$，考虑每一个 $a_i$ 的最好的 $p_i$，不太可行。但是发现上式中能取到的 $p_i$ 满足 $p_i\le\lfloor\frac{N}{x}\rfloor$ 。于是考虑每一个 $p_i$ 可以让哪些 $a_i$ 值取到最优，这是一个区间。而我们要考虑的是 min，所以取区间中最小的计算就行。

对于一个 $x$，区间个数是 $\frac{N}{x}$ 的，因此总复杂度 $\sum\limits_{i=1}^N \frac{N}{i}=n\ln n$。

### E

E 题在考场上想到了可以类似整体二分的做，先给所有的二分，然后再合并一次，查询每一个询问是否可行。查询的维护可以 dsu on tree 带一个维护线段的 set，复杂度 $O(n\log^3n)$，感觉能信仰，就写了，可惜没交上去。赛后发现其实有些边界的小错，但是交了还是 TLE 了。告诉我们 set 操作搞个 $10^7$ 问题还是比较大。

后面发现可以将询问直接塞进 dsu 的过程中，但是处理询问只能处理较小的那一边，如果是小的合到大的上面去，此时询问挂在大的上面，会非常的恼火。于是就把询问拆到两个上面去，又发现可能两个询问会在合并时变成一个但是还没解决，所以合并的时候如果变成一个就又找了一个还没合并的把询问扔上去。

然后又 TLE 了，赛后仔细分析复杂度，发现不对劲，比如有个 $O(n)$ 的点，然后又有个略小于它但主要是询问的点，然后合并的时候把询问全部扔到另一个点上去了，然后另一个点同这个 $O(n)$ 点合并的时候又把询问全部扔了，询问就扔了 $O(n^2)$ 次，寄。

然后想到可以把线段合并的过程记下来，这个就是严格 $O(n\log n)$ 级别了，后面做一个二维偏序回答询问。成功 AC。

其实 E 题和最近做的题都暴露出几个问题，思维模式僵化，没有办法 Think out of box，同时代码中常常犯一些不容易注意到的小错误，依赖数据调试。

### Sum up

关于代码小错的问题，我觉得一边写一边静态查是一个比较理想的解决方案，**先认真核实思路的正确性，再检查代码和思路是否一致**，同时可以在关键点插入数据输出。

思维上的问题，估计还只有多做题。

### 收获 1：Dsu on tree 的复杂度理解

Dsu on tree，复杂度证明的过程是这样的：考虑一个点的权值 $w_i$，当合并时，复杂度贡献为 $O(\min(w_u,w_v)$，将 $w_i$ 视为 $w_i$ 个元素。考虑每个元素的贡献次数，发现每个元素仅在其所在集合大小翻倍时贡献。所以复杂度正确。

**因此，权值的构成不影响其时间复杂度**

如果在合并的时候进行了额外的对 $w_i$ 的修改，比如我的错误做法，时间复杂度就应该认真分析了。

### Kruscal 重构树的应用和连通性

E 题可以用 Kruscal 重构树做，具体的，先做最小生成树，顺便合并点，现在一个连通块就是一个点，合并两个连通块时，新建一个点，点权为这条边的权值，作为被合并的两个点的父亲，任意两个点联通的时最小权值就是它们的 lca，然后区间 lca 应该都会。事实上甚至没有必要做区间 lca，我们考虑 $i,i+1$ 什么时候联通，设其时间为 $f(i)$，可以发现 $ans(a,b)=\max\limits_{i\in[a,b)} f(i)$，证明比较容易，首先必须取到这个值，否则必然有两个点不连通，其次，如果取到这个值，那么一定都联通，over ，复杂度 $O(n\log n)$

已经知道这个性质了，那么，将询问放到 dsu 合并过程中的方法也不难写了，合并时处理其中一个询问即可。

### LCA 的一些性质

从 2 中的性质，我们总结出了一些 LCA 的共有性质。

设树上一个点集为 $S$，定义 $\operatorname{lca}(S)$ 为点集 $S$ 中所有点的最近公共祖先。定义符号 $\operatorname{lca}(a_1,a_2\cdots a_n)$ 表示 $\operatorname{lca}(\{a_1,a_2,\cdots a_n\})$。

$\text{Lemma 1.1}$

$\operatorname{lca}(S\cup u)=\operatorname{lca}(\operatorname{lca}(S),u)$

$\text{Proof 1.1}$

若 $\operatorname{lca}(S)$ 为 $u$ 的祖先，则结论显然成立。

否则，$u$ 位于 $\operatorname{lca}(S)$ 的子树外，$\operatorname{lca}(S\cup u)$ 必须同时为 $\operatorname{lca}(S)$ 和 $u$ 的祖先，故结论同样成立。

$\text{Theorem 1.2}$

对于 $S=\{a_1,a_2\cdots,a_n\}$，满足 $\operatorname{lca}(S)\in \bigcup\limits_{i=1}^{n-1}\operatorname{lca}(a_1,a_2)$。

$\text{Proof 1.2}$

对 $S$ 集合大小归纳，设 $|S|=n$，且对于 $k\le n$，结论成立。

由 Lemma 1.1，有 $\operatorname{lca}(S\cup u) = \operatorname{lca}(\operatorname{lca}(S),u)$，

- 若满足 $\operatorname{lca}(S\cup u)=\operatorname{lca}(S)$，对于 $S\cup u$，即 $|S'|=n+1$，结论成立。
- 若不满足 $\operatorname{lca}(S\cup u)=\operatorname{lca}(S)$，记 $\operatorname{lca}(S)=w$，则有 $\forall a_i\in S,\operatorname{lca}(a_i,u)=\operatorname{lca}(w,u)=\operatorname{lca}(S\cup u)$，因此对于 $|S'|=n+1$，结论仍然成立。

证毕。

$\text{Lemma 2.1}$

记 $\operatorname{dfn}(u)$ 表示 $u$ 的 dfs 序。

对三个元素 $u,v,w$ ，满足 $\operatorname{dfn}(u)<\operatorname{dfn}(v)<\operatorname{dfn}(w)$，有 $\operatorname{lca}(w,u,v)=\operatorname{lca}(u,w)$。

$\text{Proof 2.1}$

由 Theorem 1.2，$\operatorname{lca}(u,v,w)\in\{\operatorname{lca}(u,v),\operatorname{lca}(u,w)\}$。

假设 $\operatorname{lca}(u,v,w)=\operatorname{lca}(u,v)$ 并且 $\operatorname{lca}(u,v)\neq \operatorname{lca}(u,w)$。

记 $x=\operatorname{lca}(u,v,w)$ 。

因此 $v$ 和 $\operatorname{lca}(u,w)$ 在 $x$ 的不同子树。又有 $\operatorname{dfn}(v)>\operatorname{dfn}(u)$，所以 $u$ 所在的 $x$ 的子树先被访问，即 $\operatorname{lca}(u,w)$ 所在的 $x$ 的子树先被访问，因此 $\operatorname{dfn}(w)<\operatorname{dfn}(v)$。矛盾，故假设不成立。

证毕。

$\text{Theorem 2.2}$

对于序列 $a$，若集合 $A=\{a_1,a_2\cdots a_{n}\}$，且满足 $\forall i\in [1,n),\operatorname{dfn}(a_{i+1})>\operatorname{dfn}(a_i)$，有 $\operatorname{lca}(a_1,a_n)=\operatorname{lca}(A)$。

$\text{Proof 2.2}$

归纳证明，设对 $k=n$ 成立。

由 Theorem 1.2， $\operatorname{lca}(A\cup \{a_{n+1}\})=\operatorname{lca}(a_{n+1},\operatorname{lca}(A)\})$。

由 Lemma 2.1，Theorem 1.2，$\operatorname{lca}(\operatorname{lca}(A),a_{n+1})\operatorname{lca}(\operatorname{lca}(a_1,a_{n}),a_{n+1})=\operatorname{lca}(a_1,a_{n},a_{n+1})=\operatorname{lca}(a_1,a_{n+1})$

因此定理对 $k=n+1$ 同样成立。

证毕。

$\text{Theorem 2.3}$

对于序列 $a$，若集合 $A=\{a_1,a_2\cdots a_{n}\}$，且满足 $\forall i\in [1,n),\operatorname{dfn}(a_{i+1})>\operatorname{dfn}(a_i)$。

有 $\operatorname{lca}(a_1,a_n)\in \bigcup\limits_{i=1}^{n-1}\{\operatorname{lca}(a_i,a_{i+1})\}$。

$\text{Proof 2.3}$

由 Theorem 2.1 ，$\operatorname{lca}(a_1,a_n)=\operatorname{lca}(A)$

由 Theorem 1.1，$\operatorname{lca}(A) \in \{\operatorname{lca}(a_i,a_{i+1}),i\in[1,n)\}$。



