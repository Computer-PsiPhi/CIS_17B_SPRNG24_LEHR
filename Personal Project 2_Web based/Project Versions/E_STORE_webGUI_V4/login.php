<?php
include 'DBconnect.php';
session_start();

echo "<br>";
$not_good = false;

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $user = $conn->real_escape_string($_POST["username"]);
    $pass = $_POST["password"];

    $sql = "SELECT * FROM users WHERE username = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $user);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows === 0) {
        $not_good = true;
    } else {
        $user_data = $result->fetch_assoc();

        if (password_verify($pass, $user_data['password'])) {
            echo "Login successful";
            session_start();
            session_regenerate_id();
            $_SESSION['user_id'] = $user_data['id'];
            $_SESSION['username'] = $user_data['username'];
            $_SESSION['password'] = $user_data['password'];
            $_SESSION['name'] = $user_data['name'];
            $_SESSION['type'] = $user_data['type'];

            // Set a cookie for the logged-in user
            setcookie("user_log", "true", time() + (86400 * 30), "/"); // 86400 = 1 day
            // Set a cookie to store the login time
            setcookie("login_time", time(), time() + (86400 * 30), "/"); // 86400 = 1 day

            if ($user_data['type'] === 'admin') {
                header("Location: admin_menu.php");
            } else {
                header("Location: index.php");
            }
            exit;
        } else {
            $not_good = true;
        }

        // Close the statement and connection
        $stmt->close();
        $conn->close();
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Log-in Page</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://unpkg.com/mvp.css"> 
    <script>
        function goTo() {
            window.location.href = 'signup.php';
        }
    </script>
</head>
<body>
    <h1> Login Page </h1>
    <?php if ($not_good): ?>
        <em>Invalid login</em>
    <?php endif; ?>

    <form method="post">
        <label for="username">Username</label>
        <input type="username" name="username" id="username">

        <label for="password">Password</label>
        <input type="password" name="password" id="password">

        <button>Log-in</button>      
        
        <button type="button" onclick="goTo()">Sign-up</button>
    </form>
</body>
</html>
