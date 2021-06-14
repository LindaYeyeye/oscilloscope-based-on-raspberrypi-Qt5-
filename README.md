# -基于Qt5和树莓派的示波器制作-
## -简介-
一个简单的树莓派小项目，原本的项目任务是利用树莓派制作一个示波器。
![image](https://github.com/Gienne-608/-Qt5-/blob/main/image/1.jpg)
## -树莓派与PC机通讯-
### -安装树莓派系统-
需要的设备： PC机一台，SD卡一张，读卡器一个

rasp系统是一种基于Linux的内核的系统，可以将树莓派看作一台微型计算机，树莓派的系统内核需要我们存入SD卡中。

1、首先需要在树莓派官网下载树莓派系统 官网下载：https://www.raspberrypi.org/downloads/

下载后对文件进行解压，解压后的文件即为烧录时需要使用到的 img 系统文件

2、烧录树莓派系统

我们需要将刚才下载下来的镜像文件烧录入SD卡中，这一步需要下载win32diskimager软件，下载地址https://sourceforge.net/projects/win32diskimager/

插入sd卡，开启软件，点击image文件进行烧录。

### -远程连接树莓派-
树莓派作为一个微型计算机，我们需要外接屏幕来对系统进行操作，如果有显示器的话，直接将树莓派接到显示器上即可。

但是通常来讲我们没有多余的显示器，可以利用wifi作为载体，将本身的PC机屏幕作为显示器来对树莓派进行操作。

#### -网线连接-

直接将网线和树莓派连接起来，可以实现通信

#### -无线wifi连接-

这是比较常见的方法，尤其适用于校园网，路由器等环境

需要的软件：vncviewer,putty

1、我们使用SSH通信实现远程连接，首先需要在树莓派中开启SSH功能。

在SD卡中新建两个文件，分别是命名为SSH的空文件，和 wpa_supplicant.conf 文件

在 wpa_supplicant.conf 文件中写入：

(```)

    country=CN
    ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
    update_config=1
 
    network={
    ssid="WiFi-A" #wifi名称
    psk="12345678" #WiFi密码
    key_mgmt=WPA-PSK
    priority=1  #优先级，如果有多个WiFi的话则按照优先级分别连接
    
(```)

校园网的登陆方式比较奇怪，可能需要账号密码登录。我的做法是，利用电脑热点，树莓派连接电脑热点。

要注意的是树莓派SSH不支持5G连接，所以必须要将热点设置为2.4G频段才可以。

2、远程连接

将树莓派和 PC机连接后，在PC端打开putty，输入树莓派所对应的端口（端口号可以在电脑热点连接界面找到），点击连接

打开vncviewer 开启相应功能 这一部分每个人账号密码设定不同，不在此做说明
## -硬件外设-

由于树莓派没有ADC转化模块，所以我们需要外接一个ADC芯片对模拟量进行采样和读取。 不同芯片的连接方式不同，我采用的是ADC1115

![image](https://github.com/Gienne-608/-Qt5-/blob/main/image/2.jpg)

![image](https://github.com/Gienne-608/-Qt5-/blob/main/image/3.jpg)

读取转化CSV文件程序在 readvoltage 文件夹

## -界面开发-

我采用的开发方式为qt5。树莓派首先读取电压存入CSV文件后，在Qt5上打开该文件进行读取绘制。

可以实现简介中的各项功能





