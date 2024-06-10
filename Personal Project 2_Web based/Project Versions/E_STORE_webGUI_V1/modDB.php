<?php
include 'DBconnect.php';

$item_id = 3; // ID of the item to update
$new_price = 19.99;
$new_name = 'Jacket';

$stmt = $conn->prepare("UPDATE entity_items SET name = ?, price = ? WHERE item_id = ?");
$stmt->bind_param("sdi", $new_name, $new_price,$item_id);

if ($stmt->execute()) {
    echo nl2br("\nRecord updated successfully");
    
} else {
    echo "Error: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>
