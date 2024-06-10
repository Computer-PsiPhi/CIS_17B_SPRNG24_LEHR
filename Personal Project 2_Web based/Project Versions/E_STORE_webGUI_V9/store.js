
class Product {
    constructor(id, name, price, image) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.image = image;
    }
}

class CartItem {
    constructor(product, quantity = 1) {
        this.product = product;
        this.quantity = quantity;
    }
}

class Store {
    constructor() {
        this.products = [];
        this.cart = [];
    }

    loadProducts(data) {
        this.products = data.map(item => new Product(item.id, item.name, item.price, item.image));
    }

    addProduct(product) {
        this.products.push(product);
    }

    addToCart(productId) {
        let product = this.products.find(p => p.id == productId);
        if (!product) {
            console.error(`Product with id ${productId} not found.`);
            return;
        }
        let cartItem = this.cart.find(item => item.product.id == productId);
        if (cartItem) {
            cartItem.quantity += 1;
        } else {
            this.cart.push(new CartItem(product));
        }
        this.saveCart();
    }

    changeCartQuantity(productId, type) {
        let cartItem = this.cart.find(item => item.product.id == productId);
        if (!cartItem) return;

        if (type === 'plus') {
            cartItem.quantity += 1;
        } else {
            cartItem.quantity -= 1;
            if (cartItem.quantity <= 0) {
                this.cart = this.cart.filter(item => item.product.id != productId);
            }
        }
        this.saveCart();
    }

    checkout() {
        this.cart = [];
        this.saveCart();
    }

    loadCart() {
        let cartData = JSON.parse(localStorage.getItem('cart')) || [];
        this.cart = cartData.map(item => {
            let product = this.products.find(p => p.id == item.product.id);
            if (product) {
                return new CartItem(product, item.quantity);
            } else {
                console.warn(`Product with id ${item.product.id} not found for cart item.`);
                return null;
            }
        }).filter(item => item !== null);
    }

    saveCart() {
        localStorage.setItem('cart', JSON.stringify(this.cart));
    }

    getTotalAmount() {
        return this.cart.reduce((total, item) => total + item.product.price * item.quantity, 0).toFixed(2);
    }

    getTotalQuantity() {
        return this.cart.reduce((total, item) => total + item.quantity, 0);
    }
}

// View
class View {
    constructor() {
        this.listProductHTML = document.querySelector('.listProduct');
        this.listCartHTML = document.querySelector('.listCart');
        this.iconCart = document.querySelector('.icon-cart');
        this.iconCartSpan = document.querySelector('.icon-cart span');
        this.body = document.querySelector('body');
        this.closeCart = document.querySelector('.close');
        this.checkoutButton = document.querySelector('.checkOut');
        this.totalDisplay = document.querySelector('.total');
    }

    displayProducts(products) {
        this.listProductHTML.innerHTML = '';
        products.forEach(product => {
            let newProduct = document.createElement('div');
            newProduct.dataset.id = product.id;
            newProduct.classList.add('item');
            let formattedPrice = parseFloat(product.price).toFixed(2);
            newProduct.innerHTML = `
                <h2>${product.name}</h2>
                <img src="${product.image}" alt="">
                <button class="addCart">Add To Cart</button>
                <div class="price">$${formattedPrice}</div>`;
            this.listProductHTML.appendChild(newProduct);
        });
    }

    displayCart(cart) {
        this.listCartHTML.innerHTML = '';
        cart.forEach(item => {
            let newItem = document.createElement('div');
            newItem.classList.add('item');
            newItem.dataset.id = item.product.id;
            let formattedPrice = parseFloat(item.product.price * item.quantity).toFixed(2);
            newItem.innerHTML = `
                <div class="image">
                    <img src="${item.product.image}">
                </div>
                <div class="name">
                    ${item.product.name}
                </div>
                <div class="totalPrice">$${formattedPrice}</div>
                <div class="quantity">
                    <span class="minus"><</span>
                    <span>${item.quantity}</span>
                    <span class="plus">></span>
                </div>`;
            this.listCartHTML.appendChild(newItem);
        });
        this.iconCartSpan.innerText = this.getTotalQuantity(cart);
    }

    getTotalQuantity(cart) {
        return cart.reduce((total, item) => total + item.quantity, 0);
    }

    displayTotal(totalAmount) {
        this.totalDisplay.innerHTML = `Total: $${totalAmount}`;
        this.totalDisplay.style.display = 'block';
    }

    resetTotal() {
        this.totalDisplay.style.display = 'none';
    }

    toggleCart() {
        this.body.classList.toggle('showCart');
    }
}

// Controller
class Controller {
    constructor(store, view) {
        this.store = store;
        this.view = view;

        this.view.iconCart.addEventListener('click', () => this.view.toggleCart());
        this.view.closeCart.addEventListener('click', () => {
            this.view.toggleCart();
            this.view.resetTotal();
        });
        this.view.checkoutButton.addEventListener('click', () => this.checkout());

        this.view.listProductHTML.addEventListener('click', (event) => {
            if (event.target.classList.contains('addCart')) {
                let productId = event.target.parentElement.dataset.id;
                this.addToCart(productId);
            }
        });

        this.view.listCartHTML.addEventListener('click', (event) => {
            if (event.target.classList.contains('minus') || event.target.classList.contains('plus')) {
                let productId = event.target.parentElement.parentElement.dataset.id;
                let type = event.target.classList.contains('plus') ? 'plus' : 'minus';
                this.changeCartQuantity(productId, type);
            }
        });

        this.init();
    }

    init() {
        fetch('products.json')
            .then(response => {
                if (!response.ok) {
                    throw new Error(`HTTP error! Status: ${response.status}`);
                }
                return response.json();
            })
            .then(data => {
                this.store.loadProducts(data);
                this.store.loadCart();
                this.view.displayProducts(this.store.products);
                this.view.displayCart(this.store.cart);
            })
            .catch(error => {
                console.error('Error fetching products:', error);
            });
    }

    addToCart(productId) {
        this.store.addToCart(productId);
        this.view.displayCart(this.store.cart);
    }

    changeCartQuantity(productId, type) {
        this.store.changeCartQuantity(productId, type);
        this.view.displayCart(this.store.cart);
    }

    checkout() {
        let totalAmount = this.store.getTotalAmount();
        this.store.checkout();
        this.view.displayCart(this.store.cart);
        this.view.displayTotal(totalAmount);
        this.view.iconCartSpan.innerText = '0';
    }
}

document.addEventListener('DOMContentLoaded', () => {
    const store = new Store();
    const view = new View();
    new Controller(store, view);
});
