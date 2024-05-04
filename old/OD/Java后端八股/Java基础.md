## 常用数据结构

- 数组
  1. s
- 链表
- 栈
- 队列
- 哈希表
- 图

## String

  - **String与字符串常量池、堆**
    1. String a = "abc"  
  
  - **String不可变**
    1. 将一个已有字符串"123"重新赋值成"456"，不是在原内存地址上修改数据，而是重新指向一个新对象，新地址。
    2. 好处：便于实现字符串池、多线程安全、加快字符串处理速度


  - **String,StringBuffer,StringBuilder区别**
    
    1. String：不可变，线程安全。原因：value数组是final类型。因为不可变，所以每次操作生成新对象。
    2. StringBuffer：可变，线程安全。原因：其父类（AbstractStringBuilder）的value数组不是final类型。原因：方法实现都用了synchronized关键字。（单线程时没必要用，因为加锁了，速度慢。）
    3. StringBuiler：可变，线程不安全。原因：其父类（AbstractStringBuilder）的value数组不是final类型。（单线程时建议使用，因为没加锁，速度快。）
