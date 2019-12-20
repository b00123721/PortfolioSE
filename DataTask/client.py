#Base Python client for MEng in IoT Assignment
#consumes data from IoT Gateway
import urllib.request as urlreq
import xml.etree.ElementTree as et
import matplotlib.pyplot as plt
import numpy as np
import datetime

response = urlreq.urlopen('http://localhost:8080/')
resp = response.read().decode()

#cut off some annoying stuff ant the front of the string
resp = resp[resp.find('<reading>'):]
#remove returns
#resp = resp.strip("\n")
#resp = resp.strip("b")

words = resp.split("\n")

#root = et.fromstring(resp)
templist = []
timelist = []
for word in words:
    try:
        temp = et.fromstring(word).find('temperature')
        time = et.fromstring(word).find('time')
        templist.append(int(temp.text))
        

        date_time_str = time.text
        date_time_obj = datetime.datetime.strptime(date_time_str, '%H:%M%f')
        timelist.append(date_time_obj)
    except:
        print("fuck")


plt.plot(templist)
plt.grid(True)
plt.title('Temperature Data')
plt.xlabel('Measurement')
plt.ylabel('Temperature [C°]')


plt.show()

