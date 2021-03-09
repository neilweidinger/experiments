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
    seen_notes = set()

    while len(seen_notes) < len(notes):
        note = notes[random.randrange(0, len(notes))]

        if note not in seen_notes:
            print(f'{note}')
            seen_notes.add(note)

            sys.stdin.readline()
            print('\n\n')

    print('Done!')

if __name__ == '__main__':
    main()
