/**
 * @file LspClient.cpp
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-03
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#include "LspClient.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QString>

LSPClient::LSPClient(QString path, QStringList args, QObject *parent)
    : QObject(parent) {
  process_ = new QProcess();

  LSPClient::connect(process_, &QProcess::readyReadStandardOutput, this,
                     &LSPClient::onClientReadyReadStdout);
  LSPClient::connect(process_, &QProcess::readyReadStandardError, this,
                     &LSPClient::onClientReadyReadStderr);
  LSPClient::connect(process_, &QProcess::errorOccurred, this,
                     &LSPClient::onClientError);
  LSPClient::connect(
      process_, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
      this, &LSPClient::onClientFinished);

  process_->setProgram(path);
  process_->setArguments(args);

  process_->start();

  if (!process_->waitForStarted()) {
    qDebug() << "Failed to start the process with path" << path;
    process_->waitForFinished();
    process_->close();
    process_->deleteLater();
  }
}

LSPClient::~LSPClient() {
  if (process_ != nullptr) {
    process_->close();
    process_->deleteLater();
  }
}

// slots

void LSPClient::onClientReadyReadStdout() {
  auto buffer = process_->readAllStandardOutput();

  if (buffer.isEmpty())
    return;

  auto messageStart = buffer.indexOf("\r\n\r\n") + 4;
  auto lenStart = buffer.indexOf("Content-Length: ") + 16;
  auto lenEnd = buffer.indexOf("\r\n");
  auto ok = false;
  auto contentLength = buffer.mid(lenStart, lenEnd - lenStart).toLongLong(&ok);

  if (!ok)
    return;

  auto payload = buffer.mid(messageStart);
  qDebug() << "Received from server: " << payload;
  /// @warning Incomplete message has arrived, discard it
  if (payload.size() != contentLength) {
    return;
  }
  QJsonParseError error{};

  auto msg = QJsonDocument::fromJson(payload, &error);

  if (error.error != QJsonParseError::NoError || !msg.isObject()) {
    // Some JSON Parse Error
    return;
  }

  auto obj = msg.object();

  if (obj.contains("id")) {
    if (obj.contains("method")) {
      emit onRequest(obj["method"].toString(), obj["param"].toObject(),
                     obj["id"].toObject());
    } else if (obj.contains("result")) {
      emit onResponse(obj["id"].toObject(), obj["result"].toObject());
    } else if (obj.contains("error")) {
      emit onError(obj["id"].toObject(), obj["error"].toObject());
    }
  } else if (obj.contains("method")) {
    // notification, without `id`
    if (obj.contains("params")) {
      emit onNotify(obj["method"].toString(), obj["params"].toObject());
    }
  }
}

void LSPClient::onClientReadyReadStderr() {
  QString content = process_->readAllStandardError();
  if (!content.isEmpty()) {
    emit newStderr(content);
  }
}

void LSPClient::onClientError(QProcess::ProcessError error) {
  emit onServerError(error);
}

void LSPClient::onClientFinished(int exitCode, QProcess::ExitStatus status) {
  emit onServerFinished(exitCode, status);
}

/**
 * @brief private
 *
 */

void LSPClient::writeToServer(json &in) {
  auto content = in.dump();
  qDebug() << "Sending to server: " << content.c_str();
  buffer_.push_back("Content-Length: " + std::to_string(content.length()) +
                    "\r\n");
  buffer_.push_back("\r\n");
  buffer_.push_back(content);
  if (process_ != nullptr && process_->state() == QProcess::Running) {
    for (auto s : buffer_)
      process_->write(s.c_str());
    buffer_.clear();
  }
}
