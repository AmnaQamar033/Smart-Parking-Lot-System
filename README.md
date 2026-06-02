# Smart Parking Lot System

A high-performance command-line application engineered in C++ that simulates an automated multi-vehicle parking plaza. This project demonstrates advanced Object-Oriented Programming (OOP) principles, dynamic memory management, and persistent storage via File I/O.

---

## Key Features

* **Dynamic Size-Matching Algorithm:** Automatically detects vehicle types (Bike, Car, Truck) and allocates them to compatible parking slots based on availability.
* **Runtime Polymorphism:** Implements an abstract base class with pure virtual functions to dynamically calculate tailored hourly billing rates for different vehicle classes.
* **Automated Billing & Checkout:** Processes vehicle exits by calculating exact duration fees on the fly.
* **Persistent Revenue Logging:** Integrated File Handling (fstream) to permanently append transaction receipts to a historical flat-file database (revenue_log.txt).
* **Robust Memory Management:** Ensures zero memory leaks by utilizing pointer mechanics for polymorphism and safely deallocating objects via class destructors.

---

## Core OOP Concepts Demonstrated

* **Abstract Classes & Interface Design** (Vehicle Base Class)
* **Runtime Polymorphism / Method Overriding** (calculateFee())
* **Object Composition** (ParkingPlaza HAS-A ParkingSlot array)
* **Encapsulation & Data Hiding** (Strict use of private attributes and const getters)
* **File Streams** (ofstream for logging and ifstream for reading data)

---

## Tech Stack

* **Language:** C++
* **Paradigm:** Object-Oriented Programming (OOP)
* **Storage:** Flat-file system (.txt)

---

## How to Run the Project

1. Clone this repository or download the source code:
   ```bash
   git clone [https://github.com/AmnaQamar033/Smart-Parking-Lot-System.git](https://github.com/AmnaQamar033/Smart-Parking-Lot-System.git)
