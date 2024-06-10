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
      
           .admin-button {
            position: absolute;
            
            top: 20px;
            right: 120px;
        }
        .logout-button {
            position: absolute;
            top: 20px;
            right: 50px;
        }
        table {
            width: 100%;
            border-collapse: collapse;
        }
        table, th, td {
            border: 1px solid black;
        }
        th, td {
            padding: 8px;
            text-align: left;
        }
        th {
            background-color: #f2f2f2;
        }
    </style>
</head>
<body>
    <div class="logout-button">
        <button><a href="logout.php">Log-out</a></button>
    </div>
    
       <div class="Admin-button">
        <button><a href="admin_menu.php">Administrator Menu</a></button>
    </div>
   
    
    <h1>Welcome <?php echo htmlspecialchars($_SESSION['name']); ?></h1>

    <h2>All Users</h2>
    <table>
        <tr>
            <th>Name</th>
            <th>Username</th>
            <th>Email</th>
        </tr>
        <?php
        if ($result->num_rows > 0) {
            // Output data of each row
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
    </table>

    <h2 id="edit-user">Edit User Information</h2>
    <form method="post" action="edit_user.php">
        <label for="search_username">Current Username:</label>
        <input type="text" name="search_username" id="search_username" required>
        <br><br>
        <label for="new_username">New Username:</label>
        <input type="text" name="new_username" id="new_username">
        <br><br>
        <label for="new_name">New Name:</label>
        <input type="text" name="new_name" id="new_name">
        <br><br>
        <label for="new_email">New Email:</label>
        <input type="email" name="new_email" id="new_email">
        <br><br>
        <label for="new_password">New Password:</label>
        <input type="password" name="new_password" id="new_password">
        <br><br>
        <button type="submit">Update User Info</button>
    </form>
</body>
</html>
