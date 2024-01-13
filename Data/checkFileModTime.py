import os
import datetime

# Replace this with your file path
filepath = 'lastImport.py'

# Check if file exists
if os.path.exists(filepath):
    # Get the last modified time
    epochModTime = os.path.getmtime(filepath)
    
    modifiedTime = datetime.datetime.fromtimestamp(epochModTime)
    # Convert the time in seconds since epoch to a readable format
    modifiedDate = datetime.datetime(modifiedTime.year, modifiedTime.month, modifiedTime.day)
    todaysDate = datetime.datetime(datetime.datetime.today().year, datetime.datetime.today().month, datetime.datetime.today().day)

    print(modifiedDate, todaysDate == modifiedDate)
else:
    print("File does not exist.")
