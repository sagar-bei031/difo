import subprocess
import curses

def get_disk_partitions():
    disk_partitions = []
    try:
        output = subprocess.check_output(['lsblk', '-o', 'NAME,SIZE,FSTYPE,MOUNTPOINT'])
        lines = output.decode().split('\n')
        for line in lines[1:]:  # Skip header line
            parts = line.split()
            if len(parts) >= 4:
                disk_partitions.append({
                    'name': parts[0],
                    'size': parts[1],
                    'fstype': parts[2],
                    'mountpoint': parts[3]
                })
    except subprocess.CalledProcessError as e:
        print("Error: Failed to execute lsblk command.")
        print("Error message:", e)
    except Exception as e:
        print("Error:", e)
    return disk_partitions

def draw_graph(stdscr, disk_partitions):
    stdscr.clear()
    height, width = stdscr.getmaxyx()
    title = "Disk Partitions"
    title_x = width // 2 - len(title) // 2
    stdscr.addstr(0, title_x, title, curses.A_BOLD)

    y = 2
    for partition in disk_partitions:
        partition_name = partition['name']
        partition_size = partition['size']
        partition_mountpoint = partition['mountpoint']

        partition_bar_length = min(width - 4, int(width * 0.4 * float(partition_size[:-2]) / 100)) if partition_size else 0
        partition_bar = '#' * partition_bar_length

        stdscr.addstr(y, 2, f"Partition: {partition_name}")
        stdscr.addstr(y, 30, "|")
        stdscr.addstr(y, 32, partition_bar, curses.color_pair(1))
        stdscr.addstr(y, width - 18, f"Size: {partition_size}")
        stdscr.addstr(y + 1, 2, f"Mountpoint: {partition_mountpoint}")
        y += 3

    stdscr.refresh()
    stdscr.getch()

def main(stdscr):
    curses.curs_set(0)
    curses.start_color()
    curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)

    disk_partitions = get_disk_partitions()
    draw_graph(stdscr, disk_partitions)

if __name__ == "__main__":
    curses.wrapper(main)
