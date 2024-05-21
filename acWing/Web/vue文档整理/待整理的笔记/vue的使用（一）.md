### `Vue`安装和启动

#### 1. 安装`nodejs`

- 在官网下载安装包，按照默认选项安装，安装`nodejs` 安装完毕后，用管理员启动`cmd`，`nodejs`的安装目录在`D:\nodejs\nodejs`

  1. 检查
     `node -v`
     `npm -v`

  2. 创建两个目录：
     `D:\nodejs\nodejs\node_cache`
     `D:\nodejs\nodejs\node_global`

  3. 设置`global cache`路径
     `npm config set prefix "D:\nodejs\nodejs\node_global"`
     `npm config set cache "D:\nodejs\nodejs\node_cache"`

  4. 修改用户的环境变量
     `Path`中添加`D:\nodejs\nodejs\node_global`

  5. 修改系统变量
     添加：`NODE_PATH`、`D:\nodejs\nodejs\node_global\node_modules`
     添加：`Path`  `D:\nodejs\nodejs\node_global` `D:\nodejs\nodejs`

  6. 修改镜像
     `npm config get registry`
     `npm config set registry https://registry.npm.taobao.org/`
     `npm config get registry`
     `npm install -g cnpm --registry=https://registry.npm.taobao.org`

#### 2. 安装vue

- 安装：`cnpm install -g @vue/cli`
- 启动：`vue ui`

#### 3. 常见问题及建议

使用建议：使用`vue ui`时，建议从存放`vue`项目的文件夹打开，也就是先管理员打开终端，然后终端`cd`到项目文件夹，然后再输入`vue ui`命令，不然有可能会出现项目管理一直在加载路径

常见问题1：`Windows`上运行`vue`，提示无法加载文件，表示用户权限不足。

解决方案：用管理员身份打开终端，输入`set-ExecutionPolicy RemoteSigned`，然后输入`y`

常见问题2：`vue`项目管理器一直都在加载的解决方法

解决方案：不用管理身份启动`powershell`，或使用上面的建议使用`vue ui`

#### 4. 仪表盘的使用

