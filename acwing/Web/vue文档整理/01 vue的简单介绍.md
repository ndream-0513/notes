## 1、`vue`的简单介绍

### 1.1 `vue`的基本概念

每个页面都是一个`.vue`文件，每个`.vue`文件都由`html`、`js`、`css`三部分组成。一般写网页这三部分都是分开的，在`vue`中将这三个部分放到一块了，同一个页面是一个整体。

`vue`中的`css`部分有一个特性，在`<style>`中加一个`scoped`，不同组件中的`css`文件就不会相互影响了。

`vue`是一个组件化的框架。一个页面可以拆分为若干个不同的部分，每一个部分都可以用一个单独的组件来实现，可以在`html`中通过类似标签的方式进行组件的引用，引用的时候还可以向组件传递一些信息，比如初始项目中有一个`HelloWorld.vue`组件，这个组件可以接收字符串信息，在`HomeView.vue`中的引用为`  <HelloWorld msg="Welcome to Your Vue.js App"/>`

- 后端渲染模型：每打开一个新的`url`都会向服务器发送一个请求，服务器再把这个页面返回回来

- 前端渲染模型：不管我们打开的哪个页面，服务器都会将所有页面的样式返回到一个`js`文件中，当我们在打开其它页面就不会向服务器发送请求了，就会直接用前面返回的`js`文件将新页面渲染出来，这个过程不会像服务器发送请求

### 1.2 项目目录结构介绍

```
build: 构建脚本目录
config：项目配置目录
node_modules: npm加载项目的依赖模块
static: 静态资源目录
package.json: npm包配置文件
src：源码目录
  ├─assets
  ├─components：一般用来存储各种组件，views中也可以存组件，一般怎么存看个人习惯
  ├─router：路由。网址对应的页面，默认有两个路由一个/，一个/about，默认的网址中有#，把createWebHashHistory中的`Hash`去掉即可
  ├─store
  ├─views：一般用来写各种页面。类似于`django`中的views
  └─main.js：整个项目的入口。
  createApp(App).use(store).use(router).mount('#app')创建根组件app，使用store和router（这两个就是在创建项目时安装的vuex、vue-router插件），挂载到id为app的元素上，这个id为app的元素在public/index.html中（感觉这里和hexo挺像的，也是把生成的页面放到public中）。 
```

