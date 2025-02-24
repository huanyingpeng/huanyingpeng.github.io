---
title: EM 算法
date: 2025-02-24 14:00:00
tags:
- 概率期望
- 算法
categories:
- 学术
mathjax: true
---

## 先验概率 VS 后验概率

### 定义

- 先验概率是**根据主观经验，在没有任何实验的情况下**对某件事情发生概率的预测。

- 后验概率是**根据某些已知证据**，去估计的事情发生的概率。
  $$
  P(H|E) = \dfrac{P(E|H)*P(H)}{P(E)}
  $$
  该式子中，每项含义如下：

  - $P(H|E)$：在证据 $E$ 成立的前提下，假设 $H$ 成立的概率。
  - $P(E|H)$：在假设 $H$ 成立的前提下，证据 $E$ 被观测的概率。
  - $P(E)$：证据 $E$ 成立的先验概率。
  - $P(H)$：假设 $H$ 成立的先验概率。

### 朱世衡之问 

有关朱世衡提出的硬币之问，不妨设 $E$ 表示抛 $100$ 次硬币 $50$ 次正面朝上，$H$ 表示 $p=0.9$，也就是正面朝上的概率为 $90\%$。那么：

  - 可以计算出 $P(E|H)\le \epsilon$，也就是**如果 $H$ 成立，那么观测到 $E$ 的概率会很小**。

  - 不能说：**因为 $P(E|H)\le \epsilon$，所以 $P(H|E)$ 很小**。 
  - $P(E)=\int^1_0{P(p=x)\cdot P(E|p=x) dx}$，显然 $P(p=x)$ 是个先验概率，**是确定不了的**，所以 $P(E)$ 没法计算，同理 $P(H)$ 也没法计算，故 $P(H|E)$ 计算不了。

## 最大似然

### 一般求解方式

- 考虑后验概率函数相对简单且为**凸函数**，对后验概率每个参数求偏导即可解出最大似然。
- 对后验概率函数使用**梯度下降**，求解**极大似然**。

## EM 算法

### 算法用途

EM 算法主要用于**近似求解**一些最大似然问题。

### 算法流程

1. 初始化**模型参数** $\theta$。
2. 对 $\theta$ 进行迭代，优化 $Q(\theta | \theta^{(t)}) = \mathbb{E}_{Z|Y,\theta^{(t)}} \left[ \log P(Y,Z|\theta) \right]$。
   - 根据 $\theta^{(t)}$ 计算 $Z$ 不同取值的后验概率密度函数 $F = P(Z=x|\theta^{(t)})$。
   - 根据 $F, \theta^{(t)}$ 求解上式的最大似然。 

### 算法举例

有三个硬币 $A,B,C$，正面朝上的概率为 $\theta_A,\theta_B, \pi$，每次实验先抛硬币 $C$，如果 $C$ 正面朝上，则使用 $A$，否则使用 $B$，一次实验抛完 $C$ 后抛 $A$ 或 $B$ 五次，记录为：

```
实验一：2 正 3 反

实验二：4 正 1 反

实验三：1 正 4 反

实验四：3 正 2 反

实验五：4 正 1 反
```

根据实验结果给出一个最大似然参数估计 $\theta = (\theta_A, \theta_B, \pi)$。

#### E 步骤

计算每个实验由 $A$ 或 $B$ 生成的后验概率：  
$$
\gamma_j(A) = \frac{\pi \cdot \theta_A^{n_j}(1-\theta_A)^{m_j}}{\pi \cdot \theta_A^{n_j}(1-\theta_A)^{m_j} + (1-\pi) \cdot \theta_B^{n_j}(1-\theta_B)^{m_j}}
$$

#### M 步骤

迭代更新：
$$
\pi' = \frac{\sum_{j=1}^5 \gamma_j(A)}{5}
$$

$$
\theta_A' = \frac{\sum_{j=1}^5 \gamma_j(A) \cdot n_j}{\sum_{j=1}^5 \gamma_j(A) \cdot 5}, \quad \theta_B' = \frac{\sum_{j=1}^5 \gamma_j(B) \cdot n_j}{\sum_{j=1}^5 \gamma_j(B) \cdot 5}
$$

#### 迭代

设置一个收敛阈值，似然估计变化小于阈值时令其停止。

## EM 原理证明

首先对似然函数取对数，记：
$$
L(\theta) = \log(P(Y|\theta))=\log{\sum\limits_{z}P(YZ|\theta)}=\log(\sum\limits_{z}P(Y|Z,\theta)P(Z|\theta))
$$
考虑：
$$
\begin{align}
L(\theta) - L(\theta^{(i)})&= \log\big({\sum\limits_{z}P(Y|Z,\theta)P(Z|\theta)}\big) \\
&=\log\big({\sum\limits_{z}P(Z|Y, \theta^{(i)})\frac{P(Y|Z,\theta)P(Z|\theta)}{P(Z|Y, \theta^{(i)})}}\big) - \log(P(Y|\theta^{(i)}))
\end{align}
$$
由 $\text{Jensen}$ 不等式，得
$$
\begin{align}
\text{上式} &\ge \sum\limits_{z}P(Z|Y,\theta^{(i)})\log{\frac{P(Y|Z,\theta)P(Z|\theta)}{P(Z|Y, \theta^{(i)})}} - \log(P|\theta^{(i)})\\
&= \sum\limits_{z}P(Z|Y,\theta^{(i)})\log{\frac{P(Y|Z,\theta)P(Z|\theta)}{P(Z|Y, \theta^{(i)})P(|\theta^{(i)})}})
\end{align}
$$
令：
$$
\begin{align}
B(\theta, \theta^{(i)})&= L(\theta) +  P(Z|Y,\theta^{(i)})\log{\frac{P(Y|Z,\theta)P(Z|\theta)}{P(Z|Y, \theta^{(i)})P(Y|\theta^{(i)})}}\\
&=L(\theta)+P(Z|Y,\theta^{(i)})\log{\frac{P(YZ|\theta)}{P(YZ|\theta^{(i)})}}
\end{align}
$$
*第二行来自贝叶斯公式。*

则有 $L(\theta)\ge B(\theta, \theta^{(i)})$，且 $B(\theta,\theta)=L(\theta)$。

所以令：
$$
\theta^{(i+1)} = \mathbf{argmax}_\theta B(\theta, \theta^{(i)}) 
$$
则有：
$$
L(\theta^{(i+1)}) \ge B(\theta^{(i+1)}, \theta^{(i)}) \ge B(\theta^{(i)},\theta^{(i)})=L(\theta^{(i)})
$$
即：
$$
L(\theta^{(i+1)})\ge L(\theta^{(i)})
$$

## 算法分析

### 对比

上面的三硬币问题理论上也可以直接求解最大似然，但是列出来后是一个 PDE，一般 PDE 目前是没有闭式解，所以也只能退而求其次找近似解。

梯度下降也行，但是相比于 EM，梯度下降的梯度计算比较复杂，而且无法保证满足概率约束，可解释性弱，收敛不可靠等等等。

### M 步骤最大似然的求解

三个变量是独立的，分别求偏导就能代出值来。