参考这个链接：[Vue3 v5.0.8——下载和安装过程 - AcWing](https://www.acwing.com/file_system/file/content/whole/index/content/6326802/)



### `Vue`的使用

#### 项目文件的介绍

- `src`下的目录结构：

     ```
     src
       ├─assets
       ├─components：一般用来存储各种组件，views中也可以存组件，一般怎么存看个人习惯
       ├─router：路由。网址对应的页面，默认有两个路由一个`/`，一个`/about`，默认的网址中有`#`，把`createWebHashHistory`中的`Hash`去掉即可
       ├─store
       ├─views：一般用来写各种页面。类似于`django`中的views
       └─main.js：整个项目的入口。`createApp(App).use(store).use(router).mount('#app')`创建根组件`app`，使用`store`和`router`（这两个就是在创建项目时安装的`vuex`、`vue-router`插件），挂载到`id`为`app`的元素上，这个`id`为`app`的元素在`public/index.html`中（感觉这里和`hexo`挺像的，也是把生成的页面放到`public`中）。 
     ```

- 后端渲染模型：每打开一个新的`url`都会向服务器发送一个请求，服务器再把这个页面返回回来

- 前端渲染模型：不管我们打开的哪个页面，服务器都会将所有页面的样式返回到一个`js`文件中，当我们在打开其它页面就不会向服务器发送请求了，就会直接用前面返回的`js`文件将新页面渲染出来，这个过程不会像服务器发送请求

#### 开发项目

一般秉承从上往下的思想进行开发

#### 1. `Vue`基本概念的介绍

每个页面都是一个`.vue`文件，每个`.vue`文件都有三部分组成，`html`、`js`、`css`三部分。一般写网页这三部分都是分开的，在`Vue`中将这三个部分放到一块了，同一个页面是一个整体。

`Vue`中的`css`部分有一个特性，在`<style>`中加一个`scoped`，不同组件中的`css`文件就不会相互影响了。

`Vue`是一个组件化的框架。一个页面可以拆分为若干个不同的部分，每一个部分都可以用一个单独的组件来实现，可以在`html`中通过类似标签的方式进行组件的引用，引用的时候还可以向组件传递一些信息，比如初始项目中有一个`HelloWorld.vue`组件，这个组件可以接收字符串信息，在`HomeView.vue`中的引用为`  <HelloWorld msg="Welcome to Your Vue.js App"/>`

#### 2. 网站的基本实现

<img src="C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221113213042566.png" alt="image-20221113213042566" style="zoom: 50%;" />

- 导航栏的实现（`NavBar.vue`)

  知识点一：

  每一个`vue`组件最后都会导出一个对象，目前用到了两个属性，一个`name`和一个`components`，`name`暂时还用不到，只需要起一个不重复的名词即可，`components` 表示在`template`区域会用到哪些其它的组件，把所有用到的组件都放到`components`中

  ```vue
  // src/views/HomeView.vue
  export default {
    name: 'HomeView',
    components: {
    }
  }
  ```

  因为要用到`bootstrap`，所以需要在`App.vue`中进行引用

  ```vue
  // src/App.vue
  ……
  
  <script>
  import 'bootstrap/dist/css/bootstrap.css';
  import 'bootstrap/dist/js/bootstrap';
      
  ……
  </script>
  
  ……
  ```

  引入之后发现会报错`Module not found: Error: Can't resolve '@popperjs/core' in`需要把`@popperjs/core`单独装一下，项目面板->依赖->安装依赖，搜索即可

  在`bootstrap`中寻找合适的`navbar`将代码复制到`template`中即可使用。有时需要根据自己的要求稍加修改，比如`container-fluid`靠左右一些，`container`靠中间一些，这样我们的navbar组件就完成了

  ```vue
  // src/components/NavBar.vue
  <template>
  <nav class="navbar navbar-expand-lg navbar-light bg-light">
     	<!-- container-fluid靠左右一些，container靠中间一些-->
      <div class="container">
          <a class="navbar-brand" href="#">My Space</a>
          <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarText" aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
          </button>
          <div class="collapse navbar-collapse" id="navbarText">
          <ul class="navbar-nav me-auto mb-2 mb-lg-0">
              <li class="nav-item">
              <a class="nav-link active" aria-current="page" href="#">首页</a>
              </li>
              <li class="nav-item">
              <a class="nav-link" href="#">好友列表</a>
              </li>
              <li class="nav-item">
              <a class="nav-link" href="#">用户动态</a>
              </li>
          </ul>
          <ul class="navbar-nav">
              <li class="nav-item">
              <a class="nav-link" href="#">登录</a>
              </li>
              <li class="nav-item">
              <a class="nav-link" href="#">注册</a>
              </li>
          </ul>
          
          </div>
      </div>
      </nav>
  </template>
  
  <script>
  export default {
      name: "NavBar",
  }
  </script>
  
  <style scoped>
  
  </style>
  ```

  因为这个项目的每一个页面都需要使用到`navbar`，所以需要在`App.vue`中进行引用

  ```vue
  // App.vue
  
  <template>
    <NavBar></NavBar>
    <router-view/>
  </template>
  
  <script>
  import 'bootstrap/dist/css/bootstrap.css';
  import 'bootstrap/dist/js/bootstrap';e
  import NavBar from './components/NavBar.vue';
  
  export default {
    name: "App",
    components: {
      NavBar,
    }
  }
  </script>
  ……
  ```

- 首页的实现（`HomeView.vue`)

  直接在`HomeView`的`template`中实现好看的首页比较费时，一般可以直接使用一个框把首页中要展示的内容给框起来，

  这个可以直接使用`bootstrap`中的`cards`来实现，把`cards`中原有的内容和宽度删掉，只留下`div.card`和`div.card-body`，

  实现之后发现这个框太靠左右了，可以用一个`div.container`把它框起来，

  加了一个`container`之后，发现这个框和上面的`navbar`靠太近了，我们只需要在`style`中给`container`加一个样式

  ![image-20221113224136388](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221113224136388.png)

  这样一个简单的首页就完成了。对于后面的几个页面都会用到用一个框把内容框起来的样式，所以我们可以把这个功能封装成一个组件进行使用。`vue`会把组件中的所有子元素渲染到`slot`中

  ```vue
  // components/ContentBase.vue
  
  <template>
      <div class="container">
          <div class="card">
              <div class="card-body">
            		<slot></slot>  
              </div>
          </div>
      </div>
  </template>
  
  <script>
  export default {
      name: "ContentBase",
  }
  </script>
  
  <style scoped>
  .container {
      margin-top: 20px;
    }
  </style>
  ```

  ~~这里的`components`创建命名为`Content.vue`会报错，因为高版本的`vue`要求`components`使用驼峰式命名，我们需要把这个要求关闭，在`vue.config.js`文件中，加入`lintOnSave: false`，再重启项目，就不会报错了 ，也可以直接把组件名改为驼峰式命名~~

