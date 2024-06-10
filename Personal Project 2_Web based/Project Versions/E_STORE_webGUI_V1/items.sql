CREATE DATABASE shopping_cart;

USE shopping_cart;

CREATE TABLE products (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    image VARCHAR(255) NOT NULL
);

CREATE TABLE cart (
    id INT AUTO_INCREMENT PRIMARY KEY,
    product_id INT NOT NULL,
    quantity INT NOT NULL,
    session_id VARCHAR(255) NOT NULL,
    FOREIGN KEY (product_id) REFERENCES products(id)
);
