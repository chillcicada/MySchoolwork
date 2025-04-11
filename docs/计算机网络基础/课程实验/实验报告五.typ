#import "./info.typ": *

#align(center)[
  #text(20pt)[= 实验报告（五）]
]

#set text(
  weight: "regular",
  font: ("Times New Roman", "LXGW WenKai"),
  size: 11pt,
)

实验名称：实验五 DNS 服务的实现 \
姓名：#name 学号：#studentID 实验班号：#classID 机器号：#tableID

#text(16pt)[== 一、实验目的]

+ 了解 DNS 存在的意义。
+ 了解 DNS 的工作原理。
+ 掌握 DNS 配置方法。
+ 掌握 DHCP 配置方法（选做）。

#text(16pt)[== 二、实验过程]

#text(14pt)[=== i. 实验任务 一]

+ 任务内容：实验环境配置并设置网络地址（含 DNS 服务器的安装检查）
+ 实验过程：
  + 断开非板载网卡，实验使用板载网卡（注意需要确认非板载网卡 IP 地址设置为自动获取，可在命令行 `ipconfig /all` 查看并确认）。
  + 设置板载网卡的 IP 地址与首选 DNS 服务器（考虑到该实验需要同组内人员配合，最好设置在同一网段下）。
    以下为本人的板载网卡配置：
    - IP 地址：192.168.20.218
    - 子网掩码：255.255.255.0
    - 默认网关：192.168.20.200
    - DNS 服务器地址：166.111.8.28
    - 备用 DNS 服务器地址：166.111.8.29
  + 记录如下域名对应的 IP 地址
    - www.pku.edu.cn
    - www.tsinghua.edu.cn
    - info.tsinghua.edu.cn
    - learn.tsinghua.edu.cn
    - mail.tsinghua.edu.cn
    - mails.tsinghua.edu.cn
    - www.qq.com
    - www.baidu.com
  + 将板载网卡的 DNS 服务器改为同组配置的 DNS 服务器的地址，但未对对应的 DNS 服务器进行配置。在命令提示符下输入 `ipconfig /flushdns` 刷新 DNS 缓存，并验证能否解析 www.tsinghua.edu.cn
    在实验中，本（组）机配置的 DNS 服务器地址为 192.168.20.218
  + 启动计算机，登入 windows server 系统。
  + 检查计算机是否有安装 DNS 服务，按如下步骤查找并打开 DNS 服务：“开始”-“管理工具”-“DNS”。
    如未找到 DNS 组件，可按照如下步骤安装 DNS 服务器：“开始”-“管理工具”-“服务器管理”-“角色”-“添加角色”-“DNS 服务器”-“安装”。
+ 结果与分析：
  - 在首次配置好网络配置后，记录对应域名的 IP 地址如下
    - www.pku.edu.cn -> 162.105.131.160
    - www.tsinghua.edu.cn -> 166.111.4.100
    - info.tsinghua.edu.cn -> 166.111.4.79
    - learn.tsinghua.edu.cn -> 166.111.4.79
    - mail.tsinghua.edu.cn -> 166.111.204.8
    - mails.tsinghua.edu.cn -> 166.111.204.9
    - www.qq.com -> 175.27.8.138
    - www.baidu.com -> 182.61.200.7
  - 更改 DNS 服务器地址并刷新 DNS 缓存后，`ping www.tsinghua.edu.cn` 的返回值如下：
    ```txt
    Ping 请求不到主机 www.tsinghua.edu.cn。请检查该名称，然后重试。
    ```

#text(14pt)[=== ii. 实验任务 二]

+ 任务内容：配置 DNS 服务器的正向解析
+ 实验过程：
  + 删除已有记录。在“DNS 管理器”控制台下，打卡“根提示”界面，并删除里面的所有记录。
  // #image("https://img.chillcicada.com/i/2024/05/26/6653413ade933.jpg")
  + 新建正向区域。在“正向查找区域”中新建区域，按默认选项即可（主要区域-不允许动态更新），并指定区域名称。
    本次实验中，将区域名称指定为 pku.edu.cn。
  + 新建主机。在新建好的区域中，新建主机，指定主机名和 IP 地址。
    本次实验中，将主机名指定为 www，IP 地址指定为 192.168.20.217。
+ 思考题：
  - 根据删除过程中的提示信息，思考此项的意思。
    防止根提示中已有值对设置值造成覆盖或造成冲突以至于无法使用户设置值生效。

#text(14pt)[=== iii. 实验任务 三]

+ 实验内容：客户端验证
+ 实验过程：
  （需要确保本地网络连接配置中 DNS 服务器地址设置为本组 DNS 服务器地址，可用 `ipconfig /all` 查看）
  + 命令提示符下运行 `ipconfig /flushdns` 清除 DNS 缓存。（也可在 DNS 控制界面手动刷新 DNS 服务器，如：“清除过时资源记录”，“更新服务器数据文件”等，必要时，可重启 DNS 服务。）
  + 在命令提示符下使用 `ping` 或 `nslookup` 命令测试域名解析。
    本次实验中，使用 `ping www.pku.edu.cn` 命令测试域名解析。
