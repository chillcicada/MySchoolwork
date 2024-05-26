# -*- coding: utf-8 -*-


class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

    def __len__(self):
        return 1 + len(self.next) if self.next else 1

    def count(self):
        temp = 0
        while self.next:
            temp += 1
            self = self.next
