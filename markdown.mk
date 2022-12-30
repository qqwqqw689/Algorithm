# [NOI2016] 网格

## 题目描述

跳蚤国王和蛐蛐国王在玩一个游戏。

他们在一个 $n$ 行 $m$ 列的网格上排兵布阵。其中的 $c$ 个格子中 $(0 \leq c \leq n\cdot m)$，每个格子有一只蛐蛐，其余的格子中，每个格子有一只跳蚤。

我们称占据的格子有公共边的两只跳蚤是相邻的。

我们称两只跳蚤是连通的，当且仅当这两只跳蚤相邻，或存在另一只跳蚤与这两只跳蚤都连通。

现在，蛐蛐国王希望，将某些（零个，一个或多个）跳蚤替换成蛐蛐，使得在此之后存在至少两只跳蚤不连通。

例如：图 $1$ 描述了一个 $n=4$，$m=4$，$c=2$ 的情况。

 ![](https://cdn.luogu.com.cn/upload/pic/2386.png) 

这种情况下蛐蛐国王可以通过将第二行第二列，和第三行第三列的两只跳蚤替换为蛐蛐，从而达成他的希望，如右图所示。并且，不存在更优的方案，但是可能存在其他替换两只跳蚤的方案。

你需要首先判断蛐蛐国王的希望能否被达成。如果能够达成，你还需要最小化被替换的跳蚤的个数。

## 输入格式

每个输入文件包含多组数据。

输入文件的第一行只有一个整数 $T$，表示数据的组数。

接下来依次输入 $T$ 组数据，每组数据的第一行包含三个整数 $n, m, c$。

接下来 $c$ 行，每行包含两个整数 $x, y$ 表示第 $x$ 行，第 $y$ 列的格子被一个蛐蛐占据。每一组数据当中，同一个蛐蛐不会被多次描述。

## 输出格式

对于每一组数据依次输出一行答案。

如果这组数据中，蛐蛐国王的希望不能被达成，输出 $-1$。否则，输出被替换的跳蚤的个数的最小值。

## 样例 #1

### 样例输入 #1

```
4
4 4 2
1 1
4 4
2 3 1
1 2
2 2 2
1 1
2 2
1 1 0
```

### 样例输出 #1

```
2
1
0
-1
```

## 提示

### 样例解释

第一组数据就是问题描述中的例子。

对于第二组数据，可以将第二行第二列的一只跳蚤替换为蛐蛐，从而使得存在两只跳蚤不连通，并且不存在更优的方案。

对于第三组数据，最初已经存在两只跳蚤不连通，故不需要再进行替换。

对于第四组数据，由于最多只有一只跳蚤，所以无论如何替换都不能存在两只跳蚤不连通。

### 数据范围

对于全部的测试点，保证 $1 \leq T \leq 20$。我们记 $\sum c$ 为某个测试点中，其 $T$ 组输入数据的所有 $c$ 的总和。对于所有的测试点，$\sum c \leq 10^5$。

对于全部的数据，满足 $1 \leq n,m \leq 10^9$，$0 \leq c \leq n \times m$，$1 \leq x \leq n, 1 \leq y \leq m$。

每个测试点的详细数据范围见下表。表中的 $n,m,c$ 均是对于单个输入数据（而非测试点）而言的，也就是说同一个测试点下的 $T$ 组数据均满足限制条件；而 $\sum c$是对于单个测试点而言的。为了方便阅读，“测试点”一列被放到了表格的中间而不是左边。

| $n,m$ | 测试点 | $c$ |
| :----------: | :----------: | :----------: |
| $n*m\leq 4$ | $1$ | $c\leq n*m$ |
| $n*m\leq 8$ | $2$ | $c\leq n*m$ |
| $n*m\leq 15$ | $3$ | $c\leq n*m$ |
| $n*m\leq 30$ |  $4$| $c\leq n*m$ |
| $n*m\leq 100$ | $5$ | $c\leq n*m$ |
| $n*m\leq 300$ | $6$ | $c\leq n*m$ |
| $n*m\leq 10^3$ | $7$ | $c\leq n*m$ |
| $n*m\leq 2\times 10^4$ | $8$ | $c\leq 5$ |
| $n*m\leq 2\times 10^4$ | $9$ | $c\leq 15$ |
| $n*m\leq 2\times 10^4$ | $10$ | $c\leq 30$ |
| $n,m\leq 2\times 10^4,n*m\leq2\times 10^4$ | $11$ | $\sum c\leq 2\times 10^4$ |
| $n,m\leq 2\times 10^4,n*m\leq10^5$  | $12$ | $\sum c\leq 2\times 10^4$ |
| $n,m\leq 2\times 10^4,n*m\leq3\times 10^5$ | $13$ | $\sum c\leq 2\times 10^4$ |
| $n,m\leq 2\times 10^4,n*m\leq10^6$ | $14$ | $\sum c\leq 2\times 10^4$ |
| $n,m\leq 2\times 10^4,n*m\leq 10^9$ | $15$ | $\sum c\leq 2\times 10^4$ |
| $n,m\leq 10^5$ | $16$ | $\sum c\leq 10^5$ |
| $n,m\leq 10^9$ | $17$ | $c=0$ |
| $n,m\leq 10^9$ | $18$ | $c\leq 1$ |
| $n,m\leq 10^9$ | $19$ | $c\leq 2$ |
| $n,m\leq 10^9$ | $20$ | $c\leq 3$ |
| $n,m\leq 10^9$ | $21$ | $c\leq 10$ |
| $n,m\leq 10^9$ | $22$ | $c\leq 30$ |
| $n,m\leq 10^9$ | $23$ | $c\leq 300$ |
| $n,m\leq 10^9$ | $24$ | $\sum c\leq 2 \times 10^4$ |
| $n,m\leq 10^9$ | $25$ | $\sum c\leq   10^5$ |
