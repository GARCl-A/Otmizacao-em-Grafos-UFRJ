Instances are organized in folders and subfolders depending on the number of items (500 - 700 - 800 - 1000).

For each instance file, the structure is the following:

Line 1 contains the following values:
nI nP kS
where:
nI = number of items
nP = number of forfeit pairs
kS = knapsack size

Line 2 contains item profits, in order of index 0...nI-1

Line 3 contains item weights, in order of index 0...nI-1

The remaining lines contain the following values:

id_0_0 id_0_1
(...)  
id_i_0 id_i_1
(...)  
id_(nP-1)_0 id_(nP-1)_1

where:
id_i_0 = index of first item for pair i (belonging to {0,...,nI-1})
id_i_1 = index of second item for pair i (belonging to {0,...,nI-1})
