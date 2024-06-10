<?php
include 'DBconnect.php';
session_start();

// Check if the user is logged in using session
if (!isset($_SESSION['username'])) {
    // Redirect to login page if the user is not logged in
    header("Location: login.php");
    exit;
}

$user = null;
if (isset($_SESSION["username"])) {
    // Sanitize the input to prevent SQL injection
    $username = $conn->real_escape_string($_SESSION["username"]);
    
    // Construct the SQL query
    $sql = "SELECT * FROM users WHERE username = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $username);
    $stmt->execute();
    $result = $stmt->get_result();

    // Check if any rows are returned
    if ($result->num_rows > 0) {
        // Fetch the user data
        $user = $result->fetch_assoc();
    }

    // Close the statement and connection
    $stmt->close();
    $conn->close();
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Store</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <style>
        .total {
            display: none; 
            font-size: 24px; 
            font-weight: bold; 
            color: #ffffff; 
            text-align: center; 
            margin: 20px 0; 
        }
        .user-name {
            font-size: 16px;
            font-weight: bold;
            color: #ffff;
            margin-right: 20px;
        }
        .icon-cart {
            display: flex;
            flex-direction: column;
            align-items: center;
            margin-right: 20px;
        }
        .cart-container {
            display: flex;
            align-items: center;
        }
        .header-right {
            display: flex;
            align-items: center;
            justify-content: flex-end;
            gap: 10px;
        }
        .button {
            background-color: #007bff;
            color: white;
            border: none;
            padding: 10px 20px;
            cursor: pointer;
            text-decoration: none;
            display: inline-block;
            text-align: center;
        }
        .logout-button {
            background-color: #f44336;
            color: white;
            border: none;
            padding: 10px 20px;
            cursor: pointer;
        }
        .logout-button a {
            color: white;
            text-decoration: none;
        }
        header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 20px;
            background-color: #333;
            color: white;
        }
    </style>
    <header>
        <div class="title">Store Items</div>
        <div class="header-right">
            <div class="cart-container">
                <span class="user-name">
                    <?php if(isset($user)): ?>
                        <?php echo htmlspecialchars($user["name"]); ?>
                    <?php endif; ?>
                </span>
                <div class="icon-cart">
                    <svg aria-hidden="true" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 18 20" width="24" height="24">
                        <path stroke="currentColor" stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 15a2 2 0 1 0 0 4 2 2 0 0 0 0-4Zm0 0h8m-8 0-1-4m9 4a2 2 0 1 0 0 4 2 2 0 0 0 0-4Zm-9-4h10l2-7H3m2 7L3 4m0 0-.792-3H1"/>
                    </svg>
                    <span>0</span>
                </div>
            </div>
            <?php if(isset($user)): ?>
                <button class="logout-button"><a href="logout.php">Log-out</a></button>
            <?php else: ?>
                <a class="button" href="login.php">Log-in</a>
                <a class="button" href="signup.php">Sign-up</a>
            <?php endif; ?>
        </div>
    </header>
    
    <div class="container">
        <div class="products-wrapper">
            <div class="listProduct"></div>
        </div>
    </div>
    <div class="cartTab">
        <h1>Shopping Cart</h1>
        <div class="listCart"></div>
        <div class="btn">
            <button class="close">CLOSE</button>
            <button class="checkOut">Check Out</button>
        </div>
        <div class="total"></div>
    </div>
    <script src="store.js"></script>
</body>
</html>
