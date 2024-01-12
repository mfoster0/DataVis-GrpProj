import requests
import pandas as pd
import os
import requests


#get data for both regions
regions = ["north", "south"]
for region in regions:

    regionFile = region.capitalize() + "DailyData.csv"
    
    #get latest region data
    file_url = 'https://noaadata.apps.nsidc.org/NOAA/G02135/' + region + '/daily/data/' + region[0].upper() + '_seaice_extent_daily_v3.0.csv'
    print(file_url)
    
    r = requests.get(file_url)
    r.raise_for_status()
    
    #write locally
    with open(regionFile, "wb") as f:	
        f.write(r.content)

    #get latest values from the file
    df = pd.read_csv(regionFile, skipinitialspace=True)

    # remove the first data row - this contains some unused metadata
    df = df.drop(df.index[[0]])

    #force to float data type
    df['Extent'] = pd.to_numeric(df['Extent'] , errors='coerce').fillna(0).astype(float)

    #create new cols for area changes
    df['ExtentDiff'] = df['Extent'].diff().fillna(0)
    df['ExtentPercChg'] = df['Extent'].pct_change().fillna(0)

    #get latest value
    regionDailyExtent = df['Extent'].iloc[-1]
    regionDailyYear = df['Year'].iloc[-1]
    regionDailyMonth = df['Month'].iloc[-1]
    regionDailyDay = df['Day'].iloc[-1]

    regionDailyMean = round(df.loc[( df['Day'] == regionDailyDay) & (df['Month'] == regionDailyMonth), 'Extent'].mean(),2)
    regionDailyMax = df.loc[( df['Day'] == regionDailyDay) & (df['Month'] == regionDailyMonth), 'Extent'].max()
    regionDailyMin = df.loc[( df['Day'] == regionDailyDay) & (df['Month'] == regionDailyMonth), 'Extent'].min()
    
    #current days diffs
    regionDailyExtentDiff = round(df['Extent'].iloc[-1] - df['Extent'].iloc[-2],2)
    regionDailyExtentDiffPerc = round(((df['Extent'].iloc[-1] - df['Extent'].iloc[-2])/df['Extent'].iloc[-2])*100,2)
    
    #avg change for this date historically
    regionDailyDiffMean = round(df.loc[( df['Day'] == regionDailyDay) & (df['Month'] == regionDailyMonth), 'ExtentDiff'].mean(),2)
    
    print("")
    #on first pass publish the date
    if region == regions[0]:
        print(regionDailyYear, regionDailyMonth, regionDailyDay)


    #publish latests daily data
    print("Avg extent for this date: ", regionDailyMean)
    print("Yesterday's extent: ", df['Extent'].iloc[-2])
    print("Today's extent: ", regionDailyExtent)
    print("Extent change since yesterday: ", regionDailyExtentDiff)
    print("Avg extent change for date: ",  regionDailyDiffMean)
