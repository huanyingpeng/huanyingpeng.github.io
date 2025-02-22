---
title: Docker 实践
date: 2025-02-22 10:58:19
tags:
- Docker
categories:
- 技术
description: 本文介绍了 Docker 的基本操作方法, 强调了一些易错点.
---

## 查看镜像和容器

- 显示本地所有镜像：

  ```bash
  docker image ls
  ```

- 显示所有正在运行的容器：

  ```bash
  docker ps
  ```

- 显示所有容器（包括停止的）：

  ```bash
  docker ps -a
  ```

## 运行容器

- 从镜像新建并运行一个容器

  ```shell
  docker run <image_name>
  ```

  可选参数表：

  - `-d`：以守护模式运行。
  - `-it`：保持 STDIN 打开并分配一个伪终端。（建永远选上这个）
  - `--name <name>`：给容器起个名，易于区分。
  - `-p <host_port>:<client_port>` ：进行端口映射，可以有多个 `-p <host_port>:<client_port>` 字段。也支持端口段映射，比如 `-p 8000-8010:8000-8010`。
  - `-e <key>=<value>`：设置启动时环境变量。

  其它事项：

  - 一般来说，如果不指定 `-d`，退出终端时，容器会自动退出。
  - `-d`，`--name`，`-p` 必须在通过镜像创建容器时确定，之后一般无法改变。
  - 如果本地没有 `<image_name>` 镜像，会自动从远端拉去。

- 启动一个被退出的镜像

  ```shell
  docker start <container_name>
  ```

  可选参数表：

  - `-ia`：启动交互模式并附加到一个终端上。

  其它事项：

  - `<container_name>` 支持前缀匹配，不需要全名。

- 附加到一个已经启动的容器中

  ```
  docker exec -it <container_name> /bin/bash
  ```

  可选参数：

  - `-it`：保持 STDIN 打开并进入交互式 shell。

- 在一个已经运行的容器中执行命令

  ```shell
  docker exec <container_name> <COMMAND> <ARGS...>
  ```

  可选参数：

  - `-d`：后台运行命令，不进入容器。
  - `-e <key>=<value>`：设定环境变量。
  - `-w`：指定命令执行的工作目录。

## 容器的生命周期

容器的生命周期与主进程（PID=1 的进程）绑定，主进程退出时容器生命周期结束。

1. 当以 `docker run -it` 运行容器时，**主进程是终端进程**，终端退出则容器退出。

2. 当以 `docker start -ia` 恢复容器运行时， **主进程是终端进程**，终端退出则容器退出。

3. 当以 `docker start` 恢复容器运行时，**主进程是一个守护进程**，再使用 `docker exec -it /bin/bash` 启动容器终端时，终端不作为主进程，退出对容器无影响。
4. 当以 `docker run -d` 运行容器时，**主进程是守护进程**，再使用 `docker exec -it /bin/bash` 启动容器终端时，终端不作为主进程，退出对容器无影响。（该情况下，主动 `docker stop` 容器再用 `docker start -ia` 恢复时，主进程是终端进程而不是守护进程）

## 操作容器

- 删除容器

  ```
  docker -rm <container_name>
  ```

## 制作镜像

### 直接用 container 制作

制作步骤：

- `docker run -it` 一个基础镜像。

- 用终端进行必要的修改。

- `exit` 退出基础镜像并让它停止。

- 执行 `commit` 制作镜像

  ```
  docker commit <container_name> <image_name>[:<version>]
  ```

  - 如果不使用 `[:version]`，默认使用 `latest`。

### 用 Dockerfile 制作

用 container 制作虽然方便，但把所有操作打包到一个层非常不利于维护，所以有条件的话都建议用 Dockerfile 来制作。

一个经典的 Dockerfile 如下：

```dockerfile
FROM image_name:tag

MAINTAINER YOUR_NAME "your_email@example.com"

ENV var_name value

COPY file_path destination_directory

WORKDIR /path/to/workdir

RUN command

EXPOSE port_number

CMD ["command", "arg1", "arg2"]
```

- `FROM`：指定基础镜像。
- `MAINTAINER`：指定作者信息。
- `ENV`：设置环境变量，它在**构建阶段**和**容器生命周期内**均有效。
- `COPY`：从宿主机拷贝文件过来。
- `WORKDIR`：设置工作目录，如果不存在，会递归创建。
- `RUN`：执行必要的构建命令。
- `EXPOSE`：明确要暴露的端口号，但还是需要在  `docker -run` 时使用 `-p` 指定。
- `CMD`：定义 `docker run` 时的默认命令。

制作步骤如下：

- **准备**

  建一个目录，里面创建一个名为 `Dockerfile` 的文件，在里面写命令。

  目录里加上可能要拷贝进去的文件。

- **构建**

  `Dockerfile` 的所在目录下执行以下代码。

  ```shell
  docker build -t [<image_name>[:<version>]] <cwd>
  ```

  - `-t`：一般**必选**，指定镜像名和版本。
  - `cwd`：一般就写 `.` 了。

- **测试**

  看一下构建成功没有。

  ```shell
  docker images
  ```

### 其它常用命令

- 打 tag：

  ```
  docker tag <image>:<old_version> <image>:<new_version>
  ```

  一般创建的时候你会写 `<image>` 和 `<version>`。

  可以把 `<version>` 看成一个指针，创建 image 的时候你让 `<version>` 指向了它。

  `docker tag` 的作用就是将 `<new_version>` 也指向 `<version>` 指向的对象，用以下 cpp 代码理解：

  ```c++
  Image *old_version = new Image();
  Image *new_version = old_version;
  ```

- 镜像保存到文件：

  ```shell
  docker save -o <filename> <image_name>[:<version>]
  ```

- 从文件加载镜像：

  ```shell
  docker load -i <filename>
  ```

- 容器保存到文件：

  ```shell
  docker export -o <filename> <container_name>
  ```

- 从文件将容器**加载为镜像**：

  ````shell
  docker import <filename> <image_name>[:<version>]
  ````

## 跨设备传输

### 推送到 DockerHub

有时候会把 image 推送到 DockerHub 上方便跨设备传输，步骤如下：

1. 注册一个 [DockerHub](https://hub.docker.com/) 账号。

2. 终端登录 DockerHub：

   ```shell
   docker login
   ```

   在提示下输入账号密码即可。

3. tag 你的镜像：

   ```shell
   docker tag <image_name>:<version> <username>/<image_name>:<version>
   ```

4. push 它：

   ```shell
   docker push <username>/<image_name>:<version>
   ```

注意事项：

- 如果你的 `latest` 版本同时也是 `1.0` 版本，那么需要**同时把两个标签推送上去**才行：

  ```shell
  docker push <username>/<image_name>:<latest>
  docker push <username>/<image_name>:<1.0>
  ```

  但是显然只会推一次数据，第二次只是推个标签而已。

### 用传输介质传输

参考上面的 `docker save/load`，`docker export/import` 并使用 U 盘或者网线等介质传输。