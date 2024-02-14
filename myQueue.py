import time

class Queue:
    def __init__(self):
        self.queue = []

    def enqueue(self, item):
        self.queue.append(item)

    def dequeue(self):
        return self.queue.pop(0) if self.queue else None

    def is_empty(self):
        return len(self.queue) == 0

def print_content_with_slide(file_path, slide_speed):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    queue = Queue()
    for line in lines:
        queue.enqueue(line)

    while not queue.is_empty():
        print(queue.dequeue(), end='', flush=True)
        time.sleep(slide_speed)