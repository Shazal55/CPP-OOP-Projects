# Vending Machine Project

## Overview
This is a **C++ console-based Vending Machine application** that simulates real-world vending machine operations. Users can view products, purchase drinks, and see transaction details, while admins can manage inventory, prices, and stock.

## Features

### User Side
- View available products with ID, name, price, and stock.
- Purchase products by entering the product ID and money.
- Receive change if payment exceeds product price.
- Tracks total revenue and units sold.
- Transaction logging to a file (`transactions.txt`).

### Admin Side
- Password-protected login (`shazal123`).
- View full inventory with details.
- Change prices of products.
- Restock products using available revenue.
- Add new products to the machine.
- View total revenue and most popular product.
- Inventory data is saved and loaded from `vending_data.txt`.

## Classes

- **Products**: Represents individual products (ID, name, price, stock, units sold).
- **VendingMachine** (abstract class): Handles product management, buying logic, transaction logging, and inventory persistence.
- **Admin**: Derived from `VendingMachine`, provides admin functionalities like changing prices, restocking, and adding products.
