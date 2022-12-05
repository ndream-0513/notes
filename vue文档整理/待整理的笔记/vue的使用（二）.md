`UserProfileView`页面已经写好了，再开始写`UserListView`页面

### `UserListView`页面

`UserListView`中的`user`信息是通过`acwing`的`API`返回固定的10个用户得到的，接下来需要从云端将这个十个用户的信息读取进来。

我么这里使用`ajax`来获取这些信息，在`vue`中如果想要使用`ajax`需要先安装`jquery`，`npm i jquery`，然后引入`ajax`的`$`对象，再将这些对象存到页面中

```vue
// src/view/UserListView
……

<script>
……
import $ from 'jquery'
import { ref } from 'vue'

export default {
    ……
    setup() {
        let users = ref([]);

        $.ajax({
            url: 'https://app165.acapp.acwing.com.cn/myspace/userlist/',
            type: 'get',
            success(resp) {
                users.value = resp;
            }
        });

        return {
            users
        }
    }
}
</script>

……
```

得到用户列表的信息之后，我们需要在页面中将它渲染出来，因为返回的是一个列表所以可以使用`v-for`来渲染每一个用户。

如果我们希望在某个属性中写的是变量名而不是某个特殊的字符串，则需要在属性名前加上一个`:`，这个是`v-bind`的简写，这样这个属性的值就不是这个字符串了，而是会对这个属性值取值，例如，我们需要把每一个用户的头像给渲染出来，头像的地址是存储在一个变量当中的，如果`img`的标签前面没有加`:`就获取不到这个变量的值。

```vue
// src/view/UserListView

<template>
    <ContentBase>
        <div class="card"  v-for="user in users" :key="user.id">
            <div class="card-body">
                <div class="row">
                    <div class="col-1">
                        <img :src="user.photo" alt="" class="img-fluid">
                    </div>
                    <div class="col-11">
                        <div class="username">{{user.username}}</div>
                        <div class="followerCount">{{user.followerCount}}</div>
                    </div>
                </div>
            </div>
        </div>
    </ContentBase>
</template>

<script>
……
</script>

<style scoped>
img {
    border-radius: 50%;
}
.card {
    margin-top: 20px;
    cursor: pointer;
}
.card:hover {
    box-shadow: 2px 2px 10px lightgrey;
    transition: 500ms;
}
.username {
    font-weight: bold;
    height: 50%;
}
.followerCount {
    font-size: 12px;
    color: grey;
    height: 50%;
}

</style>
```

![image-20221115154030053](https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221115154030053.png)

这样`UserListView`页面就写好了

还有一个需要补充的点，当我们访问的链接不存在的时候应该是要跳转的`404`页面的，但是现在是什么页面都没有跳转，所以我们可以在`src/router/index.js`最后加入一个正则表达式匹配和一个重定向到`404`页面的路径

```js
……
const routes = [
  ……
  // 当我们无法匹配前面的内容时，就匹配下面的内容，
  // :catchAll()中可以写入正则表达式 .*表示任意长度的字符，.任意字符 *任意长度
  {
    path: '/:catchAll(.*)',
    redirect: "/404/"
  },
]
……
```



用户动态页面（`UserProfileView`）的`url`中目前是没有`id`的，按理来说后面应该有个`id`，根据`id`的不同会展示不同用户的动态页面。`vue`中给链接加参数是通过在`path`后面加上`:userid`实现的，`userid`为变量名，例如原来的`path`为`/userprofile/`要加上`id`，则为`/userprofile/:userid/`。路径改完之后想要根据带参的路径访问页面，在导航栏中的用户动态的`router-link`需要加上`params:{userId: }`，然后`UserProfileView`页面可以通过`useRoute`来获取当前页面的参数

```vue
// src/router/index.js
……
const routes = [
……
{
	path: '/userprofile/:userid',
	name: 'userprofile',
	component: UserProfileView
},
……
]
……

// src/components/NavBar.vue
<template>
……
<li class="nav-item">
    <router-link class="nav-link" :to="{name: 'userprofile', params: {userid: '2'}}">用户动态</router-link>
</li>
……
</template>
……

// src/view/UserProfileView.vue
……

<script>
……
import { useRouter } from 'vue-router'
    
export default {
    ……
    setup() {
        const route = useRoute();
        const userId = route.params.userid;
        console.log(userId);
        ……
    }
    ……
}
</script>

……
```

