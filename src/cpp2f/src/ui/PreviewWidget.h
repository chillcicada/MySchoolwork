/**
 * @file PreviewWidget.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-11-25
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef PREVIEW_WIDGET_H
#define PREVIEW_WIDGET_H

#include "qpushbutton.h"
#include <QPlainTextEdit>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>
#include <QWebEngineSettings>
#include <QWebEngineView>
#include <QWidget>

class PreviewWidget : public QWidget {
  Q_OBJECT

public:
  explicit PreviewWidget(QWidget *parent = nullptr) : QWidget(parent) {
    setMinimumWidth(680);

    webView_ = new QWebEngineView(this);
    sourceView_ = new QPlainTextEdit(this);
    viewSourceButton_ = new QPushButton(tr("View Source"), this);

    auto settings = webView_->settings();
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    settings->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard,
                           true);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls,
                           true);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls,
                           true);
    settings->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);

    webView_->page()->setInspectedPage(webView_->page());

    auto layout = new QVBoxLayout(this);
    layout->addWidget(webView_);
    layout->addWidget(sourceView_);
    layout->addWidget(viewSourceButton_);

    connect(viewSourceButton_, &QPushButton::clicked, this,
            &PreviewWidget::viewSource);

    QUrl url("https://en.cppreference.com/w/");

    webView_->setUrl(url);

    // webView_->page()->toHtml([this](QString html) {
    //   html.replace("<body>", "<body><h1>Modified Content</h1>");
    //   webView_->setHtml(html);
    // });

    webView_->show();

    sourceView_->setReadOnly(true);
    sourceView_->hide();

    setLayout(layout);
  };

  ~PreviewWidget() = default;

private slots:
  void viewSource() {
    webView_->page()->toHtml([this](const QString &html) {
      sourceView_->setPlainText(html);
      sourceView_->show();
    });
  }

private:
  QWebEngineView *webView_;
  QPlainTextEdit *sourceView_;
  QPushButton *viewSourceButton_;
};

#endif // PREVIEW_WIDGET_H
