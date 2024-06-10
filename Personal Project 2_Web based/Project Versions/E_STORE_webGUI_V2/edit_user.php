<?php
session_start();
include 'DBconnect.php';

 echo "<br>";
if (!isset($_SESSION['password']) && $_SESSION['type'] !== 'admin') {
    echo "Unauthorized access!";
    exit;
}

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $search_username = $conn->real_escape_string($_POST["search_username"]);
    $new_username = isset($_POST["new_username"]) ? $conn->real_escape_string($_POST["new_username"]) : null;
    $new_name = isset($_POST["new_name"]) ? $conn->real_escape_string($_POST["new_name"]) : null;
    $new_email = isset($_POST["new_email"]) ? $conn->real_escape_string($_POST["new_email"]) : null;
    $new_password = isset($_POST["new_password"]) ? password_hash($_POST["new_password"], PASSWORD_BCRYPT) : null;

    // Build the SQL query dynamically
    $update_fields = [];
    if ($new_username) $update_fields[] = "username='$new_username'";
    if ($new_name) $update_fields[] = "name='$new_name'";
    if ($new_email) $update_fields[] = "email='$new_email'";
    if ($new_password) $update_fields[] = "password='$new_password'";

   
    if (count($update_fields) > 0) {
        $sql = "UPDATE users SET " . implode(", ", $update_fields) . " WHERE username=?";
        $stmt = $conn->prepare($sql);
        $stmt->bind_param("s", $search_username);
        if ($stmt->execute()) {
            echo "User information updated successfully!";
        } else {
            echo "Error updating user information.";
        }
        $stmt->close();
    } else {
        echo "Nothing to update.";
    }
}

$conn->close();
?>
<!DOCTYPE html>
<html>
<head>
    <title>Update User Info</title>
</head>
<body>
    <a href="admin_page.php">Back to Admin Page</a>
</body>
</html>
