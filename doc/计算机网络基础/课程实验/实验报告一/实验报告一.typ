#import "../info.typ": *
#set text(11pt)

= 实验报告（一）
实验名称：实验一  网络基本概念

姓名：#name  学号：#studentID  实验班号：#classID  机器号：#tableID

== 一、实验目的

+ 初步了解计算机网络的相关概念
+ 熟练掌握 Windows 环境下网络配置方法
+ 了解基本的网络命令及功能，并能够检测基本的网络问题
+ 了解网络管理诊断软件 Sniffer Pro 的简单操作

== 二、实验过程

=== 1. 实验任务  一

+ 任务内容：完成 Windows 环境下本地网络的配置；设置 IP 地址、子网掩码、网关、首选 DNS 服务器、备用 DNS 服务器，了解各部分的含义。使用 ipconfig、ping、nslookup 等命令进行测试分析。
+ 实验过程：
  + 根据指导用书
  + DNS 服务器相关内容
    + 清空 DNS 服务器设置后，在命令行执行 `ipconfig /flushdns` 刷新 DNS 缓存，此后再运行 `ipconfig /all`，在 DNS 服务器一行为空，说明 DNS 服务器已清除设置。
    + 在控制台运行 `ping info.tsinghua.edu.cn` 此时会显示 `Ping 请求找不到主机 info.tsinghua.edu.cn。请检查该名称，然后重试。`，说明 DNS 服务器未设置时，无法解析域名。
    + 进一步，在 *控制面板*- *网络和 Internet*- *网络和共享中心*- *更改适配器设置* 中，右键选择 *以太网*- *属性*- *Internet 协议版本 4 (TCP/IPv4)*，点击 *属性*，在 *常规* 标签页中，将 *使用下面的 DNS 服务器地址* 选项中的 *首选 DNS 服务器* 和 *备用 DNS 服务器* 分别设置为 `166.111.8.28` 和 `166.111.8.28`，点击 *确定*，关闭窗口后再次运行 `ipconfig /all`，在 DNS 服务器一行中，可以看到设置的 DNS 服务器地址。
    + 此时，运行 `ping info.tsinghua.edu.cn`，可以看到已经可以解析域名，且显示的 IP 地址与 DNS 服务器设置的 IP 地址相同。
    + 进一步，加上 `-a` 参数，运行 `ping -a info.tsinghua.edu.cn` 得到的结果中只有与时间有关的信息。
+ 结果与分析
  + `ipconfig` 命令用于显示所有当前的 TCP/IP 网络配置值
    + 命令格式：`ipconfig [/? | /all | /release [adapter] | /renew [adapter] | /flushdns | /displaydns | /registerdns | /showclassid adapter | /setclassid adapter [classidtohost] ]`
    + `ipconfig /all` 产生完整显示，`ipconfig /flushdns` 刷新 DNS 缓存，为常用命令，一般情况下，可以使用 `/?` 参数来查看当前命令所接受的参数
  + `ping` 命令用于测试与另一台主机的连接状态，如配置好网络时候运行 `ping info.tsinghua.edu.cn` 可以看到一下结果运行：
    ```txt
    正在 Ping info.tsinghua.edu.cn [166.111.4.79] 具有 32 字节的数据:
    来自 166.111.4.79 的回复: 字节=32 时间=3ms TTL=60
    来自 166.111.4.79 的回复: 字节=32 时间=1ms TTL=60
    来自 166.111.4.79 的回复: 字节=32 时间=4ms TTL=60
    来自 166.111.4.79 的回复: 字节=32 时间=1ms TTL=60

    166.111.4.79 的 Ping 统计信息:
        数据包: 已发送 = 4，已接收 = 4，丢失 = 0 (0% 丢失)，
    往返行程的估计时间(以毫秒为单位):
        最短 = 1ms，最长 = 4ms，平均 = 2ms
    ```
+ 思考题
  + 

=== 2. 实验任务  二

+ 任务内容：熟悉常用的网络命令，如：tracert、arp、route、net、netstat 等命令
+ 实验过程：
  + 利用 `tracert` 跟踪路由，在命令行窗口中，依次键入 `tracert 192.168.20.200`， `tracert 166.111.60.1`，`tracert 166.111.8.28`，`tracert 166.111.4.100`，`tracert info.tsinghua.edu.cn`，`tracert www.sina.com` 和 `tracert 207.46.19.254`，并分析结果。
  + 搜索 IP 物理位置，打开 `https://www.ip138.com`，将 `183.172.69.55` 输入
  + 添加多个 IP 地址，在 `WLAN 属性` - `Internet 协议版本 4 (TCP/IPv4)` - `属性` - `常规` - `高级` 中，点击 `添加`，输入 IP 地址 `192.168.2.18` 和子网掩码 `255.255.255.0`，设置完成后保存退出，运行 `ipconfig /all`，可以看到多个 IP 地址。
  + DNS 相关实验
    - `ipconfig /displaydns` 查看本地 DNS 名字缓存
    - `ipconfig /flushdns` 刷新本地 DNS 缓存
    + arp 命令，命令行运行 `arp -a` 查看本地 ARP 表，运行 `arp -d` 清空本地 ARP 表，运行 `arp -s 192.168.20.218 00-aa-00-62-c6-09` 添加本地 arp 表项
