# range for floats
def drange(start, stop, step):
    r = start
    while r < stop:
        yield r
        r += step