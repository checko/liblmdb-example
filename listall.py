import lmdb
env = lmdb.open("./testdb-store",subdir=False)
txn = env.begin()
for key, value in txn.cursor():
    print(key, value)

