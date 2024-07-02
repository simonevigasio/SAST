import os
import json

"""
    func: String
    target: Int [0, 1]
    cwe: Array
    project: String
    commit_id: String
    hash: String
    size: Int
    message: String
"""

newpath = './data' 
if not os.path.exists(newpath):
    os.makedirs(newpath)

num_vulnerable_func = 0
stats = []
all_cwe = []

with open('diversevul.json', 'r') as f:
    for line in f: 
        data = json.loads(line)
        if (data['cwe']!=[]) and (data['target']==1): 
            name = 'data/'+str(num_vulnerable_func)+'.cpp'
            func = open('./'+name, 'w')
            func.write(data['func'])
            func.close()

            num_vulnerable_func += 1

            stat = { 'name': name, 'cwe': data['cwe'] }
            stats.append(stat)

            for cwe in data['cwe']:
                if cwe not in all_cwe:
                    all_cwe.append(cwe)


with open('cwe.json', 'w') as f:
    json.dump(stats, f)
