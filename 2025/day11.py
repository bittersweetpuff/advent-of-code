"""
Advent of Code 2025: Day 11: Reactor
https://adventofcode.com/2025/day/11
"""

# Globals
devices = dict()


def load_devices():
    """
    Loads the txt file and adds all devices to devices dictionary. Key is the name of the device and value is list of devices it leads to.
    """
    file = open("./inputs/day11.txt")
    for line in file:
        device = line.strip().split(": ")[0]
        connections = line.strip().split(": ")[1].split(" ")
        devices[device] = connections


def count_paths(start: str, end: str) -> int:
    """
    Counts all paths between start and stop devices recursively
    """
    if start == end:
        return 1
    sum_paths = 0
    for device in devices[start]:
        sum_paths += count_paths(device, end)
    return sum_paths


if __name__ == "__main__":
    load_devices()
    part_1 = count_paths("you", "out")
    print(f"There are {part_1} different paths between 'you' and 'out'")
