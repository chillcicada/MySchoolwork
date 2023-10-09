# -*- coding: utf-8 -*-

# Coded by LLK
# 代码已上传至 GitHub: https://github.com/chillcicada/MySchoolwork

# 嫌弃 turtle 的像素而改用 PySide6 (doge

"""文件目录解释：
venv/ 为虚拟环境文件夹，除 pip, setuptools 以及用于打包的 pyinstaller 外，仅包含 PySide6 一个库
assets/ 为图片资源文件夹，包含两张背景图和图标文件
solution4.py 为主程序文件
solution4.spec 为打包配置文件
dist/ 为打包后的文件夹，包含可执行文件 solution4.exe
build/ 为打包时生成的临时文件夹
RandomRollCall.ui 为 Qt Designer 设计的界面文件
RandomRollCall_ui.py 为 RandomRollCall.ui 经 Pyside6-RCC 转换后的 Python 代码文件
除 u"\u4ed3\u8033\u4eca\u697703 W04" 为额外安装外的字体外其他文件均为 windows 电脑安装的文件"""

import sys  # 用于退出程序
from random import randint  # 用于生成随机数
from PySide6 import QtGui  # 用于设置图标
from PySide6.QtCore import (QCoreApplication, QMetaObject, QRect, Qt, QTimer, QDateTime)  # 用于设置按钮文字，获取时间并设置计时器
from PySide6.QtGui import (QCursor, QFont)  # 用于设置鼠标和字体
from PySide6.QtWidgets import (QApplication, QLabel, QMainWindow, QPushButton, QSizePolicy, QWidget)  # 用于设置窗口和组件


# 以下为 Qt Designer 设计的界面文件 RandomRollCall.ui 经 Pyside6-RCC 转换后的 Python 代码文件，并修改了部分代码
class Ui_RandomRollCall(object):
  listStudents = ['1',
                  '2',
                  '3',
                  '4',
                  '5',
                  '6',
                  '7',
                  '8',
                  '9',
                  '10',
                  '11',
                  '12',
                  '13',
                  '14',
                  '15',
                  '16',
                  '17',
                  '18',
                  '19',
                  '20',
                  '21',
                  '22',
                  '23',
                  '24',
                  '25',
                  '26',
                  '27',
                  '28',
                  '29',
                  '30',
                  '31',
                  '32',
                  '33',
                  '34',
                  '35',
                  '36',
                  '37',
                  '38',
                  '39',
                  '40',
                  '41',
                  '42',
                  '43',
                  '44',
                  '45',
                  '46',
                  '47',
                  '48',
                  '49',
                  '50',
                  '51',
                  '52',
                  '53',
                  '54',
                  '55',
                  '56',
                  '57',
                  '58',
                  '59',
                  '60'
                  ]  # 学生名单
  strStatusList = ['滚动点名\n Click Me!', '停止滚动\n Pause It!']  # 用于设置按钮 2 状态值
  strStatusForbidden = '暂不可用\n Plz Wait!'  # 用于设置按钮 1 不可用时状态值
  centralwidgetBackground1 = "#centralwidget {background-image: url(./assets/xibao.png)}"  # 用于设置正常背景图
  centralwidgetBackground2 = "#centralwidget {background-image: url(./assets/beibao.png)}"  # 用于设置检测到分 21 班的背景图

  def stuChoose(self):  # 用于按钮 1 的点击事件
    """生成随机数并将其作为索引值获取学生名单中的学生名字并显示在 label_2 上
    同时检测索引值是否为分 21 班
    是则修改背景样式表和 label_1 的文字
    否则恢复背景样式表和 label_1 的文字"""
    stuChosen = self.listStudents[randint(0, 59)]
    if stuChosen in self.listStudents[43:]:
      self.centralwidget.setStyleSheet(self.centralwidgetBackground2)
      self.label.setText(QCoreApplication.translate("RandomRollCall", "悲报", None))
    else:
      self.centralwidget.setStyleSheet(self.centralwidgetBackground1)
      self.label.setText(QCoreApplication.translate("RandomRollCall", "喜报", None))
    self.label_2.setText(QCoreApplication.translate("RandomRollCall", "%s" % str(stuChosen), None))

  def stuRoll(self):  # 用于计时器进行绑定的函数
    """获取当前时间，并将毫秒数转换为 0-59 的整数，再将其作为索引值获取学生名单中的学生名字并显示在 label_2 上"""
    time = QDateTime.currentDateTime()
    timeCount = int(time.toString('z'))
    stuRolled = self.listStudents[timeCount % 60]
    self.label_2.setText(QCoreApplication.translate("RandomRollCall", "%s" % str(stuRolled), None))

  def pushButtonClicked(self):  # 用于按钮 1 点击事件的绑定函数
    """仅在按钮二不可用时才可用，用于进行一次随机点名"""
    if self.pushButton_2.text() == self.strStatusList[0]:
      self.stuChoose()

  def pushButton_2Clicked(self):  # 用于按钮 2 点击事件的绑定函数
    if self.pushButton_2.text() == self.strStatusList[0]:
      self.pushButton_2.setText(self.strStatusList[1])
      self.pushButton.setCursor(QCursor(Qt.ForbiddenCursor))
      self.label_2.setText(QCoreApplication.translate("RandomRollCall", "等待点名中...", None))
      self.pushButton.setText(QCoreApplication.translate("RandomRollCall", self.strStatusForbidden, None))
      self.pushButton.setEnabled(False)
      self.timer.start(100)
      self.timer.timeout.connect(self.stuRoll)
    else:
      self.timer.stop()
      self.pushButton.setEnabled(True)
      self.pushButton_2.setText(self.strStatusList[0])
      self.pushButton.setCursor(QCursor(Qt.PointingHandCursor))
      self.pushButton.setText(QCoreApplication.translate("RandomRollCall", "随机点名\n Click Me!", None))

