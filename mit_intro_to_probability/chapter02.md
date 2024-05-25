
- [2.1 基本概念](#21-基本概念)
- [2.2 分布列（Probability Mass Function, PMF）](#22-分布列probability-mass-function-pmf)
- [2.3 期望（均值）和方差](#23-期望均值和方差)
  - [2.3.1 方差、矩和 d.r.v. 的函数的期望规则](#231-方差矩和-drv-的函数的期望规则)
  - [2.3.2 均值和方差的性质](#232-均值和方差的性质)
- [2.4 多个 d.r.v. 的联合分布列](#24-多个-drv-的联合分布列)
  - [2.4.1 多个随机变量的函数](#241-多个随机变量的函数)
- [2.5 条件](#25-条件)
  - [2.5.1 某事件发生的条件下的 r.v.](#251-某事件发生的条件下的-rv)
  - [2.5.2 给定另一个 r.v. 的值的条件下的 r.v.](#252-给定另一个-rv-的值的条件下的-rv)
  - [2.5.3 乘法法则](#253-乘法法则)
  - [2.5.4 全概率和全期望定理](#254-全概率和全期望定理)
- [2.6 独立性](#26-独立性)
  - [2.6.1 独立与期望、独立与方差](#261-独立与期望独立与方差)
- [2.7 常见的 r.v. 的均值和方差](#27-常见的-rv-的均值和方差)
  - [2.7.1 伯努利 r.v. 的均值和方差](#271-伯努利-rv-的均值和方差)
  - [2.7.2 离散均匀 r.v. 的均值和方差](#272-离散均匀-rv-的均值和方差)
  - [2.7.3 几何 r.v. 的均值和方差](#273-几何-rv-的均值和方差)
  - [2.7.4 二项 r.v. 的均值和方差](#274-二项-rv-的均值和方差)
  - [2.7.5 帽子问题的均值和方差](#275-帽子问题的均值和方差)
  - [2.7.6 泊松 r.v. 的均值和方差](#276-泊松-rv-的均值和方差)
- [2.8 补充](#28-补充)
  - [2.8.1 示性函数](#281-示性函数)
  - [2.8.2 互斥定理](#282-互斥定理)


### 2.1 基本概念

<img src='./img/图2.1-1 随机变量的解释.png' style="zoom: 50%;" />

<img src='./img/图2.1-2 RV例子.png' style="zoom: 25%;" />


>在这个例子中，令 a,b,c,d 四人为样本空间，r.v..W 表示任取一人的体重，r.v..H 表示任取一人的身高，r.v..B = $\frac{W}{H^2}$ 为 r.v..W 和 r.v..H 的函数，它表示任取一人的健康水平。

- r.v.(Random Variable)是实验结果的**实值函数**；
- 一个或多个 **r.v. 的函数**仍是 r.v.；
  > r.v. 的函数的值由原 r.v. 确定，原 r.v. 的值由试验的结果确定，因此 r.v. 的函数的值也是实验结果的实值函数，所以 r.v. 的函数也是一个 r.v. 。
- 对于一个 r.v.，可以定义一些平均量，例如**均值**和**方差**；
- 可以在某事件或某 r.v. 的**条件**下定义一个 r.v.；
- 存在一个 r.v. 与某事件或某 r.v. 相互**独立**的概念；

 r.v. 有离散和连续之分，d.r.v. 的取值范围只能是有限多个值或可数无限个值。本章的内容均为 d.r.v.。

### 2.2 分布列（Probability Mass Function, PMF）
Probability Mass Function, 概率质量定理(PMF)，只有离散 r.v. 才有，它也称作“概率律”或“概率分布”。它描述了每个数可能出现的概率；

<img src='./img/图2.2-1 PMF的计算.png' style="zoom: 50%;" />

<img src='./img/图2.2-2 PMF的计算 exa.png' style="zoom: 42%;" />

- PMF 的性质：
  - $p_X(x) \geqslant 0$；
  - $\sum_{x} p_{X}(x) = 1$；

### 2.3 期望（均值）和方差
期望例子：玩一个游戏 1000 次，描述下述 r.v. 每次可能获得的分数：
$$
X=\left \{
  \begin{aligned}
  1,&\,\,\,\, w.p.\,\,\frac {2}{10} \\
  2,&\,\,\,\, w.p.\,\,\frac {5}{10} \\
  4,&\,\,\,\, w.p.\,\,\frac {3}{10} \\
  \end{aligned}
  \right.\\[2ex]
$$

$$
  \text{“average” gain} = (1 * 200 + 2 * 500  + 4 * 300) /1000 \\
  = 1*\frac {3}{10} + 2 *\frac {5}{10}+ 4 * \frac {3}{10}
$$
>w.p. with probability 概率为
- 定义：$E[X] = \sum_x xp_X(x)$；

- $E[X]$ 就是 $X$ 的所有取值相对于它的概率的加权平均；

- 解释：大量独立重复实验的平均值；也可将分布的期望堪称分布列的“重心”；特别地，当 r.v. 的分布列具有对称中心的时候，这个对称中心必定为这个对称 r.v. 的均值（期望）。

#### 2.3.1 方差、矩和 d.r.v. 的函数的期望规则
- **方差**：提供了 X 在期望周围分散程度的一个度量，
  $$
  var(X) = E[(X-E[X])^2] = \sum_x(x-\mu)^2p_X(x)
  $$
- **标准差**：分散程度的另一个度量。标准差具有实用性，因为它的量纲与 X 相同，

  $$
  \sigma = \sqrt{var(X)}
  $$

- **矩**：n 阶矩，$E[X^n]$，$X^n$ 的期望值；期望本身为一阶矩；

- **r.v. 函数的期望值**：$E[g(x)] = \sum_xg(x)p_X(x)$
    $$
    \begin{align}
    &proof:\,\,E[g(X)] = E[Y] =\sum_yyp_Y(y)&\nonumber\\
    &=\sum_yy\sum_{\left\{x|g(x)=y\right\}}p_X(x)=\sum_y\sum_{\left\{x|g(x)=y\right\}}yp_X(x)&\nonumber\\
    &=\sum_y\sum_{\left\{x|g(x)=y\right\}}g(x)p_X(x)=\sum_x g(x)p_X(x)&\nonumber\\
    \end{align}
    $$
  >注意：一般来说，$E[g(X)] \neq g(E[X])$，例如$E[X^2]=\sum_xx^2p_X(x) \neq (E[X])^2 = (\sum_xxp_X(x))^2$

#### 2.3.2 均值和方差的性质

- 期望的基本性质：
  - $\text{IF }X \geqslant 0\,\,(\forall \omega: X(\omega)\geqslant 0)\text{, then }E[X] \geqslant 0$；
  - $\text{IF }a\leqslant X \leqslant b\text{, then }a \leqslant E[X]\leqslant b$；
  - $\text{IF c is a constant, }E[c] = c$；
- 期望和方差的线性法则：
  - $E[aX+b] = aE[X] + b$
  - $var(aX+b) = a^2var(X)$
- 计算方差的另一公式：$var(X) = E[X^2] -(E[X])^2$


### 2.4 多个 d.r.v. 的联合分布列
- 联合分布列定义：$p_{X,Y}(x,y)=P(X=x, Y=y)$
- 利用 X 和 Y 的联合分布列可以计算 X 或 Y 的分布列（X 或 Y 的分布列又称为**边缘分布列**）
  - $p_X(x) = \sum_yp_{X,Y}(x, y)$
  - $p_Y(y) = \sum_xp_{X,Y}(x, y)$

  <img src='./img/图2.4-1 联合分布列 exap.png' style="zoom: 33%;" align="left" />

#### 2.4.1 多个随机变量的函数
设 $Z = g(X, Y)$，则有，
$$
\begin{align}
&p_Z(z) = \sum_{\{(x,y)|g(x,y)=z\}}p_{X,Y}(x,y),&\nonumber\\[1.5ex]
&E[g(X,Y)]=\sum_X\sum_Yg(x,y)p_{X,Y}(x,y),&\nonumber\\[1.5ex]
&E[aX+bY+c] = aE[X] + bE[Y] = c&\nonumber\\
\end{align}
$$
>以上的结果可以推广到三个及三个以上

例如设 $X_1,X_2,...X_n$ 为 n 个随机变量，$a_1,a_2,...,a_n$ 为 n 个常数，则有，

$$E[a_1X_1 + a_2X_2 +...+a_nX_n] = a_1E[X_1] + a_2E[X_2] + ... + a_nE[X_n]$$

>二项 r.v. 的均值就是这样计算的

### 2.5 条件
#### 2.5.1 某事件发生的条件下的 r.v.
  |PMF|Condition PMF (IF A) |
  |---|---|
  |$p_X(x)=P(X=x)$| $p_{X\|A}(x)=P(X=x\|A)$|
  |$\sum_xp_X(x)=1$| $\sum_xp_{X\|A}(x)=1$|
  |$E[X]=\sum_xxp_X(x)$| $E[X\|A]=\sum_xxp_{X\|A}(x)$|
  |$E[g(X)]=\sum_xg(x)p_X(x)$| $E[g(X)\|A]=\sum_xg(x)p_{X\|A}(x)$|

  <img src='./img/2.6-1 condition RV E&var exp.png' style="zoom: 33%;" />

  >总有一些奇奇怪怪的求方差的方法：左边是直接代的离散均匀分布的方差公式，右边呢？？

#### 2.5.2 给定另一个 r.v. 的值的条件下的 r.v.
  |Condition PMF (IF A) |Condition PMF (IF Y=y)|
  |---|---|
  | $p_{X\|A}(x)=P(X=x\|A)$| $p_{X\|Y}(x\|y)=P(X=x\|Y=y)$|
  | $\sum_xp_{X\|A}(x)=1$| $\sum_xp_{X\|Y}(x\|y)=1$|
  | $E[X\|A]=\sum_xxp_{X\|A}(x)$| $E[X\|Y=y]=\sum_xxp_{X\|Y}(x\|y)$|
  | $E[g(X)\|A]=\sum_xg(x)p_{X\|A}(x)$| $E[g(X)\|Y=y]=\sum_xg(x)p_{X\|Y}(X\|y)$|

条件分布列的公式：

$$
p_{X|Y}(x|y)=P(X=x|Y=y)=\frac{P(X=x,Y=y)}{P(Y=y)}=\frac{p_{X,Y}(x,y)}{p_Y(y)}
$$

由此公式可以推出计算联合分布的公式：
$$
p_{X,Y}(x,y) = p_Y(y)p_{X|Y}(x|y)\\[1.5ex]
p_{X,Y}(x,y) = p_X(x)p_{Y|X}(y|x)\\
$$

#### 2.5.3 乘法法则
$$
P(A\cap B\cap C) = P(A)P(B|A)P(C|A\cap B)\\[1.5ex]
令\,\,A=\{X=x\},\,\,B=\{Y=y\},\,\,C=\{Z=z\}\\[1.5ex]
p_{X,Y,Z}(x,y,z)=p_X(x)p_{Y|X}(y|x)p_{Z|X,Y}(z|x,y)
$$

#### 2.5.4 全概率和全期望定理
<img src='./img/2.6-2 total E theo.png' style="zoom:33%;" />

<img src='./img/2.6-3 total e tho exp.png' style="zoom:33%;" />

>全期望定理，r.v. 的期望等于完备事件组 A1、A2... 的条件期望与对应的条件的概率的乘积之和

$$
\begin{align}
&A_1,...A_n: \,\,partition\,\,\,\,of\,\,\,\,\Omega&\nonumber\\[1.5ex]
&p_X(x)=P(A_1)p_{X|A_1}(x) +...+ P(A_n)p_{X|A_n}(x)=\sum_{i=1}^nP(A_i)p_{X|A_i}(x)&\nonumber\\[1.5ex]
&E[X]=P(A_1)E[X|A_1]+...+P(A_n)E[X|A_n]=\sum_{i=1}^nP(A_i)E[X|A_i]&\nonumber\\[1.5ex]
&let\,\,\,\, Y=\{y_1,...,y_n\},\,\,\,\,A_i=\{Y=y_i\}\,\,\,\,then\,,&\nonumber\\[1.5ex]
&p_X(x)=\sum_yp_Y(y)p_{X|Y}(x|y)&\nonumber\\[1.5ex]
&E(X)=\sum_yp_Y(y)E[X|Y=y]&\nonumber\\[1.5ex]
\end{align}
$$

$\Omega$ 上的概率和期望可以用条件概率或条件期望进行求解，同理，在将样本空间缩小为 $\Omega$ 的一个子集，它的概率和期望也可以用该子集上的条件概率或条件期望进行求解，则可推出以下公式：
$$
p_{X|B}(x)=\sum_{i=1}^nP(A_i|B)p_{X|A_i\cap B}(x)\\[1.5ex]
E[X|B]=\sum_{i=1}^nP(A_i|B)E[X|A_i\cap B]
$$

### 2.6 独立性
|独立|公式|
|---|---|
|of two events|$P(A\cap B)=P(A)P(B),\,\,\,\,P(A\|B)=P(A)$|
|of a r.v and an event|$p_{X\|A}(x)=p_X(x),\,\,\,\,P(A\|X=x)=P(A)$|
|of two r.v.'s|$p_{X,Y}(x,y)=p_X(x)p_Y(y),\\p_{X\|Y}(x\|y)=p_X(x),\,\,\,\,p_{Y\|X}(y\|x)=p_Y(y)$

注意：条件独立不包含独立，独立也不包含条件独立，下面是一个例子：

<img src='./img/图2.6-1 条件独立与独立不等价 exap.png' style="zoom:25%;" />

$p_{X|Y}(1|1)=P(X=1|Y=1)=0\neq P(X=1)=p_X(1)=\frac{3}{20}$ 说明 X 和 Y 不独立；

若将事件 $A=\{X\leqslant2,Y\geqslant3\}$ 作为条件事件，则 X 和 Y 是条件独立的，因为，
$$
p_{X|Y,A}(x|y) = p_{X|A}(x)
$$

#### 2.6.1 独立与期望、独立与方差

<img src='./img/图2.6-2 独立与期望独立与方差.png' style="zoom: 33%;"/>

>独立随机变量的和的方差等于它们的方差之和，与之对比，随机变量之和的期望等于随机变量的期望的和，而不需要任何条件

- 几个随机变量的相互独立性：如果随机变量 X、Y 和 Z 满足
  $$p_{X,Y,Z}(x,y,z)=p_X(x)p_Y(y)p_Z(z)$$
  则 X、Y 和 Z 是三个相互独立的随机变量。并且可以推出，
  - 形如 $f(X)、g(Y)、h(Z)$ 的三个随机变量也相互独立；
  - 任何两个 $g(X,Y)$ 和 $h(Z)$ 也相互独立；
  - 但是 $g(X,Y)$ 和 $h(Y,Z)$ 通常不是相互独立，因为它们都受公共的随机变量 Y 的影响；


- 若干个相互独立的随机变量的和的方差：设 $X_1,...,X_n$ 为相互独立的随机变量序列，则有，
  $$
  var(X_1+...+X_n)=var(X_1)+...+var(X_n)
  $$
  这个结论可以通过反复应用两个独立随机变量之和的方差公式得到；

### 2.7 常见的 r.v. 的均值和方差

#### 2.7.1 伯努利 r.v. 的均值和方差

<img src='./img/2.5-1 伯努利RV的E.png' style="zoom:33%;" align="left"/>

#### 2.7.2 离散均匀 r.v. 的均值和方差

<img src='./img/2.5-2 uniform RV E&Var.png' style="zoom:33%;" align="left"/>

#### 2.7.3 几何 r.v. 的均值和方差

<img src='./img/图2.7.3-1 几何分布intro.png' style="zoom:33%;" align="left"/>

- 无记忆性（几何分布是唯一具有无记忆性的离散分布）：假设已经经历了 n 次失败，则从当前起直至成功所需的次数与 n 无关；
  
  设 $X\sim G(p), \,\,\forall s,t\in N,\,\, P(X>s+t|X>s)=P(x>t)$ 

- 利用公式计算期望和方差：
  $$
  E[X]=\sum_kkp_X(k) = \sum_kk(1-p)^{k-1}p\\[1.5ex]
  var(X) = E[(k-E[X])^2]=\sum_k(k-E[X])^2p_X(k)
  $$
- 利用几何 r.v. 的无记忆性计算期望和方差：
  

#### 2.7.4 二项 r.v. 的均值和方差
- 二项分布：n 次独立重复实验中成功的次数。参数为 n,p；
- 二项分布可看作由 n 个独立的伯努利随机变量构成，每次成功的概率为 p；
$$
\begin{align}
&X = X_1 + X_2 +...+ X_n&\nonumber\\[1.5ex]
&E[X] = \sum_{i=1}^nE[X_i] = \sum_{i=1}^np = np&\nonumber\\[1.5ex]
&var(X_1) = ...=var(X_n) = p(1-p)&\nonumber\\[1.5ex]
&var(X) = var(X_1) + var(X_2) +...+ var(X_n) &\nonumber\\[1.5ex]
&\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,\,= n*var(X_1) = np(1-p)&\nonumber
\end{align}
$$

#### 2.7.5 帽子问题的均值和方差
- 假设有 n 个人，每人有一顶帽子，将它们的帽子放在一个盒子里，每人随机拿一个帽子（人和帽子的各种对应是等可能的），用随机变量 X 表示得到自己帽子的人的数量，求 X 的均值和方差。
- n 个人 n 顶帽子，有 n! 种不同的排法，每种排法都是等可能的，每种排法中 X 的数量无法得到，所以直接算行不通；
- 将 X 看作 n 重伯努利序列，由于每种排法都是等可能的，所以$E[x_i] = E[x_1] = \frac1n$ 
$$
\begin{align}
&X = X_1 + X_2 +...+ X_n&\nonumber\\[1.5ex]
&E[X] = \sum_{i=1}^nE[X_i] = \sum_{i=1}^n\frac 1n = n\frac 1n = 1&\nonumber\\[1.5ex]
\end{align}
$$
- 接下来计算方差，由于这 n 重伯努利序列不是独立的（如果有 n-1 个人拿到了自己的帽子，剩下的一个人必能拿到自己的帽子）所以不能直接使用独立性的方差公式；

$$
\begin{align}
&var(X)=E[X^2]-(E[X])^2&\nonumber\\[1.5ex]
&X = X_1+X_2+...+X_n&\nonumber\\[1.5ex]
&X^2 = \sum_iX_i^2 + \sum_{i,j:i\neq j}X_iY_j&\nonumber\\
&(前一部分有n项，后一部分n^2-n项)&\nonumber\\[1.5ex]
&E[X_i^2]=E[X_1^2]=E[X_1]=\frac 1n&\nonumber\\
&因为是0-1分布，所以X_1^2的取值和X_1的取值相同&\nonumber\\[1.5ex]
&For\,\,\,\,i\neq j:\,\,E[X_iX_j]=E[X_1X_2]=P(X_1X_2=1)&\nonumber\\
&=P(X_1=1,X_2=1)=P(X_1=1)P(X_2=1|X_1=1)&\nonumber\\
&=\frac1n\frac{1}{n-1}&\nonumber\\[1.5ex]
&E[X^2]=n*\frac1n+(n^2-n)*\frac1n\frac{1}{n-1} = 2&\nonumber\\[1.5ex]
&var(X) = 2 - 1 = 1&\nonumber
\end{align}
$$

- 总结：在求很复杂的模型的方差时，可以将其分解为多个不同随机变量的和，然后取其平方，将其分解为多个不同的项，然后逐个求这些项的期望，即可得到方差；

#### 2.7.6 泊松 r.v. 的均值和方差

<img src='./img/图2.7.6-1 泊松RV plot.png' style="zoom:50%;" />

>对应于不同的 $\lambda$ 的泊松随机变量的分布列，当 $\lambda \leqslant 1$ 时，分布列是单调递减的；当 $\lambda > 1$ 时，分布列随着 k 的递增，先递增后递减（如何证明？）
- PMF: $p_X(k)=e^{-\lambda}\frac{\lambda^k}{k!},\,\,\,\,\,\,k=0,1,2,...$

- $\sum_{k=0}^\infin e^{-\lambda}\frac{\lambda^k}{k!} = e^{-\lambda}(1+\lambda+\frac{\lambda^2}{2!}+...) = e^{-\lambda}e^\lambda=1$

- 当二项 r.v. 中的 n 很大，p 很小时，泊松 r.v. 的 PMF 无限逼近二项 r.v. 的PMF；
  $$
  e^{-\lambda}\frac{\lambda^k}{k!}\approx\frac{n!}{k!(n-k)!}p^k(1-p)^{n-k},\,\,\,\,\,\,k=0,1,2,...,n
  $$

- 泊松 r.v. 的均值
  $$
  \begin{align}
  E[X]&=\sum_{k=0}^\infin ke^{-\lambda}\frac{\lambda^k}{k!}=\sum_{k=1}^\infin ke^{-\lambda}\frac{\lambda^k}{k!}=\lambda\sum_{k=1}^\infin e^{-\lambda}\frac{\lambda^{k-1}}{(k-1)!}&\nonumber\\[1.5ex]
  &=\lambda\sum_{m=0}^\infin e^{-\lambda}\frac{\lambda^m}{m!}\,\,(let\,\,m=k-1) = \lambda&\nonumber
  \end{align}
  $$
- 泊松 r.v. 的方差
  $$
  \begin{align}
  var(X) &= E[X^2]-(E[X])^2&\nonumber\\[1.5ex]
  E[X^2]&=\sum_{k=0}^\infin k^2e^{-\lambda}\frac{\lambda^k}{k!}=\sum_{k=1}^\infin k^2e^{-\lambda}\frac{\lambda^k}{k!}=\lambda\sum_{k=1}^\infin k e^{-\lambda}\frac{\lambda^{k-1}}{(k-1)!}&\nonumber\\[1.5ex]
  &=\lambda\sum_{m=0}^\infin (m+1)e^{-\lambda}\frac{\lambda^m}{m!}\,\,(let\,\,m=k-1) = \lambda(\lambda+1)&\nonumber\\[1.5ex]
  var(X) &= E[X^2]-(E[X])^2=\lambda&\nonumber\\[1.5ex]
  \end{align}
  $$
- 图像性质的证明
  - 对应于不同的 $\lambda$ 的泊松随机变量的分布列，当 $\lambda \leqslant 1$ 时，分布列是单调递减的；当 $\lambda > 1$ 时，分布列随着 k 的递增，先递增后递减
  - 可通过证明 k 在 $[0,\lambda]$ 单调递增，在 $(\lambda, \infin)$ 单调递减证得上述结论。下面是证明过程：
  $$
  \begin{align}
  &\frac{p_X(k)}{p_X(k-1)} = \frac{e^{-\lambda}·\lambda^k}{k!}·\frac{(k-1)!}{e^{-\lambda·\lambda^{k-1}}}=\frac{\lambda}{k}\nonumber\\[1.5ex]
  &\text{if } \,\,k\in[0,\lambda],\quad \frac \lambda k\geqslant1,\,\,p_X(k)\geqslant p_X(k-1)\nonumber\\
  &\text{if } \,\,k\in(\lambda,\infin),\quad \frac \lambda k<1,\,\,p_X(k)<p_X(k-1)\nonumber\\
  \end{align}
  $$
- 泊松逼近的严格证明
  $$
  \begin{align}
  \text{condition} &:n\to\infin,\,\,p\to0, \lambda=np\,\,\text{ is constant, }\nonumber\\[1.5ex]
  p_X(k)&=\frac{n!}{(n-k)!k!}p^k(1-p)^{n-k}\nonumber\\
  &=\frac{n(n-1)···(n-k+1)}{n^k}·\frac{\lambda^k}{k!}·\left (1-\frac{\lambda}{n}\right )^{n-k}\nonumber\\
  &\to e^{-\lambda}\frac{\lambda^k}{k!}(\text{when }\,\, n\to \infin)\nonumber
  \end{align}
  $$

### 2.8 补充

#### 2.8.1 示性函数

- 示性函数（indicator function）：顾名思义，是表示自变量性态的函数，下面是示性函数的两种表示方式：

$$
I_A(\omega) = 
\begin{cases} 
1 & \text{if } \omega\in A \\
0 & \text{if } \omega\notin A
\end{cases}
\quad
X_i = 
\begin{cases}
1 & \text{if } \,\,A_i \,\, happen\\
0 & \text{if } \,\,A_i \,\, not\,\, happen 
\end{cases}
$$
- 示性函数也是一个随机变量，示性函数的期望等于它对应的事件发生的概率：

  $E[X_i] = 1·P(A_i) + 0·P(A_i^c) = P(A_i)$
- 示性函数的一些性质：
  $$
  \begin{align}
  A_i & \leftrightarrow \text{indicator } X_i & A_i^c & \leftrightarrow 1 - X_i \nonumber\\
  A_i \cap A_j & \leftrightarrow X_i X_j & A_i^c \cap A_j^c & \leftrightarrow (1 - X_i)(1 - X_j)\nonumber\\
  A_i\cup A_j & \lrarr 1-(1-X_i)(1-X_j)\nonumber
  \end{align}
  $$

#### 2.8.2 互斥定理

- $P(A_1\cup A_2) = P(A_1)+P(A_2)-P(A_1\cap A_2)$；

- $P(A_1\cup A_2\cup A_3) = P(A_1)+P(A_2)+P(A_3)-P(A_1\cap A_2) - P(A_1\cap A_3) - P(A_2\cap A_3) + P(A_1\cap A_2\cap A_3)$

- 上面两个公式很容易用文氏图推导出来，用示性函数进行推导呢？下面是推导第二个公式的过程：
  $$
  \begin{align}
  &P(A_1\cup A_2\cup A_3) = E[\text{indicator of} A_1\cup A_2\cup A_3] \nonumber\\
  &= E[1-(1-X_1)(1-X_2)(1-X_3)]\nonumber\\&= E[1 - 1 + X_1 + X_2 + X_3 - X_1X_2-X_1X_3-X_2X_3+X_1X_2X_3]\nonumber\\
  &=E[X_1]+E[X_2]+E[X_3]-E[X_1X_2]-E[X_1X_3]-E[X_2][X_3]+E[X_1X_2X_3]\nonumber\\
  &=P(A_1)+P(A_2)+P(A_3)-P(A_1\cap A_2) - P(A_1\cap A_3) - P(A_2\cap A_3) + P(A_1\cap A_2\cap A_3)\nonumber\\
  \end{align}
  $$
  
  >注意第三个等于号的因式分解，先常数，三个正一个负，所以结果为负；然后次数为 1 的项，也是数正负号，两个正两个负，所以结果为正...

- 利用类似的思想可以推出互斥定理，下面是互斥定理的内容：
  $$
  \begin{align}
  &P\left ( \bigcup_{k=1}^nA_k\right ) =\sum_iP(A_i)-\sum_{i_1<i_2}P(A_{i_1}\cap A_{i_2})\nonumber\\
  &+\sum_{i_1<i_2<i_3}P(A_{i_1}\cap A_{i_2}\cap A_{i_3})-...+(-1)^{n-1}P\left (\bigcap_{k=1}^nA_k\right )\nonumber
  \end{align}
  $$