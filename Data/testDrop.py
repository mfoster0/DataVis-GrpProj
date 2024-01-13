import pandas as pd
import numpy as np

technologies = {
    'Courses':["Spark","PySpark","Hadoop","Python"],
    'Fee' :[20000,25000,26000,22000],
    'Duration':['30day','40days',np.nan, None],
    'Discount':[1000,2300,1500,1200]
               }

df = pd.DataFrame(technologies)
 
print(df)