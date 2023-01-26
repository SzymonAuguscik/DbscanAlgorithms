import sys
import os

import pandas as pd

from matplotlib import pyplot as plt


if __name__ == "__main__":
    with open(sys.argv[1], 'r') as file:
        file.readline()
        dataset = [line.split(',')[1:6] for line in file.readlines()]

        for i, line in enumerate(dataset):
            dataset[i] = [float(num) for num in line]
            dataset[i][4] = int(dataset[i][4])
            del dataset[i][3]
            del dataset[i][2]

    df = pd.DataFrame(dataset)
    groups = sorted(pd.unique(df[2]))
    colors = ['k', 'b', 'r']

    for group, color in zip(groups, colors):
        points = df[df[2] == group]
        plt.scatter(points[0], points[1], c=color, label=f"group {group}")
    
    plt.title("Wynik grupowania")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.savefig(f"{os.path.join(os.path.dirname(sys.argv[1]), os.path.basename(sys.argv[1]))}.png")

