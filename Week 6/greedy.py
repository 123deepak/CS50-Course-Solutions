import cs50

def main():
    while True:
        print("O hai! How much change is owed?")
        amt = cs50.get_float()
        if amt >= 0:
            break

    left = 0
    a = int(round(amt * 100))

    left += a // 25
    a %= 25

    left += a // 10
    a %= 10

    left += a // 5
    a %= 5

    left += a

    print("{}".format(left))

if __name__ == "__main__":
    main()
