import primegen as pg
from collections import defaultdict

def get_pattern_vec_len(prev):
    return 1 + (prev * 2)

def trim_vec(vec_list):
    remove_idxs = list()
    for idx, a in enumerate(vec_list):
        if 1 not in a or a[-1] == 1:
            remove_idxs.insert(0, idx)
    for a in remove_idxs:
        vec_list.pop(a)

def list_cmp(l1, l2):
    count = 0
    for a in range(len(l1)):
        count += 1
        if l1[a] != l2[a]:
            return False
    return True

#returns a list of all the right shifted permutations of the given array
def right_shift(arr):
    if len(arr) == 0:
        return list()
    newarr = arr[:]
    c = [newarr]
    a = newarr.pop(-1)
    newarr.insert(0, a)
    while not list_cmp(arr, newarr):
        nextarr = newarr[:]
        c.append(nextarr)
        a = newarr.pop(-1)
        newarr.insert(0,a)
    return c

#Looks for a new previously unencountered right-shift loop
def loop_finder(permutations):
    last = permutations[0]
    for a in range(0, len(last)-1):
        if last[a] == 1 and last[a+1] == 0:
            newloop = last[:]
            newloop[a] = 0
            newloop[a+1] = 1
            found = False
            for b in permutations:
                if list_cmp(b, newloop):
                    found = True
            if not found:
                return newloop

    #If no viable element switches can be found, attempt to find a new loop by adding a 1
    newloop = permutations[0][:]
    for a in range(len(newloop)):
        if newloop[a] == 0:
            newloop[a] = 1
            return newloop

    #If no new loops can be found, return an empty list
    return list()

def longest_primes(l):
    max_nr = (10 ** l) - 1
    primes = pg.primegen(max_nr)
    primes_str = list()
    for a in primes:
        a_str = str(a)
        if len(a_str) == l:
            primes_str.append(a_str)

    return primes_str

def is_applicable(pattern, string):
    if len(pattern) < 2:
        return True
    for a in range(1,len(pattern)):
        if string[pattern[a]] != string[pattern[a-1]]:
            return False
    return True

def get_relevant_primes(primes, pattern):
    relevants = list()
    for a in primes:
        if is_applicable(pattern, a):
            relevants.append(a)
    return relevants

def relevant_match(pattern, n1, n2):
    for a in range(len(n1)):
        if a not in pattern:
            if n1[a] != n2[a]:
                return False
    return True

def get_key(const_idxs, number):
    key = 0
    for a in const_idxs:
        key += int(number[a]) * (10 ** a)
    return key

if __name__ == "__main__":
    l = 3
    foundit = False
    smallest = 0
    while smallest == 0:
        l += 1
        #List all primes of length l (In ascending order)
        primes = longest_primes(l)
        #Find all the possible permutations of where the variable x can be found within a number,
        #Then create all the corresponding vectors
        pattern_vec = [[0]*l]
        full = False
        while not full:
            newloop = loop_finder(pattern_vec)
            full_loop = right_shift(newloop)
            if len(full_loop) != 0:
                pattern_vec = full_loop + pattern_vec
            if len(newloop) == 0:
                full = True

        #Remove the vectors that indicate useless checks
        #(Setting *=ones, because it would include 5 numbers
        #guaranteed to not be prime, and the vector of 0s)
        trim_vec(pattern_vec)
        var_list = list()
        const_list = list()
        for pattern in pattern_vec:
            var_idxs = list()
            const_idxs = list()
            for idx, a in enumerate(pattern):
                if a == 1:
                    var_idxs.append(idx)
                else:
                    const_idxs.append(idx)

            var_list.append(var_idxs)
            const_list.append(const_idxs)

        count = 0
        biggest = 0
        encountered_patterns = list()
        for pattern, const_p in zip(var_list, const_list):
            encountered_patterns.append(pattern)
            pattern_dict = defaultdict(list)
            matches = get_relevant_primes(primes, pattern)
            for match in matches:
                pattern_dict[get_key(const_p, match)].append(match)
            for key in pattern_dict:
                if len(pattern_dict[key]) >= 8:
                    smallest = pattern_dict[key][0]
                    print(pattern_dict[key])
                else:
                    if len(pattern_dict[key]) >= biggest:
                        biggest = len(pattern_dict[key])
                        print("{} - {}".format(pattern_dict[key][0], biggest))

    print(smallest)
    with open("pe51answer.txt", "w")as f:
        f.write(smallest)
    quit()
