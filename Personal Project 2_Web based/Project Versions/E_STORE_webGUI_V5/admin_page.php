<?php
session_start();
include 'DBconnect.php';

if (!isset($_SESSION['password']) || $_SESSION['type'] !== 'admin') {
    echo "Unauthorized access!";
    exit;
}

// Fetch all non-admin users from the database
$sql = "SELECT username, name, email FROM users WHERE type != 'admin'";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html>
<head>
    <title>Admin Page</title>
    <style>
        body {
            font-family: Arial, sans-serif;
        }
        .container {
            text-align: center;
            margin-top: 50px;
        }
        .form-container {
            margin: 20px auto;
            width: 300px;
            text-align: left;
        }
        .form-container input, .form-container button {
            width: 100%;
            padding: 10px;
            margin: 5px 0;
        }
        .users-list {
            margin: 20px auto;
            width: 80%;
        }
        .users-list table {
            width: 100%;
            border-collapse: collapse;
        }
        .users-list th, .users-list td {
            border: 1px solid #ddd;
            padding: 8px;
        }
        .users-list th {
            background-color: #f2f2f2;
        }
        .logout-button, .menu-button {
            background-color: #2196F3;
            color: white;
            padding: 10px 20px;
            text-align: center;
            font-size: 16px;
            margin: 10px;
            cursor: pointer;
            border: none;
            border-radius: 5px;
            text-decoration: none;
        }
        .logout-button:hover, .menu-button:hover {
            background-color: #0b7dda;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Admin Page</h1>
        <div class="form-container">
            <h2>Edit User Information</h2>
            <form method="post" action="edit_user.php">
                <input type="text" name="search_user" placeholder="Current Username" required>
                <input type="text" name="new_user" placeholder="New Username">
                <input type="text" name="new_name" placeholder="New Name">
                <input type="email" name="new_email" placeholder="New Email">
                <input type="password" name="new_pass" placeholder="New Password">
                <button type="submit">Update User Info</button>
            </form>
        </div>
        <div class="users-list">
            <h2>All Users</h2>
            <table>
                <thead>
                    <tr>
                        <th>Name</th>
                        <th>Username</th>
                        <th>Email</th>
                    </tr>
                </thead>
                <tbody>
                    <?php
                    if ($result->num_rows > 0) {
                        while ($row = $result->fetch_assoc()) {
                            echo "<tr>
                                    <td>{$row['name']}</td>
                                    <td>{$row['username']}</td>
                                    <td>{$row['email']}</td>
                                  </tr>";
                        }
                    } else {
                        echo "<tr><td colspan='3'>No users found</td></tr>";
                    }
                    $conn->close();
                    ?>
                </tbody>
            </table>
        </div>
        <div>
            <form method="post" action="logout.php" style="display:inline;">
                <button type="submit" class="logout-button">Logout</button>
            </form>
            <a href="admin_menu.php" class="menu-button">Back to Admin Menu</a>
        </div>
    </div>
</body>
</html>