接下来实现一下登录页面，因为接下来很多功能都需要登录才能用。可以在`bootstrap`中找一个合适的表单样式稍加修改用于登录页面。

如果想要实现登录的功能则需要动态的获取用户名和密码，这里就需要两个双向绑定的响应式变量，响应式变量一般是用`ref`或`reactive`进行存储，这里是用的`ref`（感觉也能用`reactive`），然后可以用`v-model`将`username`和`input`双向绑定起来，同理也可以将`password`双向绑定起来，之后还有一个提交功能，这里需要手写一下点击提交之后的事件`login`，先把这个事件写为在控制台返回获取到的`username`和`password`的信息，看能不能成功获取到，写完事件之后需要在`form`标签中绑定这个事件`@submit="login"`，这样就能在控制台返回得到的信息了。此时点击提交，在控制台中会闪过我们得到的信息，这里是因为`form`只是绑定了一个在表单提交之前的事件，执行完这个事件之后仍然会执行原本的提交事件，如果希望阻止掉这个事件，可以在绑定事件的时候写为`@submit.prevent="login"`，这样就可以阻止掉表单原本的默认事件。

![image-20221116113342032](https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221116113342032.png)

因为有很多页面都需要访问到用户的信息，所以用户的信息需要存储到一个全局变量中，`vue`中父组件向子组件传递信息一般是用`props`，子组件向父组件传递信息是用`emit`，从这里可以发现，如果我们想要使用一般的方法进行传递信息只能沿着父子关系进行传递，会比较麻烦，遇到这种情况可以使用`vuex`，这是`vue`中提供的一个维护全局变量的机制，如果两个不是父子关系的组件想要进行交互则可以通过分别和`vuex`维护的全局变量进行交互来实现。下面是一个使用`vuex`的例子

```javascript
// src/store/index.js

import { createStore } from 'vuex'
import ModuleUser from './user';

export default createStore({
  state: {	// 用来存储所有数据的
      // 比如说state中有一个学生
      student: {
          stuname: "",
          id: "",
          fristName: "",
          lastName: "",
      }
  },
  getters: { // 当我们想获取state中的内容且内容不能直接获取，需要做一些计算的时候，我们一般可以放到getters里面
      // 比如果我们想要获取全名fullName
      fullName(state) {
          return state.student.firstName + state.student.lastName;
      }
  },
  mutations: {
      // 对于state直接进行修改全部放到mutations中
      // mutations不支持异步的操作，如果我们想从云端获取信息再更新到我们的state中，这样是不能写到mutations中的，因为从云端获取信息不是一个同步的过程，当我们等待云端反馈的时候，他就会切换到其它的事件中进行执行，所以这里做了一个分割，在actions中获取云端信息，再到mutations中进行赋值
  },
  actions: { // 用来定义我们对state的各种操作
      // 比如说我们这里定义一个更新用户
      updateUser() {
         
      }, 
      // 一个完整的复杂的修改可以放到actions中
  },
  modules: {
      // 当我们的state中信息比较多时，modules就可以进行分割，
      // 每一个modules中维护的对象也是一个state对象，同样具有getters、mutations、actions、modules等方法
      user: MouduleUser,
  }
})

// src/store/user.js
const ModuleUser = {
    state: {
        id: "",
        username: "",
        photo: "",
        followerCount: 0,
	},
    getters: {
        
    },
    mutations: {
        
    },
    actions: {
        
    },
    modules: {
        
    }
};

export default ModuleUser;
```

用户登录状态的维护

- 传统的维护用户登录的方式。当`client`将用户名和密码传递给`server`时，`server`会给我们的`client`传递一个`session_id`同时`server`会将`session_id`传递到数据库中，当用户访问在访问服务器时，会默认将`session_id`带上，当`server`接收到`client`的请求时，会将`session_id`截取出来再数据库中进行查询，则说明登录过，如果没有则说明没有登录过。这种验证方式的`session_id`一般是存储在`cookie`中，这种`cookie`带有`httpOnly`，`js`是不允许访问这种`cookie`的，这样的话就会有一个问题，当我们想要跨域访问时就很难去维护登录状态，所以后面就有一个新的维护登录的方式`jwt`

  <img src="https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221116124919674.png" alt="image-20221116124919674" style="zoom:50%;" />

