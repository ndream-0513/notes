第五、六章的主要内容：设计CPU内部的控制器，控制器需要什么功能呢？从主存中取指令，然后执行指令，也就是根据这条指令的功能产生有严格时间顺序的控制信号，控制计算机中的各个模块协同工作完成这条指令的功能，当这条指令执行完成之后，通常会顺序从主存中取下一条指令并执行。 

指令在计算机中是如何进行编码的？如何设置CPU的指令集

 ## 4.1 指令系统概述

**指令系统**（指令集）：一台计算机所能执行的全部指令的集合

**程序**由一系列具有时间顺序和逻辑关系的指令构成，指令是计算机运行的最小单位

**指令系统的设计**主要包括**指令的功能**（操作类型、具体操作内容）和**指令的格式**（在计算机中如何存储的）的设计

如何**评价**指令系统：完备性；高效性；规整性（格式尽可能简单）；兼容性

指令的基本格式：

![image-20230927090036807](C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230927090036807.png)

数据在主存中是如何进行存储的？

## 4.2 指令系统的结构层定义

### 4.2.1 存储模式

#### 1.数据存储顺序

![image-20230927091046950](C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230927091046950.png)

- 用哪个地址代表数据的地址？

  无论是大端存储方式还是小端存储方式，都用最小的地址代表数据地址

#### 2.边界对齐

<img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230927092821001.png" alt="image-20230927092821001" style="zoom:67%;" />

- 为了保证计算机的读取性能，一般使用边界对齐的方式对数据进行存储，虽然使用边界未对齐的方式也能对数据进行存储，但是读取时的性能较低，比如上述例子中，使用边界对齐读取第一个数据只需要一个时钟周期，而边界未对齐方式则需要两个时钟周期

#### 3.堆栈

这里的堆栈相当于数据结构中的栈

- PUSH、POP指令；隐含寻址
- 管理堆栈的三个地址寄存器：SP、SB、SL
  - Stack Pointer（堆栈指针，**指向栈顶上面的空指针**）、Stack Base（堆栈基址）、Stack Limit（堆栈界限）
- 堆栈的应用：
  - 作为临时**存储区域**
  - CALL指令，保存**返回地址**
  - 调用过程时，传递**参数**
  - 保存过程内的**局部变量**
- 防止堆栈操作错误：大小要合理；push和pop操作要成对进行，防止堆栈溢出；最好将系统堆栈和用户堆栈分开；

#### 4.冯·诺伊曼结构和哈佛结构

<img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230927100014345.png" alt="image-20230927100014345" style="zoom:67%;" />

指令流水线：→取指令→取数→执行→存数→

- 当这四条指令可以做到同时运行时，能够达到很高的并行度
- 取数和取指令操作都要访问主存，如果使用冯诺依曼结构，则不可能实现同时运行，但采用哈佛结构可以实现这两个指令的同时运行
- 目前一般在**芯片内部采用哈佛结构**（一级指令Cache和一级数据Cache），**芯片外部采用冯诺依曼结构**（如果主存采用哈佛结构，则需要两套总线系统，设计起来比较复杂，因此采用一种折中的方案）

## 4.3 指令设计

### 4.3.1 指令的功能设计

指令的典型分类：数据传送类；算术运算类；逻辑运算类；数据转换类（可选 ）；输入/输出类；系统控制类；程序控制类（转移、循环控制、过程调用和返回、程序自中断）；

计算机是通过读取输入/输出设备和系统总线之间的接口中的寄存器的数据来获得输入/输出设备的信息的，计算机对输入/输出设备的控制是通过往接口中的寄存器写入数据来实现的，因此就需要给这些寄存器相应的地址

<img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230927104621842.png" alt="image-20230927104621842" style="zoom:67%;" />

### 4.3.2 指令的格式设计

#### 1.基本寻址方式：获取操作数的方式

![image-20230927112406803](C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230927112406803.png) 

![image-20230927112433008](C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230927112433008.png)

![image-20230927112502484](C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230927112502484.png)

