import requests
import re

#Get the factors
r = requests.get('http://directus.darkscience.net:6789/')
#get the answer
content = r.text
content = content = content.split("<p>")[1]
content = re.sub ("[^0123456789x]","",content)
content = content.replace('x', '*')
answer = eval(content)
#send the answer
payload = {'answer' : answer}
r = requests.post('http://directus.darkscience.net:6789', data = payload)

#check its correct
content = r.text
content= content.split("<body>")[1]
content = content.split("</body>")[0]
print content





