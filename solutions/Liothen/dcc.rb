#!/usr/bin/env ruby
########################
### Requirements
## Ruby
## gem install mechanize
########################
# Setup
require 'mechanize'
agent = Mechanize.new

# Open source site
source = agent.get('http://directus.darkscience.net:6789/')

# Find the problem, There are only two groups of numbers then convert the array returned into integers
problem = source.at("p").to_html.scan(/\d+/).map!(&:to_i)

# Grab the form from the source
form = source.form()

# Inject the answer
form.answer = problem.inject(:*)

# Submit and record result
agent.submit(form, form.buttons.first)
result = agent.submit(form, form.buttons.first)

# Make pretty
puts "Solution for #{problem.join(' x ')} is #{problem.inject(:*)} (#{result.at("body").content.to_s}!)"


## Liothen
### Still working on rust version but rust was compiling version 0.9 and i wanted to do something 