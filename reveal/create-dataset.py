import pandas as pd


db = pd.read_pickle('reveal_test.pkl')

i = 0
for func in db['functionSource']: 
    f = open('./data/'+str(i)+'.cpp', 'w')
    f.write(func)
    f.close()
    i += 1
