<?php
session_start();
include 'DBconnect.php';

if (!isset($_SESSION['password']) || $_SESSION['type'] !== 'admin') {
    echo "Unauthorized access!";
    exit;
}

// Load existing products
$products = json_decode(file_get_contents('products.json'), true);

// Function to save products to the JSON file
function saveProducts($products) {
    file_put_contents('products.json', json_encode($products, JSON_PRETTY_PRINT));
}

// Handle form submissions
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (isset($_POST['add_product'])) {
        $newProduct = [
            'id' => (int)$_POST['id'],
            'name' => $_POST['name'],
            'price' => (float)$_POST['price'],
            'image' => $_POST['image']
        ];
        $products[] = $newProduct;
        saveProducts($products);
        header('Location: edit_store.php');
        exit();
    } elseif (isset($_POST['delete_product'])) {
        $productId = (int)$_POST['id'];
        $products = array_filter($products, function($product) use ($productId) {
            return $product['id'] != $productId;
        });
        $products = array_values($products);  // Re-index array
        saveProducts($products);
        header('Location: edit_store.php');
        exit();
    } elseif (isset($_POST['modify_product'])) {
        $productId = (int)$_POST['id'];
        foreach ($products as &$product) {
            if ($product['id'] == $productId) {
                $product['name'] = $_POST['name'];
                $product['price'] = (float)$_POST['price'];
                $product['image'] = $_POST['image'];
                break;
            }
        }
        saveProducts($products);
        header('Location: edit_store.php');
        exit();
    } elseif (isset($_POST['logout'])) {
        session_destroy();
        header('Location: login.php');
        exit();
    }
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Edit Store</title>
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
        .products-list {
            margin: 20px auto;
            width: 80%;
        }
        .products-list table {
            width: 100%;
            border-collapse: collapse;
        }
        .products-list th, .products-list td {
            border: 1px solid #ddd;
            padding: 8px;
        }
        .products-list th {
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
        img {
            max-width: 50px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Edit Store</h1>
        <div class="form-container">
            <h2>Add Product</h2>
            <form method="post" action="">
                <input type="number" name="id" placeholder="ID" required>
                <input type="text" name="name" placeholder="Name" required>
                <input type="number" step="0.01" name="price" placeholder="Price" required>
                <input type="text" name="image" placeholder="image/#.png" required>
                <button type="submit" name="add_product">Add Product</button>
            </form>
        </div>
        <div class="form-container">
            <h2>Modify Product</h2>
            <form method="post" action="">
                <input type="number" name="id" placeholder="ID" required>
                <input type="text" name="name" placeholder="New Name">
                <input type="number" step="0.01" name="price" placeholder="New Price">
                <input type="text" name="image" placeholder="image/#.png">
                <button type="submit" name="modify_product">Modify Product</button>
            </form>
        </div>
        <div class="form-container">
            <h2>Delete Product</h2>
            <form method="post" action="">
                <input type="number" name="id" placeholder="ID" required>
                <button type="submit" name="delete_product">Delete Product</button>
            </form>
        </div>
        <div class="products-list">
            <h2>Current Products</h2>
            <table>
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Name</th>
                        <th>Price</th>
                        <th>Image</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($products as $product): ?>
                        <tr>
                            <td><?php echo htmlspecialchars($product['id']); ?></td>
                            <td><?php echo htmlspecialchars($product['name']); ?></td>
                            <td><?php echo htmlspecialchars($product['price']); ?></td>
                            <td><img src="<?php echo htmlspecialchars($product['image']); ?>" alt="<?php echo htmlspecialchars($product['name']); ?>"></td>
                        </tr>
                    <?php endforeach; ?>
                </tbody>
            </table>
        </div>
        <div>
            <form method="post" action="" style="display:inline;">
                <button type="submit" name="logout" class="logout-button">Logout</button>
            </form>
            <a href="admin_menu.php" class="menu-button">Back to Admin Menu</a>
        </div>
    </div>
</body>
</html>
