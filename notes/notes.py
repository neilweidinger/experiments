import random
import sys

notes = {
    0: 'A',
    1: 'A♯/B♭',
    2: 'B',
    3: 'C',
    4: 'C♯/D♭',
    5: 'D',
    6: 'D♯/E♭',
    7: 'E',
    8: 'F',
    9: 'F♯/G♭',
    10: 'G',
    11: 'G♯/A♭',
}

def main():
    perm = random.sample(range(0, len(notes)), len(notes))

    for i in perm:
        print(f'{notes[i]}')

        sys.stdin.readline()
        print('\n\n')

    print('Done!')

if __name__ == '__main__':
    main()
