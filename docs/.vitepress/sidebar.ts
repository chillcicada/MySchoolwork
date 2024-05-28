import type { DefaultTheme } from 'vitepress'

const sidebar: DefaultTheme.Sidebar = [
  {
    text: '大二上',
    collapsed: true,
    items: [
      {
        text: 'Fortran程序设计',
        link: '/面向科学计算的Fortran程序设计/README',
        collapsed: true,
        items: [
          { text: '*计算机概论与课程概论', link: '/面向科学计算的Fortran程序设计/第一讲-计算机概论与课程概论' },
          { text: '开发环境与工具', link: '/面向科学计算的Fortran程序设计/第二讲-开发环境与工具' },
          { text: '*科学计算中的Fortran软件', link: '/面向科学计算的Fortran程序设计/第三讲-科学计算中的Fortran软件' },
          { text: 'Fortran程序设计基础', link: '/面向科学计算的Fortran程序设计/第四讲-Fortran程序设计基础' },
          { text: '输入输出及声明', link: '/面向科学计算的Fortran程序设计/第五讲-输入输出及声明' },
          { text: '流程控制与逻辑运算', link: '/面向科学计算的Fortran程序设计/第六讲-流程控制与逻辑运算' },
          { text: '循环', link: '/面向科学计算的Fortran程序设计/第七讲-循环' },
          { text: '数组', link: '/面向科学计算的Fortran程序设计/第八讲-数组' },
          { text: '函数', link: '/面向科学计算的Fortran程序设计/第九讲-函数' },
          { text: '数值计算', link: '/面向科学计算的Fortran程序设计/第十讲-数值计算' },
          { text: 'MPI 入门', link: '/面向科学计算的Fortran程序设计/第十一讲-MPI入门' },
          { text: '并行程序设计进阶', link: '/面向科学计算的Fortran程序设计/第十二讲-并行程序设计进阶' },
          { text: '文件系统', link: '/面向科学计算的Fortran程序设计/第十三讲-文件系统' },
          { text: 'MPI+OpenMP混合编程', link: '/面向科学计算的Fortran程序设计/第十四讲-MPI+OpenMP混合编程' },
          { text: 'openmpi 安装释疑', link: '/面向科学计算的Fortran程序设计/openmpi' },
          { text: '错误与调试', link: '/面向科学计算的Fortran程序设计/错误与调试' },
          { text: '小结', link: '/面向科学计算的Fortran程序设计/小结' },
        ],
      },
      {
        text: '计算机网络基础',
        link: '/计算机网络基础/课程笔记/README',
        collapsed: true,
        items: [
          { text: '前言', link: '/计算机网络基础/课程笔记/1-前言' },
          { text: '数据通信基础-上', link: '/计算机网络基础/课程笔记/2-数据通信基础-上' },
          { text: '数据通信基础-下', link: '/计算机网络基础/课程笔记/3-数据通信基础-下' },
          { text: '物理层', link: '/计算机网络基础/课程笔记/4-物理层' },
          { text: 'LAN-上', link: '/计算机网络基础/课程笔记/5-LAN-上' },
          { text: 'LAN-下', link: '/计算机网络基础/课程笔记/6-LAN-下' },
          { text: '广域网及其接入技术', link: '/计算机网络基础/课程笔记/7-广域网及其接入技术' },
          { text: '网络层协议-上', link: '/计算机网络基础/课程笔记/8-网络层协议-上' },
          { text: '网络层协议-下', link: '/计算机网络基础/课程笔记/9-网络层协议-下' },
          { text: '传输层协议', link: '/计算机网络基础/课程笔记/10-传输层协议' },
          { text: '网络基本应用-上', link: '/计算机网络基础/课程笔记/11-网络基本应用-上' },
          { text: '网络基本应用-下', link: '/计算机网络基础/课程笔记/12-网络基本应用-下' },
          { text: '小结', link: '/计算机网络基础/课程笔记/小结' },
          { text: '课程实验', link: '/计算机网络基础/课程实验/README' },
        ],
      },
    ],
  },
  {
    text: '其他',
    collapsed: true,
    items: [
      { text: 'SMILES', link: '/others/SMILES' },
    ],
  },
] satisfies DefaultTheme.Sidebar

export default sidebar
