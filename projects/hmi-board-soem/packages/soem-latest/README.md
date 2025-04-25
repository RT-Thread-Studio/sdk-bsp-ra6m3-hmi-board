# soem EtherCAT主机

## 1 介绍
SOEM(Simple Open EtherCAT Master Library)是由rt-labs AB, Sweden开发的一款自由软件，实现EtherCAT主机。
具体介绍请查看 https://github.com/OpenEtherCATsociety/SOEM

SOEM支持Windows、Linux等操作系统，但并未支持常用的RT-Thread、FreeRTOS等嵌入式实时系统。现基于lwip, 把SOEM1.4.0移植到RT-Thread。

### 1.1 目录结构
| 名称 | 说明 |
| ---- | ---- |
| docs  | 文档目录 |
| osal  | os抽象层 |
| oshw | os硬件层 |
| soem  | soem etherCAT主站 |
| examples | 应用示例 |


### 1.2 许可证
采用SOEM原始自由软件许可，详见 LICENSE 文件。

### 1.3 依赖
RT-Thread 4.0+，lwip2+

## 2 如何打开 soem
使用 hello package 需要在 RT-Thread 的包管理器中选择它，具体路径如下：

RT-Thread online packages
    miscellaneous packages --->
        [*] soem package


然后让 RT-Thread 的包管理器自动更新，或者使用 pkgs --update 命令更新包到 BSP 中。

##3 使用 soem

在打开 soem package 后，当进行 bsp 编译时，它会被加入到 bsp 工程中进行编译。

查看EtherCAT设备信息
msh>ec_slaveinfo e0

伺服运行测试
msh>ec_simpletest e0

更多文档位于 /docs 下，后续会补充

##4 注意事项
现在的实现是通过lwip的网络设备加钩子函数实现，将来会直接通过emac驱动完成网络数据包收发，提高实时性能，减小网络抖动。

