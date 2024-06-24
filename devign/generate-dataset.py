import pandas as pd

test_index = set()

with open('./assets/test.txt') as f:
    for line in f:
        line=line.strip()
        test_index.add(int(line))

mydata = pd.read_json('./assets/Devign.json')
db = mydata.iloc[list(test_index)]

quarter_dblen = len(db.func) / 4

i = 0
for func in db.func:
    j = 1
    if quarter_dblen < i: 
        if (2 * quarter_dblen) > i: j = 2
        elif (3 * quarter_dblen) > i: j = 3
        else: j = 4

    f = open('./data'+str(j)+'/'+str(i)+'.c', 'w')
    f.write(func)
    f.close()
    i += 1