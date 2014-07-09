<?php
/* version 1: without using any php extensions. */
/* WARNING: Make sure to comment out one of these to variants before executing. */
preg_match('/([0-9]{1,4}) x ([0-9]{1,4})/', file_get_contents('http://directus.darkscience.net:6789/'), $res);
if(is_array($res)) { $product = $res[1]*$res[2]; }

$c = http_build_query(array('answer' => $product));

$s = fsockopen('directus.darkscience.net', 6789);
fwrite($s, "POST / HTTP/1.1\r\n");
fwrite($s, "Host: directus.darkscience.net\r\n");
fwrite($s, "Content-Type: application/x-www-form-urlencoded\r\n");
fwrite($s, "Content-Length: " . strlen($c) . "\r\n");
fwrite($s, "Connection: close\r\n");
fwrite($s, "\r\n");
fwrite($s, $c);

$o = '';
while(!feof($s)) { $o .= fgets($s, 1024); }
fclose($s);

if(preg_match('/Correct/', $o)) { echo 'Correct'; }else { echo 'Wrong'; }





/* version 2: using the cURL extension */
preg_match('/([0-9]{1,4}) x ([0-9]{1,4})/', file_get_contents('http://directus.darkscience.net:6789/'), $res);
if(is_array($res)) { $product = $res[1]*$res[2]; }

$c = http_build_query(array('answer' => $product));

$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, 'http://directus.darkscience.net:6789/');
curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    'Host: directus.darkscience.net',
    'Content-Type: application/x-www-form-urlencoded',
    'Content-Length: ' . strlen($c),
    'Connection: close'
));
curl_setopt($ch, CURLOPT_POST, true);
curl_setopt($ch, CURLOPT_POSTFIELDS, $c);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

$out = curl_exec($ch);
curl_close($ch);

if(strstr($out, 'Correct')) { echo 'Correct!'; }else { echo 'Wrong.'; }