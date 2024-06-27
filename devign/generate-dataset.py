import os
from assets.database import db

print(db)

newpath = './data' 
if not os.path.exists(newpath):
    os.makedirs(newpath)

idx = 0
for func in db.func: 
    file = open('./data/'+str(idx)+'.c', 'w')
    file.write(func)
    file.close()
    idx += 1
