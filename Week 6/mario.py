import cs50

def main():
    while True:
        print("Height: ", end = "")
        num = cs50.get_int()
        if num >= 0 and num <= 23:
            break

    for i in range(num):
        for m in range(num - 1 - i):
            print(" ", end = "")
        for n in range(i+2):
            print("#", end = "")
        print("")

if __name__ == "_main_":
    main()