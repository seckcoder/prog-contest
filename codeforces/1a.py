import math

def main():
    line = raw_input()
    n, m, a = [int(num) for num in line.split()]

    print int(math.ceil(float(n) / a)) * int(math.ceil(float(m) / a))

if __name__ == '__main__':
    main()
