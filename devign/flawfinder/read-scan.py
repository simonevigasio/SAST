import pandas as pd

test_index = set()

with open('../test.txt') as f:
    for line in f:
        line=line.strip()
        test_index.add(int(line))

mydata = pd.read_json('../Devign.json')
db = mydata.iloc[list(test_index)]

f = open('output.txt', 'r')

func_idxs = []
results = [0] * len(db)

for l in f:
    if l[:4].startswith('data'): 
        idx = -1
        if l[9].startswith('3'):
            if l[12].startswith('.'):
                idx = l[11:12]
            elif l[13].startswith('.'): 
                idx = l[11:13]
            else: 
                idx = l[11:14]
        elif l[7].startswith('1'):
            if l[17].startswith('.'): 
                idx = l[14:17]
            else: 
                idx = l[14:18]
        elif l[7].startswith('-'):
            idx = l[15:19]
        idx = int(idx)
        if idx not in func_idxs: 
            func_idxs.append(idx)

func_idxs.sort()
for idx in func_idxs: 
    results[idx] = 1

for r in results:
    f_r = open('preds.txt', 'a')
    f_r.write(str(r)+'\n')

f_r.close()
f.close()

labels = db.target

FP = 0
FN = 0
TP = 0
TN = 0

i = 0
for l in labels: 
    if results[i] == l:
        if results[i] == 0: 
            TN += 1
        else: 
            TP += 1
    else: 
        if results[i] == 0:
            FN += 1
        else: 
            FP += 1
    i += 1

print(TP, TN, FP, FN)

Accuracy = (TP + TN) / (TN + TP + FP + FN)
Precision = TP / (TP + FP)
Recall = TP / (TP + FN)
F1 = TP / (TP + ((FN + FP) / 2))

print(Precision, Recall, F1)
print(Accuracy)