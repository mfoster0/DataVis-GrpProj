import datetime

# date in yyyy/mm/dd format
lastImported = datetime.datetime(1900,1,1)

#d1 = datetime.datetime(2023, 12, 9)
todaysDate = datetime.datetime(datetime.datetime.today().year, datetime.datetime.today().month, datetime.datetime.today().day)
importTime = datetime.datetime(datetime.datetime.today().year, datetime.datetime.today().month, datetime.datetime.today().day, 17, 0, 0)

#if todays date > than last imported and time is after 3pm, get data
if (todaysDate > lastImported and datetime.datetime.now() > importTime):
    print("Getting today's data")
    ## import monthly data on the nth day of the month
    if (datetime.datetime.today().day == 2):
        print("getting monthly data")
        

    # if data imported set last imnported date
    lastImported = todaysDate
