## 用户动态页面（一）— `UserProfileView`的基本框架

<img src="https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221114110514925.png" alt="image-20221114110514925" style="zoom:50%;" />

页面布局：可以使用`bootstrap`的`grid`系统，`grid`系统由`div.container`、`div.row`和`div.col`三部分组成，上面的样式可由这部分代码实现，在`ContentBase`组件中已经有一个`div.container`了，所以在`UserProfileView.vue`中可以直接写`div.row`和`div.col`

```vue
// src/views/UserProfileView.vue
<template>
    <div class="row">
        <div class="col-3">
            UserProfileInfo
            UserProfileWrite
        </div>
        <div class="col-9">
        	UserProfilePosts
        </div>
    </div>
</template>

……
```

## 用户动态页面（二）—`UserProfileInfo`组件

### 1、设计图

<img src="https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221114112533283.png" alt="image-20221114112533283" style="zoom:67%;" align=left />

```vue
// src/components/UserProfileInfo.vue
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

### 2、实现效果

![image-20221114115817464](https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221114115817464.png)

```vue
// src/componets/UserProfileView

<template>
    <ContentBase>
      <div class="row">
        <div class="col-3">
          <UserProfileInfo></UserProfileInfo>
        </div>
        <div class="col-9">
          帖子信息
        </div>
      </div>
    </ContentBase>
</template>
  
<script>
import ContentBase from '@/components/ContentBase.vue';
import UserProfileInfo from '@/components/UserProfileInfo.vue';

export default {
  name: 'UserProfileView',
  components: {
    ContentBase,
    UserProfileInfo,
  }
}
</script>
```

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
    color: grey;
}

button {
    padding: 2px 4px;
    font-size: 12px;
}
</style>
```

### 3、实现动态功能

这个组件实现好之后，每个人的页面应该都是不一样的，每个人都有自己各自的头像、用户名、粉丝数，应该是独立的，所以头像、用户名、粉丝数应该都是参数。同时还有发帖功能和帖子具体信息，所以我们可以发现这三个模块都需要一些数据，这些数据相互之间是需要交互的，模块之间的数据交互，一般是把数据存到最顶层的组件中，也就是`UserProfileView`组件中

**父组件向子组件传递信息**（使用的是`vue`的`compositon API`）：

在父组件的`script`中的`export default`中定义一个`setup()`方法，可以在`setup`中定义一堆变量，`setup`是一个函数，`setup: ()=> { }`可以简写为`setup() { }`。

这样就可以在`{ }`中开始定义变量了，因为子组件需要用户信息，所以需要一个`user`，这个`API`定义变量有两种方式，一种`ref`、一种`reactive`，`ref`的运行效率要比`reactive`的运行效率要低一些，所以能用`reactive`的时候尽量不要用`ref`，当我们的变量需要被重新赋值的时候就可以用`ref`，当我们这个变量不会被重新赋值的时候就用`reactive`，`user`是一个用户，当前组件的用户一般都是不会变的，当我们加载下一个页面的时候是一个新的组件，一个新的页面，所以`user`可以用`reactive`，还有一点就是`reactive`只能用来接收对象，`ref`可以用来接受普通的变量类型，比如说一个字符串、一个数字。

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
……
```

这样我们就可以在`UserProfileView`的`template`中使用这些属性了，我们这些属性的值需要在`UserProfileInfo`中被渲染出来，所以需要将这些属性的值传到`UserProfileInfo`中。

`vue`在不同组件中传递信息类似与`react`，父组件向子组件传递信息是通过`props`属性，子组件向父组件传递信息是通过调用函数的方式`event`来传递的。	

<img src="https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221114185329922.png" alt="image-20221114185329922" style="zoom:67%;" align="left" />

父组件向子组件传递信息，需要先将要传递的信息绑定到子组件上。比如`UserProfileView`要向`UserProfileInfo`传递`user`，在`UserProfileView`的`template`中使用`UserProfileInfo`时，要加上`v-bind: user="user"`，也可以直接写为`: user="user"`。`" "`中的内容可以是一个值或表达式，它不是一个普通的字符串。

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

父组件把信息传递过来之后，子组件要进行接收，如何在子组件中接收到这个消息呢？

我们需要把接收的参数放到`props`中。

传完`user`之后`UserProfileInfo`中显示的姓名是由`firstname`和`lastname`组成的，这个值其实是由某些值计算出来的，如果我们想把计算出的值展示出来，我们可以使用`computed`，它可以动态的去计算某个属性。

```vue
// src/components/UserProfileInfo
<template>
……
<div class="name">{{ fullName }}</div>
<div class="fans">粉丝数：{{ user.followerCount }}</div>
……
</template>

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

这样就可以根据`is_follow`来展示关注还是取消关注了。

接下来就需要实现当我们点击关注之后需要更新关注状态，所以这里需要绑定一个事件，我们需要在`setup`中定义一个事件处理函数，定义方法和定义一般的函数相同。定义好之后可以使用`v-on:click`绑定`click`函数，`v-on:`可以简写为`@`

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

这样当我们点击按钮之后控制台就会返回`follow`或者`unfollow`了。

接下来我们需要修改`is_followed`的状态，我们可以发现状态的信息是在`user`里面，但`user`是在父组件中定义的，所以子组件要修改的话，不能直接在子组件中修改，这里就涉及到**子组件向父组件传递信息**。

子组件向父组件传递信息是通过绑定事件的方法。首先需要在父组件的`setup`中实现要绑定的事件函数，再将这个事件绑定到`template`中的子组件上

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

### 4、知识点

- 使用bootstrap实现页面
- 父组件向子组件传递信息的方法
- 子组件向父组件传递信息方法
