"""
Advent of Code 2025: Day 10: Factory
https://adventofcode.com/2025/day/10
"""

import z3

# Globals
lights = []
buttons = []
# For part 2
buttons_raw = []
joltages = []


def load_input():
    # Array holding raw file input lines
    raw_file_input = []

    file = open("./inputs/day10.txt")
    for line in file:
        # Add line to raw input
        raw_file_input.append(line.strip())
    # Close the file
    file.close()

    # Process the input
    for raw_line in raw_file_input:
        split_line = raw_line.split(" ")
        # Count lights (-2 for brackets)
        lights_count = len(split_line[0]) - 2
        # Init lights array (array of chars)
        lights_array = ["0"] * lights_count
        lights_target = split_line[0][1:-1]
        for i, item in enumerate(lights_target):
            if item == "#":
                lights_array[i] = "1"
        # Convert array to string
        lights_string = "".join(lights_array)
        # Add lights in binary form
        lights.append(int(lights_string, 2))

        # Buttons
        connections = split_line[1:-1]
        current_buttons = []
        # Keep buttons in raw numeric format for part 2
        current_buttons_raw = []
        for connection in connections:
            # Keeps the toggled lights
            lights_toggled = 0
            for light in connection[1:-1].split(","):
                current_button = ["0"] * lights_count
                # Set toggled light to 1
                current_button[int(light)] = "1"
                current_button = "".join(current_button)
                lights_toggled += int(current_button, 2)
            current_buttons.append(lights_toggled)
            current_buttons_raw.append(
                tuple([int(x) for x in connection[1:-1].split(",")])
            )
        buttons.append(current_buttons)
        buttons_raw.append(current_buttons_raw)
        # Load joltages for part 2
        current_joltages = [int(x) for x in split_line[-1][1:-1].split(",")]
        joltages.append(current_joltages)


def get_least_button_presses_sum() -> int:
    presses_sum = 0
    for i in range(len(lights)):
        # The target we want to achieve
        target_state = lights[i]
        current_buttons = buttons[i]
        # Create a set for checked combinations
        seen_combinations = set()
        seen_combinations.add(0)
        # Reset pass counter
        steps = 0
        # Initialize queue with starting state - all lights off (binary 0)
        # And series of steps (0 since no buttons was pressed yet)
        queue = [(0, 0)]
        while len(queue) != 0:
            lights_state, steps = queue.pop(0)
            # Check if current state of lights is what we target
            if lights_state == target_state:
                break
            for button in current_buttons:
                # New state is XOR between current light state and button
                new_state = lights_state ^ button
                # Check if we got that state before
                if new_state not in seen_combinations:
                    seen_combinations.add(new_state)
                    queue.append((new_state, steps + 1))
        presses_sum += steps
    return presses_sum


def get_least_button_presses_for_joltage_sum() -> int:
    presses_sum = 0
    for light in range(len(lights)):
        solver = z3.Optimize()
        variables = []
        current_buttons = buttons_raw[light]
        target_joltages = joltages[light]
        joltage_variable = [None] * len(target_joltages)

        for i, button in enumerate(current_buttons):
            variable = z3.Int(str(i))
            variables.append(variable)
            solver.add(variable >= 0)
            for connection in button:
                if joltage_variable[connection] is None:
                    joltage_variable[connection] = variable
                else:
                    joltage_variable[connection] += variable
        for index in range(len(target_joltages)):
            if joltage_variable[index] is not None:
                solver.add(target_joltages[index] == joltage_variable[index])
        solved = solver.minimize(sum(variables))
        if solver.check() == z3.sat:
            current_pressed = solved.value().as_long()
        presses_sum += current_pressed
    return presses_sum


if __name__ == "__main__":
    load_input()

    part_1 = get_least_button_presses_sum()
    print(f"Fewest button presses required: {part_1}")

    part_2 = get_least_button_presses_for_joltage_sum()
    print(f"Fewest button presses required for joltage: {part_2}")
