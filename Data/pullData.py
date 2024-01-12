import requests
import pandas as pd
import os

northDailyExtent = ""
northDailyYear = ""
northDailyMonth = ""
northDailyDay = ""

southDailyExtent = ""
southDailyYear = ""
southDailyMonth = ""
southDailyDay = ""

"""
#get latest north data
file_url = "https://noaadata.apps.nsidc.org/NOAA/G02135/north/daily/data/N_seaice_extent_daily_v3.0.csv"
r = requests.get(file_url)
r.raise_for_status()

#write locally
with open("NorthDailyData.csv", "wb") as f:	
    f.write(r.content)
"""
"""
#get the latest values form the file
df = pd.read_csv('NorthDailyData.csv', skipinitialspace=True)

# remove the first data row - this contains some unused metadata
df = df.drop(df.index[[0]])

northDailyExtent = df['Extent'].iloc[-1]
northDailyYear = df['Year'].iloc[-1]
northDailyMonth = df['Month'].iloc[-1]
northDailyDay = df['Day'].iloc[-1]
northDailyMean = df.loc[( df['Day'] == northDailyDay) & (df['Month'] == northDailyMonth), 'Extent'].mean()

"""
"""
#get latest south data
file_url = "https://noaadata.apps.nsidc.org/NOAA/G02135/south/daily/data/S_seaice_extent_daily_v3.0.csv"
r = requests.get(file_url)
r.raise_for_status()

#write locally
with open("SouthDailyData.csv", "wb") as f:	
    f.write(r.content)
"""
"""
#get latest values from the file
df = pd.read_csv('SouthDailyData.csv', skipinitialspace=True)
# remove the first data row - this contains some unused metadata
df = df.drop(df.index[[0]])
southDailyExtent = df['Extent'].iloc[-1]
southDailyYear = df['Year'].iloc[-1]
southDailyMonth = df['Month'].iloc[-1]
southDailyDay = df['Day'].iloc[-1]
"""

regions = ["north", "south"]
for region in regions:
    regionFile = region.capitalize() + "DailyData.csv"
    
    """
    #get latest region data
    file_url = 'https://noaadata.apps.nsidc.org/NOAA/G02135/' + region + '/daily/data/' + region[0].upper() + '_seaice_extent_daily_v3.0.csv'
    r = requests.get(file_url)
    r.raise_for_status()
    
    #write locally
    with open(regionFile + "DailyData.csv", "wb") as f:	
        f.write(r.content)

    """
    #get latest values from the file
    df = pd.read_csv(regionFile, skipinitialspace=True)

    # remove the first data row - this contains some unused metadata
    df = df.drop(df.index[[0]])

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
    #regionDailyDiffMeanDiffPerc =  (round(((regionDailyDiffMean - df['Extent'].iloc[-2])/df['Extent'].iloc[-2])*100,2))
    
    #publish latests daily data
    #print(regionDailyDay, regionDailyMonth, regionDailyYear, regionDailyExtent, regionDailyMean, regionDailyMax, regionDailyMin)
    #print(regionDailyExtentDiff, regionDailyExtentDiffPerc)
    #print(df.loc[( df['Day'] == regionDailyDay) & (df['Month'] == regionDailyMonth), 'Extent'] * 100)
    print("Avg extent for this date: ", regionDailyMean)
    print("Yesterday's extent: ", df['Extent'].iloc[-2])
    print("Today's extent: ", regionDailyExtent)
    print("Extent change since yesterday: ", regionDailyExtentDiff)
    print("Avg extent change for date: ",  regionDailyDiffMean)
    #print("perc change avg vs yesterday: ",  regionDailyDiffMeanDiffPerc)
"""
print(northDailyDay, northDailyMonth, northDailyYear, northDailyExtent )
print(southDailyDay, southDailyMonth, southDailyYear, southDailyExtent )



print(df.to_string()) 

# Example 1: Get last row using row position
print(df.iloc[-1])

# Example 2: Get the last row use tail()
print(df.tail(1))

# Example 3: Get last row using range index
print(df.iloc[-1:])


# get latest values
print(df['Month'].iloc[-1])

#topData = df.head() 
     
# iterating the columns
for col in df.columns:
    print(col)
    """