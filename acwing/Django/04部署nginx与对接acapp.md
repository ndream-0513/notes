## 部署nginx与对接acapp

[5. 部署nginx与对接acapp - AcWing](https://www.acwing.com/file_system/file/content/whole/index/content/3257028/)


启动nginx

```
sudo /etc/init.d/nginx start
```

修改配置后重新加载生效

```
sudo nginx -s reload
```

启动uwsgi

```
uwsgi --ini scripts/uwsgi.ini		// 在项目路径（acapp/acapp）下启动uwsgi 
```

### 修改bug

#### bug1

鼠标点击移动的位置会有偏差，因为我们之前写的时候默认的画布是在左上角，但在acapp中并不是在左上角

进入```~/acapp/game/static/js/src/playground/player/zbase.js```，求坐标的时候是使用的```e.clientX```和```e.clientY```它是指的整个屏幕的坐标，我们要改成打开的界面的坐标，搜索```canvas getBoundingClientRect```就可以找到设置的方法，

```javascript
add_listening_events() {
    let outer = this;
    this.playground.game_map.$canvas.on("contextmenu", function(){
        return false;
    });
    this.playground.game_map.$canvas.mousedown(function(e){
        // 修改的地方
        const rect = outer.ctx.canvas.getBoundingClientRect();
        if (e.which === 3) {
            outer.move_to(e.clientX - rect.left, e.clientY - rect.top);
        } else if (e.which === 1) {
            if (outer.cur_skill === "fireball") {
                outer.shoot_fireball(e.clientX - rect.left, e.clientY - rect.top);
            }

            outer.cur_skill = null;
        }
    });

    $(window).keydown(function(e) {
        if (e.which === 81) {
            outer.cur_skill = "fireball";
            return false;
        }
    });
}

```

改完之后进行打包，还需要将game的static传到acapp的static中

```
python3 manage.py collectstatic
```

将打包命令合二为一，修改```compress_gam_js.sh```文件，加入

```
echo yes | python3 manage.py collectstatic
```



#### bug2

把菜单页面调出来，把```AcGame```和```AcGamePlayground```两个类中之前注释掉的部分解开，之后再打包运行游戏，进入游戏目录界面之后，再点击单人模式，发现游戏页面并没有变大，原因是因为我们在加载的时候直接设置了界面大小，后面无论怎么调acapp的大小，游戏的幕布都不会改变大小了，所以游戏幕布的初始化应该是在加载出来playground页面之后再初始化，所以初始化的一些参数需要全部移到```show()```里面

```javascript
class AcGamePlayground {
    constructor(root) {
        this.root = root;
        this.$playground = $(`
        <div class="ac_game_playground"></div>
        `);

        this.hide();

        this.start();
    }

    get_random_color() {
        let colors = ["blue", "red", "pink", "skyblue", "green"];
        return colors[Math.floor(Math.random() * 5)];
    }

    start() {
    }

    show() {
        this.$playground.show();
        
        this.root.$ac_game.append(this.$playground);
        this.width = this.$playground.width();
        this.height = this.$playground.height();
        this.game_map = new GameMap(this);
        this.players = [];
        this.players.push(new Player(this, this.width/2, this.height/2, this.height*0.05, "white", this.height * 0.15, true));

        for (let i = 0; i < 5; i ++) {
            this.players.push(new Player(this, this.width / 2, this.height / 2, this.height * 0.05, this.get_random_color(), this.height * 0.15, false));
        }
    }

    hide() {
        this.$playground.hide();
    }
}
```

这样就可以根据前面一个acapp页面的大小来调整大小了，但游戏打开之后再调整大小游戏的页面也不会改变，后面还需要进行更改

#### bug3对菜单页面进行修改

菜单的位置是完全固定的，理想的情况应该是随着acapp的大小而进行改变的，不应该是一个固定距离，应该是一个相对距离，将```.ac_game_menu_field```的top和left修改为百分比的。之后还要对字体大小进行修改。字体往下落是因为有内边距```padding```清空就好

