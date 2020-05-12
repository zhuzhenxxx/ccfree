# ccfree
按照实现的功能，ccfree框架大致如下：


### 从Session到Connection再到Channel后Socket

网络框架 Connection、Channel、Socket

TcpConnection - Channel - fd

TcpConnection  - fd

Session 不属于网络框架的。


### 收发数据正确的做法

收，监听可读事件，事件触发后收取；

发，先尝试直接发，当send或者write函数表明当前tcp窗口太小发不出去再注册可写事件，下次可写事件触发后将发送缓冲区的剩余数据继续发出去后，移除监听可写事件。




   \- 三种数据库连接的管理与数据操作

   \- 缓存机制的设计

   \- 信号的处理

   \- 程序初始化

   \- 端口重用与地址重用

   \- Linux 与 Windows 平台在网络通信部件上的一些区别
   


字符串操作
----------

字符串操作函数和类，包括：

1）安全的字符串复制函数；

2）安全的字符串拼接函数；

3）安全的格式化输出到字符串的函数；

4）删除字符串左边、右边和两边指定字符的函数；

5）字符串大小写转换函数；

6）字符串替换函数；

7）从字符串中提取数字的函数；

8）正则表达式函数；

9）字符串拆分的类；

10）统计字符串字数的函数。

2、xml解析
----------

从xml格式的字符串中解析出字段。

3、日期时间
-----------

1）日期时间的获取、转换和运算；

2）把整数表示的时间转换为字符串表示的时间；

3）把字符串表示的时间转换为整数表示的时间；

4）时间运算；

5）精确到微秒的计时器。

4、目录操作
-----------

1）创建目录以及子目录；

2）递归获取目录以及子目录中的文件信息。

5、文件操作
-----------

1）打开、读取、删除、重命名、复制文件；

2）获取文件的大小和时间；

3）重置文件的时间；

4）常用的文件操作方法类。

6、日志文件
-----------
base/异步日志
把C/C++服务程序记录程序运行和数据处理的日志记录到文件中，包括日志文件的创建、切换、备份等。

7、参数文件
-----------

加载C/C++服务程序运行参数。

8、tcp网络通信
--------------

1）封装了socket系列函数，实现tcp客户端，包括报文的接收和发送；

2）封装了socket系列函数，实现tcp服务端，包括报文的接收和发送；

3）解决了tcp报文粘包的问题；

4）通信可以设置超时机制。

9、ftp客户端
------------

采用ftp协议，实现ftp客户端的常用功能。

10、Oracle数据库操作
--------------------

封装了OCI（Oracle Call Interface）函数库，实现对Oracle数据库的操作。

11、MySQL数据库操作
-------------------

封装了MySQL提供的mysqlclient函数库，实现对MySQL数据库的操作。

12、PostgreSQL数据库操作
------------------------

封装了PostgreSQL提供的pq函数库，实现对PostgreSQL数据库的操作。
