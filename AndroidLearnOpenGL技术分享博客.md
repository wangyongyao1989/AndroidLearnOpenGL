# Android OpenGL ES 从入门到精通：AndroidLearnOpenGL 项目全解析

> 本文深入剖析 AndroidLearnOpenGL 开源项目，从架构设计到渲染管线，从基础三角形到骨骼动画，全面解读 Android 平台上 OpenGL ES 的工程实践。
>
> GitHub 仓库：[https://github.com/wangyongyao1989/AndroidLearnOpenGL](https://github.com/wangyongyao1989/AndroidLearnOpenGL)

---

## 系列文章

1. [LearnOpenGL 之入门基础](https://blog.csdn.net/wangyongyao1989/article/details/140616322)
2. [LearnOpenGL 之 3D 显示](https://blog.csdn.net/wangyongyao1989/article/details/140852160)
3. [LearnOpenGL 之摄像机](https://blog.csdn.net/wangyongyao1989/article/details/140920689)
4. [LearnOpenGL 之光照](https://blog.csdn.net/wangyongyao1989/article/details/141327017)
5. [LearnOpenGL 之 3D 模型加载](https://blog.csdn.net/wangyongyao1989/article/details/141327017)
6. [LearnOpenGL 之文字渲染](https://blog.csdn.net/wangyongyao1989/article/details/143488666)
7. [LearnOpenGL 之高级 OpenGL（1）](https://blog.csdn.net/wangyongyao1989/article/details/145014066)
8. [LearnOpenGL 之高级 OpenGL（2）](https://blog.csdn.net/wangyongyao1989/article/details/145209356)
9. [LearnOpenGL 之骨骼动画](https://blog.csdn.net/wangyongyao1989/article/details/145550197)
10. [LearnOpenGL 之 Shader 编程——用算法绘画](https://blog.csdn.net/wangyongyao1989/article/details/145782389)
11. [LearnOpenGL 之 Shader 编程——生成设计](https://blog.csdn.net/wangyongyao1989/article/details/145910039)

---

## 目录

- [一、项目概述](#一项目概述)
- [二、项目架构总览](#二项目架构总览)
- [三、构建配置与 NDK 环境](#三构建配置与-ndk-环境)
- [四、app 模块：Java 层架构设计](#四app-模块java-层架构设计)
- [五、glfoundation 模块：OpenGL ES 基础渲染](#五glfoundation-模块opengl-es-基础渲染)
- [六、glfoundation 模块：光照系统全景](#六glfoundation-模块光照系统全景)
- [七、glsenior 模块：高级 OpenGL 技术](#七glsenior-模块高级-opengl-技术)
- [八、gl3d 模块：3D 渲染进阶与骨骼动画](#八gl3d-模块3d-渲染进阶与骨骼动画)
- [九、技术总结与学习路线](#九技术总结与学习路线)

---

## 一、项目概述

AndroidLearnOpenGL 是一个基于 Android NDK + OpenGL ES 3.0/3.2 的系统性学习项目，灵感来自经典的 [LearnOpenGL](https://learnopengl.com/) 教程，将其核心概念完整移植到 Android 平台。项目以 C++ 作为渲染层语言，通过 JNI 与 Java 层通信，涵盖了从绘制第一个三角形到实现骨骼动画的完整技术栈。

项目包含四大功能模块，共计 37 个可交互的渲染 Demo：

| 模块 | 定位 | Demo 数量 | 核心技术 |
|------|------|-----------|----------|
| glfoundation | OpenGL ES 基础 | 17 | 三角形、纹理、3D 变换、摄像机、光照模型 |
| gl3d | 3D 渲染进阶 | 4 | 模型加载、文字渲染、骨骼动画 |
| glsenior | 高级 OpenGL | 11 | 深度/模板测试、混合、FBO、几何着色器、实例化 |
| glshader | GLSL 着色器编程 | 5 | 造型函数、颜色、形状、矩阵、图案 |

参考学习资源：
- LearnOpenGL 中文版：[https://learnopengl-cn.github.io/](https://learnopengl-cn.github.io/)
- LearnOpenGL 英文版：[https://learnopengl.com/](https://learnopengl.com/)

---

## 二、项目架构总览

### 2.1 多模块工程结构

项目采用 Gradle 多模块架构，`app` 为壳工程，依赖四个功能库模块：

```
AndroidLearnOpenGL/
├── app/                    # 主应用壳工程（Java 层 UI + Fragment 路由）
├── glfoundation/           # OpenGL ES 基础（C++ + JNI）
├── gl3d/                   # 3D 渲染进阶（C++ + JNI + Assimp + FreeType）
├── glsenior/               # 高级 OpenGL 技术（C++ + JNI + Assimp）
├── glshader/               # GLSL 着色器编程（C++ + JNI）
├── build.gradle            # 顶层构建配置
└── README.md
```

### 2.2 分层架构图

整个项目的技术架构分为三层：

```
┌─────────────────────────────────────────────────┐
│              Java 层 (app 模块)                   │
│  MainActivity → Fragment 路由 → GLSurfaceView    │
│       ↕ ViewModel + LiveData 事件总线             │
│       ↕ JNI 调用                                  │
├─────────────────────────────────────────────────┤
│              JNI 层 (各模块 native-lib)           │
│  JNI_OnLoad 动态注册 → 全局对象管理 → 方法分发    │
├─────────────────────────────────────────────────┤
│           C++ 渲染层 (各模块 cpp)                 │
│  着色器编译 → VBO/VAO → MVP 矩阵 → 渲染循环      │
│  GLM 数学库 + stb_image + Assimp + FreeType      │
└─────────────────────────────────────────────────┘
```

### 2.3 通信机制：ViewModel + LiveData 事件总线

Java 层的模块间通信采用 **ViewModel + LiveData** 模式，实现 Fragment 之间的解耦：

```java
// GLViewModel.java — 全局通信枢纽
public class GLViewModel extends ViewModel {
    private final MutableLiveData<FRAGMENT_STATUS> switchFragment = new MutableLiveData<>();

    public enum FRAGMENT_STATUS {
        MAIN, GL_FOUNDATION, GL_3D, GL_SENIOR, GL_SHADER
    }

    public MutableLiveData<FRAGMENT_STATUS> getSwitchFragment() {
        return switchFragment;
    }
}
```

`MainActivity` 通过 `observe()` 监听状态变化，执行 Fragment 的 `hide/show` 切换。所有 Fragment 共享同一个绑定到 Activity 作用域的 ViewModel 实例，形成**单向数据流**：

```
用户点击 MainFragment 卡片
    ↓ postValue(FRAGMENT_STATUS)
GLViewModel (LiveData)
    ↓ observe()
MainActivity → selectionFragment() → hide/show Fragment
```

---

## 三、构建配置与 NDK 环境

### 3.1 顶层构建配置

项目使用 Android Gradle Plugin 8.1.3，各模块的 NDK 配置保持一致：

```groovy
android {
    compileSdk 34
    defaultConfig {
        minSdk 26
        targetSdk 34
        externalNativeBuild {
            cmake {
                arguments '-DANDROID_TOOLCHAIN=clang',
                          '-DANDROID_ARM_MODE=arm',
                          '-DANDROID_STL=c++_static'
                cppFlags "-std=c++11 -frtti -fexceptions"
            }
        }
        ndk {
            abiFilters 'armeabi-v7a'
        }
    }
}
```

关键配置说明：

- **C++ 标准**：使用 `c++11`（glfoundation/glsenior/gl3d 使用 `gnu++14`），启用 RTTI 和异常处理
- **STL 策略**：`c++_static` 静态链接 C++ 运行时，每个 .so 自带一份 STL
- **ABI 过滤**：仅编译 `armeabi-v7a`，适合学习项目快速验证

### 3.2 第三方库集成

不同模块根据功能需求集成了不同的第三方库：

| 模块 | 第三方库 | 用途 |
|------|----------|------|
| glfoundation | GLM | 矩阵/向量数学运算 |
| glfoundation | stb_image | 图像加载 |
| glsenior | GLM + stb_image + Assimp | 数学 + 图像 + 3D 模型加载 |
| gl3d | GLM + stb_image + Assimp + FreeType | 数学 + 图像 + 模型 + 字体渲染 |

CMakeLists.txt 中通过 `target_link_libraries` 链接系统库和第三方库：

```cmake
# glfoundation 的 CMakeLists.txt
add_library(glfoundation SHARED ${src_list})
target_link_libraries(glfoundation
    android       # Android NDK
    EGL           # EGL 上下文
    GLESv3        # OpenGL ES 3.0
    OpenSLES      # 音频（预留）
    log           # Android log
)
```

---

## 四、app 模块：Java 层架构设计

### 4.1 模板方法模式：BaseFragment

所有功能 Fragment 继承自 `BaseFragment`，它采用**模板方法模式**定义统一的初始化流程：

```java
public abstract class BaseFragment extends Fragment {

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
            @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = getLayoutDataBing(inflater, container, savedInstanceState);
        initView();      // 初始化视图（创建数据列表、设置 Adapter）
        initData();      // 初始化数据（创建 JNI 调用对象）
        initObserver();  // 注册 ViewModel 观察者
        initListener();  // 绑定事件监听器
        return view;
    }

    public abstract View getLayoutDataBing(LayoutInflater inflater,
            ViewGroup container, Bundle savedInstanceState);
    public abstract void initView();
    public abstract void initData();
    public abstract void initObserver();
    public abstract void initListener();
}
```

这种设计保证了所有子 Fragment 遵循相同的生命周期顺序，代码结构高度一致。

### 4.2 Fragment 懒加载与切换策略

`MainActivity` 采用 **hide/show + 懒加载** 策略管理 Fragment，避免重复实例化和不必要的视图重建：

```java
private void selectionFragment(GLViewModel.FRAGMENT_STATUS status) {
    FragmentManager fragmentManager = getSupportFragmentManager();
    FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
    hideTransaction(fragmentTransaction);  // 先隐藏所有 Fragment

    switch (status) {
        case GL_FOUNDATION:
            if (mFoundationFragment == null) {
                mFoundationFragment = new GLFoundationFragment();
                fragmentTransaction.add(mFlGlFoundation.getId(), mFoundationFragment);
            }
            fragmentTransaction.show(mFoundationFragment);
            fragmentTransaction.commit();
            break;
        // 其他 case 同理...
    }
}
```

三个 `FrameLayout` 容器的分配策略：
- `fl_gl_main`：承载 MainFragment（主菜单）
- `fl_gl_foundation`：承载 GLFoundationFragment
- `fl_gl_3d`：承载 GL3DShowFragment、GLSeniorFragment、GLShaderShowFragment（三者共用）

### 4.3 JNI 调用模式

每个子模块都有独立的 JNI 封装类，Fragment 在 `initData()` 中实例化，并在创建 GLSurfaceView 时作为构造参数传入：

```java
// GLFoundationFragment.java
@Override
public void initData() {
    mFounationJniCall = new GLFounationJniCall();  // 来自 glfoundation 模块
}

@Override
public void initView() {
    SideAdapter adapter = new SideAdapter(data, item -> {
        mBinding.glShow.removeAllViews();  // 清除旧的 GL View
        switch (item.getId()) {
            case 1:
                mBinding.glShow.addView(
                    new GL3FoundationView(getActivity(), mFounationJniCall));
                break;
            case 2:
                mBinding.glShow.addView(
                    new GL3TextureView(getActivity(), mFounationJniCall));
                break;
            // ... 更多 case
        }
    });
}
```

JNI 对象的生命周期与 Fragment 一致，GLSurfaceView 子类内部通过 JNI 对象调用 C/C++ 层的 OpenGL 渲染函数。

### 4.4 RecyclerView 适配器设计

项目使用两种适配器：

- **MainAdapter**：主菜单网格布局（GridLayoutManager 2 列），使用 MaterialCardView 卡片
- **SideAdapter**：侧边栏列表布局（LinearLayoutManager），水平排列图标 + 文字

两者都通过回调接口 `OnItemClickListener` 将点击事件传递给 Fragment 处理，实现了 View 与逻辑的解耦。

---

## 五、glfoundation 模块：OpenGL ES 基础渲染

### 5.1 JNI 动态注册机制

glfoundation 模块使用 **JNI 动态注册** 而非静态注册，在 `JNI_OnLoad` 中通过 `RegisterNatives` 一次性注册所有 native 方法：

```cpp
// native-lib.cpp
static const JNINativeMethod methods[] = {
    {"native_foundation_init_opengl",  "(II)Z",  (void *)cpp_foundation_init_opengl},
    {"native_foundation_render_frame", "()V",    (void *)cpp_foundation_render_frame},
    {"native_foundation_set_glsl_path","(Ljava/lang/String;Ljava/lang/String;)V",
        (void *)cpp_foundation_set_glsl_path},
    // ... 共约 70+ 个方法注册
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **)&env, JNI_VERSION_1_6);
    jclass clazz = env->FindClass("com/wangyongyao/glfoundation/GLFounationJniCall");
    env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0]));
    return JNI_VERSION_1_6;
}
```

动态注册的优势在于：方法名不受 JNI 命名规范约束，代码更整洁；注册集中管理，易于维护。

每个场景通过全局指针管理，采用**懒加载**模式：

```cpp
OpenglesFoundation *openglesFoundation = nullptr;
OpenglesTexture *openglTexture = nullptr;
Opengles3D *opengl3D = nullptr;
// ... 共 16 个场景对象

// 初始化时检查 null，首次调用才 new
if (openglesFoundation == nullptr) {
    openglesFoundation = new OpenglesFoundation();
    return openglesFoundation->setupGraphics(w, h);
}
```

### 5.2 着色器系统：双类设计

项目设计了两个着色器类，对应不同的渲染场景需求：

#### OpenGLSingleShaderBase — 单着色器基类

用于只需要一个着色器程序的场景（三角形、矩形、纹理、3D 等）：

```cpp
class OpenGLSingleShaderBase {
protected:
    GLuint shaderProgram;
    unsigned int VBO, VAO, EBO;
    const char *gVertexShaderCode;
    const char *gFragmentShaderCode;

public:
    GLuint createProgram(const char *vertexSource, const char *fragmentSource);
    GLuint loadShader(GLenum shaderType, const char *source);
    void getSharderPath(const char *vertexPath, const char *fragmentPath);

    // uniform 工具函数
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setVec3(const std::string &name, glm::vec3 value);
    void setMat4(const std::string &name, glm::mat4 value);

    // 纯虚函数，强制子类实现
    virtual void setSharderPath() = 0;
    virtual bool setupGraphics(int w, int h) = 0;
    virtual void renderFrame() = 0;
};
```

#### OpenGLShader — 独立着色器类

用于光照场景（需要两个独立着色器程序：一个渲染被照物体，一个渲染光源立方体）：

```cpp
class OpenGLShader {
public:
    GLuint shaderId;

    GLuint createProgram();  // 使用成员变量中的着色器源码
    void use() { glUseProgram(shaderId); }
    // 同样提供完整的 uniform 工具函数...
};
```

### 5.3 着色器编译链接流程

所有着色器的编译链接遵循统一的流程：

```
GLSL 文件路径（Java 传入）
    ↓ getSharderPath() — ifstream 读取文件内容
const char* 着色器源码
    ↓ loadShader()
glCreateShader → glShaderSource → glCompileShader → glGetShaderiv 检查编译状态
    ↓ createProgram()
glCreateProgram → glAttachShader(vert) → glAttachShader(frag)
    → glLinkProgram → glGetProgramiv 检查链接状态
最终得到 shaderProgram
```

着色器源码通过 `ifstream` + `stringstream` 从文件读取：

```cpp
void getSharderPath(const char *vertexPath, const char *fragmentPath) {
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);

    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    gVertexShaderCode = vShaderStream.str().c_str();
    gFragmentShaderCode = fShaderStream.str().c_str();
}
```

### 5.4 渲染流程演进

#### 5.4.1 第一步：绘制三角形

最基础的渲染场景，展示 OpenGL ES 的完整渲染管线：

```cpp
// OpenglesFoundation.cpp — 矩形渲染（使用 EBO 索引绘制）
float vertices[] = {
     0.5f,  0.5f, 0.0f,   // 右上
     0.5f, -0.5f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f    // 左上
};
unsigned int indices[] = { 0, 1, 3, 1, 2, 3 };  // 两个三角形

// VAO/VBO/EBO 标准流程
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

// Uniform 动画：使用 sin 波动产生颜色变化
float timeValue = clock() / 1000000.0;
float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
setVec3("ourColor", vec3(0.0f, greenValue, 0.0f));

// 索引绘制
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

#### 5.4.2 第二步：纹理渲染

在基础图形上引入纹理，顶点属性扩展为位置(3) + 颜色(3) + 纹理坐标(2)：

```cpp
// 顶点数据：位置 + 颜色 + 纹理坐标，stride = 8 * sizeof(float)
float vertices[] = {
    // 位置              // 颜色            // 纹理坐标
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

// 纹理加载
stbi_set_flip_vertically_on_load(true);  // Y 轴翻转
unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

glGenTextures(1, &texture1);
glBindTexture(GL_TEXTURE_2D, texture1);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
             GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);

// 纹理参数
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// 双纹理混合
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);
setInt("texture1", 0);

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);
setInt("texture2", 1);
```

#### 5.4.3 第三步：3D 变换与 MVP 矩阵

引入模型(Model)、视图(View)、投影(Projection)矩阵，实现 3D 效果：

```cpp
// Opengles3D.cpp
void renderFrame() {
    // 模型矩阵：旋转
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)timeValue * glm::radians(50.0f),
                        glm::vec3(0.5f, 1.0f, 0.0f));

    // 视图矩阵：后退
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // 投影矩阵：透视投影
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

    // 传入着色器
    setMat4("model", model);
    setMat4("view", view);
    setMat4("projection", projection);
}
```

对应的顶点着色器：

```glsl
#version 320 es
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
```

#### 5.4.4 第四步：立方体与深度测试

从 2D 平面到 3D 立方体，需要 36 个顶点（6 面 × 2 三角形 × 3 顶点）并启用深度测试：

```cpp
// OpenglesCube3D.cpp
bool setupGraphics(int w, int h) {
    // ... 着色器编译、VAO/VBO 设置 ...

    glEnable(GL_DEPTH_TEST);  // 启用深度测试
    return true;
}

void renderFrame() {
    // 注意：同时清除颜色缓冲和深度缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 36);  // 36 个顶点
}
```

#### 5.4.5 第五步：多立方体场景

通过循环设置不同的 model 矩阵，渲染 10 个立方体：

```cpp
// OpenglesMultiCube3D.cpp
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    // ... 共 10 个位置
};

for (unsigned int i = 0; i < 10; i++) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i;
    model = glm::rotate(model, glm::radians(angle),
                        glm::vec3(1.0f, 0.3f, 0.5f));
    setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
```

#### 5.4.6 第六步：摄像机系统

`Camera3D` 类实现基于欧拉角的 FPS 摄像机：

```cpp
class Camera3D {
public:
    glm::vec3 Position, Front, Up, Right, WorldUp;
    float Yaw   = -90.0f;  // 水平偏航角
    float Pitch = 0.0f;    // 垂直俯仰角
    float MovementSpeed = 1.5f;
    float MouseSensitivity = 0.1f;
    float Zoom = 45.0f;    // FOV

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessXYMovement(float xoffset, float yoffset) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        Yaw   += xoffset;
        Pitch += yoffset;
        // 限制 Pitch 在 [-89, 89] 度
        if (Pitch > 89.0f)  Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
        updateCameraVectors();
    }

    void ProcessScroll(float yoffset) {
        Zoom -= (float)yoffset;
        if (Zoom < 25.0f)  Zoom = 25.0f;
        if (Zoom > 100.0f) Zoom = 100.0f;
    }

private:
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
```

Android 触摸事件的处理：

```cpp
void setMoveXY(float dx, float dy, int actionMode) {
    float xoffset = dx - lastX;
    float yoffset = lastY - dy;  // Y 轴反转
    lastX = dx;
    lastY = dy;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
    float scale;
    if (scaleFactor > 1)
        scale = (scaleFactor - 1) * 1000 + 45;
    else
        scale = 50 - (1 - scaleFactor) * 1000;
    mCamera.ProcessScroll(scale);
}
```

---

## 六、glfoundation 模块：光照系统全景

光照系统是该项目的核心亮点之一，通过 11 个渐进式 Demo 完整展示了 Phong 光照模型的构建过程。所有光照场景采用**双着色器架构**：`lightColorShader`（渲染被照物体）+ `lightCubeShader`（渲染光源立方体），共享同一 VBO 但使用不同 VAO。

### 6.1 环境光照

最基础的光照——环境光，模拟光线在环境中的散射：

```glsl
// light_color_fragment.glsl
void main() {
    vec3 ambient = 0.2 * lightColor;
    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
}
```

### 6.2 漫反射光照

引入法线和光线方向，计算入射角对光照强度的影响：

```glsl
// diffuse_reflection_color_fragment.glsl
in vec3 Normal;     // 法线
in vec3 FragPos;    // 片段位置

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    vec3 ambient = 0.2 * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);  // 入射角余弦
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
```

### 6.3 镜面光照（Phong 模型）

引入观察方向和反射方向，计算高光效果：

```glsl
// specular_color_fragment.glsl
uniform vec3 viewPos;  // 观察者位置

void main() {
    // 环境光 + 漫反射（同上）
    vec3 ambient = 0.2 * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);  // 32 是反光度
    vec3 specular = 0.5 * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
```

### 6.4 材质系统

将光照参数封装为结构体，实现材质的灵活配置：

```glsl
// material_color_fragment.glsl
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main() {
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
```

C++ 端通过动态颜色让光源随时间变化：

```cpp
// 动态光源颜色
glm::vec3 lightColor;
lightColor.x = sin(timeValue * 2.0f);
lightColor.y = sin(timeValue * 0.7f);
lightColor.z = sin(timeValue * 1.3f);
```

### 6.5 漫反射贴图

将 `material.diffuse` 从 `vec3` 改为 `sampler2D`，用纹理采样替代固定颜色：

```glsl
// diffuse_map_color_fragment.glsl
struct Material {
    sampler2D diffuse;  // 纹理代替颜色
    vec3 specular;
    float shininess;
};

void main() {
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff *
                   texture(material.diffuse, TexCoords).rgb;
    // ...
}
```

### 6.6 镜面光贴图

`material.specular` 也改为 `sampler2D`，允许不同区域有不同的镜面反射强度——例如金属部分高反射，布料部分不反射。

### 6.7 平行光

模拟太阳光，使用方向而非位置，无衰减：

```glsl
// direction_light_color_fragment.glsl
struct Light {
    vec3 direction;  // 方向代替位置
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

void main() {
    vec3 lightDir = normalize(-light.direction);  // 反向作为入射方向
    // ... 其余计算相同
}
```

### 6.8 点光源衰减

随距离增加而减弱的光照，使用二次衰减公式：

```glsl
// attenuation_light_color_fragment.glsl
void main() {
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant
                             + light.linear * distance
                             + light.quadratic * distance * distance);

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
}
```

C++ 端设置衰减参数：

```cpp
setFloat("light.constant", 1.0f);
setFloat("light.linear",   0.09f);
setFloat("light.quadratic", 0.032f);
// 这组参数对应约 50m 的光照范围
```

### 6.9 聚光手电筒（硬边缘）

模拟手电筒效果，光照限定在一个圆锥范围内：

```glsl
// flash_light_color_fragment.glsl
void main() {
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    if (theta > light.cutOff) {
        // 聚光范围内：完整光照
        // ambient + diffuse + specular
    } else {
        // 聚光范围外：仅环境光
        FragColor = vec4(light.ambient * objectColor, 1.0);
    }
}
```

光源跟随摄像机移动：

```cpp
setVec3("light.position",  mCamera.Position);  // 灯光位置 = 相机位置
setVec3("light.direction", mCamera.Front);     // 灯光方向 = 相机朝向
setFloat("light.cutOff",   glm::cos(glm::radians(12.5f)));  // 切光角
```

### 6.10 软边缘聚光

引入 `outerCutOff` 实现平滑过渡，消除硬边缘：

```glsl
// spot_light_color_fragment.glsl
void main() {
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse  *= intensity;
    specular *= intensity;
    // ambient 不受影响
}
```

### 6.11 多光源组合

终极光照场景，同时组合 1 个平行光 + 4 个点光源 + 1 个聚光：

```glsl
// multi_light_color_fragment.glsl
#define NR_POINT_LIGHTS 4

struct DirLight   { vec3 direction; vec3 ambient, diffuse, specular; };
struct PointLight { vec3 position;  vec3 ambient, diffuse, specular;
                    float constant, linear, quadratic; };
struct SpotLight  { vec3 position, direction; float cutOff, outerCutOff;
                    vec3 ambient, diffuse, specular;
                    float constant, linear, quadratic; };

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

// 计算函数
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}
```

多光源场景的顶点着色器使用了正确的法线矩阵变换：

```glsl
// multi_light_color_vertex.glsl
void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    // 法线矩阵 = transpose(inverse(model))，处理非均匀缩放
    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
```

### 6.12 光照场景顶点数据演进

| 场景 | 顶点属性 | stride | 新增内容 |
|------|---------|--------|----------|
| 环境光 | 位置(3) | 3 | 基础 |
| 漫反射 | 位置(3)+法线(3) | 6 | 法线 |
| 镜面光 | 位置(3)+法线(3) | 6 | 同上 |
| 材质 | 位置(3)+法线(3) | 6 | 结构体 |
| 漫反射贴图 | 位置(3)+法线(3)+UV(2) | 8 | 纹理坐标 |
| 镜面光贴图 | 位置(3)+法线(3)+UV(2) | 8 | 双纹理 |

---

## 七、glsenior 模块：高级 OpenGL 技术

glsenior 模块基于 OpenGL ES 3.2，涵盖了 11 项高级渲染技术。JNI 注册到 `com/wangyongyao/GLSeniorCallJni` 类，管理 12 个渲染模块实例。

### 7.1 深度测试

深度测试确保 3D 场景中物体的遮挡关系正确：

```cpp
// GLSeniorDepthTest.cpp
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);  // 小于当前深度值的片段通过测试
```

场景包含两个立方体和一个地面平面，通过深度测试正确处理遮挡关系。

### 7.2 模板测试：物体轮廓

模板测试的经典应用——实现物体描边效果，采用**两遍渲染**策略：

```cpp
// GLSeniorStencilTest.cpp

// 初始化
glEnable(GL_STENCIL_TEST);
glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  // 通过时替换模板值

void renderFrame() {
    // 第一阶段：绘制地面，禁止写入模板
    glStencilMask(0x00);
    drawFloor();

    // 第二阶段：第一遍 — 绘制物体，模板值写为1
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    drawContainers();

    // 第三阶段：第二遍 — 绘制放大的单色轮廓
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);  // 模板值不等于1时渲染
    glStencilMask(0x00);                   // 禁止写入模板
    glDisable(GL_DEPTH_TEST);              // 关闭深度测试，轮廓不被遮挡
    drawScaledContainers(1.1f);            // 放大 1.1 倍，单色着色器
}
```

轮廓着色器输出固定颜色：

```glsl
// stencil_single_color_fragment.glsl
void main() {
    FragColor = vec4(0.04, 0.28, 0.26, 1.0);  // 固定青色
}
```

### 7.3 混合：丢弃与排序

#### 7.3.1 Alpha 丢弃

对于完全透明或完全不透明的纹理（如草地），使用 `discard` 丢弃透明片段：

```glsl
// blending_discard_fragment.glsl
void main() {
    vec4 texColor = texture(texture1, TexCoords);
    if (texColor.a < 0.1)
        discard;  // alpha < 0.1 的片段直接丢弃，不写入缓冲
    FragColor = texColor;
}
```

#### 7.3.2 半透明混合与排序

对于半透明物体，需要启用混合并按距离排序：

```cpp
// GLSeniorBlendingSort.cpp
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// 使用 std::map 按距离自动排序
std::map<float, glm::vec3> sorted;
for (unsigned int i = 0; i < windows.size(); i++) {
    float distance = glm::length(mCamera.Position - windows[i]);
    sorted[distance] = windows[i];
}

// 逆序遍历（从远到近）绘制
for (auto it = sorted.rbegin(); it != sorted.rend(); ++it) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, it->second);
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
```

### 7.4 立方体贴图与天空盒

#### 7.4.1 立方体贴图加载

```cpp
// GLSeniorCubeMap.cpp
unsigned int loadCubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // 6 个面：右、左、上、下、前、后
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(),
                                        &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                     width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
```

#### 7.4.2 天空盒渲染技巧

天空盒渲染有两个关键技巧：

```cpp
// 技巧 1：移除视图矩阵的平移分量，让天空盒始终包围摄像机
glm::mat4 view = glm::mat4(glm::mat3(mCamera.GetViewMatrix()));

// 技巧 2：改变深度测试函数
glDepthFunc(GL_LEQUAL);  // 小于等于，让深度值 1.0 的天空盒通过测试
```

天空盒着色器中，将 z 分量设为 w，使深度值始终为 1.0（最远）：

```glsl
// cube_map_skybox_vertex.glsl
void main() {
    TexCoords = aPos;  // 位置直接作为采样方向
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;  // z = w，深度值 = 1.0
}
```

### 7.5 反射

利用立方体贴图实现镜面反射效果：

```glsl
// reflection_vertex.glsl
out vec3 Normal;
out vec3 Position;

void main() {
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

// reflection_fragment.glsl
in vec3 Normal;
in vec3 Position;
uniform vec3 cameraPos;
uniform samplerCube skybox;

void main() {
    vec3 I = normalize(Position - cameraPos);    // 入射方向
    vec3 R = reflect(I, normalize(Normal));      // 反射方向
    FragColor = vec4(texture(skybox, R).rgb, 1.0);  // 采样天空盒
}
```

### 7.6 FBO 帧缓冲与后期处理

#### 7.6.1 FBO 创建

```cpp
// GLSeniorFBO.cpp
void setupFBO() {
    // 1. 生成帧缓冲对象
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // 2. 创建颜色附件纹理
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, NULL);  // 不初始化数据
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, textureColorbuffer, 0);

    // 3. 创建渲染缓冲对象（深度+模板）
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, rbo);

    // 4. 检查完整性
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LOGE("Framebuffer not complete!");
}
```

#### 7.6.2 渲染流程

```cpp
void renderFrame() {
    // 第一遍：绑定 FBO，正常渲染场景
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawScene();  // 绘制 3D 场景到 FBO 纹理

    // 第二遍：绑定默认帧缓冲，绘制全屏四边形
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    screenShader.use();
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    drawScreenQuad();  // 采样 FBO 纹理绘制到屏幕
}
```

#### 7.6.3 后期处理效果

`GLFBOPostProcessing` 支持动态切换 4 种后处理效果，通过切换 fragment shader 实现：

```cpp
// 检测效果切换
if (m_filter != m_prevFilter) {
    m_prevFilter = m_filter;
    delete_program(screenProgram);           // 删除旧着色器程序
    screenShader->getSharderStringPath(
        m_vertexStringPath,
        m_fragmentStringPathes.at(m_prevFilter));  // 加载新着色器
    createPostProcessingProgram();           // 创建新程序
}
```

灰度化效果着色器：

```glsl
// fbo_post_gray_scale_fragment.glsl
void main() {
    FragColor = texture(screenTexture, TexCoords);
    float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
    FragColor = vec4(average, average, average, 1.0);
}
```

核效果（边缘检测）着色器，使用 3×3 卷积核：

```glsl
// fbo_post_nuclear_effect_fragment.glsl
const float offset = 1.0 / 300.0;
vec2 offsets[9] = vec2[](
    vec2(-offset,  offset), vec2( 0.0,    offset), vec2( offset,  offset),
    vec2(-offset,  0.0),    vec2( 0.0,    0.0),    vec2( offset,  0.0),
    vec2(-offset, -offset), vec2( 0.0,   -offset), vec2( offset, -offset)
);

float kernel[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
);

void main() {
    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    FragColor = vec4(col, 1.0);
}
```

### 7.7 几何着色器

几何着色器在顶点和片段着色器之间运行，可以增减图元。项目实现了将点扩展为房屋形状的效果：

```glsl
// geometry_shader.glsl — 几何着色器
#version 320 es
layout(points) in;                              // 输入：点
layout(triangle_strip, max_vertices = 5) out;   // 输出：三角带，最多5个顶点

in VS_OUT { vec3 color; } gs_in[];
out vec3 fColor;

void build_house(vec4 position) {
    fColor = gs_in[0].color;  // 继承顶点颜色

    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); EmitVertex(); // 左下
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0); EmitVertex(); // 右下
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0); EmitVertex(); // 左上
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0); EmitVertex(); // 右上
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0); // 屋顶
    fColor = vec3(1.0, 1.0, 1.0);                              // 屋顶白色
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_house(gl_in[0].gl_Position);
}
```

绘制方式只需 4 个点：

```cpp
glDrawArrays(GL_POINTS, 0, 4);  // 4 个点 → 4 个房屋
```

### 7.8 实例化

实例化（Instancing）用于高效渲染大量相同物体，通过 `glVertexAttribDivisor` 实现每实例更新属性：

```cpp
// GLSeniorInstance.cpp
// 生成 100 个偏移位置
glm::vec2 translations[100];
int index = 0;
float offset = 0.1f;
for (int y = -10; y < 10; y += 2) {
    for (int x = -10; x < 10; x += 2) {
        translations[index++] = glm::vec2(
            x / 10.0f + offset, y / 10.0f + offset);
    }
}

// 实例化 VBO
unsigned int instanceVBO;
glGenBuffers(1, &instanceVBO);
glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100,
             &translations[0], GL_STATIC_DRAW);

// 关键：绑定到 location 2，并设置 divisor
glEnableVertexAttribArray(2);
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                      2 * sizeof(float), (void*)0);
glVertexAttribDivisor(2, 1);  // 每实例更新一次（而非每顶点）

// 一次绘制 100 个实例
glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
```

对应的顶点着色器：

```glsl
// instance_vertex.glsl
layout(location = 2) in vec2 aOffset;  // 实例偏移

void main() {
    fColor = aColor;
    gl_Position = vec4(aPos + aOffset, 0.0, 1.0);  // 位置 + 偏移
}
```

### 7.9 Uniform Buffer Object (UBO)

UBO 允许多个着色器共享同一块 uniform 数据，避免重复设置：

```cpp
// GLSeniorUniform.cpp
// 1. 获取各着色器的 uniform block 索引并绑定到绑定点 0
unsigned int blockIndex = glGetUniformBlockIndex(shader->shaderId, "Matrices");
glUniformBlockBinding(shader->shaderId, blockIndex, 0);

// 2. 创建 UBO（2 个 mat4 = projection + view）
unsigned int uboMatrices;
glGenBuffers(1, &uboMatrices);
glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

// 3. 写入 projection（只设置一次）
glBufferSubData(GL_UNIFORM_BUFFER, 0,
                sizeof(glm::mat4), glm::value_ptr(projection));

// 4. 每帧写入 view
glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4),
                sizeof(glm::mat4), glm::value_ptr(view));
```

着色器中使用 `std140` 布局声明 UBO：

```glsl
// uniform_vertex.glsl
layout(std140) uniform Matrices {
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
```

### 7.10 3D 模型加载（Assimp 集成）

项目使用 Assimp 库加载 3D 模型文件（OBJ、FBX、DAE 等格式）：

```cpp
// GLSenior3DModel.cpp
Assimp::Importer importer;
const aiScene *scene = importer.ReadFile(path,
    aiProcess_Triangulate        |  // 确保所有面是三角形
    aiProcess_GenSmoothNormals   |  // 生成平滑法线
    aiProcess_FlipUVs            |  // 翻转 UV 坐标
    aiProcess_CalcTangentSpace);    // 计算切线和副切线

// 递归处理节点树
void processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

// 处理单个网格
Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
    // 提取顶点：Position, Normal, TexCoords, Tangent, Bitangent
    // 提取索引：面索引
    // 提取材质纹理：diffuse, specular, normal, height（4 种类型）
    // 纹理去重：textures_loaded 缓存
}
```

### 7.11 小行星批量绘制

实例化的进阶应用——渲染 1000 个小行星：

```cpp
// GLSenior3DShow.cpp
unsigned int amount = 1000;
glm::mat4 *modelMatrices = new glm::mat4[amount];

for (unsigned int i = 0; i < amount; i++) {
    float angle = (float)i / (float)amount * 360.0f;
    float radius = 30.0f;
    float x = radius * sin(angle);
    float y = radius * 0.2f * (rand() % 10 - 5);  // 随机 Y
    float z = radius * cos(angle);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, z));
    model = glm::rotate(model, angle, glm::vec3(0.4, 0.6, 0.8));
    float scale = 0.05f + (rand() % 20) / 1000.0f;  // 随机缩放
    model = glm::scale(model, glm::vec3(scale));
    modelMatrices[i] = model;
}
```

---

## 八、gl3d 模块：3D 渲染进阶与骨骼动画

gl3d 模块在 glsenior 基础上增加了完整的光照模型、FreeType 文字渲染和**骨骼动画系统**，是项目中技术含量最高的模块。

### 8.1 完整 Phong 光照模型

`GL3DFlashLight` 实现了带聚光灯效果的完整 Phong 光照：

```cpp
// 光源跟随摄像机
lightColorShader->setVec3("light.position",  mCamera.Position);
lightColorShader->setVec3("light.direction", mCamera.Front);
lightColorShader->setFloat("light.cutOff",
    glm::cos(glm::radians(12.5f)));

// 距离衰减参数
lightColorShader->setFloat("light.constant", 1.0f);
lightColorShader->setFloat("light.linear",   0.09f);
lightColorShader->setFloat("light.quadratic", 0.032f);

// 材质参数
lightColorShader->setFloat("material.shininess", 64.0f);
```

### 8.2 骨骼动画系统

骨骼动画是该项目的核心高级功能，由 5 个类协作完成：

```
ModelAnimation    — 加载带骨骼信息的模型
    ↓
Animation         — 加载动画数据（关键帧、节点层级）
    ↓
Animator          — 驱动动画播放，递归计算骨骼变换
    ↓
Bone              — 骨骼关键帧插值（位置/旋转/缩放）
    ↓
GL3DAnimationShow — 每帧更新 + 渲染
```

#### 8.2.1 顶点骨骼数据结构

每个顶点最多受 4 个骨骼影响：

```cpp
#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int   m_BoneIDs[MAX_BONE_INFLUENCE];   // 4 个骨骼 ID
    float m_Weights[MAX_BONE_INFLUENCE];    // 4 个骨骼权重
};
```

#### 8.2.2 骨骼权重提取

模型加载时从 Assimp 的 `aiBone` 提取骨骼权重信息：

```cpp
// ModelAnimation.cpp — ExtractBoneWeightForVertices
for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {
    std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();

    int boneID;
    if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
        // 新骨骼：分配 ID，存储 offset 矩阵
        BoneInfo newBoneInfo;
        newBoneInfo.id = boneCount;
        newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(
            mesh->mBones[boneIndex]->mOffsetMatrix);
        boneInfoMap[boneName] = newBoneInfo;
        boneID = boneCount++;
    } else {
        boneID = boneInfoMap[boneName].id;
    }

    // 将骨骼权重写入顶点数据
    auto weights = mesh->mBones[boneIndex]->mWeights;
    for (int w = 0; w < numWeights; ++w) {
        int vertexId = weights[w].mVertexId;
        float weight = weights[w].mWeight;
        SetVertexBoneData(vertices[vertexId], boneID, weight);
    }
}
```

`SetVertexBoneData` 将骨骼 ID 和权重写入顶点的空闲槽位：

```cpp
void SetVertexBoneData(Vertex &vertex, int boneID, float weight) {
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
        if (vertex.m_BoneIDs[i] < 0) {
            vertex.m_Weights[i] = weight;
            vertex.m_BoneIDs[i] = boneID;
            break;
        }
    }
}
```

#### 8.2.3 动画数据加载

`Animation` 类从模型文件中读取动画数据：

```cpp
// Animation.cpp
Animation::Animation(const std::string &animationPath, ModelAnimation *model) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(animationPath, aiProcess_Triangulate);

    // 提取动画时长和帧率
    aiAnimation *animation = scene->mAnimations[0];
    m_Duration = animation->mDuration;
    m_TicksPerSecond = animation->mTicksPerSecond;

    // 递归读取节点层级树
    ReadHierarchyData(&m_RootNode, scene->mRootNode);

    // 读取所有骨骼动画通道
    ReadMissingBones(animation, *model);
}
```

#### 8.2.4 关键帧插值

`Bone` 类负责在两个关键帧之间插值计算当前时间的骨骼变换：

```cpp
// Bone.cpp
void Bone::Update(float animationTime) {
    glm::mat4 translation = InterpolatePosition(animationTime);
    glm::mat4 rotation = InterpolateRotation(animationTime);
    glm::mat4 scale = InterpolateScaling(animationTime);
    m_LocalTransform = translation * rotation * scale;
}

