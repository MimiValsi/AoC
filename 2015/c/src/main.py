#!/usr/bin/env python3

import json


def recsum(r):
    s = 0

    if isinstance(r, list):
        d = r
        # print("d list > ", r)
        # print("\n")
    elif isinstance(r, dict):
        if "red" in r.values():
            # print("r dict > ", r)
            # print("\n")
            return 0
        else:
            d = r.values()
            # print("d > ", d)
            # print("\n")
    else:
        return 0

    for v in d:
        try:
            s += v
            # print("s > ", s)
        except:
            s += recsum(v)
            # print("se > ", s)

    return s


# with open("./data/day12_4.txt") as f:
with open("./data/day12.txt") as f:
    d = json.loads(f.read())
    # print("str > ", d)
    # print("\n")
    print(recsum(d))
