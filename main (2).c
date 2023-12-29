#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
// Structure to represent an itinerary
typedef struct {
    char departure_point[50];
    char destination[50];
    char departure_time[10];
    float bus_rating;
    int wifi_available;
    int capacity;
    char ac_type[20];
    char accessibility_features[50];
} Itinerary;
// Structure to represent a bus with an itinerary
typedef struct {
    int bus_number;
    Itinerary itinerary;
} Bus;
// Structure to represent the bus database
typedef struct {
    Bus *buses;  // Array to store buses
    int count;   // Number of buses in the database
} BusDatabase;
// Structure to represent a traveler account
typedef struct {
    char firstname[50];
    char lastname[50];
    char email[100];
    char password[50];
} TravelerAccount;
// Structure to represent the traveler database
typedef struct {
    TravelerAccount *accounts;
    int count;
} TravelerDatabase;
// Function to initialize the bus database
void initializeBusDatabase(BusDatabase *database, int initialSize) {
    database->buses = (Bus *)malloc(initialSize * sizeof(Bus));
    database->count = 0;
}
// Function to initialize the traveler database
void initializeTravelerDatabase(TravelerDatabase *database, int initialSize) {
    database->accounts = (TravelerAccount *)malloc(initialSize * sizeof(TravelerAccount));
    database->count = 0;
}
// Function to add a new bus to the database
void addBus(BusDatabase *database, Bus newBus) {
    // Resize the array if necessary
    if (database->count == 0) {
        database->buses = (Bus *)malloc(sizeof(Bus));
    } else {
        database->buses = (Bus *)realloc(database->buses, (database->count + 1) * sizeof(Bus));
    }
    // Add the new bus to the database
    database->buses[database->count] = newBus;
    database->count++;
}
// Function to display the details of a bus
void displayBusDetails(Bus *bus) {
    printf("Bus Number: %d\n", bus->bus_number);
    printf("Itinerary Details:\n");
    printf("  Departure Point: %s\n", bus->itinerary.departure_point);
    printf("  Destination: %s\n", bus->itinerary.destination);
    printf("  Departure Time: %s\n", bus->itinerary.departure_time);
    printf("  Bus Rating: %.2f\n", bus->itinerary.bus_rating);
    printf("  Wifi Availability: %s\n", bus->itinerary.wifi_available ? "Available" : "Not Available");
    printf("  Capacity: %d\n", bus->itinerary.capacity);
    printf("  Air Conditioning Type: %s\n", bus->itinerary.ac_type);
    printf("  Accessibility Features: %s\n", bus->itinerary.accessibility_features);
}
// Function to display all buses in the database
void displayAllBuses(BusDatabase *database) {
    printf("All Buses in the Database:\n");
    for (int i = 0; i < database->count; i++) {
        printf("Bus #%d\n", i + 1);
        displayBusDetails(&(database->buses[i]));
        printf("\n");
    }
}
// Function to display the available countries
void displayAvailableCountries(BusDatabase *database) {
    printf("Available Countries:\n");
    // Create a temporary array to keep track of unique countries
    char uniqueCountries[30][50];  // Assuming a maximum of 30 countries
    int uniqueCount = 0;
    // Loop through the buses and add unique countries to the temporary array
    for (int i = 0; i < database->count; i++) {
        int isUnique = 1;
        // Check if the country is already in the unique array
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(uniqueCountries[j], database->buses[i].itinerary.destination) == 0) {
                isUnique = 0;
                break;
            }
        }
        // If the country is unique, add it to the temporary array and display
        if (isUnique) {
            strcpy(uniqueCountries[uniqueCount], database->buses[i].itinerary.destination);
            uniqueCount++;
            printf("%s\n", database->buses[i].itinerary.destination);
        }
    }
}
// Function to display the details of the bus for a specific country
void displayBusDetailsForCountry(BusDatabase *database, const char *country) {
    printf("Bus Details for %s:\n", country);
    for (int i = 0; i < database->count; i++) {
        if (strcmp(database->buses[i].itinerary.destination, country) == 0) {
            displayBusDetails(&(database->buses[i]));
            printf("\n");
        }
    }
}
// Function to create a new traveler account
void createNewTravelerAccount(TravelerDatabase *database, TravelerAccount newAccount) {
    // Resize the array if necessary
    if (database->count == 0) {
        database->accounts = (TravelerAccount *)malloc(sizeof(TravelerAccount));
    } else {
        database->accounts = (TravelerAccount *)realloc(database->accounts, (database->count + 1) * sizeof(TravelerAccount));
    }
    // Add the new account to the traveler database
    database->accounts[database->count] = newAccount;
    database->count++;
}
// Function to check if a traveler account exists
int travelerAccountExists(TravelerDatabase *database, const char *email, const char *password) {
    for (int i = 0; i < database->count; i++) {
        if (strcmp(database->accounts[i].email, email) == 0 && strcmp(database->accounts[i].password, password) == 0) {
            return 1;  // The account exists
        }
    }
    return 0;  // The account does not exist
}
// Function to free the memory allocated for the bus database
void freeBusDatabase(BusDatabase *database) {
    free(database->buses);
}
// Function to free the memory allocated for the traveler database
void freeTravelerDatabase(TravelerDatabase *database) {
    free(database->accounts);
}
// Function to generate a random time for demonstration purposes
void generateRandomTime(char *timeStr) {
    sprintf(timeStr, "%02d:%02d", rand() % 24, rand() % 60);
}
// Function to check if a string contains only letters
int containsOnlyLetters(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i])) {
            return 0;  // The string contains at least one character that is not a letter
        }
    }
    return 1;  // The string contains only letters
}
// Function to check if a string contains at least one digit
int containsNumber(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            return 1;  // The string contains at least one digit
        }
    }
    return 0;  // The string does not contain a digit
}
// Function to make a reservation
void makeReservation(BusDatabase *database) {
    int busNumber, numSeats;
    printf("We recommend choosing a bus from the listed options to ensure you reach your intended destination safely., Otherwise this could lead to an incorrect destination. \n" );
    

    printf("Enter the bus number you want to book: ");
    scanf("%d", &busNumber);
    // Validate if the entered bus number is within the available range
    if (busNumber < 1 || busNumber > database->count) {
        printf("Invalid bus number. Please choose a valid bus number.\n");
        return;
    }
    int maxSeats = rand() % 6 + 3; // Random number between 3 and 8
    Bus *selectedBus = &(database->buses[busNumber - 1]);
    printf("Enter the number of seats you want to book (Maximum %d available): ", maxSeats);
    scanf("%d", &numSeats);
    // Validate the number of seats
    if (numSeats < 1 || numSeats > selectedBus->itinerary.capacity) {
        printf("Invalid number of seats. Please choose a valid number.\n");
        return;
    }
    // Simulate realistic seat availability
    if (numSeats > maxSeats) {
        printf("Sorry, you can only book up to %d seats. Please choose a smaller number.\n", maxSeats);
        return;
    }
    // Ask for additional notes
    char notes[100];
    printf("Do you have any additional notes or special requests? (Enter 'none' if not)\n");
    scanf("%s", notes);
    // Payment options
    int paymentOption;
    printf("Choose a payment option:\n");
    printf("0 - Credit Card\n");
    printf("1 - PayPal\n");
    scanf("%d", &paymentOption);
    // Validate payment option
    if (paymentOption != 0 && paymentOption != 1) {
        printf("Invalid payment option. Please choose a valid option.\n");
        return;
    }
    // Ask for payment details
    char paymentID[20], password[20];
    printf("Enter %s ID: ", (paymentOption == 0) ? "Credit Card" : "PayPal");
    scanf("%s", paymentID);
    printf("Enter %s password: ", (paymentOption == 0) ? "Credit Card" : "PayPal");
    scanf("%s", password);
    // Process payment (this is a simulation, in a real system, this would be handled securely)
    printf("Processing payment...\n");
    // Generate a random reservation ID
    int reservationID = rand() % 10000 + 1000;
    // Display reservation details
    printf("Reservation successful!\n");
    printf("Your Reservation ID: %d\n", reservationID);
    // Provide information for modification or cancellation
    printf("To modify or cancel your reservation, please use the Reservation ID: %d\n", reservationID);
}
    // Function to check the format of an email address
