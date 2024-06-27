import json
import pandas as pd

db = pd.read_pickle('../assets/reveal_test.pkl')

print('dataset loaded...')

out = open('output.txt', 'r')

stats = []
prev_stat = { 'name': '', 'CWEs': [] }
scan_prompt = False
cwe = ''

for line in out: 

    if line.startswith('ANALYSIS SUMMARY:'): scan_prompt = False

    if scan_prompt:

        if line[0] == '.':

            stat = { 'name': '', 'CWEs': [] }

            i = 0
            while (line[i] != '.' or line[i+1] != 'c'):
                stat['name'] += line[i]
                i += 1                

            if (stat['name'] != '') and (stat['name'] not in [s['name'] for s in stats]):
                stats.append(stat)

            if (cwe != '') and (prev_stat['name'] != ''): 
                [s['CWEs'] for s in stats if s['name'] == prev_stat['name']][0].append(cwe)

            stat = [s for s in stats if s['name'] == stat['name']][0]
            prev_stat = stat
            cwe = ''

        elif prev_stat['name'] != '': 
            cwe += line

    if line.startswith('FINAL RESULTS:'): scan_prompt = True

out.close()

print('output read...')

with open('stats.json', 'w') as f:
    json.dump(stats, f)

idx_files = []

for stat in stats:

    stat['name'] = stat['name'][::-1]
    idx_file = ''

    i = 0
    while stat['name'][i] != '/':
        idx_file += stat['name'][i]
        i += 1

    idx_file = idx_file[::-1]
    idx_files.append(int(idx_file))

idx_files.sort()

print('vulnerable files found...')

results = [0]*len(db)

for idx in idx_files:
    results[idx] = 1

preds = open('preds.txt', 'w')
for result in results:
    preds.write(str(result)+'\n')

preds.close()

TP, TN, FP, FN, c = 0, 0, 0, 0, 0
for label in db['label']:
    pred = results[c]
    c += 1

    if pred == label: 
        if pred == 0: TN += 1
        else: TP += 1
    else: 
        if pred == 0: FN += 1
        else: FP += 1

Accuracy = (TP + TN) / (TN + TP + FP + FN)
Precision = TP / (TP + FP)
Recall = TP / (TP + FN)
F1 = TP / (TP + ((FN + FP) / 2))

print('computed evaluation...')
print('TP', TP)
print('TN', TN)
print('FP', FP)
print('FN', FN)
print('Accuracy', Accuracy)
print('Precision', Precision)
print('Recall', Recall)
print('F1', F1)