- `jwt`（`json web token`），这个东西并不是只用于维护登录状态，它可以用来传递很多信息。第一次访问时将用户名和密码传递给服务器，服务器验证成功之后，会给`client`传递一个`jwt`，其实也是一个字符串，但时`server`并不会存储这个字符串，之后`client`在向`server`发送需要验证的请求时，`client`会附加上这个`jwt`，`server`虽然没有存储`jwt`但是它能够验证这个`jwt`是不是合法的。y总的获取`jwt`的`API`中返回的包括两个信息一个`refresh`、一个`access`，`access`就是生成的`jwt`，`refresh`是用来刷新`jwt`的

  ![image-20221116130157234](https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221116130157234.png)

  知道这个原理之后就可以开始写登录了

  ```javascript
  // src/store/index.js
  
  import { createStore } from 'vuex'
  import ModuleUser from './user';
  
  export default createStore({
    state: {
    },
    getters: {
    },
    mutations: {
    },
    actions: {
    },
    modules: {
        user: MouduleUser,
    }
  })
  
  // src/store/user.js
  import $ from 'jquery';
  
  const ModuleUser = {
      state: {
          id: "",
          username: "",
          photo: "",
          followerCount: 0,
  	},
      getters: {
          
      },
      mutations: {
      },
      actions: {	// context用来传api，data是自己传的
          login(context, data) {
              $.ajax({
                  url: "https://app165.acapp.acwing.com.cn/api/token/",
                  type: "POST",
                  data: {
                      username: data.username,
                      password: data.password,
                  },
                  success(resp) {
                      console.log(resp);
                  }
              });
          }
      },
      modules: {
          
      }
  };
  
  export default ModuleUser;
  ```

  在`loginView`中进行调用。首先导入`useStore`，如果我们想要在外面调用`actions`中的某一个事件的话，需要用到`dispatch`这个`api`，

  ```vue
  ……
  
  <script>
  ……
  import { useStore } from 'vuex';
  
  export default {
      ……
  
      setup() {
          const store = useStore();
       	……
  
          const login = () => {
              // 参数为login事件和其对应的参数，username、password、一个成功的回调函数和一个失败的回调函数
              store.dispatch("login", {
                  username: username.value,
                  password: password.value,
                  success() {
                      console.log("success");
                  },
                  error() {
                      console.log("failed");
                  }
              })
          }
  		……
      }
  }
  </script>
  
  
  ```

  这样就能得到`api`中返回的`refresh`和`access` 了

  ![image-20221116152248711](https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221116152248711.png)

  获取完之后我们可以把它解析出来，就可以获取用户信息了，这个也是通过调用y总的`api`来实现的，这个`api`需要`userId`做为参数且需要验证，`userId`在`jwt`中，需要`npm i jwt-decode`引入解码包，将`jwt`进行解码即可得到`userId`，使用`ajax`进行访问验证成功之后，`server`就会返回用户的具体信息，有了这些信息之后我们需要将信息存到`state`中，更新信息的时候不能直接在`actions`中进行更新，需要在`mutations`中进行更新，在`mutations`中定义一个赋值的事件，在`actions`中的事件成功获取到用户的信息之后使用`context.commit`调用`mutations`中的赋值的事件进行赋值

  ```vue
  import $ from 'jquery'
  import jwt_decode from 'jwt-decode'
  
  const ModuleUser = {
      state: {
          id: "",
          username: "",
          photo: "",
          followerCount: 0,
          access: "",
          refresh: "",
          is_login: false,
      },
      getters: {
  
      },
      mutations: {
          updateUser(state, user) {
              state.id = user.id;
              state.username = user.username;
              state.photo = user.photo;
              state.followerCount = user.followerCount;
              state.access = user.access;
              state.refresh = user.refresh;
              state.is_login = user.is_login;
          }
      },
      actions: { // context用来传api，data是自己定义的
          login(context, data) {
              $.ajax({
                  url: "https://app165.acapp.acwing.com.cn/api/token/",
                  type: "POST",
                  data: {
                      username: data.username,
                      password: data.password,
                  },
                  success(resp) {
                      const {access, refresh} = resp;
                      const access_obj = jwt_decode(access);
                      $.ajax ({
                          url: "https://app165.acapp.acwing.com.cn/myspace/getinfo/",
                          type: "GET",
                          data: {
                              user_id: access_obj.user_id
                          },
                          // jwt验证不要忘了Bearer后面的空格
                          headers: {
                              'Authorization': "Bearer " + access,
                          },
                          success(resp) {
                              context.commit("updateUser", {
                                  ...resp,    // 解构resp
                                  access: access,
                                  refresh: refresh,
                                  is_login: true,
                              });
                              data.success();
                          },
                      })
                  },
                  error() {
                      data.error();
                  }
              });
          }
      },
      modules: {
  
      }
  };
  
  export default ModuleUser;
  ```

  y总的返回的`jwt api`中的`access`过五分钟就会过期，所以需要定期的去刷新`access`，这里可以用很多种方式实现，一种比较智能的方式就是当我们每次访问的时候如果发现`access`过期了就去刷新一下`access`得到 一个新的`access`再进行访问，但是这种方法实现起来比较复杂一些，因为我们这里是学习，不是写项目，所以可以先用一种比较傻一点的方式防止`access`过期，就是每隔五分钟就刷新一次`access`。

  ```vue
  // src/store/user.js
  import $ from 'jquery'
  import jwt_decode from 'jwt-decode'
  
  const ModuleUser = {
  	……
      mutations: {
          ……
          updateAccess(state, access) {
              state.access = access;
          }
      },
      actions: { // context用来传api，data是自己定义的
          login(context, data) {
              $.ajax({
                  ……
                  success(resp) {
                      ……
  
                      setInterval(() => {
                          $.ajax({
                              url: "https://app165.acapp.acwing.com.cn/api/token/refresh/",
                              type: "POST",
                              data: {
                                  refresh: refresh,
                              },
                              success(resp) {
                                  context.commit("updateAccess", resp.access);
                              }
                          });
                      }, 4.5 * 60 * 1000);
  
                     ……
              });
          }
      },
      modules: {
  
      }
  };
  
  export default ModuleUser;
  ```

  这样就实现了从表单中获取用户名和密码，发送给服务器进行登录验证，验证成功之后服务器把用户信息返回给用户，并将用户信息成功的存储到了全局变量`state`中（不知道为什么我输入错误的用户名和密码的时候会提示跨域失败，输入正确的密码的时候可以登录成功且不会报错）

  一般登录成功之后会跳转到首页，我们这里设置成登录成功之后跳转到好友列表界面，在`LoginView`中引入`router`，`import router from '@/router/index`，`@`默认为`src/`，之后在登录成功的回调函数中调用用户列表界面`router.push({name: 'userlist'})`，在登录失败的回调函数中返回`用户名或密码错误`，这样就实现了完整的登录了

  ```vue
  // src/views/LoginView
  
  ……
  
  <script>
  ……
  import router from '@/router/index'
  
  export default {
  	……
      setup() {
      	……
          const login = () => {
              error_message.value = '';
              store.dispatch("login", {
                  username: username.value,
                  password: password.value,
                  success() {
                      router.push({name: 'userlist'});
                  },
                  error() {
                      error_message.value = '用户名或密码错误';
                  }
              })
          }
  
          ……
      }
  }
  </script>
  
  ……
  ```

