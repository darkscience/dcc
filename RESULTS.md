# Darkscience Code Contest
## Participants
The winner of this contest is: *whoami*.
Congratulations!

All participants:

  - whoami
  - Mantis
  - MrDownNL

## Submissions
### whoami
Submission::

    <?php

    $code = '<?php

    $code = \'\';

    $rcode = str_replace(chr(39), chr(92) . chr(39), $code);
    $code  = str_replace(\'$code = \' . chr(39) . chr(39) . \';\', \'$code = \' . chr(39) . $rcode . chr(39) . \';\', $code);

    print $code . PHP_EOL;';

    $rcode = str_replace(chr(39), chr(92) . chr(39), $code);
    $code  = str_replace('$code = ' . chr(39) . chr(39) . ';', '$code = ' . chr(39) . $rcode . chr(39) . ';', $code);

    print $code . PHP_EOL;


With 8 effective lines and 427 effective characters, this submission is the
largest of all three. However, I was pleasantly surprised in having difficulty
finding a similar PHP quine on the internet. The operation of the quine is easy
to grasp and very likely to work in other languages as well. I also like the
fact that the script works despite the missing endtag.

### Mantis
Submission::

    <?php
    echo str_replace(chr(42), 'PD9waHAKZWNobyBzdHJfcmVwbGFjZShjaHIoNDIpLCAnKicsIGJhc2U2NF9kZWNvZGUoJyonKSk7Cj8+Cg==', base64_decode('PD9waHAKZWNobyBzdHJfcmVwbGFjZShjaHIoNDIpLCAnKicsIGJhc2U2NF9kZWNvZGUoJyonKSk7Cj8+Cg=='));
    ?>

Mantis submitted a much shorter PHP quine that effectively consists of a single
line. While I find this a nice solution to the quine problem, it bears a strong
resemblence to another PHP quine that can be found on the internet. This
submission does have an improvement to reduce the linecount (but increase the
amount of characters). Because of the uncertainty of the origin of this quine,
it cannot win this contest. The technique used in this quine is definately
interesting and I thank Mantis for his submission.

### MrDownNL
Submission::

    a='a=%r;print(a%%a)';print(a%a)

Above you can see the shortest submission in this contest: a single line
consisting of merely 32 characters. The elegance of this quine is simply
stunning. Unfortunately this quine is easy to find on the internet and I can
say with high certainty that MrDownNL's input in this submission is minimal.
Nevertheless, it is an amazing quine and I'm glad I had the chance to see it
and learn about it's operation.
