import pandas as pd

idx = set()
with open('../assets/test.txt') as f:
    for line in f:
        line = line.strip()
        idx.add(int(line))

data = pd.read_json('../assets/Devign.json')
db = data.iloc[list(idx)]
out = open('output.txt', 'r')

errs = []
for line in out:    

    if line[:6].startswith('devign'):

        line = line[::-1]
        err = ''

        counter = 1
        if line[counter] == ']':
            while line[counter] != '[':
                err += line[counter]
                counter += 1
                
        if err not in errs:
            errs.append(err)

rules = ['arrayIndexOutOfBounds', 'shiftNegativeLHS', 'invalidPrintfArgType_sint', 'uninitvar', 'preprocessorErrorDirective', 'noValidConfiguration', 'arithOperationsOnVoidPointer', 'internalAstError', 'AssignmentIntegerToAddress', 'unknownEvaluationOrder', 'shiftTooManyBitsSigned', 'autoVariables', 'invalidPointerCast']

print(errs)