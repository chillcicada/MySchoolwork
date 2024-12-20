/**
 * @file EditorUtils.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief
 * @version 0.0.0
 * @date 2024-12-03
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef EDITOR_UTILS_H
#define EDITOR_UTILS_H

#include "qdir.h"
#include <LspUri.h>

#include <QDir>

namespace util {
/**
 * @brief get the native path
 *
 * @param path
 * @return QString
 */
inline QString formatFilePath(const QString &path) {
  return QDir::toNativeSeparators(path);
}

/**
 * @brief get the absolute path
 *
 * @param filename
 * @return QString
 */
inline QString absolutePath(const QString &filename) {
  return QDir::current().absoluteFilePath(filename);
}

/**
 * @brief get the URI for file
 *
 * @param filename
 * @return URIForFile
 */
inline URIForFile uriForFile(const QString &filename) {
  auto path = absolutePath(filename);

  URIForFile uri;
  uri.from(path.toStdString());

  return uri;
}
} // namespace util

#endif // EDITOR_UTILS_H
