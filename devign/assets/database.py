import pandas as pd
import os

module_dir = os.path.dirname(__file__)
if module_dir != '': module_dir += '/'

idx = set()
with open(module_dir+'test.txt') as f:
    for line in f:
        line = line.strip()
        idx.add(int(line))

data = pd.read_json(module_dir+'Devign.json')
db = data.iloc[list(idx)]