实现登录之后右上角显示用户名和退出，点击用户名就会跳转到自己的空间，点击退出会退出登录

因为登录成功之后的用户信息是存储在`state`中，所以在`template`中可以直接进行使用，如果当前状态为登录成功的状态右上角就返回用户的信息，如果当前状态未登录右上角就显示登录。

点击用户名跳转到用户空间界面，`vue`中界面的跳转是通过`router-link`实现的，只需要改变`:\to`中的信息即可。

退出只需要把`jwt`删除就可以实现退出登录的功能了，这里不需要用到页面的跳转所以不需要用到`router-link`，所以可以把退出的标签改为`a`标签，把删除`jwt`的事件绑定到`a`标签上，点击这个标签触发删除`jwt`的事件。删除`jwt`也就是清空从`jwt`中获取到信息，需要对`state`进行操作，而对`state`中的对象进行赋值的操作只能在`actions`或`mutations`中进行，所以需要在`actions`或`mutations`中写一个事件负责清空`state`（因为只是一个清空的操作比较简单，所以可以在`mutations`中直接进行），然后就可以在其它组件中调用这个事件从而实现退出登录。调用`actions`中的`api`要使用`store.dispatch`，调用`mutations`中的`api`需使用`store.commit`，使用之前都需要对`useRoute`进行引用。

