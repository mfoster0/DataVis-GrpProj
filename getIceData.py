
import pandas as pd

values = range(1,13)

for i in values:
    print(pd.read_csv(f"https://noaadata.apps.nsidc.org/NOAA/G02135/north/monthly/data/N_{i:02d}_extent_v3.0.csv"))

for i in values:
    print(pd.read_csv(f"https://noaadata.apps.nsidc.org/NOAA/G02135/south/monthly/data/S_{i:02d}_extent_v3.0.csv"))
                     

