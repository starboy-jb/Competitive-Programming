import requests
from bs4 import BeautifulSoup
import time
import os

def message(title, message):
	os.system('notify-send "' + title + '" "' + message + '"')

class CodechefContestAnnouncer:
	def __init__(self, contest_link):
		self.contest_link = contest_link
  	
	def run(self):
		contest_link = self.contest_link
		current_annoucement = ""
		while True:
			try:
				html = requests.get(contest_link)
				soup = BeautifulSoup(html.text, 'lxml')
				data = soup.find('div', {'id' : 'announce_content'})
				announcement = str(data.text)
				if current_annoucement != announcement:
					message("Codechef Announcement", announcement)
					current_annoucement = announcement
			except:
				pass

if __name__ == '__main__':
	Contest = CodechefContestAnnouncer("https://www.codechef.com/FFC12019?utm_source=contest_listing&utm_medium=link&utm_campaign=FFC12019")
	Contest.run()
