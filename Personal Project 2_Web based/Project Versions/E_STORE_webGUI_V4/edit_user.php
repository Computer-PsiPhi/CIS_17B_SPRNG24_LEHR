<?php
session_start();
include 'DBconnect.php';

if (!isset($_SESSION['password']) || $_SESSION['type'] !== 'admin') {
    echo "Unauthorized access!";
    exit;
}

$update_success = false;

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $search_user = $conn->real_escape_string($_POST["search_user"]);
    $new_user = isset($_POST["new_user"]) ? $conn->real_escape_string($_POST["new_user"]) : null;
    $new_name = isset($_POST["new_name"]) ? $conn->real_escape_string($_POST["new_name"]) : null;
    $new_email = isset($_POST["new_email"]) ? $conn->real_escape_string($_POST["new_email"]) : null;
    $new_pass = isset($_POST["new_pass"]) ? password_hash($_POST["new_pass"], PASSWORD_BCRYPT) : null;

    // Build the SQL query dynamically
    $update_fields = [];
    if ($new_user) $update_fields[] = "username='$new_user'";
    if ($new_name) $update_fields[] = "name='$new_name'";
    if ($new_email) $update_fields[] = "email='$new_email'";
    if ($new_pass) $update_fields[] = "password='$new_pass'";

    if (count($update_fields) > 0) {
        $sql = "UPDATE users SET " . implode(", ", $update_fields) . " WHERE username=?";
        $stmt = $conn->prepare($sql);
        $stmt->bind_param("s", $search_user);
        if ($stmt->execute()) {
            $update_success = true;
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
    <script>
        function refreshPage() {
            if (<?php echo $update_success ? 'true' : 'false'; ?>) {
                alert('User information updated successfully!');
                window.location.href = 'admin_page.php'; // Redirect to the admin page after update
            }
        }
    </script>
</head>
<body onload="refreshPage()">
    <a href="admin_menu.php">Back to Admin Page</a>
</body>
</html>
