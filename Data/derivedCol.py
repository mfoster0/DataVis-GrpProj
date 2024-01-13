import pandas as pd
import numpy as np

oriData = {
    'Type':["A","B","C","D"],
    'Fee' :[20000,25000,26000,22000],
    'Rate':[1,0.5,1, 0.75]
               }
df = pd.DataFrame(oriData)
df['Actual'] = df['Fee'] * df['Rate']
df['Diff'] = df['Actual'].diff().fillna(0)
df['PercChg'] = df['Actual'].pct_change().fillna(0)


print(df)