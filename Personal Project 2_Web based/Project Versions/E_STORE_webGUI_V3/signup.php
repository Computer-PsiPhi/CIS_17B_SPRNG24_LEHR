<?php
include 'DBconnect.php';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    echo "<br>";
    if(empty($_POST["name"])){
        die("Name can't be empty");
    }

    if(!filter_var($_POST["email"], FILTER_VALIDATE_EMAIL)){
        die("Enter valid mail");
    }

    if(strlen($_POST["password"]) < 4){
        die("Password not long enough");
    }
    if(!preg_match("/[a-z]/i", $_POST["password"])){
        die("Password must contain at least one letter");
    }
    if(!preg_match("/[0-9]/", $_POST["password"])){
        die("Password must contain at least one digit");
    }

    if($_POST["password"] !== $_POST["password_confirm"]){
        die("Non-matching passwords");
    }

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
            echo "<br>";
            echo "The username already exists. Please choose a different username.";
        } else {
            echo "Error: " . $e->getMessage();
        }
    }

    $conn->close();
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
            window.location.href = 'index.php';
        }
    </script>
</head>
<body>
    <h1>Sign-up Page</h1>
    <form action="signup.php" method="post" novalidate>
        <div>
            <label for="name">Name</label>
            <input type="text" id="name" name="name">
        </div>
        <div>
            <label for="username">Username</label>
            <input type="text" id="username" name="username">
        </div>
        <div>
            <label for="email">E-mail</label>
            <input type="email" id="email" name="email">
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
          <button type="button" onclick="goTo()">To Store</button>
    </form>
</body>
</html>
