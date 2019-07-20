from plyer import notification
import requests
from bs4 import BeautifulSoup
import time
import os

def message(title, message):
	notification.notify (
	    title = title,
	    message = message,
	)

class CodechefContestAnnouncer:
	def __init__(self, contest_link):
		self.contest_link = contest_link
  	
	def run(self):
		contest_link = self.contest_link
		current_annoucement = ''
		while True:
			try:
				html = requests.get(contest_link)
				soup = BeautifulSoup(html.text, 'lxml')
				data = soup.find('div', {'id' : 'announce_content'})
				announcement = str(data.text)
				l = len(announcement)
				if l > 1 and current_annoucement != announcement:
					message("Codechef Announcement", announcement)
					current_annoucement = announcement
			except:
				pass

if __name__ == '__main__':
	#replace the contest link
	contest_link = "https://www.codechef.com/JULY19B"
	Contest = CodechefContestAnnouncer(contest_link)
	Contest.run()
