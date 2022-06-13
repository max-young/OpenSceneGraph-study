自己敲的《OpenSceneGraph三维渲染引擎设计与实践》里的代码.

不同章节的代码可以通过commit看到:
```shell
$ git log --pretty=oneline
```
通过`git checkout`命令切换.

环境搭建参见: <https://maxyoung.fun/blog/first_step_on_osg.html>

编译和运行:
```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./main
```