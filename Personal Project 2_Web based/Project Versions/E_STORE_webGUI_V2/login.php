<?php
include 'DBconnect.php';
echo "<br>";
$not_good = false;

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $username = $conn->real_escape_string($_POST["username"]);
    $password = $_POST["password"];

    $sql = "SELECT * FROM users WHERE username = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $username);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows === 0) {
        $not_good = true;
    } else {
        $user = $result->fetch_assoc();

        if (password_verify($password, $user['password'])) {
            echo "Login successful";
            session_start();
            session_regenerate_id();
            $_SESSION['user_id'] = $user['id'];
            $_SESSION['username'] = $user['username'];
            $_SESSION['password'] = $user['password'];
            $_SESSION['name'] = $user['name'];
            $_SESSION['type'] = $user['type'];

            if ($user['type'] === 'admin') {
                header("Location: admin_page.php");
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
    </form>
</body>
</html>
