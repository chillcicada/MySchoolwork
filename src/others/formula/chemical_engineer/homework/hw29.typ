#import "../../template.typ": *

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set list(indent: 2em)
#set enum(indent: 2em)

= 化学工程基础 - 第二十九次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

在泡罩塔板、浮阀塔板和筛孔塔板中，浮阀塔板在工业精馏中得到了广泛应用，请从流体力学和传质的角度，说明浮阀塔相对于另外两种塔板的优势。

筛孔塔板操作弹性小，筛孔容易阻塞；泡罩塔板结构复杂，板压降大，生产强度低，造价高。相比之下，浮阀塔板可随气量自动调节开度，操作弹性大，塔板压降小；此外，浮阀塔板中气体从阀片下水平吹出，强化了气液接触和界面更新，传质效率高。

== 题 2

对用于精馏分离的筛板塔，说明出现液泛的可能原因，以及在结构设计上抑制液泛的方法与原理。

- 塔板液体流率过大，超出了降液管的处理能力，因而液泛；
- 降液管设置不合理，导致液体在塔板上积聚，形成液泛；
- 上升气体速度过快，使液沫夹带量猛增，造成夹带液泛；
- 塔板间距过小使泡沫层填充积聚造成液泛；
- 筛板堵塞或孔径过小使得液相负荷增大，导致液泛；
- 液体容易形成稳定的泡沫层，阻碍气体上升，导致液泛。

结构设计上抑制液泛主要可以从提高抗液泛能力和抑制液沫两方面入手：

- 使用大降液管，优化降液管进口结构，增加液相处理能力，降低液体在塔板上的积聚；
- 采用大孔径的筛板或浮阀塔板，有效降低塔板压降，减少液体在塔板上的停留时间；
- 增加塔板间距，提供足量的气液交换空间，减少夹带液泛的可能性。

== 题 3

板式塔和填料塔都是重要的气液传质设备，请从流动、传质和结构的角度说明它们的异同点和各自的优势。

异同点：

- 流动上：

  + 气相和液相的流动方向均为逆流，气相从从塔底流向塔顶，液相从塔顶流向塔底；
  + 流动上均存在操作上限。

  板式塔中，气液为逐级流动，气相垂直向上穿过塔板，而液相水平流下塔板，气相具有较高的持液量，压降相对更大且呈现阶梯变化；填料塔中气相和液相均为连续流动，同时气相持液量低，压降相对更低且连续变化。

- 传质上：

  + 二者的传质推动力都是浓度差；
  + 二者的传质速率均受气液平衡关系、扩散系数、流动状态等因素影响。

  在板式塔中，气液逐级传质，传质推动力在塔板处阶跃式变化，传质速率受塔板结构和操作状态影响，传质效率使用塔板数和塔板高度衡量；填料塔中，气液连续传质，传质推动力在填料层内连续变化，传质速率受填料形状、尺寸、堆积密度和液相分布等影响，传质效率使用传质单元数和传质单元高度衡量。

- 结构上：

  + 二者都有塔体、物料进出口、支撑结构等基本组成部分。

  板式塔的结构相对更为复杂，核心部件是多级塔板，溢流式板式塔还需要降流塔，生产强度和生产能力更大；填料塔的核心部件是填料层，填料塔的结构相对简单，通常只需要填料和支撑结构，生产强度和生产能力相对较低。

各自的优势：

- 板式塔：

  板式塔具有更高的处理能力和处理强度，因而多适用于大规模的生产，且由于塔板的设计，工程上容易扩展改造和监控检修，可以方便地侧线采出和单板更换，同时，板式塔具有更好的健壮性，对固体阻塞、结垢结晶等问题的适应性更强。

- 填料塔：

  填料塔具有更低的压降和更高的传质效率，适用于低压差和高传质效率的场合以及真空操作，填料塔的填料层可以提供更大的比表面积，因而在相同体积下可以提供更多的传质面积，此外，填料塔的结构简单，易于制造和安装，且对操作条件变化的适应性较强，适用于腐蚀性液体、热敏材料和强发泡液体的处理。
