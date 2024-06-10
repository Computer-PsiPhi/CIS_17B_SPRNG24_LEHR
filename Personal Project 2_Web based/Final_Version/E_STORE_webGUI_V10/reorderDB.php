<?php
include 'DBconnect.php';


$conn->query("SET FOREIGN_KEY_CHECKS = 0");

// Update item_id to be sequential
$update_ids = "SET @count = 0; 
               UPDATE entity_items SET item_id = @count:= @count + 1 ORDER BY item_id";

if ($conn->multi_query($update_ids) === TRUE) {
    echo nl2br("\nItem IDs updated successfully");
 
    while ($conn->more_results() && $conn->next_result());
} else {
    echo "Error updating item IDs: " . $conn->error;
}

// Reset AUTO_INCREMENT
$reset_ai = "ALTER TABLE entity_items AUTO_INCREMENT = 1";

if ($conn->query($reset_ai) === TRUE) {
    echo nl2br("\nAUTO_INCREMENT reset successfully");
} else {
    echo "Error resetting AUTO_INCREMENT: " . $conn->error;
}


$conn->query("SET FOREIGN_KEY_CHECKS = 1");

$conn->close();
?>
