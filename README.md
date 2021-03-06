# <center>《面向对象程序设计课程设计》报告 </center>
[![](https://img.shields.io/github/v/release/li1553770945/course-design-GUI?include_prereleases)](https://github.com/li1553770945/course-design-GUI/releases)
[![](https://img.shields.io/github/license/li1553770945/course-design-GUI)](https://github.com/li1553770945/course-design-GUI/blob/master/LICENSE)
![](https://img.shields.io/github/repo-size/li1553770945/course-design-GUI) 
![](https://img.shields.io/badge/Qt-5.14.2-green)  
因为课设的种种要求，本项目仅做学习参考，没有实际意义。  
如访问太慢，请参见[Gitee镜像](https://gitee.com/li1553770945/course-design-GUI)，下载请见[Gitee上的发行版](https://gitee.com/li1553770945/course-design-GUI/releases)。

### <center>FIVESTAR图书管理系统的设计与实现</center>
  - [一、程序的主要功能](#1)
  - [二、系统总框架图](#2)
  - [三、系统各个类的说明](#3)
  - [四、模块分析](#4)
  - [五、比较有特色的函数](#5)
  - [六、存在的不足与对策、编程体会](#6)
  - [七、编程体会](#7)
  - [八、程序源代码](#8)

<h2 id=1>一、程序的主要功能</h2>
程序主要是按照课本要求完成，有一些细微的改动。

+ ### 前台收银模块
  用户可输入ISBN来查找一本书，可以按指定数量添加到购物车。最后可以选择结算。用户在选择时可以点击查看书的详细信息，并且可以打开书库，可以查找。
+ ### 管理模块
  + 添加：可以添加一本书。
  + 编辑：用户输入一个ISBN查找一本书，可以对找到的书进行修改或删除。
  + 修改税率：修改全局交易税率。
+ ### 报表模块  
  可以查看当前书库所有的书，并支持显示部分列，支持按特定一列排序。
<h2 id=2>二、系统总框架图</h2>

### 目录结构
```
│  .gitattributes  
│  .gitignore  
│  README.md   说明文档
│  课设GUI.sln  
│  课设GUI.vcxproj  
│  课设GUI.vcxproj.filters  
│  课设GUI.vcxproj.user  
│  
├─cpp  存储数据层的实现cpp文件
│      BookData.cpp  
│      global.cpp  
│      main.cpp    
│      Management.cpp 
│      Report.cpp 
│      Sale.cpp  
│      TitleInfo.cpp 
│      
├─GUIcpp   GUI层的实现cpp文件
│      AboutWindow.cpp
│      BookInfoWindow.cpp
│      FindWindow.cpp
│      MainWindow.cpp
│      ManageWindow.cpp
│      ReportWindow.cpp
│      SaleWindow.cpp
│      
├─GUIh  GUI层头文件
│      AboutWindow.h
│      BookInfoWindow.h
│      FindWindow.h
│      MainWindow.h
│      ManageWindow.h
│      ReportWindow.h
│      SaleWindow.h
│      
├─h   数据层头文件
│      global.h
│      library.h
│      
├─qrc  资源文件
│  │  About.qrc
│  │  MainWindow.qrc
│  │  qt_zh_CN.qm  中文翻译
│  │  
│  └─image
│          profile.jpg 关于里面的头像
│          
├─ui  qt designer设计的ui文件
│      AboutWindow.ui
│      BookInfoWindow.ui
│      FindWindow.ui
│      MainWindow.ui
│      ManageWindow.ui
│      ReportWindow.ui
│      SaleWindow.ui
│      
└─UnitTest  单元测试项目
    book.data
    pch.cpp
    pch.h
    UnitTest.vcxproj
    UnitTest.vcxproj.filters
    UnitTest.vcxproj.user
    UnitTestGlobal.cpp
    UnitTestLibrary.cpp
    
```              

  
<h2 id=3>三、系统各个类的说明</h2> 

<h2 id=4>四、模块分析</h2>
<h2 id=5>五、比较有特色的函数</h2>  

  1. global.cpp中的my_atoi和my_atof函数：原来自带的atoi和atof如果无法转换则返回0，但是有些数据，例如库存等是可能输入0的，为了区分到底是输入了0，还是输入错误，重写这两个函数，如果转换失败会返回一个负数，从而可以根据是否返回负数判断是否输入错误，如若用户本身输入负数，则本身就是错误的，因此不必担心是输入错误还是本身输入了负数（因为两种情况下输入都是错误的）。

<h2 id=6>六、存在的不足与对策、编程体会</h2>

1. ### 界面不够美观  
    虽然写了界面，但是事实上就是最最普通的界面，没有任何修饰。  
    对策：考虑到本程序为图书管理系统，因此效率至上，对于程序的美观度要求适当放宽。

2. ### 文件只在最后保存，如果中途遇突然断电等情况，修改将无法保存
    程序在打开时载入文件，关闭时重新打开文件，将所有内容重新写入文件。如果中途发生意外，所有修改都将丢失。  
    对策：可以再开一个守护线程，定时备份并在打开时检测，如果有备份提示用户是否恢复。  

3. ### 单元测试并不完善
    虽然写了单元测试，但是测试类并非全部，而是在需要的时候才加的。
<h2 id=7>七、编程体会</h2>
写代码比较多的程序和写一个简单的程序比起来，需要注意很多问题。

1. 如果写一个几十行的程序，可以把变命名为"a","b","c1","c2"等，如果是3000行的代码这样命名，估计自己就乱了。
2. 一个几十行的程序不用管单元测试，但是3000行的程序没有单元测试，任何一个函数的修改都要重新编译、运行，自己编数据，太麻烦。
<h2 id=8>八、程序源代码</h2>
这一项为上交课设报告需要，仅在上交时添加。