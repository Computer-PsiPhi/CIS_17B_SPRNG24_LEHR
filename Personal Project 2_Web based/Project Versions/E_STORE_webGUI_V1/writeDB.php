<?php
include 'DBconnect.php';

$id =1;
$name = "Bacon";
$price = 69.99;

$stmt = $conn->prepare("INSERT INTO entity_items (item_id, name, price) VALUES (?, ?, ?)");
$stmt->bind_param("isd",$id, $name, $price);

if ($stmt->execute()) {
    echo "New record created successfully";
} else {
    echo "Error: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>
