import pandas as pd


db = pd.read_pickle('reveal_test.pkl')

quarter_dblen = len(db['functionSource']) / 4

i = 0
for func in db['functionSource']: 
    j = 1
    if quarter_dblen < i: 
        if (2 * quarter_dblen) > i: j = 2
        elif (3 * quarter_dblen) > i: j = 3
        else: j = 4

    f = open('./data'+str(j)+'/'+str(i)+'.cpp', 'w')
    f.write(func)
    f.close()
    i += 1