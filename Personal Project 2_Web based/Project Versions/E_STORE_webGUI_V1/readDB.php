<?php
include 'DBConnect.php';

$sql = "SELECT item_id, name, price FROM entity_items";
$result = $conn->query($sql);

// Read contents from database and display 
 echo "<br>";
if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
       
        echo "Item ID: " . $row["item_id"] . " - Name: " . $row["name"] . " - Price: " . $row["price"] . "<br>";
    }
} else {
    echo "0 results";
}

$conn->close();
?>
