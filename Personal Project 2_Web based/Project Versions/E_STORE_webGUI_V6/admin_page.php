<?php
session_start();
include 'DBconnect.php';

if (!isset($_SESSION['password']) || $_SESSION['type'] !== 'admin') {
    echo "Unauthorized access!";
    exit;
}

// Fetch all  users from the database
function fetchUsers($conn) {
    $sql = "SELECT username, name, email FROM users WHERE type != 'admin'";
    $result = $conn->query($sql);

    $users = [];
    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            $users[] = $row;
        }
    }
    return $users;
}

$users = fetchUsers($conn);
$conn->close();
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
       
        .custom-alert {
            display: none;
            position: fixed;
            left: 50%;
            top: 50%;
            transform: translate(-50%, -50%);
            padding: 20px;
            background: white;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
            z-index: 1000;
            border: 1px solid #ddd;
            border-radius: 5px;
        }
        .custom-alert p {
            font-size: 16px;
            margin-bottom: 20px;
        }
        .custom-alert button {
            background-color: #2196F3;
            color: white;
            padding: 10px 20px;
            text-align: center;
            font-size: 16px;
            cursor: pointer;
            border: none;
            border-radius: 5px;
        }
        .custom-alert button:hover {
            background-color: #0b7dda;
        }
    </style>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script>
        function showAlert(message) {
            $('#custom-alert-message').text(message);
            $('#custom-alert').show();
        }

        $(document).ready(function() {
            $("#edit-form").on("submit", function(event) {
                event.preventDefault();
                $.ajax({
                    url: "edit_user.php",
                    type: "POST",
                    data: $(this).serialize(),
                    dataType: "json",
                    success: function(response) {
                        if (response.success) {
                             window.location.reload();
                           // showAlert("Operation successful!");
                        } else {
                            alert(response.error);
                        }
                    },
                    error: function(xhr, status, error) {
                        console.log("XHR Status:", status);
                        console.log("Error:", error);
                        console.log("Response Text:", xhr.responseText); 
                        alert("An error occurred: " + xhr.status + " " + xhr.statusText);
                    }
                });
            });

            $(document).on("submit", ".delete-form", function(event) {
                event.preventDefault();
                if (confirm("Are you sure you want to delete this user?")) {
                    $.ajax({
                        url: "edit_user.php",
                        type: "POST",
                        data: $(this).serialize(),
                        dataType: "json",
                        success: function(response) {
                            if (response.success) {
                               
                                window.location.reload();
                            } else {
                                alert(response.error);
                            }
                        },
                        error: function(xhr, status, error) {
                            console.log("XHR Status:", status);
                            console.log("Error:", error);
                            console.log("Response Text:", xhr.responseText); 
                            alert("An error occurred: " + xhr.status + " " + xhr.statusText);
                        }
                    });
                }
            });

            // Refresh the page when the alert button is clicked
            $('#custom-alert-button').on('click', function() {
                window.location.reload();
            });
        });
    </script>
</head>
<body>
    <div class="container">
        <h1>Admin Page</h1>
        <div class="form-container">
            <h2>Edit User Information</h2>
            <form id="edit-form" method="post">
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
            <table id="users-table">
                <thead>
                    <tr>
                        <th>Name</th>
                        <th>Username</th>
                        <th>Email</th>
                        <th>Action</th>
                    </tr>
                </thead>
                <tbody>
                    <?php
                    foreach ($users as $row) {
                        echo "<tr>
                                <td>{$row['name']}</td>
                                <td>{$row['username']}</td>
                                <td>{$row['email']}</td>
                                <td>
                                    <form class='delete-form' method='post'>
                                        <input type='hidden' name='delete_user' value='{$row['username']}'>
                                        <button type='submit' style='background-color:red; color:white; border:none; padding:5px 10px;'>Delete</button>
                                    </form>
                                </td>
                              </tr>";
                    }
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
    <!-- Custom alert box -->
    <div id="custom-alert" class="custom-alert">
        <p id="custom-alert-message"></p>
        <button id="custom-alert-button">OK</button>
    </div>
</body>
</html>
