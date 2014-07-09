#!/usr/bin/ruby

require "net/http"
require "uri"

(a, b = Net::HTTP.get(URI.parse("http://directus.darkscience.net:6789")).scan(/([0-9]+) x ([0-9]+)/)[0]) and print /(Correct|Wrong)/.match(Net::HTTP.post_form(URI.parse("http://directus.darkscience.net:6789"), {"answer" => (a.to_i.send '*', b.to_i)}).body)