- 用户列表`UserListView.vue`、用户动态`UserProfileView.vue`、用户登录`LoginView.vue`、用户注册`RegisterView.vue`、404`NotFoundView.vue`的实现

  引用`ContentBase.vue`组件（以`UserList.vue`为例）

  ```vue
   <template>
      <ContentBase>
          好友列表
      </ContentBase>
  </template>
  
  <script>
  export default {
      name: "UserListView",
      components: {
          ContentBase,
      }
  }
  </script>
  
  <style>
  
  </style>
  ```

- 加路由

  在`src/router/index.js`中引入路由

  ```vue
  import { createRouter, createWebHistory } from 'vue-router'
  import HomeView from '../views/HomeView.vue'
  import UserListView from '../views/UserListView.vue'
  import UserProfileView from '../views/UserProfileView.vue'
  import LoginView from '../views/LoginView.vue'
  import RegisterView from '../views/RegisterView.vue'
  import NotFoundView from '../views/NotFoundView.vue'
  
  const routes = [
    {
      path: '/',
      name: 'home',
      component: HomeView
    },
    {
      path: '/userlist',
      name: 'userlist',
      component: UserListView
    },
    {
      path: '/userprofile',
      name: 'userprofile',
      component: UserProfileView
    },
    {
      path: '/login',
      name: 'login',
      component: LoginView
    },
    {
      path: '/register',
      name: 'register',
      component: RegisterView
    },
    {
      path: '/404',
      name: '404',
      component: NotFoundView
    },
  ]
  
  ……
  ```

- 实现前端渲染

  改了路由之后还是需要改变`url`才能改变路径，我们这是前端渲染，按理来说不需要改变`url`就可以实现页面切换，应该用`js`来实现页面的切换，

  如果直接改变`NavBar`组件中的`href`会发现，我们每点击切换一次页面就会刷新一次，也就是会向服务器重新请求一遍数据，这种不是前端渲染，

  如果想要实现前端渲染就要使用`vue`中的`router-link`，这个`router-link`其实就是我们的`a`标签，只不过里面有一个特殊的属性`:to`，`:to`的值为一个对象，这个对象有这么几个属性，`name`，就是我们在`router`中定义的`name`，

  ```vue
  // src/components/NavBar.vue
  
  <template>
  <nav class="navbar navbar-expand-lg navbar-light bg-light">
      <div class="container">
          <router-link class="navbar-brand" :to="{name: 'home'}">My Space</router-link>
          <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarText" aria-controls="navbarText" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
          </button>
          <div class="collapse navbar-collapse" id="navbarText">
          <ul class="navbar-nav me-auto mb-2 mb-lg-0">
              <li class="nav-item">
              <router-link class="nav-link active" aria-current="page" :to="{name: 'home'}">首页</router-link>
              </li>
              <li class="nav-item">
                  <router-link class="nav-link" :to="{name: 'userlist'}">用户列表</router-link>
              </li>
              <li class="nav-item">
              <router-link class="nav-link" :to="{name: 'userprofile'}">用户动态</router-link>
              </li>
          </ul>
          <ul class="navbar-nav">
              <li class="nav-item">
              <router-link class="nav-link" :to="{name: 'login'}">登录</router-link>
              </li>
              <li class="nav-item">
                  <router-link class="nav-link" :to="{name: 'register'}">注册</router-link>
                  </li>
          </ul>
          
          </div>
      </div>
      </nav>
  </template>
  ```

  这样前端渲染就完成了

