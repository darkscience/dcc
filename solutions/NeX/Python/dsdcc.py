#!/usr/bin/python

import urllib2
import urllib

resp = urllib2.urlopen("http://directus.darkscience.net:6789/").read()
i = resp.split().index("x")
a = int(resp.split()[i-1])
b = int(resp.split()[i+1])

req = urllib2.Request("http://directus.darkscience.net:6789/",urllib.urlencode({'answer':a*b}))
resp = urllib2.urlopen(req).read()

if "Correct" in resp:
    print "Correct! %d * %d = %d" % (a,b,a*b)
else:
    print "Incorrect :< Apparently %d * %d is not %d" % (a,b,a*b)
