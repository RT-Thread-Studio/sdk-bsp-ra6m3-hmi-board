# HMI-Board Video Demo 上手指南

## 硬件连接方式

* 将 SD 卡插入开发板背面卡槽
* 将喇叭插入开发板背面音频输出接口

## SD卡格式化

这里我使用 `DiskGenius` 工具进行 SD卡格式化，值得注意的是：SD卡需要使用 512 Byte 大小格式化扇区。

![](docs/picture/8.png)

## 视频制作方式

这里我使用 [格式工厂](http://down.pcgeshi.com/FormatFactory_setup.exe) 软件进行视频转码处理，具体使用方式如下：

![](docs/picture/3.png)

* 视频配置选项：

![](docs/picture/4.png)

* 音频配置选项：

![](docs/picture/5.png)

* 配置选择好并选择指定的输出路径后，点击确定。最后点击开始转码即可完成视频转换步骤

![](docs/picture/6.png)

* 视频转换成功后，将其后缀名为 .avi 的视频存放到 sdcard 中即可

## HMI-Board-Video Demo 使用方式

1. 准备一张 8GB SDCard，拷贝视频资源到存储卡
2. 将 SDCard 插入 SD 卡接口
3. 连接 RGB 屏幕
4. 烧录固件
5. 正常运行上电屏幕上会便会循环遍历播放文件系统中的视频文件
6. 使用 UI 的上下按键可以切换上/下一个视频资源，使用左侧的滑条可以调节音量大小（向上滑动+，向下滑动-）