+ 结果与分析
  - 结果1：在测试前几个 ipv4 地址或域名时，能较快返回完整结果，而在之后的域名通常会出现某个路由超时连接的情况。
  - 分析：`tracert` 用于跟踪数据包的路由，用于确定 IP 数据包访问目标所采取的路径，其默认情况下最多跟踪（返回）30 个 IP 节点，每个节点的最大超时时间为 3 秒。当数据包到达目标时，或者到达最大跟踪次数时，跟踪就会停止。在尝试某个节点超时时，会以星号`*`的形式返回数据。
  - 结果2：在 `https://www.ip138.com` 中，输入 `183.172.69.55` 显示 IP 的物理地址为：北京市	清华大学
  - 分析：
  - 结果3：添加 IP 地址后，运行 `ipconfig /all` 的结果中，显示本机的 IP 地址为 `192.168.20.218` 和 `192.168.2.18`
  - 分析：
  - 结果4：在 `ipconfig /displaydns` 中，显示本地 DNS 名字缓存，其中包含了本机访问过的域名和 IP 地址的对应关系，按 `Ctrl + C` 退出
  - 分析：
  - 结果5：在 `ipconfig /flushdns` 中，显示本地 DNS 缓存已刷新
  - 分析：`ipconfig /flushdns` 用于刷新本地 DNS 缓存，当本地 DNS 服务器的缓存内容过多或者内容已经过期时，可以使用该命令来刷新本地 DNS 缓存。修改本地网络配置时（如修改 DNS），就需要刷新 DNS 缓存
  - 结果6：运行 `arp -a` 首先返回接口地址，同时返回本地 ARP 表，其中包含了本机访问过的 IP 地址和 MAC 地址的对应关系，如：
    ```txt
    接口: 183.172.69.55 --- 0xd
      Internet 地址         物理地址              类型
      183.172.64.1          90-03-25-b9-24-0a     动态
      183.172.71.255        ff-ff-ff-ff-ff-ff     静态
      224.0.0.2             01-00-5e-00-00-02     静态
      224.0.0.22            01-00-5e-00-00-16     静态
      224.0.0.113           01-00-5e-00-00-71     静态
      224.0.0.251           01-00-5e-00-00-fb     静态
      224.0.0.252           01-00-5e-00-00-fc     静态
      239.255.255.250       01-00-5e-7f-ff-fa     静态
      255.255.255.255       ff-ff-ff-ff-ff-ff     静态
    ```
    进一步，运行 `arp -d` 清空本地 ARP 表，然后再次运行 `arp -a`，此时返回的本地 ARP 表为空，最后，运行 `arp -s 192.168.20.218 00-aa-00-62-c6-09` 后，再运行 `arp -a`，可看到本地 ARP 表中已添加了一项映射——`192.168.20.218 00-aa-00-62-c6-09`
  - 分析：arp 命令用于显示和修改 IP 与 MAC 地址的映射表，`arp -a` 用于显示本地 ARP 表，`arp -d` 用于清空本地 ARP 表，`arp -s` 用于添加本地 ARP 表项，`arp -a` 用于显示本地 ARP 表，需要注意的是，再同一个局域网中，不允许出现两个相同的 MAC 地址指向不同的 IP，因而，在一个人添加了 ARP 表项之后，另一个人就不能用其他 IP 值来添加指向的 MAC 地址，否则会出现冲突

=== 3. 实验任务  三

+ 实验内容：DHCP 客户端的应用
+ 实验过程：
  + 实验开始前，通过 `ipconfig /all` 查看当前分配的 IP 地址等信息
  + 在 `服务` 中找到 `DHCP Client`，讲启动类型改为禁用，并保存退出
  + 此时再运行 `ipconfig /all` 查看 IP 地址等信息，此时 IP 地址已固定，显示 DHCP 已关闭
+ 结果与分析:
  - 

=== 4. 实验任务  四

+ 实验内容：利用 Sniffer Pro 软件完成简单的网络诊断任务
+ 实验过程：
  + 配置环境，在 `File -> select settings` 中设置网络适配器
  + 监听网络通讯状况，在 `Capture -> Start` 中开始监听
  + 捕获报文并进行解析，在 `Capture -> Stop` 中停止监听，然后在 `Analyze -> Decode As` 中选择 `Decode As`，在 `Decode As` 窗口中选择 `Transport`，在 `Transport` 窗口中选择 `TCP`，在 `TCP` 窗口中选择 `Port`，在 `Port` 窗口中选择 `80`，然后点击 `OK`
  + 设置捕获条件，在 `Capture -> Capture Filter` 中设置捕获条件
  + 查看源为本机的报文，在 `Analyze -> Display Filters` 中选择 `IP`，在 `IP` 窗口中选择 `Source`，在 `Source` 窗口中选择 `Host`
  + 查看源为本机的报文，在 `Analyze -> Display Filters` 中选择 `IP`，在 `IP` 窗口中选择 `Destination`，在 `Destination` 窗口中选择 `Host`
  + 分析IP协议和ARP协议内容，在 `Analyze -> Decode As` 中选择 `Decode As`，在 `Decode As` 窗口中选择 `Network`，在 `Network` 窗口中选择 `IP`，在 `IP` 窗口中选择 `ARP`，然后点击 `OK`
+ 结果与分析

== 三、实验小结

- 本次实验是第一次计算机网络基础实验，因为有些计算机基础，所以对这次实验的看法是觉得第一次实验是真的基础，很多东西讲的也很详细，实验指导书也较为详尽。
- 本次实验的收获是对计算机网络有了初步的了解，对计算机网络的一些基本概念有了一定的认识，对计算机网络的一些基本命令也有了一定的了解，对计算机网络的一些基本配置也有了一定的认识。
