#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PASSENGERS 500
#define MAX_TRAINS 5

typedef struct {
    int train_no;
    char train_name[50];
    char source[30];
    char destination[30];
    int seats;
    float fare;
} Train;

typedef struct {
    int ticket_no;
    char name[50];
    int age;
    int train_no;
    int seat_no;
    float fare_paid;
} Passenger;

Train trains[MAX_TRAINS];
Passenger passengers[MAX_PASSENGERS];
int passenger_count = 0;
int ticket_counter = 1;

void initializeTrains();
void loadPassengers();
void savePassengers();
void displayTrains();
void bookTicket();
void viewPassengers();
Train* findTrain(int train_no);

int main() {
    int choice;
    initializeTrains();
    loadPassengers();
    while (1) {
        printf("\n=== Railway Reservation System ===\n");
        printf("1. View Trains\n");
        printf("2. Book Ticket\n");
        printf("3. View Passengers\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: displayTrains(); break;
            case 2: bookTicket(); break;
            case 3: viewPassengers(); break;
            case 4: savePassengers(); printf("Exiting...\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

void initializeTrains() {
    FILE *f = fopen("trains.csv", "w");
    if (!f) { printf("Error creating trains.csv\n"); exit(1); }
    fprintf(f, "Train No,Train Name,Source,Destination,Seats,Fare\n");
    trains[0] = (Train){101, "Express A", "City X", "City Y", 50, 500.0};
    trains[1] = (Train){102, "Express B", "City Y", "City Z", 40, 650.0};
    trains[2] = (Train){103, "Superfast C", "City X", "City Z", 60, 800.0};
    trains[3] = (Train){104, "Local D", "City X", "City W", 30, 300.0};
    trains[4] = (Train){105, "Rajdhani", "City W", "City Z", 20, 1200.0};
    for (int i = 0; i < MAX_TRAINS; i++) {
        fprintf(f, "%d,%s,%s,%s,%d,%.2f\n",
                trains[i].train_no, trains[i].train_name, trains[i].source,
                trains[i].destination, trains[i].seats, trains[i].fare);
    }
    fclose(f);
}

void loadPassengers() {
    FILE *f = fopen("passengers.csv", "r");
    if (!f) return;
    char line[200];
    fgets(line, sizeof(line), f);
    while (fgets(line, sizeof(line), f)) {
        Passenger p;
        sscanf(line, "%d,%49[^,],%d,%d,%d,%f",
               &p.ticket_no, p.name, &p.age, &p.train_no, &p.seat_no, &p.fare_paid);
        passengers[passenger_count++] = p;
        if (p.ticket_no >= ticket_counter) ticket_counter = p.ticket_no + 1;
    }
    fclose(f);
}

void savePassengers() {
    FILE *f = fopen("passengers.csv", "w");
    if (!f) { printf("Error writing passengers.csv\n"); return; }
    fprintf(f, "Ticket No,Name,Age,Train No,Seat No,Fare Paid\n");
    for (int i = 0; i < passenger_count; i++) {
        fprintf(f, "%d,%s,%d,%d,%d,%.2f\n",
                passengers[i].ticket_no, passengers[i].name, passengers[i].age,
                passengers[i].train_no, passengers[i].seat_no, passengers[i].fare_paid);
    }
    fclose(f);
}

void displayTrains() {
    printf("\nAvailable Trains:\n");
    printf("No.  Name            Source   Destination   Seats   Fare\n");
    for (int i = 0; i < MAX_TRAINS; i++) {
        printf("%d   %-15s %-8s %-12s %d      %.2f\n",
               trains[i].train_no, trains[i].train_name, trains[i].source,
               trains[i].destination, trains[i].seats, trains[i].fare);
    }
}

Train* findTrain(int train_no) {
    for (int i = 0; i < MAX_TRAINS; i++) {
        if (trains[i].train_no == train_no)
            return &trains[i];
    }
    return NULL;
}

void bookTicket() {
    if (passenger_count >= MAX_PASSENGERS) {
        printf("Passenger limit reached!\n");
        return;
    }
    Passenger p;
    int train_no;
    printf("Enter passenger name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;
    printf("Enter passenger age: ");
    scanf("%d", &p.age);
    getchar();
    displayTrains();
    printf("Enter train number to book: ");
    scanf("%d", &train_no);
    getchar();
    Train* t = findTrain(train_no);
    if (!t) { printf("Invalid train number!\n"); return; }
    if (t->seats <= 0) { printf("No seats available!\n"); return; }
    t->seats--;
    p.train_no = t->train_no;
    p.seat_no = t->seats + 1;
    p.fare_paid = t->fare;
    p.ticket_no = ticket_counter++;
    passengers[passenger_count++] = p;
    savePassengers();
    printf("\nTicket booked!\nTicket No: %d\nPassenger: %s\nTrain: %s\nSeat No: %d\nFare Paid: %.2f\n",
           p.ticket_no, p.name, t->train_name, p.seat_no, p.fare_paid);
}
