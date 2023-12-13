## Karel

### 1、环境配置

[Stanford Engineering Everywhere | CS106A - Programming Methodology](https://see.stanford.edu/Course/CS106A)

在上面的网址中的`software`中下载好`stanford eclipse`、`java 1.6`，安装`java 1.6`将`java`的环境变量配置为`1.6`版本的，`java`版本可以在`cmd`中使用`java -version`进行查看，我之前默认的是`java17`直接打不开`eclipse`，后来换成`java1.8`也打不开，换成课程给的`java1.6`才能正常打开。

配置好`eclipse`之后，在上面的网址的`Assignment/Programming Assignments`下下载本节课的`Assignment`，通过点击eclipse的这个图标![image-20221204122021934](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221204122021934.png)将包导入进来，记得下载之后解压再导入，导入之后发现没有课程讲的`SteepleChaseKare.java`项目，自己创建一个文件，配置好地图就行

运行：点击![image-20221204123148547](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221204123148547.png)选中要运行的文件，即可运行

### 2、本节内容

- 介绍了`move();、turnLeft();、pickBeeper();、putBeeper();、frontIsClear();、beeperPresent();`方法

- 实现了`karel`障碍跑（还有其它的几个内容，没有详细写了）

  `karel`程序的入口为`public void run()`，把`run`改为其它的名字不动了，也可以写其它的`public`方法，在`run`中也能调用，一般是将其它方法写为`private`再在`run`中进行调用（具体的原理我也不清楚，有可能是`public`定义的方法在其它类中也能调用，只把需要暴露出去的方法定义为`public`类型）

  ```java
  import stanford.karel.*;
  
  public class SteepleChaseKarel extends SuperKarel {
  	
      // 前面没墙就往前走，有墙就翻墙
  	public void run() {
  		for (int i = 0; i < 9; i ++) {
  			if (frontIsClear()) {
  				move();
  			} else {
  				jumpHurdle();
  			}
  		}
  	}
  	
      // 翻墙分为三步，爬上墙，移动一下，跳下墙
  	private void jumpHurdle() {
  		ascendHurdle();
  		move();
  		descendHurdle();
  	}
  	
  	private void ascendHurdle() {
  		turnLeft();
  		while (rightIsBlocked()) {
  			move();
  		}
  		turnRight();
  	}
  	
  	private void descendHurdle() {
  		turnRight();
  		moveTheWall();
  		turnLeft();
  	}
  	
  	private void moveTheWall() {
  		while (frontIsClear()) {
  			move();
  		}
  	}
  }
  ```

- `karel`常用方法表格

  ![image-20221204122537918](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221204122537918.png)

- `karel`练手的平台[Learn to Program (stanford.edu)](https://web.stanford.edu/~cpiech/karel/learn.html)，后面几章内容好像用不了，但大部分都没问题

### 3、Assignment（作业）

- Problem 1

  `karel`在一个房子里，门外有一个`beeper`，捡起`beeper`并返回初始位置

  <img src="C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221204194535499.png" alt="image-20221204194535499" style="zoom:50%;" />

  ```java
  import stanford.karel.*;
  
  public class CollectNewspaperKarel extends SuperKarel {
  
  	// You fill in this part
  	public void run() {
  		move();
  		move();
  		turnRight();
  		move();
  		turnLeft();
  		move();
  		pickBeeper();
  		turnAround();
  		while (frontIsClear()) {
  			move();
  		}
  		turnRight();
  		move();
  		turnRight();
  	}
  }
  ```

- Problem 2

  题目要求：要求`Karel`能够使得图中每隔4列的列中都填满`beeper`（已经有的地方不可重复），起始位置是（1,1）

  ![image-20221204195739580](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221204195739580.png)

  ```java
  import stanford.karel.*;
  
  public class StoneMasonKarel extends SuperKarel {
  
  	public void run() {
  		repair();
  		goBack();
  		while (frontIsClear()) {
  			for (int i = 0; i < 4; i ++) {
  				if (frontIsClear())
  					move();
  			}
  			repair();
  			goBack();
  		}
  	}
  	
  	private void repair() {
  		turnLeft();
  		if (noBeepersPresent()) {
  			putBeeper();
  		}
  		while (frontIsClear()) {
  			move();
  			if (noBeepersPresent()) {
  				putBeeper();
  			}
  		}
  	}
  	
  	private void goBack() {
  		turnAround();
  		while (frontIsClear()) {
  			move();
  		}
  		turnLeft();
  	}
  }
  
  ```

- Problem 3

  题目要求：

  - 要求`Karel`在任意给定的矩形地图里间隔放置`beeper`
  - 同时满足下图的两种情况
  - 单行、单列的情况也要满足

  题目思路：

  第一行执行`putOddLineBeeper`之后，

  - 如果左边为空且前面为空，则下一行需要执行`putEvenLineBeeper`；
    - `putEvenLineBeeper`：在偶数位置放置`beeper`，最后的位置在一行的最左边，且面朝北
  - 如果左边不为空且前面为空，则下一行需要执行`putOddLineBeeper`；
    - `putOddLineBeeper`：在奇数位置放置`beeper`，最后的位置在一行的最右边，且面朝北

  上面的思路可以满足图中的两种情况和单行的情况，但无法满足单列的情况，为了满足单列的情况，我给判断左边为空的条件中加了一个判断当前是否有`beeper`的条件，也就是，只有左边不为空且现在位置没有`beeper`才执行`putOddLineBeeper`，其余情况都执行`putEvenLineBeeper`

  ![image-20221204205616572](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221204205616572.png)

  ```java
  /*
   * File: CheckerboardKarel.java
   * ----------------------------
   * When you finish writing it, the CheckerboardKarel class should draw
   * a checkerboard using beepers, as described in Assignment 1.  You
   * should make sure that your program works for all of the sample
   * worlds supplied in the starter folder.
   */
  
  import stanford.karel.*;
  
  public class CheckerboardKarel extends SuperKarel {
  
  	// You fill in this part
  	public void run() {
  		putOddLineBeeper();
  		while (frontIsClear()) {
  			if (leftIsBlocked() && noBeepersPresent()) {
  				move();
  				turnRight();
  				putOddLineBeeper();
  			} else {
  				goBack();
  				move();
  				turnRight();
  				putEvenLineBeeper();
  			}
  		}
  	}
  	
  	private void putEvenLineBeeper() {
  		// 这里的if是单列特判
  		if (frontIsClear()) {
  			move();
  			putBeeper();
  		}
  		while (frontIsClear()) {
  			move();
  			if (frontIsClear()) {
  				move();
  				putBeeper();
  			}
  		}
  		turnLeft();
  		goBack();
  	}
  	
  	private void putOddLineBeeper() {
  		putBeeper();
  		while (frontIsClear()) {
  			move();
  			if (frontIsClear()) {
  				move();
  				putBeeper();
  			}
  		}
  		turnLeft();
  	}
  	
  	private void goBack() {
  		turnLeft();
  		while (frontIsClear()) {
  			move();
  		}
  		turnRight();
  	}
  }
  ```

- Problem 4

  在一行的中间位置方式`beeper`

  ```java
  import stanford.karel.*;
  
  public class MidpointFindingKarel extends SuperKarel {
  
  	// You fill in this part
  	public void run() {
  		int i =	1;
  		while (frontIsClear()) {
  			move();
  			i ++;
  		}
  		turnAround();
  		for (int j = 0; j < i / 2; j ++) {
  			move();
  		}
  		putBeeper();
  		while (frontIsClear()) {
  			move();
  		}
  		turnAround();
  	}
  
  ```

  