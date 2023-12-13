## 2.2 Web & HTTP

### 2.2.1 Web概况

- Web的应用层协议为超文本传输协议(HyperText Transfer Protocol, HTTP)。HTTP由两个程序实现：一个客户程序和一个服务器程序
- 一个Web页面由一个或多个对象组成，一个对象只是一个文件，可以通过一个URL地址寻址。多数Web页面包含一个HTML基本文件以及几个引用文件(比如图片或视频的URL)，因此当我们请求一个页面时，往往是对Web服务器请求多个对象，由此引出HTTP的非持续连接和持续连接

### 2.2.2 非持续连续和持续连接

**非持续连接**：每个请求/响应对经一个单独的TCP连接发送；**持续连接**：多个请求/响应对经相同的TCP连接发送（默认使用）

- 使用非持续连接和持续连接请求一个HTML基本文件和10个JPEG文件的过程：

  ![image-20231016112231652](C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231016112231652.png)

  - **RTT(Round-Trip Time，往返时间)**：指一个短分组从客户到服务器然后再返回客户所花费的时间
  - 非持续连接耗时：22RTT+11个文件的传输时间；持续连接耗时：12个RTT+11个文件的传输时间
  - 不仅一个完整的Web页面可以用单个持续TCP连接进行传送，有时位于同一台服务器的多个Web页面在从该服务器发送给同一个客户时，也可以在单个持续TCP连接上进行

### 2.2.3 HTTP报文格式

<img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231016135630395.png" alt="image-20231016135630395" style="zoom: 48%;" />

```c
/* HTTP请求报文例子 */
GET /somedir/page.html HTTP/1.1
Host: www.someschool.edu
Connection: close
User-agent; Mozilla/5.0
Accept-language: fr
```

- 第一行为**请求行**，由方法字段、URL字段和HTTP版本字段组成，常用的方法字段：GET、POST、HEAD、PUT、DELETE；其余后继行叫做**首部行**；本例中没有**实体体**，一般只有POST方法有实体体(entity body)
- **Host: 首部行**：该首部行所提供的信息是Web代理高速缓存所要求的
- **Connection: 首部行**：决定是否打开持续连接
- **User-agent: 首部行**：用来指明用户代理，即服务器发送请求的浏览器类型
- **Accept-language**: 首部行：指定对象的语言版本(如果服务器中有的话，没有就发默认的)，HTTP众多可用的内容协商首部之一

<img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231016135941150.png" alt="image-20231016135941150" style="zoom:48%;" />

```c
/* HTTP响应报文例子 */
HTTP/1.1 200 OK
Connection: close
Date: Tue, 18 Aug 2015 15:44:04 GMT
Server: Apache/2.2.3 (CenOS)
Last-Modified: Tue, 18 Aug 2015 15:11:03 GMT
Content-Length: 6821
Content-Type: text/html

(data data data data ...)
```

- 该报文包括三个部分：一个初始**状态行**、6个**首部行**、**实体体**，状态行包括三个部分，**协议版本字段、状态码和响应状态信息**
- 常见的状态码和相关短语：
  - 200 OK：请求成功，信息在响应报文中
  - 301 Moved Permanently：请求的对象已被永久转移，新的URL定义在响应报文的Location: 首部行中
  - 400 Bad Request：通用差错代码，指示请求不能被服务器理解
  - 404 Not Found：请求的文档不在服务器上
  - 505 HTTP Version Not Supported

### 2.2.4 用户与服务器的交互：cookie

HTTP服务器是**无状态**的，它不保存关于客户的任何信息，有时服务器为了限制用户的访问或希望把内容与用户身份联系起来，Web服务器希望能够识别用户，由此产生了cookie，它允许Web站点对用户进行跟踪。**cookie**技术有**四个组件**：

- 在HTTP响应报文中的一个cookie首部行，set-cookie:
- 在HTTP请求报文中的一个cookie首部行，cookie:
- 在用户端系统中保留有一个cookie文件，由用户的浏览器进行管理
- 位于Web站点的一个后端数据库

<img src="C:\Users\ndream\AppData\Roaming\Typora\typora-user-images\image-20231016142313583.png" alt="image-20231016142313583" style="zoom:50%;" />

### 2.2.5 Web缓存

Web缓存也叫代理服务器(proxy server)，它是能够代表初始Web服务器来满足HTTP请求的网络实体，它有自己的磁盘存储空间并在存储空间中保存最近请求过的对象的副本

在因特网上**部署Web缓存的两个原因**：

- 首先，Web缓存器可以大大减少对客户请求的响应时间，特别是当客户与初始服务器之间的瓶颈带宽远低于客户与Web缓存器之间的瓶颈带宽时
- Web缓存器能够大大减少一个机构的接入链路到因特网的通信量

### 2.2.6 条件GET方法

尽管高速缓存能够减少用户感受到的响应时间，但也引入了一个问题，即存放在缓存器中的对象副本可能是陈旧的。这个问题可以使用条件GET进行解决，下面是**条件GET解决Web缓存信息老旧的问题**的一个例子：

```c
/** 首先客户向Web服务器发送了一个请求报文，
这个请求报文实际上并没有发送给服务器，而是发送给了Web缓存器，
Web缓存器接收到请求信息后先判断缓存器中有没有该对象，
如果没有，Web缓存器将向初始服务器发送请求报文 */
GET /fruit/kiwi.gif HTTP/1.1
Host: www.abc.com

/* Web服务器向缓存器发送具有被请求的对象的响应报文 */
HTTP/1.1 200 OK
Date: Tue, 18 Aug 2015 15:44:04 GMT
Server: Apache/2.2.3 (CenOS)
Last-Modified: Tue, 18 Aug 2015 15:11:03 GMT
Content-Type: image/gif

(data data data data ...)

/* 缓存器将对象转发到请求的浏览器并在本地缓存该对象 */

/* 过了一段时间后，有一个用户想要访问相同的信息，Web缓存接收到请求报文，
发现缓存中有该对象，但是该对象有可能被修改了，
所以缓存器会向初始服务器发送一个条件GET执行最新检查 */
GET /fruit/kiwi.gif HTTP/1.1
Host: www.abc.com
If-modified-since: Tue, 18 Aug 2015 15:11:03 GMT	// 该值等于得到该对象时的Last-Modified

/* Web服务器接收到条件GET后，告诉缓存器没有被修改 */
HTTP/1.1 304 Not Modified
Date: Tue, 25 Aug 2015 16:41:04 GMT
Server: Apache/2.2.3 (CenOS)

(empty entity body)

/* 缓存器接收到响应报文后，将缓存器中的对象通过响应报文发送给用户浏览器 */
```



