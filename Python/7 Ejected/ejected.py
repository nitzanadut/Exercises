import re
import math

# Regex to check if a command is legal
validate_command = lambda command: re.match(r'^(UP|DOWN|LEFT|RIGHT)\s\d+$', command)

def main():
    print("Hey! Expecting input of format: (UP/DOWN/LEFT/RIGHT NUMBER). 0 to stop inserting commands")

    commands = []
    command = ''
    
    # Input from user
    while command != '0':
        command = input('$ ')
        if not validate_command(command) and command != '0':
            print('Invalid Command')
            continue
        elif validate_command(command):
            commands.append((command.split()[0], int(command.split()[1])))
    
    delta_x = 0
    delta_y = 0

    # Calculate delta x/y
    for cmd in commands:
        if cmd[0] == 'UP': delta_y += cmd[1]
        elif cmd[0] == 'DOWN': delta_y -= cmd[1]
        elif cmd[0] == 'LEFT': delta_x -= cmd[1]
        elif cmd[0] == 'RIGHT': delta_x += cmd[1]

    # Printing the final distance using Pythagoras' Theorem
    print('The final distance from (0,0) is', round(math.sqrt(delta_x**2 + delta_y**2)))


if __name__ == '__main__':
    main()