<?php
$ch = curl_init();

// $postData = array(
//     'login' => 'acogneau',
//     'pwd' => 'secretpassword',
//     'redirect_to' => 'http://example.com',
//     'testcookie' => '1'
// );

curl_setopt_array($ch, array(
    CURLOPT_URL => 'http://yilinmiao.com/user_display.php',
    CURLOPT_HEADER => false,
    CURLOPT_RETURNTRANSFER => true,
    // CURLOPT_POST => true,
    // CURLOPT_POSTFIELDS => $postData,
    // CURLOPT_FOLLOWLOCATION => true,
    // CURLOPT_COOKIESESSION => true,
    // CUROPT_COOKIEJAR => 'cookie.txt'
));

$output = curl_exec($ch);
echo $output;

curl_close($ch);
?>
