---
title: 对C++程序进行性能分析
mathjax: true
date: 2022-07-17 16:33:08
tags:
- 性能分析
- C++
categories:
- 算法竞赛
---

## 前情提要

某道题，某人写了，然后交了，然后过了，但跑的很慢。

某人卡了好几次常，都不行。

看了下跑得比较快的代码，其实没啥差别。

输出运行时间，发现没什么差异，所以某人要对程序做个性能分析。

性能分析本质上是运行了一遍程序，然后把占用大量时间的函数抓出来，对这个函数进行优化。

## 在 Windows 下使用 gprof 对程序进行性能分析

gprof 是 g++ 自带的性能分析工具，简单易用，命令行中 `gprof --version` 查看是否可用，如果不行，先把  `g++` 添加进系统路径里，多半就可以了。

性能分析需要特殊的编译参数，格式为

`g++ -pg demo.cpp -o demo`

其它参数可以照常添加，但是不能开 `O2` 等性能优化，这会破坏掉程序结构。

 然后运行程序，**这一步必不可少。**

`./demo`

**不要使用其它IDE编译执行后的gmon.out文件进行性能分析,请在命令行使用以上命令编译运行后进行下面的操作**

`gprof demo.exe gmon.out > result.txt`

这会生成性能数据到 result.txt 中，查看一下就行。

**最后一步中，.exe 不能省略**

给出一个性能数据的例子,例子中有详细的解释，我就不解释了

 ~~啥，看不懂英文？那就别学了。~~

