# 电子科技大学2023级 计算机图形学实验



## 实验内容

三维图形绘制，几何变换，观察变换，视角切换

3d模型导入 (.obj格式)

贝塞尔曲线绘制

分形图形



## 项目构成

```
ProjectRoot/
│
├── head/                       # 头文件目录
│   ├── matrix.h                # 矩阵运算相关功能，键鼠函数
│   ├── shader.h                # 着色器管理相关功能
│   ├── model.h                 # 模型加载及处理
│   ├── Bezier.h                # Bezier曲线生成
│   ├── Window.h                # 窗口管理相关功能
│   └── Vertices.h              # 顶点数据读取与绘制
│
├── src/                        # 源文件目录
│   ├── matrix.cpp              # matrix.h 的实现文件
│   ├── shader.cpp              # shader.h 的实现文件
│   ├── model.cpp               # model.h 的实现文件
│   ├── Bezier.cpp              # Bezier.h 的实现文件
│   ├── Window.cpp              # Window.h 的实现文件
│   └── Vertices.cpp            # Vertices.h 的实现文件
│
├── lib/                        # 第三方库目录
│   ├── glad/                   # OpenGL 函数加载库
│   │   ├── glad.h
│   │   └── glad.c
│   ├── glm/                    # OpenGL 数学库 (头文件库)
│   │   ├── glm.hpp
│   │   └── ...
│   ├── glut/                   # GLUT 窗口管理库
│   │   └── freeglut.lib
│   ├── assimp/                 # 模型导入库
│   │   └── ...
│   └── glfw/                   # GLFW 窗口与输入库
│       └── ...
│
├── res/                        # 资源文件目录
│
├── shader/                     # GLSL着色器目录
│
├── main.cpp                    # 前三个实验入口文件
├── test.cpp                    # 分形图形入口文件
├── CMakeLists.txt              # CMake构建的配置文件
└── README.md                   # 项目说明文档
```



## 运行环境

macos （windows亲测费劲 虽然构建用的cmake 但可能是gcc要求更加严格 会有编译错误）

```cmake
mkdir build
cd build
cmake ..
cmake --build .
./openGL_App
```