```vue
// src/components/NavBar

<template>
<nav class="navbar navbar-expand-lg navbar-light bg-light">
    <div class="container">
        ……
        <ul class="navbar-nav" v-if="!$store.state.user.is_login">
            <li class="nav-item">
            <router-link class="nav-link" :to="{name: 'login'}">登录</router-link>
            </li>
            <li class="nav-item">
                <router-link class="nav-link" :to="{name: 'register'}">注册</router-link>
                </li>
        </ul>
        <ul class="navbar-nav" v-else>
            <li class="nav-item">
            <router-link class="nav-link" 
            :to="{name: 'userprofile', params: {userid: $store.state.user.id }}">{{ $store.state.user.username }}</router-link>
            </li>
            <li class="nav-item">
                <router-link class="nav-link" :to="{name: 'register'}">注册</router-link>
                </li>
        </ul>
        
        ……
    </div>
    </nav>
</template>

<script>
import { useStore } from 'vuex';

export default {
    name: "NavBar",
    setup() {
        const store = useStore();
        const logout = () => {
            store.commit("logout");
        };

        return {
            logout,
        }
    }
}
</script>

// src/store/user.js

const ModuleUser = {
    state: {
        ……
    },
    getters: {

    },
    mutations: {
        ……
        logout(state) {
            state.id = "";
            state.username = "";
            state.photo = "";
            state.followerCount = "";
            state.access = "";
            state.refresh = "";
            state.is_login = false;
        },
    },
    actions: {
        ……
    },
    modules: {

    }
};
……

```

将用户动态页面整合到用户列表中，当用户是登录状态时，点击不同的用户显示不同的用户动态，如果是 未登录的状态就跳转到登录界面

首先在导航栏中将用户动态页面删掉，然后在用户列表中实现一个事件判断当前是否登录，以及登录之后的跳转，判断一个函数是否登录需要使用到`state`中的`user.is_login`，所以要引入`useStore`，登录之后的跳转要使用到`router.push`，所以要引入`router`。`vue`的`template`中给标签绑定的事件传参数只需要在事件名后加一个括号在括号中写入参数名即可（如果是`react`中则需要自己写一个箭头函数来传参数），事件加不加括号是两种不同的概念，不加括号时传的是定义，加了括号的是函数调用，`vue`中能这两者混为一谈是因为在底层加了判断，如果是一个执行逻辑就会把这个函数封装为一个箭头函数。

```vue
<template>
    <ContentBase>
        <div class="card"  v-for="user in users" :key="user.id" @click="open_user_profile(user.id)">
            ……
        </div>
    </ContentBase>
</template>

<script>
……
import { useStore } from 'vuex'
import router from '@/router'

export default {
   ……

    setup() {
        const store = useStore();
        ……
        const open_user_profile = userId => {
            if (store.state.user.is_login) {
                router.push({
                    name: "userprofile",
                    params: {
                        userid: userId,
                    }
                })
            } else {
                router.push({
                    name: "login",
                })
            }
        }

        return {
            users,
            open_user_profile,
        }
    }
}
</script>

……
```

实现点击不同的好友，动态空间中展示不同用户的信息

删除用户动态页面之前写的静态的内容，从云端拉取信息，一个是用户信息，一个是这个用户历史上发的所有的帖子。

从云端动态拉去信息需要用到`ajax`，所以需要把`$`引入进来，`import $ from 'jquery'`。使用`ajax`访问y总的`api`得到用户信息，并将得到的用户信息存储到当前组件中，然后再把之前`template`中显示的静态内容改为得到的动态内容即可

```
// src/view/UserProfileView

setup() {
        const route = useRoute();
        const userId = route.params.userid;
        // console.log(userId);
        const user = reactive({});
        const posts = reactive({});

        $.ajax({
            url: "https://app165.acapp.acwing.com.cn/myspace/getinfo/",
            type: "GET",
            data: {
                user_id: userId,
            },
            headers: {
                'Authorization': "Bearer " + store.state.user.access,
            },
            success(resp) {
                console.log(resp);
                user.id = resp.id;
                user.username = resp.username;
                user.photo = resp.photo;
                user.followerCount = resp.followerCount;
                user.is_followed = resp.is_followed;
            }
        });

        ……

        return {
            user: user,
            follow,
            unfollow,
            posts,
            post_a_post,
        }
    }
    
// 以下css样式可以时一个div内的图片垂直居中
.img-field {
    display: flex;
    flex-direction: column;
    justify-content: center;
}
```

获取用户发过的动态，方法和前面一样也是用`ajax`从`api`中获得

