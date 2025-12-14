"""
Advent of Code 2025: Day 12: Christmas Tree Farm
https://adventofcode.com/2025/day/12
"""

# Globals
presents = []
regions = []


def load_data():
    """
    Loads data from file and fills presents and regions global arrays
    """
    file = open("./inputs/day12.txt")
    input = []
    for line in file:
        input.append(line.strip())
    file.close()
    present = []
    loading_presents = True
    # Ignore first line with 0:
    for line in input[1:]:
        if loading_presents:
            # Load presents
            if "x" in line:
                loading_presents = False
                presents.append(present)
            if line == "":
                continue
            elif ":" in line:
                presents.append(present)
                present = []
            else:
                present.append(line)
        if not loading_presents:
            size = line.split(": ")[0]
            present_counts_line = line.split(": ")[1]
            size_x = int(size.split("x")[0])
            size_y = int(size.split("x")[1])
            present_counts = [int(n) for n in present_counts_line.split(" ")]
            region = [[size_x, size_y], present_counts]
            regions.append(region)


def get_present_area(present) -> int:
    """
    Returns the number of 'active' segments in present to easly tell if there is area left
    """
    area = 0
    for line in present:
        area += line.count("#")
    return area


def get_valid_regions() -> int:
    """
    Returns number of regions that can fit given number of presents
    """
    valid_regions = 0
    for region in regions:
        size = region[0]
        all_segments = size[0] * size[1]
        present_counts = region[1]
        all_segments_needed = 0
        for i, count in enumerate(present_counts):
            all_segments_needed += get_present_area(presents[i]) * count
        if all_segments >= all_segments_needed:
            valid_regions += 1
    return valid_regions


if __name__ == "__main__":
    load_data()
    valid_regions = get_valid_regions()

    print(f"There are {valid_regions} regions you can fit presents in")
