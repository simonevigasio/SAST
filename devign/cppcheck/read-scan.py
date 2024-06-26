import pandas as pd
import json

idx = set()
with open('../assets/test.txt') as f:
    for line in f:
        line = line.strip()
        idx.add(int(line))

data = pd.read_json('../assets/Devign.json')
db = data.iloc[list(idx)]
out = open('output.txt', 'r')

rule_types = []
files = []

for line in out:    

    if line[:6].startswith('devign'):

        file = { 'name': '', 'rules': [] }

        i = 0
        while (line[i] != '.' or line[i+1] != 'c'):
            file['name'] += line[i]
            i += 1

        i += 3
        while line[i] != ':':
            i += 1

        i += 1
        while line[i] != ':':
            i += 1

        rule_category = ''
        i += 2
        while line[i] != ':':
            rule_category += line[i]
            i += 1

        line = line[::-1]
        rule_type = ''

        if line[1] == ']':
            i = 2
            while line[i] != '[':
                rule_type += line[i]
                i += 1
                
        rule_type = rule_type[::-1]

        rule = { 'rule_category': rule_category, 'rule_type': rule_type }

        if (file['name'] != '') and (file['name'] not in [f['name'] for f in files]):
            files.append(file)

        if (rule_type != '') and (rule_type not in rule_types):
            rule_types.append(rule_type)

        if (rule_type != '') and (rule not in [f['rules'] for f in files if f['name'] == file['name']][0]): 
            [f['rules'] for f in files if f['name'] == file['name']][0].append(rule)

out.close()
rule_types.sort()

with open('stats.json', 'w') as f:
    json.dump(files, f)

idx_files = []
valid_categories = ['error', 'portability', 'warning', 'style']
not_valid_types = ['unusedFunction', 'syntaxError']

for file in files: 

    is_valid = False
    for rule in file['rules']:
        if (rule['rule_category'] in valid_categories) and (rule['rule_type'] not in not_valid_types):
            is_valid = True

    if is_valid:

        file['name'] = file['name'][::-1]
        idx_file = ''
        
        i = 0
        while file['name'][i] != '/':
            idx_file += file['name'][i]
            i += 1

        idx_file = int(idx_file[::-1])
        idx_files.append(idx_file)

idx_files.sort()
results = [0]*len(db)

for idx in idx_files:
    results[idx] = 1

preds = open('preds.txt', 'w')
for result in results:
    preds.write(str(result)+'\n')

preds.close()

TP, TN, FP, FN, c = 0, 0, 0, 0, 0
for label in db.target:
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

print('TP', TP)
print('TN', TN)
print('FP', FP)
print('FN', FN)
print('Accuracy', Accuracy)
print('Precision', Precision)
print('Recall', Recall)
print('F1', F1)
