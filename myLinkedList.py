from mycolors import *
import os
from datetime import datetime

class ListNode:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, data):
        new_node = ListNode(data)
        if not self.head:
            self.head = new_node
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = new_node


def create_linked_list(files, show_hidden):
    linked_list = LinkedList()
    for file in files:
        if show_hidden or not file.startswith('.'):
            linked_list.insert(file)
    return linked_list


def merge_sort_linked_list(head, reverse=False):
    if not head or not head.next:
        return head

    left_half, right_half = split_linked_list(head)
    sorted_left_half = merge_sort_linked_list(left_half, reverse)
    sorted_right_half = merge_sort_linked_list(right_half, reverse)
    return merge(sorted_left_half, sorted_right_half, reverse)


def split_linked_list(head):
    slow = head
    fast = head.next

    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next

    mid = slow.next
    slow.next = None
    return head, mid


def merge(left, right, reverse=False):
    if not left:
        return right
    if not right:
        return left

    if (not reverse and left.data < right.data) or (reverse and left.data > right.data):
        result = left
        result.next = merge(left.next, right, reverse)
    else:
        result = right
        result.next = merge(left, right.next, reverse)

    return result


def print_linked_list(head):
    current = head
    while current:
        print(current.data)
        current = current.next

def sort_files(directory, sort_type, order):
    files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    if sort_type == "name":
        files.sort(reverse=(order == "desc"))
    elif sort_type == "date":
        files.sort(key=lambda x: os.path.getmtime(os.path.join(directory, x)), reverse=(order == "desc"))
    elif sort_type == "size":
        files.sort(key=lambda x: os.path.getsize(os.path.join(directory, x)), reverse=(order == "desc"))
    return files

def sort(args, path):
    sort_type, order = args.sort
    if sort_type not in ["name", "date", "size"]:
        print("Invalid sort type. Choose from 'name', 'date', or 'size'.")
        return
    if order not in ["asc", "desc"]:
        print("Invalid sort order. Choose 'asc' or 'desc'.")
        return
    sorted_files = sort_files(path, sort_type, order)
    for file in sorted_files:
        color = get_file_color(os.path.join(path, file), file.startswith('.') and not args.all)
        if sort_type == "date":
            date_str = datetime.fromtimestamp(os.path.getmtime(os.path.join(path, file))).strftime("%Y-%m-%d %H:%M:%S")
            print_colored_text(f"{file.ljust(50)} {date_str}", color)
        elif sort_type == "size":
            size = os.path.getsize(os.path.join(path, file))
            size_str = f"{size} bytes" if size < 1024 else f"{size / 1024:.2f} KB"
            print_colored_text(f"{file.ljust(50)} {size_str}", color)
        else:
            print_colored_text(file, color)