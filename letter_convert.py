from scipy.io.arff import loadarff
import pandas as pd
import arff


if __name__ == "__main__":
    data, meta = loadarff('datasets/letter.arff')
    df = pd.DataFrame(data)
    letters = meta[meta.names()[-1]][1]
    translation = dict(zip(letters, range(len(letters))))

    df['class'] = df['class'].str.decode("utf-8")
    df = df[df['class'].isin(letters[:5])]
    df['class'].replace(translation, inplace=True)
    print(df.head())
    print(len(df))
    arff.dump('datasets/letter_mapped.arff', df.values, relation='letter', names=df.columns)
