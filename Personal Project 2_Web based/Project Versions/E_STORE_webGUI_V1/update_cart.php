<?php
session_start();
include 'DBconnect.php';

$session_id = session_id();
$data = json_decode(file_get_contents("php://input"), true);

$sql = "DELETE FROM cart WHERE session_id='$session_id'";
$conn->query($sql);

foreach ($data['cart'] as $item) {
    $product_id = $item['product_id'];
    $quantity = $item['quantity'];
    $sql = "INSERT INTO cart (product_id, quantity, session_id) VALUES ('$product_id', '$quantity', '$session_id')";
    $conn->query($sql);
}

$conn->close();
?>