int isValidEmail(const char *email) {
    int atIndex = -1;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            if (atIndex != -1) {
                return 0;  // There should be only one @ in the email address
            }
            atIndex = i;
        }
    }
    return (atIndex != -1 && atIndex > 0 && email[atIndex + 1] != '\0');  // There must be at least one character before and after @
}
// Function to check the format of a password
int isValidPassword(const char *password) {
    int hasLetter = 0;
    int hasNumber = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isalpha((unsigned char)password[i])) {
            hasLetter = 1;
        } else if (isdigit((unsigned char)password[i])) {
            hasNumber = 1;
        }
    }
    return (strlen(password) >= 5 && hasLetter && hasNumber);
}
void calculateNearestRandomTime(const char* inputTime, char* resultTime) {
    // Parse the input time to extract hours and minutes
    int inputHours, inputMinutes;
    sscanf(inputTime, "%d:%d", &inputHours, &inputMinutes);
    // Generate a random deviation between -30 and 30 minutes
    int deviation = rand() % 61 - 30;
    // Calculate the new time
    int newMinutes = (inputMinutes + deviation + 60) % 60;
    int newHours = (inputHours + (inputMinutes + deviation) / 60) % 24;
    // Format the result time
    sprintf(resultTime, "%02d:%02d", newHours, newMinutes);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main() {
    srand(time(NULL));
    BusDatabase busDB;
    initializeBusDatabase(&busDB, 0);
    // Add 30 buses to the
      //database with real cities
    for (int i = 0; i < 30; i++) {
        Bus newBus;
        newBus.bus_number = i + 1;
        strcpy(newBus.itinerary.departure_point, "Tunis");
        switch (i % 5) {
            case 0:
                strcpy(newBus.itinerary.destination, "Kairouan");
                break;
            case 1:
                strcpy(newBus.itinerary.destination, "Sousse");
                break;
            case 2:
                strcpy(newBus.itinerary.destination, "Gafsa");
                break;
            case 3:
                strcpy(newBus.itinerary.destination, "Bizerte");
                break;
            case 4:
                strcpy(newBus.itinerary.destination, "Gabès");
                break;
        }
        generateRandomTime(newBus.itinerary.departure_time);
        // Assign random values to the new fields
        newBus.itinerary.bus_rating = 2.5 + (rand() % 26) / 10.0;  
        newBus.itinerary.capacity = rand() % 50 + 20;  
        strcpy(newBus.itinerary.ac_type, (rand() % 2 == 0) ? "Regular AC" : "Premium AC");
        strcpy(newBus.itinerary.accessibility_features, (rand() % 2 == 0) ? "Wheelchair Accessible" : "Not Accessible");
        addBus(&busDB, newBus);
    }
    TravelerDatabase travelerDB;
    initializeTravelerDatabase(&travelerDB, 0);
    int userChoice;
    printf("Bienvenue sur notre service de réservation de bus!\n");
    printf("Veuillez entrer 0 pour vous inscrire  ");
    scanf("%d", &userChoice);
    if (userChoice == 0) {
        // L'utilisateur veut s'inscrire, demandez toutes les informations nécessaires
        TravelerAccount newAccount;
        printf("Prénom : ");
        scanf("%s", newAccount.firstname);
        if (!containsOnlyLetters(newAccount.firstname)) {
            printf("Erreur: Le prénom ne doit contenir que des lettres.\n");
            return 1;
        }
        printf("Nom : ");
        scanf("%s", newAccount.lastname);
        if (!containsOnlyLetters(newAccount.lastname)) {
            printf("Erreur: Le nom ne doit contenir que des lettres.\n");
            return 1;
        }
        printf("Email : ");
        scanf("%s", newAccount.email);
        if (!isValidEmail(newAccount.email)) {
            printf("Erreur: Format d'email invalide.\n");
            return 1;
        }
        printf("Mot de passe : ");
        scanf("%s", newAccount.password);
        if (!isValidPassword(newAccount.password)) {
            printf("Erreur: Le mot de passe doit contenir au moins 5 caractères, y compris au moins une lettre et un chiffre.\n");
            return 1;
        }
        // Add the new account to the traveler database
        createNewTravelerAccount(&travelerDB, newAccount);
        printf("Inscription réussie!\n");
        // After successful registration, display a menu for the logged-in user
        printf("Que souhaitez-vous faire ?\n");
        printf("0 - Voir la liste des bus\n");
        printf("1 - Voir la liste des pays disponibles\n");
        printf("2 - Noter un bus\n");  
        int userLoggedInChoice;
        printf("Votre choix : ");
        scanf("%d", &userLoggedInChoice);
        switch (userLoggedInChoice) {
            case 0:
                displayAllBuses(&busDB);
            
                break;
            
            
            case 2 :
                {
                int busNumber;
                printf("Veuillez entrer le numéro du bus que vous souhaitez noter : ");
                scanf("%d", &busNumber);

                // Validate if the entered bus number is within the available range
                if (busNumber < 1 || busNumber > busDB.count) {
                printf("Numéro de bus invalide. Veuillez choisir un numéro de bus valide.\n");
                return 1;
                }

                // Ask the user for the rating
                float userRating;
                printf("Veuillez entrer votre note pour le bus (de 0 à 5) : ");
                scanf("%f", &userRating);

                // Validate the user rating
                if (userRating < 0 || userRating > 5) {
                printf("Note invalide. Veuillez entrer une note entre 0 et 5.\n");
                return 1;
                }

                // Ask the user for special notes
                char specialNotes[100];
                printf("Avez-vous des notes spéciales à ajouter? (Entrez 'none' si non)\n");
                scanf("%s", specialNotes);

                // Display a thank-you message
                printf("Merci pour votre contribution!\n");

                // End of case 2 block
                break;
                }   
               
            
            
            case 1:
                displayAvailableCountries(&busDB);
                // After displaying available countries, let the user choose a country
                char selectedCountry[50];
                printf("Veuillez entrer le pays de votre choix : ");
                scanf("%s", selectedCountry);
                // Display bus details for the selected country
                printf("Recommended buses for %s:\n", selectedCountry);
                displayBusDetailsForCountry(&busDB, selectedCountry);
                // Ask for reservation or modification
                int reservationChoice;
                printf("0 - Faire une réservation\n");
                printf("1 - Modifier une réservation\n");
                printf("2 - Détails de la réservation\n");
                printf("Votre choix : ");
                scanf("%d", &reservationChoice);
                switch (reservationChoice) {
                    case 0:
                        makeReservation(&busDB);
                        break;
                    case 1:
                        printf("Please enter ID reservation: ");
                        int reservationID;
                        scanf("%d", &reservationID);
                        // Display current reservation details
                        printf("Current Reservation Details:\n");
                        printf("Reservation ID: %d\n", reservationID);
                        // Ask the user if they want to cancel or modify the reservation
                        int modificationChoice;
                        printf("Do you want to:\n");
                        printf("0 - Cancel the reservation\n");
                        printf("1 - Modify the reservation\n");
                        printf("Your choice: ");
                        scanf("%d", &modificationChoice);
                        switch (modificationChoice) {
                            case 0:
                                printf("Reservation canceled successfully.\n");
                                break;
                            case 1:
                                printf("What do you want to modify?\n");
                                printf("1 - Bus Number\n");
                                printf("2 - Number of Seats\n");
                                printf("3 - Departure Time\n");
                                printf("Your choice: ");
                                int modificationOption;
                                scanf("%d", &modificationOption);
                                switch (modificationOption) {
                                    case 1:
                                        int newBusNumber;
                                        printf("Enter the new bus number: ");
                                        scanf("%d", &newBusNumber);
                                        if (newBusNumber < 1 || newBusNumber > 30 ) {
                                        printf("Invalid number of seats. Please choose a valid number.\n"); }
                                        printf("Bus number updated successfully.\n");
                                        break;
                                    case 2:
                                        int newNumSeats;
                                        
                                        int maxSeats = rand() % 6 + 3; // Random number between 3 and 8
                                        printf("Enter the new number of seats:  (Maximum %d available): ", maxSeats);
                                        scanf("%d", &newNumSeats);
                                        // Validate the number of seats
                                        if (newNumSeats < 1 || newNumSeats > maxSeats ) {
                                         printf("Invalid number of seats. Please choose a valid number.\n");
                                         
                                         }
                                        printf("Number of seats updated successfully.\n");
                                        break;
                                    case 3:
    // Modify departure time
    char newDepartureTime[10];
    printf("Enter the new departure time (HH:MM): ");
    scanf("%s", newDepartureTime);
    // Calculate the nearest random time based on the user input
    char nearestRandomTime[10];
    calculateNearestRandomTime(newDepartureTime, nearestRandomTime);
    // Ask the user if they want to confirm the modification
    printf("The closest available departure time to %s is %s. Would you like to update the departure time ? (0 - No, 1 - Yes): ", newDepartureTime, nearestRandomTime);
    int confirmModification;
    scanf("%d", &confirmModification);
    if (confirmModification == 1) {
        // Update the reservation with the new departure time
        printf("Departure time updated successfully to %s.\n", nearestRandomTime);
    } else {
        printf("Departure time modification canceled.\n");
    }
    break;
                                }
                                break;
                            default:
                                printf("Invalid choice. Please enter either 0 or 1.\n");
                                break;
                        }
                        break;
                    case 2:
                        // View reservation details case
                        printf("Veuillez entrer l'ID de la réservation : ");
                        int viewReservationID;
                        scanf("%d", &viewReservationID);
                        printf("Détails de la réservation #%d :\n", viewReservationID);
                        printf("Bus Number: %d\n", rand() % 30 + 1);  
                        printf("Number of Seats Reserved: %d\n", rand() % 5 + 1);  
                        printf("Date and Time of Reservation: 2023-01-%02d %02d:%02d\n", rand() % 31 + 1, rand() % 24, rand() % 60);
                        printf("Amount Paid: %.2f\n", (rand() % 50) + 20.0);  
                        if (rand() % 2 == 0) {
                            printf("Special Notes: This is a special reservation!\n");
                        } else {
                            printf("No special notes for this reservation.\n");
                        }
                        break;
                    default:
                        printf("Choix invalide.\n");
                        break;
                }
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    }
    // Free allocated memory before exiting
    freeBusDatabase(&busDB);
    freeTravelerDatabase(&travelerDB);
    return 0;
}