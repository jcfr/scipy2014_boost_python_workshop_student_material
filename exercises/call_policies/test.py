import call_policies as cp

mtx = cp.Matrix(10, 10)
row = mtx.get(4)
del mtx
print(row.get(2))
