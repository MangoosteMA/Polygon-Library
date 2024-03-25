import os
import sys

def loadFileData(file):
    with open(file, 'r') as f:
        return f.read()

def isLibraryInclude(line):
    return line.startswith('#include \"')

def isPragmaOnce(line):
    return line.startswith('#pragma once')

SOURCE_PATH = os.path.dirname(os.path.abspath(__file__))

sourceFiles = []
headerFiles = []
for subdir, dirs, files in os.walk(f'{SOURCE_PATH}/gen'):
    for file in files:
        relativePath = f'{subdir}/{file}'
        if file.endswith('.cpp'):
            sourceFiles.append(relativePath)
        elif file.endswith('.h'):
            headerFiles.append(relativePath)

nHeaders = len(headerFiles)
graph = [[] for i in range(nHeaders)]
for i, header in enumerate(headerFiles):
    headerPath = os.path.dirname(header)
    for line in loadFileData(header).split('\n'):
        if isLibraryInclude(line):
            startPos = line.find('\"')
            endPos = line.rfind('\"')
            libraryName = line[startPos + 1 : endPos]
            includedHeader = os.path.abspath(os.path.join(headerPath, libraryName))

            try:
                graph[i].append(headerFiles.index(includedHeader))
            except:
                print(f'Incorrect include: {line}')
                sys.exit(0)

used = [False] * nHeaders
topSort = []

def dfs(vertex):
    used[vertex] = True
    for adj in graph[vertex]:
        if not used[adj]:
            dfs(adj)
    topSort.append(vertex)

for i in range(nHeaders):
    if not used[i]:
        dfs(i)

filesList = []
for i in topSort:
    filesList.append(headerFiles[i])
filesList += sourceFiles

dumpData = ''
for file in filesList:
    fileData = ''
    for line in loadFileData(file).split('\n'):
        if not isLibraryInclude(line) and not isPragmaOnce(line):
            dumpData += line + '\n'

print(dumpData.strip('\n'))
