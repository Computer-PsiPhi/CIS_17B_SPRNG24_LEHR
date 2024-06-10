<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Store Data Insertion</title>
    <style>
        body {
            text-align: center;
        }
        ul {
            display: inline-block;
            text-align: left;
        }
    </style>
</head>
<body>
    <h1>Data Insertion Status</h1>
    <?php
    include 'DBconnect.php';

    // Create a connection
    $conn = new mysqli($servername, $username, $password, $dbname);

    // Check the connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 

    // Function to fetch and display current items in the database
    function displayCurrentItems($conn) {
        $result = $conn->query("SELECT item_id, name, price FROM items");
        if ($result->num_rows > 0) {
            echo "<h2>Current Items in Database:</h2>";
            echo "<ul>";
            while ($row = $result->fetch_assoc()) {
                echo "<li>ID: " . $row["item_id"]. " - Name: " . $row["name"]. " - Price: " . number_format((double)$row["price"], 2). "</li>";
            }
            echo "</ul>";
        } else {
            echo "<p>No items found in the database.</p>";
        }
    }

    // Function to insert items into the database
    function insertItems($conn, $itemsArray) {
        $stmt = $conn->prepare("INSERT INTO items (item_id, name, price) VALUES (?, ?, ?)");
        if (!$stmt) {
            echo "Prepare failed: (" . $conn->errno . ") " . $conn->error;
            return;
        }
        $stmt->bind_param("isd", $id, $name, $price);

        foreach ($itemsArray as $item) {
            $id = $item['id'];
            $name = $item['name'];
            $price = $item['price'];
            if (!$stmt->execute()) {
                echo "Error: (" . $stmt->errno . ") " . $stmt->error;
            }
        }

        $stmt->close();
    }

    // Check if the items table is empty
    $result = $conn->query("SELECT COUNT(*) as count FROM items");
    $row = $result->fetch_assoc();
    if ($row['count'] == 0) {
        // Table is empty, insert data from the cookie
        if (isset($_COOKIE['products'])) {
            $itemsJson = urldecode($_COOKIE['products']);
            $itemsArray = json_decode($itemsJson, true);

            // Display the items found in the cookie
            echo "<h2>Items Found in Cookie:</h2>";
            echo "<ul>";
            foreach ($itemsArray as $item) {
                echo "<li>ID: {$item['id']}, Name: {$item['name']}, Price: " . number_format($item['price'], 2) . "</li>";
            }
            echo "</ul>";

            // Insert items into the database
            insertItems($conn, $itemsArray);

            echo "<p>Items inserted successfully!</p>";

            // Display updated items in the database
            displayCurrentItems($conn);
        } else {
            echo "<p>No items found in cookie. Please load the items first.</p>";
        }
    } else {
        echo "<p>JSON to COOKIES to Items Database: Success.</p>";

        // Display current items in the database
        displayCurrentItems($conn);
    }

    // Close the database connection
    $conn->close();
    ?>
</body>
</html>
