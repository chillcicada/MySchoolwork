/**
 * @file mystl.h
 * @author liukuan (liukuan22@mails.tsinghua.edu.cn)
 * @brief usage: #include "mystl.h"
 * @version 0.0.0
 * @date 2024-12-06
 *
 * @copyright Copyright (C) 2024 GPLv3
 *
 */

#ifndef MYSTL_H
#define MYSTL_H

#include "my_container.h"
#include "my_deque.h"
#include "my_list.h"
#include "my_queue.h"
#include "my_stack.h"
#include "my_vector.h"

namespace mystl {

template <typename T> using container = MyContainer<T>;

template <typename T> using vector = MyVector<T>;

template <typename T> using list = MyList<T>;

template <typename T> using deque = MyDeque<T>;

template <typename Tp, typename Tc = MyDeque<Tp>> using stack = MyStack<Tp, Tc>;

template <typename Tp, typename Tc = MyDeque<Tp>> using queue = MyQueue<Tp, Tc>;

} // namespace mystl

#endif // MYSTL_H