// 位置插值：线性插值
glm::mat4 InterpolatePosition(float animationTime) {
    int p0Index = GetPositionIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(
        m_Positions[p0Index].timeStamp,
        m_Positions[p1Index].timeStamp,
        animationTime);
    glm::vec3 finalPosition = glm::mix(
        m_Positions[p0Index].position,
        m_Positions[p1Index].position,
        scaleFactor);
    return glm::translate(glm::mat4(1.0f), finalPosition);
}

// 旋转插值：球面线性插值（四元数）
glm::mat4 InterpolateRotation(float animationTime) {
    int p0Index = GetRotationIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(
        m_Rotations[p0Index].timeStamp,
        m_Rotations[p1Index].timeStamp,
        animationTime);
    glm::quat finalRotation = glm::slerp(
        m_Rotations[p0Index].orientation,
        m_Rotations[p1Index].orientation,
        scaleFactor);
    return glm::toMat4(finalRotation);
}
```

三种插值方式的选择依据数据类型：
- **位置（Translation）**：`glm::mix()` 线性插值
- **旋转（Rotation）**：`glm::slerp()` 球面线性插值（四元数）
- **缩放（Scale）**：`glm::mix()` 线性插值

#### 8.2.5 递归骨骼变换计算

`Animator` 的核心是递归遍历节点树，计算每个骨骼的全局变换矩阵：

```cpp
// Animator.cpp
void Animator::UpdateAnimation(float dt) {
    m_DeltaTime = dt;
    if (m_CurrentAnimation) {
        m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * dt;
        m_CurrentTime = fmod(m_CurrentTime, m_CurrentAnimation->GetDuration());
        CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(),
                               glm::mat4(1.0f));
    }
}

