<?php
// DBconnect.php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "estore_db";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

echo"estore project connection successful";

//
//$servername = "localhost";
//$username = "root";
//$password = "";
//$dbname = "estore_db";
//
//// Create connection
//$conn = new mysqli($servername, $username, $password, $dbname);
//
//
//if($conn->connect_errno){
//    die("Connection failed ". $conn->connect_error);
//}
//
//echo nl2br("estore project connection successful");
//
//return $conn;

?>
