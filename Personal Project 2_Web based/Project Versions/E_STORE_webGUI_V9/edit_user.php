<?php
session_start();
include 'DBconnect.php';

header('Content-Type: application/json');

// Ensure no previous output
ob_clean();

if (!isset($_SESSION['password']) || $_SESSION['type'] !== 'admin') {
    echo json_encode(['success' => false, 'error' => 'Unauthorized access!']);
    exit;
}

$response = ['success' => false, 'error' => ''];

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (isset($_POST["search_user"])) {
        $search_user = $conn->real_escape_string($_POST["search_user"]);
        $new_user = isset($_POST["new_user"]) ? $conn->real_escape_string($_POST["new_user"]) : null;
        $new_name = isset($_POST["new_name"]) ? $conn->real_escape_string($_POST["new_name"]) : null;
        $new_email = isset($_POST["new_email"]) ? $conn->real_escape_string($_POST["new_email"]) : null;
        $new_pass = isset($_POST["new_pass"]) ? password_hash($_POST["new_pass"], PASSWORD_BCRYPT) : null;

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
                $response['success'] = true;
            } else {
                $response['error'] = "Error updating user information: " . $stmt->error;
            }
            $stmt->close();
        } else {
            $response['error'] = "Nothing to update.";
        }
    }

    if (isset($_POST["delete_user"])) {
        $delete_user = $conn->real_escape_string($_POST["delete_user"]);
        $sql = "DELETE FROM users WHERE username=?";
        $stmt = $conn->prepare($sql);
        $stmt->bind_param("s", $delete_user);
        if ($stmt->execute()) {
            $response['success'] = true;
        } else {
            $response['error'] = "Error deleting user: " . $stmt->error;
        }
        $stmt->close();
    } else {
        $response['error'] = 'Delete user parameter missing.';
    }
} else {
    $response['error'] = 'Invalid request method.';
}

echo json_encode($response);
$conn->close();
?>
