<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Shopping Cart</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <header>
        <div class="title">My Store</div>
        <div class="icon-cart">
            <span>0</span>
            🛒
        </div>
    </header>
    <div class="container">
        <div class="products-wrapper">
            <div class="listProduct"></div>
        </div>
    </div>
    <div class="cartTab">
        <button class="close">Close</button>
        <div class="listCart"></div>
        <div class="total">Total: $0.00</div>
        <button class="checkOut">Checkout</button>
    </div>

    <script>
        let listProductHTML = document.querySelector('.listProduct');
        let listCartHTML = document.querySelector('.listCart');
        let iconCart = document.querySelector('.icon-cart');
        let iconCartSpan = document.querySelector('.icon-cart span');
        let body = document.querySelector('body');
        let closeCart = document.querySelector('.close');
        let checkoutButton = document.querySelector('.checkOut');
        let totalDisplay = document.querySelector('.total');
        let products = [];
        let cart = [];

        iconCart.addEventListener('click', () => {
            body.classList.toggle('showCart');
        });
        closeCart.addEventListener('click', () => {
            body.classList.toggle('showCart');
            resetTotal();
        });

        checkoutButton.addEventListener('click', () => {
            checkoutCart();
        });

        const addDataToHTML = () => {
            if (products.length > 0) {
                products.forEach(product => {
                    let newProduct = document.createElement('div');
                    newProduct.dataset.id = product.id;
                    newProduct.classList.add('item');
                    newProduct.innerHTML = `
                        <img src="${product.image}" alt="${product.name}">
                        <h2>${product.name}</h2>
                        <div class="price">$${product.price}</div>
                        <button class="addCart">Add To Cart</button>`;
                    listProductHTML.appendChild(newProduct);
                });
            }
        };

        listProductHTML.addEventListener('click', (event) => {
            let positionClick = event.target;
            if (positionClick.classList.contains('addCart')) {
                let id_product = positionClick.parentElement.dataset.id;
                addToCart(id_product);
            }
        });

        const addToCart = (product_id) => {
            let positionThisProductInCart = cart.findIndex((value) => value.product_id == product_id);
            if (cart.length <= 0) {
                cart = [{
                    product_id: product_id,
                    quantity: 1
                }];
            } else if (positionThisProductInCart < 0) {
                cart.push({
                    product_id: product_id,
                    quantity: 1
                });
            } else {
                cart[positionThisProductInCart].quantity = cart[positionThisProductInCart].quantity + 1;
            }
            addCartToHTML();
            addCartToMemory();
        };

        const addCartToMemory = () => {
            fetch('update_cart.php', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ cart: cart })
            }).then(response => response.json())
              .then(data => {
                  console.log(data);
              });
            document.cookie = `listCart=${JSON.stringify(cart)}; path=/;`;
        };

        const addCartToHTML = () => {
            listCartHTML.innerHTML = '';
            let totalQuantity = 0;
            if (cart.length > 0) {
                cart.forEach(item => {
                    totalQuantity = totalQuantity + item.quantity;
                    let newItem = document.createElement('div');
                    newItem.classList.add('item');
                    newItem.dataset.id = item.product_id;

                    let positionProduct = products.findIndex((value) => value.id == item.product_id);
                    let info = products[positionProduct];
                    listCartHTML.appendChild(newItem);
                    newItem.innerHTML = `
                    <div class="image">
                            <img src="${info.image}">
                        </div>
                        <div class="name">
                        ${info.name}
                        </div>
                        <div class="totalPrice">$${info.price * item.quantity}</div>
                        <div class="quantity">
                            <span class="minus"><</span>
                            <span>${item.quantity}</span>
                            <span class="plus">></span>
                        </div>
                    `;
                });
            }
            iconCartSpan.innerText = totalQuantity;
        };

        listCartHTML.addEventListener('click', (event) => {
            let positionClick = event.target;
            if (positionClick.classList.contains('minus') || positionClick.classList.contains('plus')) {
                let product_id = positionClick.parentElement.parentElement.dataset.id;
                let type = 'minus';
                if (positionClick.classList.contains('plus')) {
                    type = 'plus';
                }
                changeQuantityCart(product_id, type);
            }
        });

        const changeQuantityCart = (product_id, type) => {
            let positionItemInCart = cart.findIndex((value) => value.product_id == product_id);
            if (positionItemInCart >= 0) {
                let info = cart[positionItemInCart];
                switch (type) {
                    case 'plus':
                        cart[positionItemInCart].quantity = cart[positionItemInCart].quantity + 1;
                        break;

                    default:
                        let changeQuantity = cart[positionItemInCart].quantity - 1;
                        if (changeQuantity > 0) {
                            cart[positionItemInCart].quantity = changeQuantity;
                        } else {
                            cart.splice(positionItemInCart, 1);
                        }
                        break;
                }
            }
            addCartToHTML();
            addCartToMemory();
        };

        const checkoutCart = () => {
            checkCart();
            let totalAmount = 0;
            cart.forEach(item => {
                let product = products.find(product => product.id == item.product_id);
                totalAmount += product.price * item.quantity;
            });
            totalDisplay.innerHTML = `Total: $${totalAmount.toFixed(2)}`;

            // Clear the cart
            cart = [];
            addCartToHTML();
            addCartToMemory();

            // Reset the cart quantity display
            iconCartSpan.innerText = '0';

            // Show the total amount
            totalDisplay.style.display = 'block';
        };

        const resetTotal = () => {
            totalDisplay.style.display = 'none';
        };

        const checkCart = () => {
            var cookieValue = document.cookie
                .split('; ')
                .find(row => row.startsWith('listCart='));
            if (cookieValue) {
                cart = JSON.parse(cookieValue.split('=')[1]);
            }
        };

        const initApp = () => {
            fetch('fetch_products.php')
                .then(response => response.json())
                .then(data => {
                    products = data;
                    addDataToHTML();

                    fetch('fetch_cart.php')
                        .then(response => response.json())
                        .then(cartData => {
                            cart = cartData;
                            addCartToHTML();
                        });
                });
        };

        initApp();

      
        resetTotal();
    </script>
</body>
</html>
