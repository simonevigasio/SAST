import pandas as pd

test_index = set()

with open('./utils/test.txt') as f:
    for line in f:
        line=line.strip()
        test_index.add(int(line))

mydata = pd.read_json('./Devign.json')
db = mydata.iloc[list(test_index)]

print(len(db.target))

for l in db.target:
    file = open('labels', 'a')
    file.write(str(l)+'\n')