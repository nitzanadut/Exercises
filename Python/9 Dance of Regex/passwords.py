import sys
import re

def main():
    if len(sys.argv) != 2:
        print('Usage: {} (passwords seperated by commas)'.format(sys.argv[0]))
        sys.exit(1)
    
    passwords = sys.argv[1].split(',')

    # Regex to filter the passwords
    print(','.join(filter(lambda password: bool(re.match(r'^(.{6,12})$', password)) and
                                           bool(re.match(r'^.*[a-z]+.*$', password)) and 
                                           bool(re.match(r'^.*[A-Z]+.*$', password)) and 
                                           bool(re.match(r'^.*[@#$%^&*]+.*$', password)) , passwords)))

if __name__ == '__main__':
    main()