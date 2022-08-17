---
title: 从一道题看CPU底层优化-第二弹
mathjax: true
date: 2022-08-05 10:30:33
tags:
- 常数优化
categories:
---

### 题意

- 给定一个序列 $a$，长度为 $2^n$，每次询问给定 $mask$，询问 $b_i=a_{i\bigoplus mask}$ 得到的 $b$ 序列的最大字段和。

- $n\leq 18,q\leq 2\times 10^5$
- 原题意参考[题意](https://codeforces.com/contest/1716/problem/E)，这里做了一些不影响做题的转化。

### 思考

我们发现可以类似于线段树一样的去维护最大子段和，即考虑对一层维护其所有可能的交换序列的信息，然后计算一个**节点左右儿子构成的区间**的最大子段和，这样是可以得到正确答案的。

不难发现我们只需要知道一层的**前缀和最大值和最小值**就可以完成向上传递，这样的信息量是 $O(1)$ 的，对于第 $i$ 层，会影响它的值的只有它下面的状态，因为上面的状态如何不影响该层最大值和最小值的位置，因此不会影响其计算答案的结果。

因此很容易设计出一个 $O(2^n\times n)$ 的做法，但是我觉得它有点难写。

所以我们考虑只分两层，预处理第一层的前缀和和最大值位置，最小值位置，扫描第二层计算答案，这样的话，复杂度为 $O(2^{\frac{3n}{2}})$ ，约为 $1.25\times 10^8$，能卡在边界上。

### 实现1

这是我们的第一份代码，得到了 TLE19 的成绩。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename _type>
inline void read(_type &x){
	x=0;int f=1;char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}x*=f;
}
template<typename _type1,typename _type2>void cmin(_type1 &a,const _type2 b){if(a>b)a=b;}
template<typename _type1,typename _type2>void cmax(_type1 &a,const _type2 b){if(a<b)a=b;}
const int N=18;
int i,j,k,n,s,t,m,tp1,tp2;
int a[1<<N],ans[1<<N],mx[1<<N],mi[1<<N],sum[1<<N];
signed main()
{
	read(n);
	for(i=0;i<1<<n;i++)read(a[i]);
	int now=0;
	for(int mask1=0;mask1<1<<n/2;mask1++){
		int gap=1<<n/2,max_val=0;
		for(i=0;i<1<<n;i+=gap){
			mi[i]=mx[i]=i;sum[i]=a[i^mask1],cmax(max_val,sum[i]);
			for(j=i+1;j<i+gap;j++){
				sum[j]=sum[j-1]+a[j^mask1];
				if(sum[j]>sum[mx[i]])mx[i]=j;
				if(sum[j]<sum[mi[i]])mi[i]=j;
				cmax(max_val,sum[j]-sum[mi[i]]);
			}
		}
		for(int mask2=0;mask2<1<<n;mask2+=gap){
			ans[mask2^mask1]=max_val;
			int min_val=0,sm=0;
			for(i=0;i<1<<n;i+=gap){
				cmax(ans[mask2^mask1],sm+sum[mx[i^mask2]]-min_val);
				cmin(min_val,sm+sum[mi[i^mask2]]);
				sm+=sum[(i+gap-1)^mask2];
			}
		}
	}
	int q;read(q);
	for(i=1;i<=q;i++){
		read(tp1);s^=1<<tp1;
		cout<<ans[s]<<endl;
	}
	return 0;
}
 
