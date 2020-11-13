from sys import stdin

print("Enter input: ", end="", flush=True)

user_input = stdin.readline().rstrip()

print(user_input)

if user_input == 'hello':
    print("hi!")
elif user_input == 'world':
    print("hey!")
else:
    print("hello?")