```
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 17.14      0.06     0.06        3    20.00    74.92  NTT(num*, int)
 17.14      0.12     0.06                             _mcount_private
 14.29      0.17     0.05 14680064     0.00     0.00  num::num(int, int, int)
 14.29      0.22     0.05  7602174     0.00     0.00  num::operator*(num const&)
 11.43      0.26     0.04  7077888     0.00     0.00  num::operator-(num const&)
 11.43      0.30     0.04                             __fentry__
  5.71      0.32     0.02  7077888     0.00     0.00  num::operator+=(num const&)
  2.86      0.33     0.01   392448     0.00     0.00  std::enable_if<std::__and_<std::__not_<std::__is_tuple_like<num> >, std::is_move_constructible<num>, std::is_move_assignable<num> >::value, void>::type std::swap<num>(num&, num&)
  2.86      0.34     0.01   262144     0.00     0.00  num::operator*=(num const&)
  2.86      0.35     0.01                             main
  0.00      0.35     0.00  1177344     0.00     0.00  std::remove_reference<num&>::type&& std::move<num&>(num&)
  0.00      0.35     0.00   149817     0.00     0.00  void read<int>(int&)
  0.00      0.35     0.00   149815     0.00     0.00  num::num(int)
  0.00      0.35     0.00   149813     0.00     0.00  printf(char const*, ...)
  0.00      0.35     0.00   149813     0.00     0.00  num::get()
  0.00      0.35     0.00       16     0.00     0.00  quick(int, int, int, int)

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.

 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.

Copyright (C) 2012-2018 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

		     Call graph (explanation follows)


granularity: each sample hit covers 4 byte(s) for 2.86% of 0.35 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]     71.4    0.01    0.24                 main [1]
                0.06    0.16       3/3           NTT(num*, int) [2]
                0.01    0.00  262144/262144      num::operator*=(num const&) [10]
                0.00    0.00  524286/7602174     num::operator*(num const&) [3]
                0.00    0.00       2/14680064     num::num(int, int, int) [6]
                0.00    0.00  149817/149817      void read<int>(int&) [96]
                0.00    0.00  149815/149815      num::num(int) [97]
                0.00    0.00  149813/149813      num::get() [99]
                0.00    0.00  149813/149813      printf(char const*, ...) [98]
                0.00    0.00      16/16          quick(int, int, int, int) [100]
-----------------------------------------------
                0.06    0.16       3/3           main [1]
[2]     64.2    0.06    0.16       3         NTT(num*, int) [2]
                0.05    0.02 7077888/7602174     num::operator*(num const&) [3]
                0.04    0.02 7077888/7077888     num::operator-(num const&) [4]
                0.02    0.00 7077888/7077888     num::operator+=(num const&) [8]
                0.01    0.00  392448/392448      std::enable_if<std::__and_<std::__not_<std::__is_tuple_like<num> >, std::is_move_constructible<num>, std::is_move_assignable<num> >::value, void>::type std::swap<num>(num&, num&) [9]
-----------------------------------------------
                0.00    0.00  524286/7602174     main [1]
                0.05    0.02 7077888/7602174     NTT(num*, int) [2]
[3]     21.7    0.05    0.03 7602174         num::operator*(num const&) [3]
                0.03    0.00 7602174/14680064     num::num(int, int, int) [6]
-----------------------------------------------
                0.04    0.02 7077888/7077888     NTT(num*, int) [2]
[4]     18.3    0.04    0.02 7077888         num::operator-(num const&) [4]
                0.02    0.00 7077888/14680064     num::num(int, int, int) [6]
-----------------------------------------------
                                                 <spontaneous>
[5]     17.1    0.06    0.00                 _mcount_private [5]
-----------------------------------------------
                0.00    0.00       2/14680064     main [1]
                0.02    0.00 7077888/14680064     num::operator-(num const&) [4]
                0.03    0.00 7602174/14680064     num::operator*(num const&) [3]
[6]     14.3    0.05    0.00 14680064         num::num(int, int, int) [6]
-----------------------------------------------
                                                 <spontaneous>
[7]     11.4    0.04    0.00                 __fentry__ [7]
-----------------------------------------------
                0.02    0.00 7077888/7077888     NTT(num*, int) [2]
[8]      5.7    0.02    0.00 7077888         num::operator+=(num const&) [8]
-----------------------------------------------
                0.01    0.00  392448/392448      NTT(num*, int) [2]
[9]      2.9    0.01    0.00  392448         std::enable_if<std::__and_<std::__not_<std::__is_tuple_like<num> >, std::is_move_constructible<num>, std::is_move_assignable<num> >::value, void>::type std::swap<num>(num&, num&) [9]
                0.00    0.00 1177344/1177344     std::remove_reference<num&>::type&& std::move<num&>(num&) [95]
-----------------------------------------------
                0.01    0.00  262144/262144      main [1]
[10]     2.9    0.01    0.00  262144         num::operator*=(num const&) [10]
-----------------------------------------------
                0.00    0.00 1177344/1177344     std::enable_if<std::__and_<std::__not_<std::__is_tuple_like<num> >, std::is_move_constructible<num>, std::is_move_assignable<num> >::value, void>::type std::swap<num>(num&, num&) [9]
[95]     0.0    0.00    0.00 1177344         std::remove_reference<num&>::type&& std::move<num&>(num&) [95]
-----------------------------------------------
                0.00    0.00  149817/149817      main [1]
[96]     0.0    0.00    0.00  149817         void read<int>(int&) [96]
-----------------------------------------------
                0.00    0.00  149815/149815      main [1]
[97]     0.0    0.00    0.00  149815         num::num(int) [97]
-----------------------------------------------
                0.00    0.00  149813/149813      main [1]
[98]     0.0    0.00    0.00  149813         printf(char const*, ...) [98]
-----------------------------------------------
                0.00    0.00  149813/149813      main [1]
[99]     0.0    0.00    0.00  149813         num::get() [99]
-----------------------------------------------
                0.00    0.00      16/16          main [1]
[100]    0.0    0.00    0.00      16         quick(int, int, int, int) [100]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index	A unique number given to each element of the table.
		Index numbers are sorted numerically.
		The index number is printed next to every function name so
		it is easier to look up where the function is in the table.

     % time	This is the percentage of the `total' time that was spent
		in this function and its children.  Note that due to
		different viewpoints, functions excluded by options, etc,
		these numbers will NOT add up to 100%.

     self	This is the total amount of time spent in this function.

     children	This is the total amount of time propagated into this
		function by its children.

     called	This is the number of times the function was called.
		If the function called itself recursively, the number
		only includes non-recursive calls, and is followed by
		a `+' and the number of recursive calls.

     name	The name of the current function.  The index number is
		printed after it.  If the function is a member of a
		cycle, the cycle number is printed between the
		function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the function into this parent.

     children	This is the amount of time that was propagated from
		the function's children into this parent.

     called	This is the number of times this parent called the
		function `/' the total number of times the function
		was called.  Recursive calls to the function are not
		included in the number after the `/'.

     name	This is the name of the parent.  The parent's index
		number is printed after it.  If the parent is a
		member of a cycle, the cycle number is printed between
		the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the child into the function.

     children	This is the amount of time that was propagated from the
		child's children to the function.

     called	This is the number of times the function called
		this child `/' the total number of times the child
		was called.  Recursive calls by the child are not
		listed in the number after the `/'.

     name	This is the name of the child.  The child's index
		number is printed after it.  If the child is a
		member of a cycle, the cycle number is printed
		between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.

Copyright (C) 2012-2018 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

Index by function name

   [2] NTT(num*, int)          [6] num::num(int, int, int) [9] std::enable_if<std::__and_<std::__not_<std::__is_tuple_like<num> >, std::is_move_constructible<num>, std::is_move_assignable<num> >::value, void>::type std::swap<num>(num&, num&)
  [96] void read<int>(int&)   [10] num::operator*=(num const&) [7] __fentry__
 [100] quick(int, int, int, int) [4] num::operator-(num const&) [5] _mcount_private
  [98] printf(char const*, ...) [3] num::operator*(num const&) [1] main
  [99] num::get()              [8] num::operator+=(num const&)
  [97] num::num(int)          [95] std::remove_reference<num&>::type&& std::move<num&>(num&)

```

## VTune

一个更厉害的性能分析工具，可以分析 CPU 流水线利用率和高速缓存命中率等进一步性能。
