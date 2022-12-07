## 用户动态界面（三）— `UserProfilePosts`

`UserProfilePosts`组件的功能是将用户发过的帖子全部渲染出来，帖子可以存储在一个列表中。可以先在`UserProfileView`中存储一个静态的帖子列表，然后在`UserProfilePosts`中渲染出来。

首先定义一个动态列表和定义`user`类似，也就是在`UserProfileView`的`setup`中定义`posts`，定义完之后在`template`中进行绑定，就可以将`posts`传到`UserProfilePosts`中了

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

![image-20221114212942577](https://typora-1303258815.cos.ap-chengdu.myqcloud.com/typora-imgs/image-20221114212942577.png)