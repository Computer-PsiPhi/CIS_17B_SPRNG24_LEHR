<?php
include 'DBconnect.php';

$item_id = 1; // ID of the item to delete

$stmt = $conn->prepare("DELETE FROM entity_items WHERE item_id = ?");
$stmt->bind_param("i", $item_id);

if ($stmt->execute()) {
    echo "Record deleted successfully";
} else {
    echo "Error: " . $stmt->error;
}

$stmt->close();
$conn->close();
?>
