import lmdb
import sys
env = lmdb.open(sys.argv[1],subdir=False)
txn = env.begin()
for key, value in txn.cursor():
    print(key, value)

