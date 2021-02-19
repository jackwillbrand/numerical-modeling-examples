import numpy as np
import matplotlib.pyplot as plt
import os.path
from os import path
import sys

'''
@brief function to convert csv located at 'csv_path' to jpg at 'map_path'
@pre csv_path must point to existing csv file
@param[in] csv_path path, centered at current dir, to csv
@param[in] map_path path, centered at current dir, where jpg is desired to go
@throw RuntimeError if given csv_path does not exist
@post convert the supplied csv to a heatmap comparing csv's float values
'''
def csv_to_heatmap(csv_path: str, map_path: str) -> None:
    if(not path.exists(csv_path)):
        raise RuntimeError('supplied csv_path doesnt exist')

    data = np.genfromtxt(csv_path, delimiter=",")
    figure = plt.figure()
    plt.imshow(data, cmap='hot', interpolation='nearest')
    plt.colorbar()
    figure.savefig(map_path)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print('Pass 2 args: csv file, output image name')
        raise RuntimeError('wrong number of cmd line args')
    csv_to_heatmap(sys.argv[1], sys.argv[2])