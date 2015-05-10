# Darkscience Code Contest

## Current contest
Recently while renovating the Science Museum in London, staff have discovered
a previously unknown asset. It appears that in the archives blueprints and demo
programs were present for one of the very first game consoles to exist.

The TGS, or Terrible Game System, as the retro console is called was briefly
released to the public but was increadibly badly received. The traumatic
experience has caused everyone from that time to simply forget that the device
ever existed.

This DCC assignment is a little different from the previous ones. Rather than
lasting a month, you will get a large part of the summer to work on your
submission.  This is done in order to accommodate for people with a busy
schedule, not because you need that much time. You may also consider to work in
a (small) team, however that is not a requirement and the assignment can be
done on your own just fine.

Your task consists of writing an emulator for the TGS based on the available
information in `blueprints.md`. It is completely up to you how advanced you
want to make the user interface, however you should support all the core
functionality of the TGS's processor and peripherals. Both demo programs have
also been read from their ROM cartridges and saved to `demo1.bin` and
`demo2.bin` respectively, which you can use to test your emulator.

There were also designs for a successor, the TGS2, but after the failure of the
TGS these designs were never implemented. Should you be bored, feel free to
implement the additional TGS2 features for a special award, independent of the
main contest results.

### Prizes
With this specific assignment, we'll be offering a few prizes for the
contestants finishing in the top 3.

   1. Besiege (DRM-free + Steam key), a large and a small Darkscience sticker
   2. A large and a small Darkscience sticker
   3. A large Darkscience sticker

Prizes are handed out per submission, any teams will have to figure out how to
share the prize.

### Help, this sounds way too hard!
Don't worry, it's actually not that hard at all. More likely, you're just not
familiar with some of the concepts involved. If so, use this as an opportunity
to learn something interesting! Here are a few links that might help you piece
a solution toghether:

   - Machine code: [Wikibooks - Machine code and processor instruction set](http://en.wikibooks.org/wiki/A-level_Computing/AQA/Computer_Components,_The_Stored_Program_Concept_and_the_Internet/Machine_Level_Architecture/Machine_code_and_processor_instruction_set)
   - Writing a Brainfuck interpreter: [Zac Stewart - Learning C++: A brainfuck interpreter](http://zacstewart.com/2013/09/15/learning-cpp-a-brainfuck-interpreter.html)
   - Writing a NES emulator: [Hackaday - How to write a program that functions like an NES CPU](http://hackaday.com/2012/10/12/emulators-101-how-to-write-a-program-that-functions-like-an-nes-cpu/)
   - 7-Segment display: [Wikipedia - Seven-segment display](http://en.wikipedia.org/wiki/Seven-segment_display)
   - If all else fails: [Plan B](http://www.floristrycourseonline.com/)

### Calendar

   - Start of assignment: 2015 May 11
   - End of submissions: 2015 Jul 12
   - Results: 2015 Jul 26

After the submission deadline has passed, a reference assembler and compiler
that were used during development of the demo programs will be released.

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
February 2014 | Steganography | *Liothen*  | [Feb14](https://github.com/darkscience/dcc/tree/Feb14)
January 2014  | Timed Product | *Fox*      | [Jan14](https://github.com/darkscience/dcc/tree/Jan14)
December 2013 | Quine         | *whoami*   | [Dec13](https://github.com/darkscience/dcc/tree/Dec13)
October 2013  | Game of Life  | *MrDownNL* | [Oct13](https://github.com/darkscience/dcc/tree/Oct13)

## Contact
If you have any questions regarding the contest feel free to join #dcc on
irc.darkscience.net:6697 (SSL). Current organisers/judges:

   - Derecho
   - Liothen
