#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define N 6

/* =========================================
   FUNCTIONALITY 1: SATELLITE REGISTRY
   DSA: LINKED LIST
   ========================================= */

struct Satellite {
    int id;
    char name[30];
    char status[20];
    struct Satellite *next;
};

struct Satellite *head = NULL;

void addSatellite() {
    struct Satellite *newNode, *temp;

    newNode = (struct Satellite *)malloc(sizeof(struct Satellite));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter satellite ID: ");
    scanf("%d", &newNode->id);

    printf("Enter satellite name (no spaces): ");
    scanf("%29s", newNode->name);

    printf("Enter status (ACTIVE/INACTIVE): ");
    scanf("%19s", newNode->status);

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    printf("Satellite added successfully!\n");
}

void displaySatellites() {
    struct Satellite *temp = head;

    if (temp == NULL) {
        printf("No satellites registered.\n");
        return;
    }

    printf("\n--- SATELLITE REGISTRY ---\n");

    while (temp != NULL) {
        printf("ID: %d | Name: %s | Status: %s\n",
               temp->id, temp->name, temp->status);

        temp = temp->next;
    }
}

void searchSatellite() {
    struct Satellite *temp = head;
    int id;

    printf("Enter satellite ID to search: ");
    scanf("%d", &id);

    while (temp != NULL) {
        if (temp->id == id) {
            printf("Satellite found: %d | %s | %s\n",
                   temp->id, temp->name, temp->status);
            return;
        }

        temp = temp->next;
    }

    printf("Satellite not found.\n");
}

void deleteSatellite() {
    struct Satellite *temp = head;
    struct Satellite *previous = NULL;
    int id;

    printf("Enter satellite ID to delete: ");
    scanf("%d", &id);

    while (temp != NULL && temp->id != id) {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Satellite not found.\n");
        return;
    }

    if (previous == NULL)
        head = temp->next;
    else
        previous->next = temp->next;

    free(temp);

    printf("Satellite deleted successfully!\n");
}