#### 3. 细化实现每一个页面

- 用户动态页面`UserProfile.vue`

  <img src="C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221114110514925.png" alt="image-20221114110514925" style="zoom:50%;" />

  页面布局：可以使用`bootstrap`的`grid`系统，`grid`系统由`div.container`、`div.row`和`div.col`三部分组成，上面的样式可由这部分代码实现，在`ContentBase`组件中已经有一个`div.container`了，所以在`UserProfileView.vue`中可以直接写`div.row`和`div.col`

  ```vue
  // src/views/UserProfileView.vue
  
  <template>
      <div class="row">
          <div class="col-3">
              UserProfileInfo
              <div class="row">
                  <div class="col">
                      UserProfileWrite
                  </div>
              </div>
          </div>
          <div class="col-9">
          	UserProfilePosts
          </div>
      </div>
  </template>
  
  ……
  ```

  框架实现了，之后再继续细化每一个组件

  - `UserProfileInfo`组件

    <img src="C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221114112533283.png" alt="image-20221114112533283" style="zoom:67%;" align=left />

    ```vue
    <template>
        <div class="row">
            <div class="col-3">
                图片
            </div>
            <div class="col-9">
        		个人信息	
        	</div>
        </div>
    </template>
    ```

    最终实现代码

    ```vue
    // src/componets/UserProfileInfo
    
    <template>
        <div class="card">
            <div class="card-body">
                <div class="row">
                    <div class="col-3">
                        <img class="img-fluid" src="https://cdn.acwing.com/media/user/profile/photo/74146_lg_8ea329acf6.jpg" alt="">
                    </div>
                    <div class="col-9">
                        <div class="username">ndream</div>
                        <div class="fans">粉丝数：123</div>
                        <button type="button" class="btn btn-secondary btn-sm">+关注</button>
                    </div>
                </div>
            </div>
        </div>
    </template>
    
    <script>
    export default {
        name: "UserProfileInfo",
    }
    </script>
    
    <style scoped>
    img {
        border-radius: 50%;
    }
    .username {
        font-weight: bold;
    }
    .fans {
        font-size: 12px;
        color: gray;
    }
    
    button {
        padding: 2px 4px;
        font-size: 12px;
    }
    </style>
    ```

    实现效果

    ![image-20221114115817464](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221114115817464.png)

    这个组件实现好之后，每个人的页面应该都是不一样的，每个人都有自己各自的头像、用户名、粉丝数，应该是独立的，所以头像、用户名、粉丝数应该都是参数。同时还有发帖功能和帖子具体信息，所以我们可以发现这三个模块都需要一些数据，这些数据相互之间是需要交互的，模块之间的数据交互，一般是把数据存到最顶层的组件中，也就是`UserProfileView`组件

    父组件向子组件传递信息（使用的是`vue`的`compositon API`）：

    就是有一个入口叫做`setup`，可以在`setup`中定义一堆变量，`setup`是一个函数，`setup: ()=> { }`可以简写为`setup() { }`（这里不清楚），这样就可以在`{ }`中开始定义变量了，因为子组件需要用户信息，所以需要一个`user`，这个`API`定义变量有两种方式，一种`ref`、一种`reactive`，`ref`的运行效率要比`reactive`的运行效率要低一些，所以能用`reactive`的时候尽量不要用`ref`，当我们的变量需要被重新赋值的时候就可以用`ref`，当我们这个变量不会被重新赋值的时候就用`reactive`，`user`是一个用户，当前组件的用户一般都是不会变的，当我们加载下一个页面的时候是一个新的组件，一个新的页面，所以`user`可以用`reactive`，还有一点就是`reactive`只能用来接收对象，`ref`可以用来接受普通的变量类型，比如说一个字符串、一个数字。

    ```vue
    // src/views/UserProfileView
    
    ……
    
    <script>
    ……
    import { reactive } from 'vue'
    
    export default {
        ……
        
        setup() {
            const user = reactive({
                id: 1,
                userName: "ndream",
                lastName: "n",
                firstName: "dream",
                followerCount: 0,
                is_followed: false,
            });
            
            // 在template中需要使用到的值都要return出去
            return {
                user: user,
            }
        }
    }
    
    </script>
    ```

    这样我们就可以在`UserProfileView`的`template`中使用这些属性了，我们这些属性的值需要在`UserProfileInfo`中被渲染出来，所以需要将这些属性的值传到`UserProfileInfo`中。`vue`在不同组件中传递信息类似与`react`，父组件向子组件传递信息是通过`props`属性，子组件向父组件传递信息是通过调用函数的方式`event`来传递的。	 

    <img src="C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221114185329922.png" alt="image-20221114185329922" style="zoom:67%;" align="left" />

    父组件向子组件传递信息，需要先将要传递的信息绑定到子组件上。比如`UserProfileView`要向`UserProfileInfo`传递`user`，在`UserProfileView`的`template`中使用`UserProfileInfo`时，要加上`v-bind: "user"`，也可以直接写为`: "user"`。`" "`可以是一个值或表达式，它不是一个普通的字符串。

    ```vue
    // src/view/UserProfileView
    
    <template>
        <ContentBase>
            <div class="row">
                <div class="col-3">
                    <UserProfileInfo :user="user"/>
                </div>
                <div class="col-9">
                    <UserProfilePosts />                
                </div>
            </div>
        </ContentBase>
    </template>
    
    ……
    ```

    如何在子组件中接收到这个消息呢，我们需要把接收的参数放到`props`中。传完`user`之后`UserProfileInfo`中显示的姓名是由`firstname`和`lastname`组成的，这个值其实是由某些值计算出来的，如果我们想把计算出的值展示出来，我们可以使用`computed`，它可以动态的去计算某个属性。

    ```vue
    // src/components/UserProfileInfo
    ……
    
    <script>
    import { computed } from 'vue'
        
    export default {
        ……
        props: {
        	user: {
        		type: Object,
        		required: true,	// 表示必须要传user，不传就会报错
    		},
    	}
        
        // vue中没有this这个东西，所以需要把props传进去
        setup(props) {
            let fullName = computed(() => props.user.lastName + ' ' + props.user.firstName);
            
            return {
                fullName
            }
        }
    }
    </script>
    
    ……
    ```

    之后再来实现关注按钮，没有关注的话应该要显示关注，关注了的话应该要显示取消关注。`vue`中实现判断是通过`v-if`实现的

    ```vue
    // src/components/UseProfileInfo
    
    <template>
    ……
    <button v-if="!user.is_followed" type="button" class="btn btn-secondary btn-sm">+关注</button>
    <button v-if="user.is_followed" type="button" class="btn btn-secondary btn-sm">取消关注</button>
    ……
    </template>
    ```

    这样就实现了关注和取消关注的切换，接下来就需要实现当我们点击关注之后需要更新关注状态，所以这里需要绑定一个事件，我们需要在`setup`中定义一个事件处理函数，定义方法和定义一般的函数相同。定义好之后可以使用`v-on:click`绑定`click`函数，`v-on:`可以简写为`@`

    ```vue
    // src/components/UserProfileInfo
    <template>
    ……
    	<button @click="follow" v-if="!user.is_followed" type="button" class="btn btn-secondary btn-sm">+关注</button>
    	<button @click="unfollow" v-if="user.is_followed" type="button" class="btn btn-secondary btn-sm">取消关注</button>
    ……                
    </template>
    
    <script>
    ……
    
    export default {
        ……
        
        setup(props) {
            ……
            
            const follow = () => {
                console.log("follow");
            };
            
            const unfollow = () => {
                console.log("unfollow");
            };
            
            // 需要将函数返回才能使用
            return {
                follow,
                unfollow,
            }
        }
    }
        
    </script>
    
    ……
    ```

    这样当我们点击按钮之后控制台就会返回`follow`或者`unfollow`了。接下来我们需要修改`is_followed`的状态，我们可以发现状态的信息是在`user`里面，但`user`是在父组件中定义的，所以子组件要修改的话，不能直接在子组件中修改，这里就涉及到子组件向父组件传递信息。子组件向父组件传递信息是通过绑定事件的方法。首先需要在父组件的`setup`中实现要绑定的事件函数，再将这个事件绑定到`template`中的子组件上

    ```vue
    // src/view/UserProfileView
    <template>
    ……
    <UserProfileInfo @follow="follow" @unfollow="unfollow" :user="user" />
    ……
    </template>
    
    <script>
    ……
    export default {
        ……
        setup() {
            ……
            const follow = () => {
                if (user.is_followed)  return;
                user.is_followed = true;
                user.followerCount ++;
            };
            
            const unfollow = () => {
                if (!user.is_followed) return;
                user.is_followed = false;
                use.followerCount --;
            }
            
            return {
                follow,
                unfollow,
            }
        }
    }
        
    </script>
    
    ……
    ```

    如果子组件想要修改父组件中的信息，需要通过触发父组件中绑定的函数来实现这一点，在子组件中触发父组件中绑定的函数是通过`context.emit()`来实现的

    ```vue
    // src/components/UserProfileInfo
    ……
    
    <script>
    ……
    export default {
        ……
        setup(props, context) {
            ……
            const follow = () => {
                context.emit('follow');
            };
            const unfollow = () => {
                context.emit('unfollow');
            };
            ……
        }
    }
    </script>
    
    ……
    ```

    这样就实现了动态的关注功能

  

  - `UserProfilePosts`组件

    渲染动态列表，

    首先定义一个动态列表和定义`user`类似，也就是在`UserProfileView`的`setup`中定义`posts`，

    定义完之后在`template`中进行绑定，就可以将`posts`传到`UserProfilePosts`中了

    ```vue
    // src/views/UserProfileView
    
    <template>
    ……
    <UserProfilePosts :posts="posts"/>                
    ……
    </template>
    
    <script>
    ……
    
    export default {
    ……
        setup() {
    		……
            const posts = reactive({
                count: 3,
                posts: [
                    {
                        id: 1,
                        userId: 1,
                        content: "今天上了Web真开心",
                    },
                    {
                        id: 2,
                        userId: 1,
                        content: "今天上了算法课，更开心了",
                    },
                    {
                        id: 3,
                        userId: 1,
                        content: "今天上了acwing，超开心",
                    },
                ]
            });
    
            ……
            return {
              ……
                posts,
            }
        }
    }
    </script>
    
    ……
    ```

    父组件将信息传过来之后，子组件使用`props`进行接收，传过来之后是一个列表，需要写循环进行渲染。`vue`中通过`v-for`来进行循环，`vue`中所有的循环的对象都需要绑定一个`key`属性，这个`key`需要保证是唯一的，我们这里可以使用`post.id`来作为一个唯一的值，这个`key`是`vue`用来做优化的，我们一般用不到，但需要每一个循环都要绑定一个`key`，且每次循环的`key`不一样。

    ```vue
    // src/component/UserProfilePosts
    
    <template>
        <div class="card">
            <div class="card-body">
                <div v-for="post in posts.posts" :key="post.id">
                    <div class="card single-post">
                        <div class="card-body ">
                            {{post.content}}
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </template>
    
    <script>
    export default {
        name: "UserProfilePosts",
        props: {
            posts: {
                type: Object,
                required: true,
            },
        }
    }
    </script>
    
    <style scoped>
    .single-post {
        margin-bottom: 10px;
    }
    
    </style>
    ```

    ![image-20221114212942577](C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221114212942577.png)

  - `UserProfileWrite`组件

    页面实现

    ```vue
    // src/components/UserProfileWrite
    <template>
        <div class="card edit-field">
            <div class="card-body">
                <div class="mb-3">
                    <label for="edit-post" class="form-label">发布动态</label>
                    <textarea class="form-control" id="edit-post" rows="3"></textarea>
                    <button type="button" class="btn btn-primary btn-sm">发帖</button>
                </div>
            </div>
        </div>
    </template>
    
    <script>
    export default {
        name: "UserProfileWrite",
    }
    </script>
    
    <style scoped>
    .edit-field {
        margin-top: 20px;
    }
    
    .btn {
        margin-top: 10px;
    }
    </style>
    ```

    <img src="C:/Users/ndream/AppData/Roaming/Typora/typora-user-images/image-20221114214202921.png" alt="image-20221114214202921" style="zoom:80%;" align="left" />

    功能实现：

    首先需要获取`textarea`中的信息，`vue`中的`v-model`实现了这个功能，在`textarea`标签中直接使用就好了。

    ```
    // src/components/UserProfileWrite
    
    <template>
    ……
    <textarea v-model="content" class="form-control" id="edit-post" rows="3"></textarea>
    ……
    </template>
    
    <script>
    import { ref } from 'vue'
    
    export default {
    	……
        setup() {
    	    // ref变量的值的读取和修改都要使用.value
            let content = ref('');
    
            return {
                content
            }
        }
    }
    </script>
    
    ……
    ```

    之后需要给发帖按钮绑定一个触发函数，当我们点击发帖之后，可以将内容发布为一个帖子。

    ```vue
    // src/components/UserProfileWrite
    
    <template>
    ……
    <button @click="post_a_post" type="button" class="btn btn-primary btn-sm">发帖</button>
    ……
    </template>
    
    <script>
    ……
    
    export default {
        ……
    
        setup() {
            ……
    
            const post_a_post = () => {
                console.log(content.value);
                content.value="";
            }
    
            return {
                ……
                post_a_post,
            }
        }
    }
    </script>
    
    ……
    ```

    接下还需要实现的就是当我们点完发帖之后，可以将帖子的内容展示到帖子列表中。帖子的值是存储在`UserProfileView`中的，也就是`UserProfileWrite`的父组件中的，所以这里就涉及到了子组件向父组件传递信息，所以就要使用前面的触发函数的方法来传递。先在父组件的`setup`中实现一个函数，这个函数就是实现点击发帖之后将帖子的内容加入到帖子列表中的功能，再将这个函数绑定到父组件的`template`的`UserprofileWriter`标签上，然后再在子组件中通过`context.emit`来触发绑定在这个组件的函数，利用这个函数来实现发帖的功能。

    ```vue
    // src/components/UserProfileView
    
    <template>
    ……
    <UsereProfileWrite @post_a_post="post_a_post"/>
    ……
    </template>
    
    <script>
    ……
    
    export default {
        ……
        setup() {
            ……
    
            const post_a_post = (content) => {
                posts.count ++;
                // unshift将元素添加到列表头
                posts.posts.unshift({
                    id: posts.count,
                    userId: 1,
                    content: content,
                })
            }
    
            return {
                ……
                post_a_post,
            }
        }
    }
    </script>
    ……
    ```

    过程分析：当我们点击发帖的时候会触发`UserProfileWrite`中的`post_a_post`函数，这个函数会触发父组件的`post_a_post`事件，这个事件的参数是`content.value`也就是我们发的内容，当父组件的`post_a_post`事件触发之后，会调用`post_a_post`函数，这个函数会在`posts`中增加一个新的帖子，贴子的内容就是`content`，`posts`是`reactive`类型的，当`posts`发生变化的时候，引用`posts`的组件就会重新渲染

    ```
    @ v-on 是用来绑定事件的
    : v-bind 是用来绑定变量的
    ```

    

    

    