```vue
// src/view/UserProfileView

$.ajax({
    url: "https://app165.acapp.acwing.com.cn/myspace/post/",
    type: "GET",
    data: {
    	user_id: userId,
    },
    headers: {
    	'Authorization': "Bearer " + store.state.user.access,
    },
    success(resp) {
		posts.count = resp.count;
    	posts.posts = resp;
    }
})
```

实现添加帖子和删除帖子

只有在自己的页面才有添加帖子的模块，所以需要判断一下。在用户动态页面写一个事件使用`computed()`返回判断得到的结果（注意`UserProfileView`的`userId`是`route.params.userid`类型是`string`，而`store.state.user.id`是`number`类型的所以需要把`userId`使用`parseInt`强制转化为整数，再进行判断），将得到的结果作为`v-if`的判断条件

```vue
// src/view/UserProfileView

<template>
……
<UsereProfileWrite v-if="is_me" @post_a_post="post_a_post"/>
……
</template>

<script>
……
expport default {
    ……
    setup() {
        ……
        const userId = parseInt(route.params.userid);
		……
        const is_me = computed(() => userId === store.state.user.id);
		……
        return {
          	……
            is_me,
        }
    }
}
    
</script>
```

当我们打开其它用户的`userProfileView`页面的时候，可以发现我们点击右上角的信息时虽然`url`中的`userid`改变了，但是无法跳转到自己的`userProfileView`页面，原因是因为在判断链接是否相同的时候是不包含我们的参数的，所以我们自己的页面和其它同学的页面是一样的，为了能根据参数来判断页面是否相同，我们需要在`src/App.vue` 的`router-view`标签中加上一个`:key="$route.fullPath"`参数，表示用完整路径来判重，这个就能够进行跳转了。

实现动态添加帖子

同样也是使用`ajax`调用`api`

```vue
// src/components/UserProfileWrite
……
const post_a_post = () => {
    $.ajax({
        url: "https://app165.acapp.acwing.com.cn/myspace/post/",
        type: "POST",
        data: {
            content: content.value,
    	},
    	headers: {
      		'Authorization': "Bearer " + store.state.user.access,
    	},
        success(resp) {
            if (resp.result === "success") {
                context.emit("post_a_post", content.value);
                content.value="";
        	}
        }
	});
}
……
```

实现删除帖子

首先给`postlist`加上一个删除按钮，可以直接在`bootstrap`中找一个`button`样式，然后自己再进行修改。自己只能删除自己发布的帖子，所以需要加入一个辅助的计算属性`is_me`，用来判断当前页面是不是自己的，判断当前动态页面是不是自己的是通过比较`store.state.user.id`和`user.id`是否相同，`user.id`存储在父组件中，所以需要绑定后，再使用`props`进行接收

```vue
<template>
……
<button type="button" class="btn btn-danger" v-if="is_me">删除</button>
……
</template>

<script>
import { computed } from 'vue';
import { useStore } from 'vuex';

export default {
    name: "UserProfilePosts",
    props: {
        posts: {
            type: Object,
            required: true,
        },
        user: {
            type: Object,
            required: true,
        }
    },
    setup(props) {
        const store = useStore();
        let is_me = computed(() => store.state.user.id === props.user.id);

        return {
            is_me,
        }
    }
}
</script>

<style scoped>
……

button {
    float: right;
}
</style>
```

这样前端展示删除按钮就实现了，我们还需要给它绑定一个删除事件能够让它真的删除，`posts`中的信息是存储在`UserProfileView`页面上，所以需要在这个页面写一个删除`post`的事件（根据`post_id`进行删除，删除之后更新`posts.count`），绑定到子组件的标签上，然后再在子组件中写一个事件绑定到按钮上，当我们点击按钮就会触发这个事件，子组件中的这个事件又会触发父组件中删除`post`的事件，这样就完成了前端删除`post`

```vue
// src/views/UserProfileView

<template>
    <div class="col-9">
        <UserProfilePosts :posts="posts" :user="user" @delete_a_post="delete_a_post"/>                
    </div>
</template>

<script>
……
setup() {
    ……
    const delete_a_post = post_id => {
        posts.posts = posts.posts.filter(post => post.id !== post_id);
        posts.count = posts.posts.length;
    }
    ……
    
    return {
        delete_a_post,
    }
}
……
</script>
……

// src/components/UserProfilePosts

<template>
……
<button @click="delete_a_post(post.id)" type="button" class="btn btn-danger" v-if="is_me">删除</button>
……
</template>

<script>
……
setup(props, context) {
    const delete_a_post = post_id => {
        context.emit('delete_a_post', post_id);
    }

    return {
        delete_a_post,  
    }
}
……
</script>
……
```

