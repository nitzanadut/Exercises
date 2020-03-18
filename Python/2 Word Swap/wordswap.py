import sys

"Returns a new sentence with every second word swapped with Biss10"
swap = lambda sentence: ' '.join([word if index % 2 == 0 else "Biss10" for index, word in enumerate(sentence.split())])    

def main():
    if len(sys.argv) != 2:
        print("Usage: {} \"sentence\"".format(sys.argv[0]))
        sys.exit(1)
    
    print(swap(sys.argv[1]))

if __name__ == '__main__':
    main()