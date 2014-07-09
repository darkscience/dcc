#!/usr/bin/perl

use LWP::Simple;

eval "print LWP::UserAgent->new()->post('http://directus.darkscience.net:6789', {'answer' => $1*$2})->decoded_content() =~ /(Correct|Wrong)/g;\n" if get("http://directus.darkscience.net:6789") =~ /([0-9]+) x ([0-9]+)/g