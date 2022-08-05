def primegen(mp):
    candidates = [0] * mp
    primes = [2]
    for a in range(4,mp,2):
        a = 1
    for a in range(3, mp, 2):
        if candidates[a] == 0:
            primes.append(a)
            for b in range(2*a, mp, a):
                candidates[b] = 1
    return primes
