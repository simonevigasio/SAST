import pandas as pd
import os

db = pd.read_pickle('./assets/reveal_test.pkl')

print(db)

newpath = './data' 
if not os.path.exists(newpath):
    os.makedirs(newpath)

idx = 0
for func in db['functionSource']: 
    file = open('./data/'+str(idx)+'.c', 'w')
    file.write(func)
    file.close()
    idx += 1
