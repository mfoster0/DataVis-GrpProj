import pandas as pd
import numpy as np
import time

initialData = 'MonthlyData.csv'
data = pd.read_csv(initialData)

# loop through the rows using iterrows()
for index, row in data.iterrows():
    print(row['year'].astype(np.int64), row['mo'].astype(np.int64), row['extent_north'], row['extent_south'])
    time.sleep(1)
