<?php
include 'DBconnect.php';

$errorMessages = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Regular expressions
    $nameRegex = "/^[a-zA-Z\s]+$/";
    $usernameRegex = "/^[a-zA-Z0-9]{3,20}$/";
    $emailRegex = "/^[^\s@]+@[^\s@]+\.[^\s@]+$/";
    $passWordReg = "/[a-z]/i";
    $passWrdDig = "/[0-9]/";

    if (empty($_POST["name"]) || !preg_match($nameRegex, $_POST["name"])) {
        $errorMessages[] = "Name can't be empty and must contain only letters and spaces.";
    }

    if (empty($_POST["username"]) || !preg_match($usernameRegex, $_POST["username"])) {
        $errorMessages[] = "Username must be alphanumeric and between 3 to 20 characters.";
    }

    if (!filter_var($_POST["email"], FILTER_VALIDATE_EMAIL) || !preg_match($emailRegex, $_POST["email"])) {
        $errorMessages[] = "Enter a valid email.";
    }

    if (strlen($_POST["password"]) < 4 || !preg_match($passWordReg, $_POST["password"]) || !preg_match($passWrdDig, $_POST["password"])) {
        $errorMessages[] = "Password must be at least 4 characters long, contain at least one letter and one digit.";
    }

    if ($_POST["password"] !== $_POST["password_confirm"]) {
        $errorMessages[] = "Non-matching passwords.";
    }

    if (empty($errorMessages)) {
        $passHash = password_hash($_POST["password"], PASSWORD_DEFAULT);

        try {
            // Enable exceptions for mysqli
            mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);

            // Prepare and bind the SQL statement
            $stmt = $conn->prepare("INSERT INTO users (name, username, email, password) VALUES (?, ?, ?, ?)");
            $stmt->bind_param("ssss",
                $_POST["name"],
                $_POST["username"],
                $_POST["email"],
                $passHash
            );

            // Execute the statement
            if ($stmt->execute()) {
                header("Location: login.html");
                exit;
            }
        } catch (mysqli_sql_exception $e) {
            if ($e->getCode() === 1062) { // Error code for duplicate entry
                $errorMessages[] = "The username already exists. Please choose a different username.";
            } else {
                $errorMessages[] = "Error: " . $e->getMessage();
            }
        }

        $conn->close();
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Sign-up Page</title>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://unpkg.com/mvp.css">
    <script>
        function goTo() {
            window.location.href = 'login.php';
        }
    </script>
</head>
<body>
    <h1>Sign-up Page</h1>
    <?php if (!empty($errorMessages)): ?>
        <div style="color: red;">
            <ul>
                <?php foreach ($errorMessages as $message): ?>
                    <li><?php echo htmlspecialchars($message); ?></li>
                <?php endforeach; ?>
            </ul>
        </div>
    <?php endif; ?>
    <form action="signup.php" method="post" novalidate>
        <div>
            <label for="name">Name</label>
            <input type="text" id="name" name="name" value="<?php echo isset($_POST['name']) ? htmlspecialchars($_POST['name']) : ''; ?>">
        </div>
        <div>
            <label for="username">Username</label>
            <input type="text" id="username" name="username" value="<?php echo isset($_POST['username']) ? htmlspecialchars($_POST['username']) : ''; ?>">
        </div>
        <div>
            <label for="email">E-mail</label>
            <input type="email" id="email" name="email" value="<?php echo isset($_POST['email']) ? htmlspecialchars($_POST['email']) : ''; ?>">
        </div>
        <div>
            <label for="password">Password</label>
            <input type="password" id="password" name="password">
        </div>
        <div>
            <label for="password_confirm">Repeat Password</label>
            <input type="password" id="password_confirm" name="password_confirm">
        </div>
        <button>Sign-up</button>
        <button type="button" onclick="goTo()">Login</button>
    </form>
</body>
</html>
