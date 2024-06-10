<?php
session_start();
include 'DBconnect.php';

if (!isset($_SESSION['password']) && $_SESSION['type'] !== 'admin') {
    echo "Unauthorized access!";
    exit;
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Admin Page</title>
    <style>
        .logout-button {
            position: absolute;
            top: 20px;
            right: 50px;
        }
    </style>
</head>
<body>
    <div class="logout-button">
        <button><a href="logout.php">Log-out</a></button>
    </div>
    
    <h1>Welcome <?php echo htmlspecialchars($_SESSION['name']); ?></h1>
  

    <h2 id="edit-user">Edit User Information</h2>
    <form method="post" action="edit_user.php">
        <label for="search_username">Current Username:</label>
        <input type="text" name="search_username" id="search_username" required>
   <br></br>
        <label for="new_username">New Username:</label>
        <input type="text" name="new_username" id="new_username">
           <br></br>
        <label for="new_name">New Name:</label>
        <input type="text" name="new_name" id="new_name">
           <br></br>
        <label for="new_email">New Email:</label>
        <input type="email" name="new_email" id="new_email">
           <br></br>
        <label for="new_password">New Password:</label>
        <input type="password" name="new_password" id="new_password">
        <br></br>
        <button type="submit">Update User Info</button>
    </form>
</body>
</html>
