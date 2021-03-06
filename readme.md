<!--
 * @Description: 
 * @Author: MALossov
 * @Date: 2021-12-28 13:05:29
 * @LastEditTime: 2021-12-30 00:51:28
 * @LastEditors: MALossov
 * @Reference: 
-->
# GhostTyper项目说明 
- [GhostTyper项目说明](#ghosttyper项目说明)
  - [环境依赖](#环境依赖)
  - [项目的功能](#项目的功能)
  - [项目的使用说明](#项目的使用说明)
  - [项目运行时可能发生的错误以及解决方法](#项目运行时可能发生的错误以及解决方法)
  - [项目的基本文件结构树](#项目的基本文件结构树)
  - [贡献者](#贡献者)
  - [鸣谢](#鸣谢)
  - [V0.1版本的更新](#v01版本的更新)
- [</p>](#p)

## 环境依赖 
编写者的运行环境为 **Windows11**和**Windows10**的**64**位操作系统
- ### 如果为仅安装项目生成的打包程序 
  > 打包安装程序的地址为：**.\GhostTyperV0.1\Release\GhostTyperV0.1.msi**
- 需要的磁盘空间：小于1MB
- 需要的运行内存：25MB~60MB 左右
- 注意事项：**不要将应用直接安装在C盘**
    -  原因：如果安装在C盘，容易导致需要管理员权限才能修改文件内容，导致文件内容无法修改，从而无法正常进入打字游戏和打字训练。
- ### 如果需要打开VisualStudio的项目文件
  > 项目解决方案的地址为：**.\E:\GhostTry\GhostTyper\GhostTyper.sln**
- 需要的VS版本：最低为**VS2019**，并且安装最新工具集
    - 即：SDK版本为**10.0**，平台工具集为：**v143**
    - 也可以通过对于项目SDK和工具集的重新定向，以此通过低版本的VS进行运行（已经在**VS2017**尝试过）
- C++标准：**ISO C++17 标准 (/std:c++17)** 及以上才能通过编译
    - 同时C/C++**语言**选项中：符合模式应该设置为**否**
    - 在项目使用的**编码**中设置：**多字节字符集**，而非UTF-8字符集
    - 如果无法正确调用库函数，请在VC++选项中添加包含路径：**$(SolutionDir)\Inc** 否则无法读取对应库文件

- ### 如果仅需打开可执行文件
  >项目的可执行文件为：**.\GhostTyper\GhostTyper.exe** 可以直接打开
  </p>
  
## 项目的功能
**GhostTyper**作为新生项目中完成的**英文打字训练软件**，拥有和商业软件相似的：
1. 打字训练功能 *（可以自由选择用户名和从文章库中选择需要训练的文章）*
2. 文章管理功能 *（包括增加文章和删除文章）*
3. 打字游戏功能 *（具体实现为一个字符掉落游戏）*
4. 排行榜功能 *（记录单次打字成绩的正确率并通过正确率输出为一个排行榜）*
5. 单次训练——新手引入功能 *（可以在屏幕上打印出键盘，同时键盘会高亮显示下一个需要打印的字母，来方便新手进行打字学习）*
</p>

## 项目的使用说明
- 主界面和其他子界面有可视化的按钮，可以直接鼠标点击进入；进入打字训练之后主要使用键盘完成输入。
- 本项目可以直接从按钮的标题中获得对应进入功能的提醒，不再赘述具体按钮作用
- 如果误入下一级菜单，或者**想要返回上一级菜单**，可直接按**Esc**键进行返回操作
  - 弹窗界面除外，但是大部分弹窗界面都会有**取消操作按钮**的设计来方便您的返回，点按取消按钮即可返回上一行的界面
- 本项目的设计初衷是作为英文打字练习软件，所以请务必在所有的地方输入英文，而**不要录入中文**，可能造成系统的崩溃</p> 

## 项目运行时可能发生的错误以及解决方法
- 在开始文章练习时，第一次输入符号录入的屏幕显示和录入操作之间存在一定的时间差，但是这个**时间差**中所有的**键盘操作也会被记录**
  - 在打字练习开始前的加载期，请**不要误触键盘**
- 如果文件读写失败，可能导致文件内容被完全清除
  - 请**重新安装软件**或者**复制对应文件**进入对应目录。
  >如：ArticleList.txt和Ranking.txt
- 软件在运行次数过多的时候，可能因为Windows符号系统问题而无法正确开始导致意外闪退
  - 一般可以通过重启解决
- 在项目中输入中文：如添加新文章标题和在打字时使用了中文会导致项目的崩溃。
  - 请在项目的使用过程中**避免使用中文**</p>

## 项目的基本文件结构树
大部分需要的**接口**以及**函数**可以直接在文件系统树中的对应注释描述中获得，而且**头文件**的编写比较符合规范，可以直接从对应函数命名中获取对应函数的功能。
>文件树如下↓
```cpp
├─readme.md     //项目的介绍性文件（纯文本格式）
├─readme.html     //项目的介绍性文件（Markdown网页渲染后格式）
├─GhostTyper    //项目的主文件目录
│  │  GhostTyper.sln    //工程项目解决方案的名称
│  │  GhostTyper.vcxproj    //生成项目的名称
│  │  ……    //※在此处省略Debug/.vs/Release等调试文件夹※
│  │  passage.txt   //临时文件：本次练习的文章
│  │  
│  ├─Articles   //文章和索引文件目录
│  │      ArticleList.txt   //文章目录的索引
│  │      Darkness.txt  //以下为具体的文章篇目
│  │      HighestScore.txt  //打字游戏最高成绩的存储文件
│  │      word.txt  //单词练习的单词词库
│  │      Ranking.txt   //排行榜的存储文件
│  │      ShortLife.txt //其他文章
│  │      SunShine.txt
│  │      ……
│  ├─Inc    //库文件目录
│  │      ArticleManagement.h   //基础管理界面的库文件
│  │      BasicWidget.h  //计算打表基础宽度的库文件
│  │      Configure.h   //easyX.h的功能扩展配置
│  │      GAME.h    //打字游戏的程序库
│  │      LineEdit.h    //文章管理界面打印库
│  │      Management.h  //主界面即管理系统库
│  │      PushButton.h  //按钮功能实现库
│  │      Ranking.h //排行榜打印库
│  │      RankingData.h //读取排行榜信息的库
│  │      Student.h //存储用户（学生）打字成绩需要的库
│  │      Table.h   //打印文章列表的库
│  │      Timer.h   //计时器库
│  │      typeparactise.h   //※文章练习的实现库※
│  │      window.h  //初始化窗口的库
│  │      
│  ├─Resources  //图片资源文件
│  │      BG.jpg    //基础界面背景图
│  │      TyperBG.jpg   //打字界面背景图
│  │      what.jpg  //单词训练中，键盘上的特殊符号：右键 用图片打印
│  │      windos.jpg    //键盘上的特殊符号：Win键
│  │      
│  ├─Src    //根据库函数同步生成的.cpp文件，编写具体的程序实现
│        ArticleManagement.cpp
│        BasicWidget.cpp
│        LineEdit.cpp
│        main.cpp   //※主程序入口※
│        Management.cpp
│        PushButton.cpp
│        Ranking.cpp
│        RankingData.cpp
│        Student.cpp
│        Table.cpp
│        Timer.cpp
│        window.cpp
│ 
└─GhostTyperV0.1    //项目的打包生成项目
    │  GhostTyperV0.1.vdproj    //打包项目的项目文件
    │  
    └─Realease
          GhostTyperV0.1.msi   //生成的项目安装程序（.msi)
          setup.exe    //生成的项目安装程序（.exe）   
```
</p>

## 贡献者
1. **MALossov**:因为新生项目被逼出来的编程苦手一枚
2. **ASimpleHeart**:被MALossov拉上贼船的C++苦手一枚
   
## 鸣谢
- *CSDN* 上的一件小作品 能够被我们修改用作打字训练软件的主体[打字软件小学期作品-C/C++代码类资源-CSDN文库](https://download.csdn.net/download/lurenchengwangji/10680103)
- BiliBili上的项目视频：[C++学生成绩管理系统，搭配Easyx拥有清晰简约，低调奢华的界面，如此详细的教学，学不会算我输~_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1uf4y1L75v?share_source=copy_web) 作为我们界面的主入口模板

## V0.1版本的更新
- 在文章管理界面和开始训练界面都做了**取消**按钮的设置，方便退出
- 新增了打字游戏按**Esc**键进行退出的功能
- 对于部分文件的命名规范进行了修改
- 对于文章录入换行符造成一些文章在打字训练时对齐比较困难的情况进行优化，为方便打字训练进行，录入新文章时，所有的**换行符**都会直接被修改为**空格**
- 修复了在文章首行按Backspace键会导致意外情况发生的BUG
</p>
=======
</p>

Editor:MALossov