+ 结果与分析：
  + `ping www.pku.edu.cn` 的测试结果如下：
    // #image("https://img.chillcicada.com/i/2024/05/26/6653414b26230.jpg")
    说明 DNS 服务器正向解析配置成功。

#text(14pt)[=== iv. 实验任务 四]

+ 实验内容：配置 DNS 服务器的委派
+ 实验过程：
  （该实验需要组内成员共同完成，在本次实验中，本机（192.168.20.218）为 A 服务器，邻机（192.168.20.217）为 B 服务器）
  + 在本机新建区域 aaa.com。
  + 右键 aaa.com，选择“新建委派”，在“受委派域名”界面中填入“bbb”，按默认选项即可。
  + 进入“名称服务器”页面，在“新建名称服务器记录”页面中，“服务器完全限定的域名”处填入“bbb.aaa.com”，在 IP 地址处填入邻机地址（192.168.20.217），单机确认退出。
  // #image("https://img.chillcicada.com/i/2024/05/26/665341549a6b9.jpg")
  + 在邻机新建区域 bbb.aaa.com。接着在该区域中新建主机“www”，设置 IP 地址。
    在本次实验中，“www.bbb.aaa.com” 的 IP 地址被设置为 192.168.20.216 （此设备为关机状态）。
  // #image("https://img.chillcicada.com/i/2024/05/26/6653415cb99f8.jpg")
  + 在命令提示符下使用 `ping` 或 `nslookup` 命令测试域名解析。
    本次实验中，使用 `ping www.pku.edu.cn` 命令测试域名解析。
+ 结果与分析：
  + `ping www.bbb.aaa.com` 的测试结果如下：
    // #image("https://img.chillcicada.com/i/2024/05/26/66534164e4472.jpg")
    说明 DNS 服务器委派配置成功。

#text(14pt)[=== v. 实验任务 五]

+ 实验内容：配置 DNS 转发器或根提示
+ 实验过程：
  + 在根提示中添加学校 DNS 服务器，域名 dns2.tsinghua.edu.cn，IP 地址 166.111.8.31。
    （由于该服务器只能解析校内域名，使用时需要删除本机上与 tsinghua.edu.cn 相关的记录、区域和主机）
  + 在命令提示符下使用 `ping` 或 `nslookup` 命令测试域名解析。
    在本实验中只测试了 `ping www.tsinghua.edu.cn` 命令。
+ 结果与分析：
  + `ping www.tsinghua.edu.cn` 的测试结果如下：
    // #image("https://img.chillcicada.com/i/2024/05/26/6653416e519e9.jpg")
    返回的 IP 地址与实验起始的记录值相同，说明 DNS 服务器根提示配置成功。
+ 思考题：
  + 如果在自己配置的 DNS 服务器建立了区域 "tsinghua.edu.cn"，并在此区域上建立了 "www" 主机和 "info" 主机。但未定义 "mail" 和 "mails" 主机。客户端测试时能否解析。如果不能是为什么？应如何处理？
    - 客户端测试是无法解析 "mail" 和 "mails" 主机。
      原因在于 "mail" 和 "mails" 主机未被定义在区域 "tsinghua.edu.cn" 中，DNS 服务器无法提供相应的解析结果。
      解决方案：
      + 在区域 "tsinghua.edu.cn" 中定义 "mail" 和 "mails" 主机。然后刷新 DNS 缓存。
      + 设置 "mail" 和 "mails" 主机的转发，将其转发到正确的 IP 地址。

#text(14pt)[=== vi. 实验任务 六]

+ 实验内容：配置 DNS 服务器的反向解析
+ 实验过程：
  + 展开 DNS 管理器左侧的*反向查找区域*，右键单击，然后新建区域，选择*主要区域*，点击*下一步*，选择*IPv4 反向查找区域*和*不允许动态更新*，指定网络 ID 为 `192.168.20`。
  + 进入新建好的区域，在面板右键单击，然后新建指针，新建 IP 地址 `192.168.20.217` 指向 `www.tsinghua.edu.cn`，保存设置。
  + 进入控制台界面，运行 `ipconfig /flushdns` 清除 DNS 缓存，然后运行 `nslookup 192.168.20.217`，查看解析结果。（注意此处不能使用 `ping` 命令。）
+ 结果与分析：
  + 返回得到 IP 地址 `192.168.20.217` 的名称为 `www.tsinghua.edu.cn`，结果如下图所示。
// #image("https://img.chillcicada.com/i/2024/05/26/6653417737ed3.jpg")

#text(14pt)[=== vii. 实验任务 七]

+ 实验内容：配置 DHCP 服务器（选座，本次实验未做）

#text(16pt)[== 三、实验小结]

- 本次实验主要是对 DNS 服务的配置，通过配置 DNS 服务器的正向解析、委派、转发器、根提示和反向解析，加深了对 DNS 服务的理解。
- DNS 服务器的原理：当用户与某一域名建立连接时，用户所用的计算机会向 DNS 服务器发送请求，DNS 服务器会将域名解析为 IP 地址（如果 DNS 服务器中存在相应记录值），然后将 IP 地址返回给用户，用户再通过 IP 地址与域名建立连接。
- DNS 服务器在域名解析过程中的查询顺序为：本地缓存 -> 区域记录（本地区域 -> 委派区域）-> 转发器 -> 根提示。
