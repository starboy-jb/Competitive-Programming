import requests
import bs4
import time
import os

def message(title, message):
  os.system('notify-send "' + title + '" "' + message + '"')

cur = ""

while True:
	try:
		link = 'https://www.codechef.com/LTIME71A'
		res = requests.get(link)
		soup = bs4.BeautifulSoup(res.text, 'lxml')
		data = soup.find('div', {'id' : 'announce_content'})
		actual_data = str(data.text)
		if cur != actual_data:
			message("Codechef Announcement", actual_data)
			cur = actual_data
	except:
		pass
