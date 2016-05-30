'''
Example of reading and writing a HDF5 file using Pandas
'''

import pandas

ts = pandas.read_csv("data.csv", delim_whitespace=True)

# Following line was used to create the HDF5 file in teh first place
# ts.to_hdf("data.hdf5", "table")

ts2 = pandas.read_hdf("data.hdf5", "table")

print(all(ts == ts2))

