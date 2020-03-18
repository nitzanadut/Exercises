"@Nitzan Adut"

import sys
import re
from itertools import islice

def take(n, iterable):
    "Return first n items of the iterable as a list"
    return list(islice(iterable, n))

def parse_file(filename):
    "Checks whether a file filename exists and has permissions to read"
    try:
        return open(filename, 'r')
    except FileNotFoundError:
        print('No such file or directory {}'.format(filename))
        sys.exit(1)

def extract_words(filename):
    "Returns a dict of words. Keys - words, Values - number of occurrences in the file filename"
    f = parse_file(filename).read()
    words = dict()
    
    for word in f.split():
        # Stripping the non letters and the start and at the end (commas, dots, parentheses, etc...)
        word = re.sub('^[^a-zA-Z]*', '', word).lower()
        word = re.sub('[^a-zA-Z]*$', '', word)
        
        if word in words:
            words[word] += 1
        else:
            words[word] = 1
    
    return words

def print_words(filename):
    "Printing every word in file, lowercased, with the number of occurrences in the file"
    words = extract_words(filename)

    for item in sorted(words.items()):
        print(item[0], item[1])
    
def print_top(filename):
    "Printing the 20th most common words in a file"
    words = extract_words(filename)

    words = {k: v for k, v in sorted(words.items(), key=lambda item: item[1], reverse=True)}

    for word in take(20, words):
        print(word, words[word])

def main():
    if len(sys.argv) != 3:
        print("usage: ./wordcount.py {--count | ---topcount} file")
        sys.exit(1)

    option = sys.argv[1]
    filename = sys.argv[2]

    if option == '--count':
        print_words(filename)
    elif option == '--topcount':
        print_top(filename)

    else:
        print("unknown option: " + option)
        sys.exit(1)


if __name__ == '__main__':
    main()