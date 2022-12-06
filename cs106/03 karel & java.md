## Karel & Java

### 1、本节内容

- OBOB：Off By One Bug（少执行了一次循环）
- comment（注释）
  - 建议在所有程序顶端加上注释，表明文件名和程序的功能的简短说明
  - 建议在每个方法前加注释，方法的功能、pre-condition、post-condition
- 设计方法
  - “top down design” 自顶向下设计（建议）
  - “bootom up design”自底向上设计
- 命名方法
  - 驼峰式命名：每个单词的首字母大写（方法的首字母可以的大写也可以小写）
- 自顶向下decomposition（分解）的原则
  - solve 1 problem
  - methods 1~15
  - good names
  - comment

### 2、本节项目

- double beeper

  ![image-20221206211529475](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221206211529475.png)

  ```java
  /*
  * File: DoubleBeepers.java
  * ------------------------
  * Karel doubles the number of beepers on the corner directly
  * in front of him in the world. He then returns to his
  * original position/orientation.
  */
  
  import stanford.karel.*;
  
  public class DoubleBeepers extends SuperKarel{
  	
  	public void run() {
  		move();
  		doubleBeeperInPile();
  		moveBackward();
  	}
  	
  	/*
  	 * 将当前位置的beeper翻倍
  	 */
  	private void doubleBeeperInPile() {
  		while (beepersPresent()) {
  			pickBeeper();
  			putTwoBeepersNextDoor();
  		}
  		movePileNextDoorBack();
  	}
  	
  	/*
  	 * karel在下一个位置放置两个beeper并返回初始位置
  	 */
  	private void putTwoBeepersNextDoor() {
  		move();
  		putBeeper();
  		putBeeper();
  		moveBackward();
  	}
  	
  	/*
  	 * 将下一个位置的beeper全部移到当前位置，karel的位置不变
  	 */
  	private void movePileNextDoorBack() {
  		move();
  		while (beepersPresent()) {
  			moveOneBeeperBack();
  		}
  		moveBackward();
  	}
  	
  	/*
  	 * 将一个beeper搬到karel的后面，karel的位置不变
  	 */
  	private void moveOneBeeperBack() {
  		pickBeeper();
  		moveBackward();
  		putBeeper();
  		move();
  	}
  	
  	/*
  	 * karel向后退一步，方向不变
  	 */
  	private void moveBackward() {
  		turnAround();
  		move();
  		turnAround();
  	}
  }
  ```

- clean karel

  <img src="C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221206211605084.png" alt="image-20221206211605084" style="zoom:67%;" />

  ```java
  /*
  * File: CleanupKarel.java
  * -----------------------
  * Karel starts at (1, 1) facing East and cleans up any
  * beepers scattered throughout his world.
  */
  
  import stanford.karel.*;
  
  public class CleanupKarel extends SuperKarel {
  	
  	/* 清除区域内的所有beeper，一次一行 */
  	public void run() {
  		cleanRow();
  		while (leftIsClear()) {
  			repositionForRowToWest();
  			cleanRow();
  			if (rightIsClear()) {
  				repositionForRowToRight();
  				cleanRow();
  			} else {
  				turnAround();
  			}
  		}
  	}
  	
  	/* karel进入下一行，并朝向东边 */
  	private void repositionForRowToRight() {
  		turnRight();
  		move();
  		turnRight();
  	}
  	
  	/* karel进入下一行，并朝向西边 */
  	private void repositionForRowToWest() {
  		turnLeft();
  		move();
  		turnLeft();
  	}
  	
  	/* 清除karel面前的一行中的所有beeper */
  	private void cleanRow() {
  		if (beepersPresent()) {
  			pickBeeper();
  		}
  		while (frontIsClear()) {
  			move();
  			if (beepersPresent()) {
  				pickBeeper();
  			}
  		}
  	}
  }
  ```

  