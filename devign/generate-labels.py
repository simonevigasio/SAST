from assets.database import db

file = open('labels', 'w')
for l in db.target:
    file.write(str(l)+'\n')
file.close()
