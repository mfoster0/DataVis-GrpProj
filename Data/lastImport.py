import datetime
import pandas as pd
import requests
import os

monthlyNorthImported = False
monthlySouthImported = False

dailySouthImported = False
dailySouthImported = False


nextMonthlyNorthImportDate = ""
nextMonthlySouthImportDate = ""


nextDailyNorthImportTime = ""
nextDailySouthImportTime = ""

#if (datetime.datetime.now() > nextDailyNorthImportTime)

print(datetime.datetime(2022, 12, 28, 18, 1, 00))
today = datetime.date.today()
print(datetime.datetime(today.year, today.month, today.day, 18, 1, 00))

nextImportTime = datetime.datetime(today.year, today.month, today.day, 2, 1, 00)
if (datetime.datetime.now() > nextImportTime):
    #set next import time so another import does start whilst this is in progress
    nextImportTime = datetime.datetime.now() + datetime.timedelta(hours=1)
    
    file_url = "https://noaadata.apps.nsidc.org/NOAA/G02135/north/daily/data/N_seaice_extent_daily_v3.0.csv"
    r = requests.get(file_url)

    lastFile = "NorthDailyData.csv"
    tmpFile = "tmp" + lastFile
    with open(tmpFile, "wb") as f:	
        f.write(r.content)

    tmpSize = os.path.getsize(tmpFile)   
    lastSize = os.path.getsize(lastFile)   

    print(tmpSize)
    print(lastSize)

    nextImportTime = datetime.datetime(today.year, today.month, today.day, 18, 1, 00) + datetime.timedelta(hours=24)


""" 
# date in yyyy/mm/dd format
d1 = datetime.datetime(2023, 12, 1)
d2 = datetime.datetime(2023, 12, 1)

print("d2 > d1: ", d2 > d1)
print("d2 == d1: ", d2 == d1)
"""

def main():
    #check if import required
    # daily data arrives before noon
    # monthly data in the afternoon for the 2nd
    pass