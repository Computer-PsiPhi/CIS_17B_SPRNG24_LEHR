<?php
session_start();
include 'DBconnect.php';

if (!isset($_SESSION['password']) || $_SESSION['type'] !== 'admin') {
    echo "Unauthorized access!";
    exit;
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Administrator Menu</title>
    <style>
        body {
            font-family: Arial, sans-serif;
        }
        .container {
            text-align: center;
            margin-top: 50px;
        }
        .menu-button {
            background-color: #007bff;
            color: white;
            padding: 15px 32px;
            text-align: center;
            font-size: 16px;
            margin: 10px;
            cursor: pointer;
            border: none;
            border-radius: 5px;
        }
        .menu-button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Administrator Menu</h1>
        <form method="post" action="">
            <button type="submit" name="edit_users" class="menu-button">Edit Users</button>
            <button type="submit" name="edit_store" class="menu-button">Edit Store</button>
              <button type="submit" name="log_out" class="menu-button">Log-out</button>
        </form>

        <?php
        if ($_SERVER['REQUEST_METHOD'] == 'POST') {
            if (isset($_POST['edit_users'])) {
                // Redirect to the edit users page
                header('Location: admin_page.php');
                exit;
            } elseif (isset($_POST['edit_store'])) {
                // Redirect to the edit store page
                header('Location: edit_store.php');
                exit;
            } elseif (isset($_POST['log_out'])) {
                // Redirect to the edit store page
                header('Location: logout.php');
                exit;
            }
        }
        ?>
    </div>
</body>
</html>