实现后端删除，使用`ajax`调用后端`api`进行删除

```vue
// src/components/UserProfilePosts

const delete_a_post = post_id => {
    $.ajax({
        url: "https://app165.acapp.acwing.com.cn/myspace/post/",
        type: "DELETE",
        data: {
        	post_id,
        },
        headers: {
        	'Authorization': "Bearer " + store.state.user.access,
        },
        success(resp) {
            if (resp.result === "success") {
            	context.emit('delete_a_post', post_id);
        	}
        }
    });
}
```

实现关注功能

现在能够关注，但是不会保存到后端的数据库中，所以需要使用`ajax`调用后端的`api`来实现后端存储（问题：自己可以关注自己）

```vue
// src/components/UserProfileInfo

setup(props, context) {

    const store = useStore();

    const follow = () => {
        $.ajax({
            url: "https://app165.acapp.acwing.com.cn/myspace/follow/",
            type: "POST",
            data: {
            	target_id: props.user.id,
            },
            headers: {
            	'Authorization': "Bearer " + store.state.user.access,
            },
            success(resp) {
            	if (resp.result === "success") {
            		context.emit("follow");
            	}
            }
        });
    };

    const unfollow = () => {
   		$.ajax({
            url: "https://app165.acapp.acwing.com.cn/myspace/follow/",
            type: "POST",
            data: {
            	target_id: props.user.id,
            },
            headers: {
            	'Authorization': "Bearer " + store.state.user.access,
            },
            success(resp) {
            	if (resp.result === "success") {
            		context.emit("unfollow");
            	}
            }
        });
};
```



实现注册功能，成功注册之后直接登录，登录成功之后跳转到用户列表界面，注册或者登录失败返回失败信息

```vue
// src/views/RegisterView

<template>
    <ContentBase>
        <div class="row justify-content-md-center">
            <div class="col-3">
                <form @submit.prevent="register">
                    <div class="mb-3">
                      <label for="username" class="form-label">用户名</label>
                      <input v-model="username" type="text" class="form-control" id="username">
                    </div>
                    <div class="mb-3">
                      <label for="password" class="form-label">密码</label>
                      <input v-model="password" type="password" class="form-control" id="password">
                    </div>
                    <div class="mb-3">
                        <label for="password_confirm" class="form-label">确认密码</label>
                        <input v-model="password_confirm" type="password" class="form-control" id="password_confirm">
                      </div>
                    <div class="error-message">{{ error_message }}</div>
                    <button type="submit" class="btn btn-primary">登录</button>
                </form>
            </div>
        </div>
    </ContentBase>
</template>

<script>
import ContentBase from '../components/ContentBase.vue'
import { ref } from 'vue'
import { useStore } from 'vuex';
import router from '@/router/index'
import $ from 'jquery';

export default {
    name: "RegisterView",
    components: {
        ContentBase,
    },

    setup() {
        const store = useStore();
        console.log(store, router);
        let username = ref('');
        let password = ref('');
        let password_confirm = ref('');
        let error_message = ref('');

        const register = () => {
            $.ajax({
                url: "https://app165.acapp.acwing.com.cn/myspace/user/",
                type: "POST",
                data: {
                    username: username.value,
                    password: password.value,
                    password_confirm: password_confirm.value,
                },
                success(resp) {
                    if (resp.result === "success") {
                        store.dispatch("login", {
                            username: username.value,
                            password: password.value,
                            success() {
                                router.push({name: "userlist"});
                            },
                            error() {
                                error_message = "系统异常，请稍后重试";
                            }
                        });
                    } else {
                        error_message.value = resp.result;
                    }
                }
            });
        }

        return {
            username,
            password,
            password_confirm,
            error_message,
            register,
        }
    }
}
</script>

<style scoped>

button {
    width: 100%;
}
.error-message {
    color: red;
}
</style>
```



项目部署

因为是要放到`django`服务器的`myspace`路径下，所以`vue`中所有的路径前都需要加上`/myspace`再进行打包，点击`build`，生成`dist`文件夹，`tar -zcvf dist.tar.gz dis/`打包`dist`文件夹，上传到`django`服务器，
