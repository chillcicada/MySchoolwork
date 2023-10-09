# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'RandomRollCall.ui'
##
## Created by: Qt User Interface Compiler version 6.5.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
                            QMetaObject, QObject, QPoint, QRect,
                            QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QAction, QBrush, QColor, QConicalGradient,
                           QCursor, QFont, QFontDatabase, QGradient,
                           QIcon, QImage, QKeySequence, QLinearGradient,
                           QPainter, QPalette, QPixmap, QRadialGradient,
                           QTransform)
from PySide6.QtWidgets import (QApplication, QLabel, QMainWindow, QPushButton,
                               QSizePolicy, QWidget)


class Ui_RandomRollCall(object):
  def setupUi(self, RandomRollCall):
    if not RandomRollCall.objectName():
      RandomRollCall.setObjectName(u"RandomRollCall")
    RandomRollCall.resize(980, 735)
    font = QFont()
    font.setPointSize(12)
    font.setBold(False)
    RandomRollCall.setFont(font)
    RandomRollCall.setCursor(QCursor(Qt.ArrowCursor))
    RandomRollCall.setMouseTracking(False)
    RandomRollCall.setDocumentMode(False)
    self.centralwidget = QWidget(RandomRollCall)
    self.centralwidget.setObjectName(u"centralwidget")
    self.centralwidget.setStyleSheet(u"#RandomRollCall {\n"
                                     "  background-image=\"./\u559c\u62a5.jpg\"\n"
                                     "}")
    self.pushButton = QPushButton(self.centralwidget)
    self.pushButton.setObjectName(u"pushButton")
    self.pushButton.setGeometry(QRect(210, 520, 181, 101))
    font1 = QFont()
    font1.setFamilies([u"\u534e\u6587\u6977\u4f53"])
    font1.setPointSize(20)
    font1.setBold(True)
    self.pushButton.setFont(font1)
    self.pushButton.setCursor(QCursor(Qt.PointingHandCursor))
    self.label = QLabel(self.centralwidget)
    self.label.setObjectName(u"label")
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
    self.label_2.setObjectName(u"label_2")
    self.label_2.setGeometry(QRect(260, 230, 461, 141))
    font3 = QFont()
    font3.setFamilies([u"\u4ed3\u8033\u4eca\u697703 W04"])
    font3.setPointSize(48)
    font3.setBold(False)
    self.label_2.setFont(font3)
    self.label_2.setAlignment(Qt.AlignCenter)
    self.pushButton_2 = QPushButton(self.centralwidget)
    self.pushButton_2.setObjectName(u"pushButton_2")
    self.pushButton_2.setGeometry(QRect(590, 520, 181, 101))
    self.pushButton_2.setFont(font1)
    self.pushButton_2.setCursor(QCursor(Qt.PointingHandCursor))
    RandomRollCall.setCentralWidget(self.centralwidget)

    self.retranslateUi(RandomRollCall)

    QMetaObject.connectSlotsByName(RandomRollCall)

  # setupUi

  def retranslateUi(self, RandomRollCall):
    RandomRollCall.setWindowTitle(QCoreApplication.translate("RandomRollCall", u"MainWindow", None))
    self.pushButton.setText(QCoreApplication.translate("RandomRollCall", u"\u968f\u673a\u70b9\u540d\n"
                                                                         " Click Me!", None))
    self.label.setText(QCoreApplication.translate("RandomRollCall", u"\u559c\u62a5", None))
    self.label_2.setText(QCoreApplication.translate("RandomRollCall", u"\u7b49\u5f85\u70b9\u540d\u4e2d...", None))
    self.pushButton_2.setText(QCoreApplication.translate("RandomRollCall", u"\u6eda\u52a8\u70b9\u540d\n"
                                                                           " Click Me!", None))
  # retranslateUi
