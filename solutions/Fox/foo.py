import requests
import re
import zlib
import bz2
u = 'http://directus.darkscience.net:6789/'
print re.search('(Correct|Wrong)', requests.post(u, {'answer': eval(re.search('[0-9]+ x [0-9]+', requests.get(u).text).group(0).replace('x', '*'))}).text).group(0)
# Derecho: oeps shit weggehaald enzo
