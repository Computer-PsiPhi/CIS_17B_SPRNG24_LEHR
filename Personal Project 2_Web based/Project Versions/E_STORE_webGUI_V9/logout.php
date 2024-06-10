<?php
session_start();

// Calculate the total time the user was logged in
if (isset($_COOKIE['login_time'])) {
    $login_time = $_COOKIE['login_time'];
    $logout_time = time();
    $total_time = $logout_time - $login_time;
    $total_convert = rawurlencode(timeElapsed($total_time)); // Convert the time to a readable format and URL encode it
}

// Destroy the session
session_destroy();

// Redirect to login page with total time as a query parameter
header("Location: login.php?total_time={$total_convert}");
exit;

// Function to convert time in seconds to a readable format
function timeElapsed($seconds) {
    $minutes = floor($seconds / 60);
    $seconds = $seconds % 60;
    $hours = floor($minutes / 60);
    $minutes = $minutes % 60;
    $days = floor($hours / 24);
    $hours = $hours % 24;

    $time = '';
    if ($days > 0) $time .= $days . ' days ';
    if ($hours > 0) $time .= $hours . ' hours ';
    if ($minutes > 0) $time .= $minutes . ' minutes ';
    if ($seconds > 0) $time .= $seconds . ' seconds';

    return $time;
}
?>
