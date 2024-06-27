import pandas as pd

db = pd.read_pickle('./assets/reveal_test.pkl')

file = open('labels', 'w')
for l in db['label']:
    file.write(str(l)+'\n')
file.close()