<img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20230930213427060.png" alt="image-20230930213427060" style="zoom:67%;" />

#### 2.操作码的设计

- 指令长度的设计（指令字长与机器字长无固定关系）    

  | 一般原则                                                     | 常用方案                                                     |
  | ------------------------------------------------------------ | ------------------------------------------------------------ |
  | - 指令长度为存储器**最小可寻址单位**的整数倍：CISC（x86）<br />- 指令长度一般设计为**总线宽度**的整数倍：RISC | - 变长操作码，变长指令码：CISC（x86）<br />- 定长操作码，定长指令码：RISC<br />    - MIPS，6位定长操作码，32位定长指令码<br />    - RISC-V，7位定长操作码，32位定长指令码 |

- 操作码设计举例，某型号计算机共有14条指令，各条指令的使用频率分别为：0.01、0.15、0.12、0.03、0.02、0.04、0.02、0.04、0.01、0.13、0.15、0.14、0.11、0.03

  - **定长操作码设计**

    - 14条指令，$2^n\geq14$，n = 4，编码长度均为4，平均码长：H = 4

      | 频率 | 0.15 | 0.15 | 0.14 | 0.13 | 0.12 | 0.11 | 0.04 | 0.04 | 0.03 | 0.03 | 0.02 | 0.02 | 0.01 | 0.01 |
      | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
      | 编码 | 0000 | 0001 | 0010 | 0011 | 0100 | 0101 | 0110 | 0111 | 1000 | 1001 | 1010 | 1011 | 1100 | 1101 |

      优点：操作码构造简单；硬件设计简单；译码速度快；

      缺点：操作码占的存储空间大；指令规模扩充受限

  - 变长操作码设计

    - 原则：（短码不能是长码的前缀）

      | 如果指令字长度固定                                           | 如果指令字长度可变                                           |
      | ------------------------------------------------------------ | ------------------------------------------------------------ |
      | 则**长地址码**对应**短操作码**，操作码长度随地址码长度缩短而增加 | 则以指令使用频度作为设计依据，使用**频度高**的指令用**短码**，使用**频度低**的指令用**长码**（霍夫曼编码） |

    - **Huffman编码**

      将数据从大到小排列，将最小的两个数连到一起构成一个新数，再在这个新集合中找两个最小的连到一起构成一个新数，直到只剩一个数

      ![image-20231001141635614](C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231001141635614.png)

      - 平均编码长度：$H = \sum_{i=1}^np_il_i$

        H = (0.15 + 0.15 + 014 + 0.13 + 0.12 + 0.11) X 3 + 0.04 X 4 + (0.04 + 0.03 + 0.03 + 0.02 + 0.02) X 5 + (0.01 + 0.01) X 6 = 0.8 X 3 + 0.16 + 0.14 X 5 + 0.02 X 6 = 3.38 

      - Huffman**编码不唯一**（0、1对换；合并次序），但Huffman编码的**平均码长**是**唯一**的

      - 操作码的编码种类较多，控制器译码的时候比较麻烦，在设计变长操作码时，要求平均编码长度要尽可能最优，但同时也要求编码长度的种类不能太多，编码长度的种类太多会导致控制器的设计比较复杂，因此，一般采用扩展操作码的方法

    - 两种码长的**扩展操作码**

      将14种频度分为大概率（6）和小概率（8）两种，大概率的使用短码编码，小概率的使用长码编码，先对短码进行编码，$2^x > 6$（不能为 =，短码不能是长码的前缀，如果为=，则短码必为长码的前缀），$x = 3，$$(2^3-6)*2^y \geq 8，y = 2$

      <img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231001144909211.png" alt="image-20231001144909211" style="zoom:67%;" />

    - 基于特定规则的扩展操作码

      <img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231001145152784.png" alt="image-20231001145152784" style="zoom:67%;" />

    - 根据地址码数量扩展操作码  

      <img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231001145604686.png" alt="image-20231001145604686" style="zoom:67%;" />

      <img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231001145643349.png" alt="image-20231001145643349" style="zoom:67%;" />