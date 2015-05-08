# Darkscience Code Contest

## Current contest: January 2014 - Timed Product
The current DCC assignment consists of creating an application that does the
following:

    1. Retrieve formula from this page. (No longer up, see `organisation/server.py`)
    2. Calculate the product.
    3. Submit formula on the above page using a POST request.
    4. Display whether answer was accepted or not (human-readable).

The formula is global and changes every two seconds. You do not need to
implement any cookie handling. The webserver on which the above page is
hosted was specifically created for this challenge, do not attempt to abuse
it.

Good luck!

## Summary

The Darkscience Code Contest, or DCC for short, is a contest organized by and
for the Darkscience community. The contest is held on a per-month basis. A new
assignment is given each first Monday of the month and submissions are due
before each fourth Monday of the month. Concrete dates will be present in the
Current contest description.

## General rules
Please refer to `RULES.md`.

## Instructions
During a contest, the master branch will contain all the files related to that
assignment. In order to make a submission, do the following:

   - Fork the master branch of the dcc repository
   - In the `solutions` directory, create a directory with your nickname
   - Work on your solution within that directory
   - When finished, create a pull request against the official dcc repository

If you create your pull request before the contest is over and do not violate
any rules, your submission should be accepted by us into the master branch. As
long as the contest is not over yet, you are allowed to make additional changes
and pull requests, although we'd like to ask you to keep these to a minimum.

Once the judging period commences, the contents of the solutions directory are
moved to a new branch created for that assignment. Winners will be made visible
in master until a new contest starts, afterwards this information will be moved
into the according branch for there to stay.

## Previous contests
Month         | Assignment    | Winner     | Branch
--------------|---------------|------------|------------------------------------------------------
December 2013 | Quine         | *whoami*   | [Dec13](https://github.com/darkscience/dcc/tree/Dec13)
October 2013  | Game of Life  | *MrDownNL* | [Oct13](https://github.com/darkscience/dcc/tree/Oct13)

## Contact
If you have any questions regarding the contest feel free to join #dcc on
irc.darkscience.net:6697 (SSL). Current organisers/judges:

   - Derecho
   - Liothen
