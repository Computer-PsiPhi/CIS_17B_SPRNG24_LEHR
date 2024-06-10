<?php
session_start();
include 'DBconnect.php';

$session_id = session_id();
$sql = "SELECT * FROM cart WHERE session_id='$session_id'";
$result = $conn->query($sql);

$cart = array();
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        $cart[] = $row;
    }
}

echo json_encode($cart);

$conn->close();
?>