void satelliteMenu() {
    int choice;

    do {
        printf("\n--- SATELLITE REGISTRY ---\n");
        printf("1. Add satellite\n");
        printf("2. Display satellites\n");
        printf("3. Search satellite\n");
        printf("4. Delete satellite\n");
        printf("5. Return to main menu\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: addSatellite(); break;
            case 2: displaySatellites(); break;
            case 3: searchSatellite(); break;
            case 4: deleteSatellite(); break;
            case 5: break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 5);
}

/* =========================================
   FUNCTIONALITY 2: EMERGENCY SIGNALS
   DSA: PRIORITY QUEUE USING SORTED ARRAY
   ========================================= */

struct Alert {
    int satelliteID;
    int severity;
    char message[50];
};

struct Alert alerts[MAX];
int alertCount = 0;

void addAlert() {
    struct Alert newAlert;
    int i;

    if (alertCount == MAX) {
        printf("Alert queue is full.\n");
        return;
    }

    printf("Enter satellite ID: ");
    scanf("%d", &newAlert.satelliteID);

    printf("Enter severity (1-5): ");
    scanf("%d", &newAlert.severity);

    if (newAlert.severity < 1 || newAlert.severity > 5) {
        printf("Invalid severity. Enter 1 to 5.\n");
        return;
    }

    printf("Enter alert message (no spaces): ");
    scanf("%49s", newAlert.message);

    i = alertCount - 1;

    while (i >= 0 &&
           alerts[i].severity < newAlert.severity) {
        alerts[i + 1] = alerts[i];
        i--;
    }

    alerts[i + 1] = newAlert;
    alertCount++;

    printf("Alert added successfully!\n");
}

void displayAlerts() {
    int i;

    if (alertCount == 0) {
        printf("No pending alerts.\n");
        return;
    }

    printf("\n--- PENDING EMERGENCY ALERTS ---\n");

    for (i = 0; i < alertCount; i++) {
        printf("Satellite: %d | Severity: %d | Message: %s\n",
               alerts[i].satelliteID,
               alerts[i].severity,
               alerts[i].message);
    }
}

void processAlert() {
    int i;

    if (alertCount == 0) {
        printf("No alerts to process.\n");
        return;
    }

    printf("\nProcessing highest-priority alert:\n");
    printf("Satellite ID: %d\n", alerts[0].satelliteID);
    printf("Severity: %d\n", alerts[0].severity);
    printf("Message: %s\n", alerts[0].message);

    for (i = 0; i < alertCount - 1; i++)
        alerts[i] = alerts[i + 1];

    alertCount--;

    printf("Alert processed successfully!\n");
}

void emergencyMenu() {
    int choice;

    do {
        printf("\n--- EMERGENCY SIGNAL MANAGEMENT ---\n");
        printf("1. Add emergency alert\n");
        printf("2. Display pending alerts\n");
        printf("3. Process highest-priority alert\n");
        printf("4. Return to main menu\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: addAlert(); break;
            case 2: displayAlerts(); break;
            case 3: processAlert(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }

    } while (choice != 4);
}

/* =========================================
   FUNCTIONALITY 3: COMMUNICATION NETWORK
   DSA: GRAPH + BFS
   ========================================= */

char *satellites[N] = {
    "EARTH", "SAT1", "SAT2",
    "MOON", "MARS", "SAT3"
};

int graph[N][N] = {
    {0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 0},
    {0, 0, 1, 1, 0, 1},
    {0, 1, 0, 0, 1, 0}
};

void displayNetwork() {
    int i, j;

    printf("\n--- SPACE COMMUNICATION NETWORK ---\n");

    for (i = 0; i < N; i++) {
        printf("%s connects to: ", satellites[i]);

        for (j = 0; j < N; j++) {
            if (graph[i][j] == 1)
                printf("%s ", satellites[j]);
        }

        printf("\n");
    }
}

int findSatelliteIndex(char name[]) {
    int i;

    for (i = 0; i < N; i++) {
        if (strcmp(satellites[i], name) == 0)
            return i;
    }

    return -1;
}

void BFS(int start, int destination) {
    int visited[N] = {0};
    int parent[N];
    int queue[N];
    int front = 0, rear = 0;
    int current, i;
    int path[N], pathLength = 0;

    for (i = 0; i < N; i++)
        parent[i] = -1;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        current = queue[front++];

        if (current == destination)
            break;

        for (i = 0; i < N; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = current;
                queue[rear++] = i;
            }
        }
    }

    if (!visited[destination]) {
        printf("No communication route found.\n");
        return;
    }

    current = destination;

    while (current != -1) {
        path[pathLength++] = current;
        current = parent[current];
    }

    printf("\nRoute with the fewest links:\n");

    for (i = pathLength - 1; i >= 0; i--) {
        printf("%s", satellites[path[i]]);

        if (i > 0)
            printf(" -> ");
    }

    printf("\nTotal communication links: %d\n",
           pathLength - 1);
}

void networkMenu() {
    int choice, start, destination;
    char sourceName[20], destinationName[20];

    do {
        printf("\n--- SPACE COMMUNICATION NETWORK ---\n");
        printf("1. Display network\n");
        printf("2. Find route using BFS\n");
        printf("3. Return to main menu\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayNetwork();
                break;

            case 2:
                printf("Enter starting satellite (e.g. EARTH): ");
                scanf("%19s", sourceName);

                printf("Enter destination (e.g. MARS): ");
                scanf("%19s", destinationName);

                start = findSatelliteIndex(sourceName);
                destination = findSatelliteIndex(destinationName);

                if (start == -1 || destination == -1)
                    printf("Invalid satellite name.\n");
                else
                    BFS(start, destination);

                break;

            case 3:
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 3);
}

/* =========================================
   MAIN MENU
   ========================================= */

int main() {
    int choice;

    do {
        printf("\n====================================\n");
        printf("       SPACE-LINK MISSION CONTROL\n");
        printf("====================================\n");
        printf("1. Satellite Registry (Linked List)\n");
        printf("2. Emergency Signals (Priority Queue)\n");
        printf("3. Communication Network (Graph + BFS)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                satelliteMenu();
                break;

            case 2:
                emergencyMenu();
                break;

            case 3:
                networkMenu();
                break;

            case 4:
                printf("Exiting SPACE-LINK. Mission complete!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);

    /* Free all remaining linked-list nodes */
    while (head != NULL) {
        struct Satellite *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