void Animator::CalculateBoneTransform(const AssimpNodeData *node,
                                       glm::mat4 parentTransform) {
    std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transformation;

    Bone *bone = m_CurrentAnimation->FindBone(nodeName);
    if (bone) {
        bone->Update(m_CurrentTime);
        nodeTransform = bone->GetLocalTransform();  // 使用插值后的变换
    }

    // 全局变换 = 父节点变换 × 当前节点变换
    glm::mat4 globalTransformation = parentTransform * nodeTransform;

    // 如果节点对应一个骨骼，计算最终变换矩阵
    auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end()) {
        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offset;
        // 最终矩阵 = 全局变换 × offset（模型空间→骨骼空间→模型空间）
        m_FinalBoneMatrices[index] = globalTransformation * offset;
    }

    // 递归处理子节点
    for (int i = 0; i < node->childrenCount; i++) {
        CalculateBoneTransform(&node->children[i], globalTransformation);
    }
}
```

#### 8.2.6 骨骼动画顶点着色器

最终的骨骼变换在顶点着色器中通过加权混合应用到顶点位置：

```glsl
// gl_3d_animation_vertex.glsl
#version 320 es
layout(location = 0) in vec3  pos;
layout(location = 5) in ivec4 boneIds;
layout(location = 6) in vec4  weights;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    vec4 totalPosition = vec4(0.0f);

    for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
        if (boneIds[i] == -1) continue;       // 无骨骼影响
        if (boneIds[i] >= MAX_BONES) {         // 超出范围，使用原始位置
            totalPosition = vec4(pos, 1.0f);
            break;
        }
        // 加权混合各骨骼的变换
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos, 1.0f);
        totalPosition += localPosition * weights[i];
    }

    gl_Position = projection * view * model * totalPosition;
}
```

#### 8.2.7 渲染循环

```cpp
// GL3DAnimationShow.cpp
void renderFrame() {
    // 1. 计算帧时间差
    float currentFrame = clock() * 5 / CLOCKS_PER_SEC;
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // 2. 更新骨骼动画
    animator->UpdateAnimation(deltaTime);

    // 3. 将最终骨骼矩阵传递给着色器
    auto transforms = animator->GetFinalBoneMatrices();
    for (int i = 0; i < transforms.size(); ++i) {
        modelShader->setMat4("finalBonesMatrices[" +
            std::to_string(i) + "]", transforms[i]);
    }

    // 4. 绘制模型
    gl3DModel->Draw(*modelShader);
}
```

### 8.3 文字渲染（FreeType）

gl3d 模块集成了 FreeType 库实现 TrueType 字体文字渲染，支持中文（项目中包含 `jianti.ttf` 简体字体和 `arial.ttf` 字体）。FreeType 将字形渲染为位图纹理，再通过 OpenGL 绘制到屏幕上。

---

## 九、技术总结与学习路线

### 9.1 项目技术栈全景

| 技术领域 | 具体技术 | 实现模块 |
|----------|----------|----------|
| **Java 架构** | ViewModel+LiveData、Fragment 懒加载、模板方法模式 | app |
| **JNI** | 动态注册、全局对象管理、懒加载 | 所有模块 |
| **着色器系统** | 单/双着色器类、文件加载、编译链接 | glfoundation |
| **基础渲染** | VAO/VBO/EBO、Uniform 动画、纹理混合 | glfoundation |
| **3D 变换** | MVP 矩阵、深度测试、摄像机系统 | glfoundation |
| **光照模型** | 环境光→漫反射→镜面→材质→贴图→平行光→衰减→聚光→多光源 | glfoundation |
| **高级测试** | 深度测试、模板测试（描边） | glsenior |
| **混合** | Alpha 丢弃、半透明排序 | glsenior |
| **立方体贴图** | 天空盒、反射 | glsenior |
| **帧缓冲** | FBO 离屏渲染、后期处理（灰度/核效果） | glsenior |
| **着色器进阶** | 几何着色器、实例化、UBO | glsenior |
| **模型加载** | Assimp 集成、节点树遍历、纹理加载 | glsenior/gl3d |
| **骨骼动画** | 骨骼权重提取、关键帧插值、递归变换计算 | gl3d |
| **文字渲染** | FreeType 字体光栅化 | gl3d |

### 9.2 渲染管线演进

项目展示了一条清晰的 OpenGL 学习路径：

```
三角形（基础管线）
    → 矩形（EBO 索引绘制）
    → Uniform 动画（着色器交互）
    → 纹理（stb_image + 多纹理混合）
    → 3D 变换（MVP 矩阵）
    → 立方体（深度测试）
    → 多立方体（矩阵复用）
    → 摄像机（欧拉角 + 触摸交互）
    → 光照系统（11 个渐进场景）
    → 高级技术（测试/混合/FBO/几何着色器/实例化/UBO）
    → 模型加载（Assimp）
    → 骨骼动画（关键帧插值 + 骨骼蒙皮）
