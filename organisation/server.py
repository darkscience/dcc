#!/usr/bin/env python3

import time
import hashlib
import http.server
import cgi

PORT = 6789

def getSeed(divider = 2):
    currentTime = int(time.time())
    flattenedTime = currentTime - (currentTime % divider)
    h = hashlib.new('ripemd160')
    h.update(str(flattenedTime).encode('utf-8'))
    return h.hexdigest()

def getFactors(seed):
    a = int(seed[9:12],16) + 7
    b = int(seed[15:18], 16) + 8
    return (a, b)

class DccHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        (a, b) = getFactors(getSeed())

        message = "<html><head><title>Dark Science Code Contest - January 2014</title></head><body>"
        message += "<p>What is the answer to " + str(a) + " x " + str(b) + " ?</p>"
        message += "<p><form action=\"\" method=\"post\"><input type=\"text\" name=\"answer\" />"
        message += "<input type=\"submit\" value=\"Submit\" /></form></p>"
        message += "</body></html>"

        self.wfile.write(message.encode('utf-8'))

    def do_POST(self):
        ctype, pdict = cgi.parse_header(self.headers['content-type'])
        if ctype == 'multipart/form-data':
            postvars = cgi.parse_multipart(self.rfile, pdict)
        elif ctype == 'application/x-www-form-urlencoded':
            length = int(self.headers['content-length'])
            postvars = cgi.parse_qs(self.rfile.read(length), keep_blank_values=1)
        else:
            postvars = {}

        answer = int(postvars["answer".encode('utf-8')][0])
        (a, b) = getFactors(getSeed())
        
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        message = "<html><head><title>Dark Science Code Contest - January 2014</title></head><body>"
        if (a * b) == answer:
            message += "Correct"
            self.log_message("Correct")
        else:
            message += "Wrong"
            self.log_message("Wrong")
        message += "</body></html>"

        self.wfile.write(message.encode('utf-8'))

httpd = http.server.HTTPServer(('', PORT), DccHandler)
httpd.serve_forever()