# 以下为启动 ui 时调用的函数，初始化组件，由 ui 文件转换而得，不做解释
  def setupUi(self, RandomRollCall):
    if not RandomRollCall.objectName():
      RandomRollCall.setObjectName("RandomRollCall")
    RandomRollCall.resize(980, 735)
    RandomRollCall.setFixedSize(980, 735)
    font = QFont()
    font.setPointSize(12)
    font.setBold(False)
    RandomRollCall.setFont(font)
    RandomRollCall.setCursor(QCursor(Qt.ArrowCursor))
    RandomRollCall.setMouseTracking(False)
    RandomRollCall.setDocumentMode(False)
    self.timer = QTimer()
    self.centralwidget = QWidget(RandomRollCall)
    self.centralwidget.setObjectName("centralwidget")
    self.centralwidget.setStyleSheet(self.centralwidgetBackground1)
    self.pushButton = QPushButton(self.centralwidget)
    self.pushButton.setObjectName("pushButton")
    self.pushButton.setGeometry(QRect(210, 520, 181, 101))
    font1 = QFont()
    font1.setFamilies([u"\u534e\u6587\u6977\u4f53"])
    font1.setPointSize(20)
    font1.setBold(True)
    self.pushButton.setFont(font1)
    self.pushButton.setCursor(QCursor(Qt.PointingHandCursor))
    self.pushButton.clicked.connect(self.pushButtonClicked)
    self.label = QLabel(self.centralwidget)
    self.label.setObjectName("label")
    self.label.setGeometry(QRect(0, -30, 231, 141))
    sizePolicy = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
    sizePolicy.setHorizontalStretch(0)
    sizePolicy.setVerticalStretch(0)
    sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
    self.label.setSizePolicy(sizePolicy)
    font2 = QFont()
    font2.setFamilies([u"\u534e\u6587\u4e2d\u5b8b"])
    font2.setPointSize(72)
    font2.setBold(True)
    self.label.setFont(font2)
    self.label.setAlignment(Qt.AlignBottom | Qt.AlignHCenter)
    self.label_2 = QLabel(self.centralwidget)
    self.label_2.setObjectName("label_2")
    self.label_2.setGeometry(QRect(260, 230, 461, 141))
    font3 = QFont()
    font3.setFamilies([u"\u4ed3\u8033\u4eca\u697703 W04"])
    font3.setPointSize(48)
    font3.setBold(False)
    self.label_2.setFont(font3)
    self.label_2.setAlignment(Qt.AlignCenter)
    self.pushButton_2 = QPushButton(self.centralwidget)
    self.pushButton_2.setObjectName("pushButton_2")
    self.pushButton_2.setGeometry(QRect(590, 520, 181, 101))
    self.pushButton_2.setFont(font1)
    self.pushButton_2.setCursor(QCursor(Qt.PointingHandCursor))
    self.pushButton_2.clicked.connect(self.pushButton_2Clicked)
    RandomRollCall.setCentralWidget(self.centralwidget)
    self.retranslateUi(RandomRollCall)
    QMetaObject.connectSlotsByName(RandomRollCall)

  def retranslateUi(self, RandomRollCall):
    """界面初始函数，依次为标题，按钮1，标签1，标签2，按钮2"""
    RandomRollCall.setWindowTitle(QCoreApplication.translate("RandomRollCall", "随机点名 :-) by LLK", None))
    self.pushButton.setText(QCoreApplication.translate("RandomRollCall", "随机点名\n Click Me!", None))
    self.label.setText(QCoreApplication.translate("RandomRollCall", "喜报", None))
    self.label_2.setText(QCoreApplication.translate("RandomRollCall", "等待点名中...", None))
    self.pushButton_2.setText(QCoreApplication.translate("RandomRollCall", "滚动点名\n Click Me!", None))


# 添加启动应用程序的主函数
def main():
  app = QApplication(sys.argv)
  mw = QMainWindow()
  obj = Ui_RandomRollCall()
  icon = QtGui.QIcon()
  icon.addPixmap(QtGui.QPixmap("./assets/TChub.ico"))  # 设置图标
  mw.setWindowIcon(icon)
  obj.setupUi(mw)
  mw.show()
  sys.exit(app.exec())


# 启动主函数
if __name__ == '__main__':
  main()
