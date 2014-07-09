#!/usr/bin/python

import httplib
import urllib2
import re

m = re.findall('([0-9]{1,4}) x ([0-9]{1,4})', urllib2.urlopen('http://directus.darkscience.net:6789/').read())
product = str(int(m[0][0])*int(m[0][1]))

s = 'answer=' + product

headers = {
    "Host": "directus.darkscience.net",
    "Content-Type": "application/x-www-form-urlencoded",
    "Content-Length": len(s),
    "Connection": "close"
}

c = httplib.HTTPConnection("directus.darkscience.net:6789")
c.request('POST', "/", s, headers)
response = c.getresponse()
data = response.read()

if data.find('Correct'):
    print 'Correct!'
else:
    print 'Wrong.'

c.close()