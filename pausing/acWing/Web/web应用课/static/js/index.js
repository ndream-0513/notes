let input = document.querySelector(".input");
let run = document.querySelector("button");
let output = document.querySelector("pre");

function main() {
    for (let i = 2; i <= 100; i ++) {
        let flag = true;
        for (let j = 2; j * j <= i; j ++)
            if (i % j == 0) {
                flag = false;
                break;
            }
        if (flag) console.log(i);
    }
}

export {
    main
}