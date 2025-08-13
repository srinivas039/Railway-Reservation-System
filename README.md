# Railway-Reservation-System

# Overview
This project is a Railway Reservation System implemented in the C programming language.
It allows users to:
View available trains and their details.
Book tickets with seat allocation.
Calculate fares automatically.
Store and manage passenger details.
Save data persistently in CSV files for trains and passengers (up to 500 records).
The project uses a modular design for better readability and maintainability.

# Features
Train Management: Displays train number, name, source, destination, seats, and fare.
Ticket Booking: Allows passengers to book seats for a specific train.
Fare Calculation: Automatically calculates the total fare.
Seat Management: Updates seat availability in real time.
CSV Integration:
        trains.csv – Stores train details & seat availability.
        passengers.csv – Stores passenger booking details.

# Technology Stack
Language: C
Data Storage: CSV files (no external database)
Compiler: GCC (C99 or C11 standard recommended)

# How to Compile & Run
(bash)
gcc Main.c -o railway -std=c99
(bash)
./railway

# CSV File Format
(trains.csv)
Train No,Train Name,Source,Destination,Seats,Fare
101,Express A,City X,City Y,50,500.00
102,Express B,City Y,City Z,40,650.00
(passengers.csv)
Ticket No,Name,Age,Train No,Seat No,Fare Paid
1,Ravi Kumar,28,101,50,500.00

# Future Enhancements
Cancellation and refund system.
Search trains by source & destination.
Sorting trains by fare or seats.
Date & time management for train schedules.
