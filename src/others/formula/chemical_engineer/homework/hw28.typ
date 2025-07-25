#import "../../template.typ": *

#show: define-config

#set par(first-line-indent: (amount: 2em, all: true))
#set math.equation(numbering: "(1)")

= 化学工程基础 - 第二十八次作业

#align(center)[刘宽 ~ 2022013189 ~ 探微分21]

== 题 1

某工厂有一股放空的氮气中含有 2% 甲醇（质量分数），现因环保和经济的考虑，需要回收其中的甲醇，且甲醇的质量分数不低于 99%。试设计一个概念流程实现该任务，指出流程的关键参数。

甲醇的沸点约64.7℃，可以先将气体降低至30～40℃便于使用清水吸收富集甲醇，然后再解吸并精馏得到高纯度的甲醇。主要的关键设备即吸收塔和精馏塔，整体流程如下面的简图所示：

#figure(image("hw28/q1.jpg", width: 50%))

关键参数主要为吸收塔的液气比和精馏塔的回流比与温度等，使得整体能尽可能减少废气废水的产生和排放，同时保证产出甲醇的纯度要求，达到环保和经济效益。

== 题 2

使用精馏技术分离乙醇水溶液时受到恒沸点的限制，请说明对于该体系，产生恒沸点的原因。采用萃取精馏和共沸精馏可以突破恒沸点，请说明原因以及萃取剂和共沸剂是如何循环的。

恒沸点源于乙醇-水分子间的强氢键缔合，使得乙醇和水的分子在混合物中相互关联并形成一个稳定的共沸混合物。

萃取精馏在形成共沸物的乙醇-水料液中加入挥发性很小的萃取剂后，可以使乙醇-水的相对挥发度增大，从而易于用精馏方法分离。由于萃取剂的沸点很高，因而可以在蒸出乙醇的塔顶回流回收萃取剂，同时也在水分离塔的塔釜回收萃取剂，从而实现整体的萃取剂循环。

共沸精馏则通过加入与水-乙醇中一个或两个组分形成比原来组分和原来恒沸点更地的新的最低共沸物的共沸剂，使组分间的相对挥发度增大，从而使原溶液易于精馏分离。对于乙醇水体系，可以加入与水不互溶但与乙醇互溶的油性物质（如苯）形成共沸物，这样在形成的新恒沸液冷凝后可以分层，以苯为例，分离后得到的富苯层可以直接回流到共沸精馏塔中使用，实现共沸剂苯的循环利用。
