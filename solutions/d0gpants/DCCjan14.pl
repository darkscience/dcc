#!/usr/bin/perl

$|=1; # because perl: buffer ALL the prints!

use strict;
use warnings;
use Time::HiRes qw(usleep);
use LWP::UserAgent;

sub getFreshSum
{
	my ($host, $tmpsum, $ua) = @_;
	my $resp = $ua->get($host);
	if($resp->is_success)
	{
		my $page = $resp->decoded_content;
		my @eqsplit = split(' ', $page);
		my $sum = $eqsplit[11] * $eqsplit[13];
		print("New: $sum : Old: $tmpsum\n");
		print("Fresh!\n") if($sum != $tmpsum and $tmpsum);
		usleep(200000); #results seem to vary per call but even though its single-threaded perl on a netbook
				#it can be a tad floody without sleeping.
		return getFreshSum($host, $sum, $ua) if(($tmpsum == $sum) or not $tmpsum);
			# call getFreshSum again if value isn't fresh or first call, otherwise...
		return $sum;
	} 
	else	
		{ die $resp->status_line }
	
}

sub postAnswer
{
	my ($host,$sum,$ua) = @_;
	my $resp = $ua->post($host, {'answer' => $sum});
	if($resp->is_success)
		{ return $resp->decoded_content }
	else
		{ die $resp->status_line }

}


my $ua = LWP::UserAgent->new;
$ua->timeout(10);
$ua->env_proxy;

my $host = "http://directus.darkscience.net:6789";
my $sum = 0;
my $resp = '';

print("Getting fresh answer...\n");
$sum = getFreshSum($host, $sum, $ua);

print("\nPosting: $sum\n");
$resp = postAnswer($host, $sum, $ua);

if ($resp =~ m/Correct/)
	{ print("$sum was Correct. :>\n") }
else 
	{ print("$sum was Wrong.\n Either you are unlucky or you have a pants connection\n") }