```

### 9.3 第三方库一览

| 库 | 功能 | 集成方式 |
|----|------|----------|
| GLM | OpenGL 数学库（矩阵、向量、四元数） | 头文件包含 |
| stb_image | 图像加载（PNG/JPG 等） | 单头文件 |
| Assimp | 3D 模型加载（OBJ/FBX/DAE 等） | 预编译 .so |
| FreeType | 字体光栅化 | 预编译 .a |

### 9.4 GitHub 仓库

项目完整源码位于 GitHub，包含所有 C++ 源码、GLSL 着色器、3D 模型资源和示例图片：

**[https://github.com/wangyongyao1989/AndroidLearnOpenGL](https://github.com/wangyongyao1989/AndroidLearnOpenGL)**

### 9.5 学习建议

对于想通过此项目学习 Android OpenGL ES 的开发者，建议按照以下顺序学习：

1. 先理解 `app` 模块的 Fragment 路由和 JNI 调用模式，建立 Java-C++ 通信的全局认知
2. 从 `glfoundation` 的三角形开始，逐步理解 VAO/VBO/EBO 和着色器编译流程
3. 沿着纹理 → 3D 变换 → 摄像机 → 光照的路径，掌握 OpenGL ES 核心概念
4. 进入 `glsenior` 学习高级测试和帧缓冲技术
5. 最后通过 `gl3d` 的骨骼动画理解 3D 模型的完整渲染流程

每个 Demo 都可以独立运行和调试，结合 [LearnOpenGL 中文教程](https://learnopengl-cn.github.io/) 阅读效果更佳。

---

> 本文基于 AndroidLearnOpenGL 项目源码分析撰写，如有疑问或建议，欢迎在 [GitHub 仓库](https://github.com/wangyongyao1989/AndroidLearnOpenGL) 提交 Issue。
