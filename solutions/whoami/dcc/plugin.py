import re
import urllib

DCC3_URL           = "http://directus.darkscience.net:6789/"
DCC3_PROBLEM_REGEX = re.compile(r"([0-9]+) x ([0-9]+)")
DCC3_BODY_REGEX    = re.compile(r"<body>(.*)</body>")

class DCCPlugin(object):
	def dcc3(self, cardinal, user, channel, msg):
		try:
			page    = urllib.urlopen(DCC3_URL)
			problem = re.search(DCC3_PROBLEM_REGEX, page.read())
		except:
			cardinal.sendMsg(channel, "Error retrieving problem.")
			return

		answer   = int(problem.group(1)) * int(problem.group(2))
		response = urllib.urlopen(DCC3_URL, urllib.urlencode({'answer': answer })).read()
		response = re.search(DCC3_BODY_REGEX, response).group(1)
		cardinal.sendMsg(channel, "The problem was... %d x %d = %d. Response: %s." % (int(problem.group(1)), int(problem.group(2)), answer, response))

	dcc3.commands = ['dcc', 'dcc3']

def setup():
	return DCCPlugin()
