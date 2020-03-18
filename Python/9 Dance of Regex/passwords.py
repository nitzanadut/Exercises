import sys
import re

def main():
    if len(sys.argv) != 2:
        print('Usage: {} (passwords seperated by commas)'.format(sys.argv[0]))
        sys.exit(1)
    
    passwords = sys.argv[1].split(',')

    # Regex to filter the passwords
    print(','.join(filter(lambda password: re.match(r'^(?=.+[a-z])(?=.+[0-9])(?=.+[A-Z])(?=.+[@#\$%^&\*])[a-z\dA-Z@#$%^&*]{6,12}$', password), passwords)))

if __name__ == '__main__':
    main()