```

### 常数分析1

我们最开始对 $a$ 进行了 $512$ 次乱序扫描，但容易发现一共进行了 $512\times512$ 次每次扫描的区间大小均为 $512\times4$ Byte 的扫描，这种方式可以比较好的利用高速缓存，因为被一次 cacheline 读取的 64Byte 数据都被放入了高速缓存并在时间上具有局部性。

注意到第二部分对 `sum` 计算的前缀和，由于 L3 高速缓存的约能存下 $2^{18}$ 个 `long long` 数据，但是我们又存储了 `sum`，并且在第三部分有对 `sum` 一些固定位置的随机访问，因此，`a` 数组就被踢出了高速缓存，再次访问的时候需要重复读取，造成了相当大的浪费。

事实上，我们并不需要存储每一个 `sum`，每一个块需要存储的数据量是 $O(1)$ 的，对这个做一个优化，我们得到了一份新的代码。

### 实现2 

```c++
#include<bits/stdc++.h>
#define y1 y3647
#define INF 1000000000
#define LL long long
#define pii pair<int,int>
using namespace std;
template<typename _type>
inline void read(_type &x){
	x=0;int f=1;char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}x*=f;
}
template<typename _type1,typename _type2>void cmin(_type1 &a,const _type2 b){if(a>b)a=b;}
template<typename _type1,typename _type2>void cmax(_type1 &a,const _type2 b){if(a<b)a=b;}
const int N=18;
int i,j,k,n,s,t,m,tp1,tp2;
int a[1<<N];
LL mx[1<<N/2],mi[1<<N/2],sum[1<<N/2],ans[1<<N];
signed main()
{
// 	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".in","w",stdout);
	read(n);
	for(i=0;i<1<<n;i++)read(a[i]);
	int now=0;
	for(int mask1=0;mask1<1<<n/2;mask1++){
		LL gap=1<<n/2,max_val=0,m=n>>1;
		memset(mx,0,sizeof(mx)),memset(mi,0,sizeof(mi));
		for(i=0;i<1<<n;i+=gap){
			LL sm=0;
			for(j=i;j<i+gap;j++){
				sm+=a[j^mask1];
				if(sm>mx[i>>m])mx[i>>m]=sm;
				if(sm<mi[i>>m])mi[i>>m]=sm;
				cmax(max_val,sm-mi[i>>m]);
			}
			sum[i>>m]=sm;
		}
		for(int mask2=0;mask2<1<<n;mask2+=gap){
			ans[mask2^mask1]=max_val;
			LL min_val=0,sm=0;
			for(i=0;i<1<<n;i+=gap){
				cmax(ans[mask2^mask1],sm+mx[(i^mask2)>>m]-min_val);
				cmin(min_val,sm+mi[(i^mask2)>>m]);
				sm+=sum[(i^mask2)>>m];
			}
		}
	}
	int q;read(q);
	for(i=1;i<=q;i++){
		read(tp1);
		s^=1<<tp1;
		cout<<ans[s]<<endl;
	}
	return 0;
}
 
```

### 常数分析2

我们将 `a` 从 `long long` 改为了 `int`，提升了  cacheline 读取效率，并只额外存储了 $512\times3\times8 \text{ Byte}$ 的块信息，这样在以后的计算中，对大数组的随机访问可以变为对小数组的访问，大大提升了高速缓存利用率。

可以通过此题。

### Further Explore

继续对代码进行修改，观察其时间变化。

最初代码用时为 `1450ms`

#### E1

```c++
LL sm=0;
for(j=i;j<i+gap;j++){
    sm+=a[j^mask1];
    if(sm>mx[i>>m])mx[i>>m]=sm;
    if(sm<mi[i>>m])mi[i>>m]=sm;
    cmax(max_val,sm-mi[i>>m]);
}
sum[i>>m]=sm;
```

改为

```c++
sum[i>>m]=0;
for(j=i;j<i+gap;j++){
    sum[i>>m]+=a[j^mask1];
    if(sum[i>>m]>mx[i>>m])mx[i>>m]=sum[i>>m];
    if(sum[i>>m]<mi[i>>m])mi[i>>m]=sum[i>>m];
    cmax(max_val,sum[i>>m]-mi[i>>m]);
}

```

预期效率降低，原因为全局变量不会放入寄存器。

实际效率未降低，原因推测为 $O2$ 优化自动使用了该优化。

继续进行本机测试，共 `9` 次随机数据，运行时间分别为 `16339ms 16339ms `，符合预期，不开启优化时，全局变量一定不会放入寄存器。  

#### E2

`a` 数组改为 `long long` 类型。

预期由于高速缓存溢出，效率下降，实际未发生效率下降，应该是不明高速缓存机制原因。

#### #defin int long long

预期由于高速缓存溢出，效率下降，`64bit` 编译器和机子，实际效率有提升，`9` 组时间分别为 `16636ms 16167ms`。

开启 `O2` 后无明显差异，分别为 `5577ms 5561ms `

`32bit` 编译器，`64bit` 机子，`O2` 效率出现明显下降，分别为 `11839ms 14920ms `

### Conclusion

- O2 优化后，编译器会自动完成很多代码层面上的优化，我们更需要关注的是算法常数本身
- 高速缓存的利用情况很大程度决定了代码的效率，编写需要卡常的程序时应该尤为注意，滚动数组能有效提升高速缓存利用率，分块处理减少数组大小也是提升效率的一种可行方案。



