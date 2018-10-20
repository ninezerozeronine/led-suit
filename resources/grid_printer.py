reverse = True
end = 0

for row in range(16):
    numbers = range(end, end+16)
    if reverse:
        numbers.reverse()
    for number in numbers:
        print "{0:<4}".format("{0:d},".format(number)),
    reverse = not reverse
    end += 16
    print ""
