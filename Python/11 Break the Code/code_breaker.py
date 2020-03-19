from string import ascii_lowercase
import time

'''
Hey,
I know the runtime is absolutely horrendous.
Maybe removing the file writing and starting from the end will improve it :)
Nitzan
'''

def main():
    start = time.time()
    cipher_text = open('big_secret.txt', 'r').read().split(',')
    output = open('output.txt', 'w')

    for a in ascii_lowercase:
        for b in ascii_lowercase:
            for c in ascii_lowercase:
                
                # For every combination of keys, solve the ciphertext
                txt = ''
                for i, ci in enumerate(cipher_text):
                    if i % 3 == 0:   txt += chr(int(ci) ^ ord(a))
                    elif i % 3 == 1: txt += chr(int(ci) ^ ord(b))
                    else:            txt += chr(int(ci) ^ ord(c))
                output.write(a + b + c + ' ->       ' + txt + '\n')

                if 'Pyjamas' in txt:
                    print('Found the secret message!\n' + txt)
                    print('\nRuntime: {0} seconds\nNow finishing writing all possibilites to output.txt...'.format(time.time() - start))
                

if __name__ == '__main__':
    main()