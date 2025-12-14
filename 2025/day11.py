"""
Advent of Code 2025: Day 11: Reactor
https://adventofcode.com/2025/day/11
"""

from functools import cache

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
    # out device have no connections so if we reach it we just
    # count it as 1 connection between node connected to out
    if start == end:
        return 1
    sum_paths = 0
    for device in devices[start]:
        sum_paths += count_paths(device, end)
    return sum_paths


# cache becouse of time
@cache
def count_paths_from_server(
    start: str, end: str, dac_visited: bool, fft_visited: bool
) -> int:
    """
    Counts all paths between start and stop devices recursively, making sure
    it goes through dac and fft
    """
    if start == end and dac_visited and fft_visited:
        return 1
    elif start == end and (not dac_visited or not fft_visited):
        # If reaches end but haven't visited dac and fft, return 0
        return 0

    if start == "dac":
        dac_visited = True
    if start == "fft":
        fft_visited = True
    sum_paths = 0
    for device in devices[start]:
        sum_paths += count_paths_from_server(device, end, dac_visited, fft_visited)
    return sum_paths


if __name__ == "__main__":
    load_devices()
    part_1 = count_paths("you", "out")
    print(f"There are {part_1} different paths between 'you' and 'out'")
    part_2 = count_paths_from_server("svr", "out", dac_visited=False, fft_visited=False)
    print(
        f"There are {part_2} different paths between 'svr' and 'out' that go through out 'dac' and 'fft'"
    )
