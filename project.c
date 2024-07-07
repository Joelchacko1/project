#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_JUNCTIONS 4
#define MAX_SIM_TIME 3600 23
enum LightColor { RED, GREEN, YELLOW };

struct Junction {
    enum LightColor light;
    int traffic_density;  
};

void initialize_junctions(struct Junction junctions[]) {
    
    srand(time(NULL));
    for (int i = 0; i < NUM_JUNCTIONS; i++) {
        junctions[i].light = rand() % 3; 
        junctions[i].traffic_density = rand() % 10 + 1; 
    }
}

void simulate_traffic(struct Junction junctions[], int current_hour) {
   
    for (int i = 0; i < NUM_JUNCTIONS; i++) {
        
        if (current_hour >= 8 && current_hour <= 10) {  
            junctions[i].traffic_density += rand() % 3;
        } else if (current_hour >= 17 && current_hour <= 19) { 
            junctions[i].traffic_density += rand() % 2;
        } else {
            junctions[i].traffic_density += rand() % 3 - 1; 
        }
        if (junctions[i].traffic_density < 1) {
            junctions[i].traffic_density = 1;
        }
    }
}


enum LightColor get_light_color(int junction_index, int current_hour, int cycle_time) {
    int current_time_in_seconds = current_hour * 3600; 
    int cycle_number = current_time_in_seconds / cycle_time;
    int offset = junction_index % NUM_JUNCTIONS;

    if ((cycle_number + offset) % NUM_JUNCTIONS == 0) {
        return GREEN;
    } else {
        return RED;
    }
}


void search_light_status(struct Junction junctions[], int search_hour, int cycle_time) {
    if (search_hour < 0 || search_hour >= 24) {
        printf("Invalid search time. Please enter a time between 0 and 23 hours.\n");
        return;
    }

    printf("Traffic Light Status at %d:00:\n", search_hour);
    for (int i = 0; i < NUM_JUNCTIONS; i++) {
        enum LightColor light_color = get_light_color(i, search_hour, cycle_time);
        char *color_name;
        switch (light_color) {
            case RED:
                color_name = "RED";
                break;
            case GREEN:
                color_name = "GREEN";
                break;
            case YELLOW:
                color_name = "YELLOW";
                break;
        }
        printf("Junction %d: %s (Traffic Density: %d)\n", i + 1, color_name, junctions[i].traffic_density);
    }
}

int main() {
    struct Junction junctions[NUM_JUNCTIONS];
    int cycle_time = 30; 1


    initialize_junctions(junctions);

    int choice;
    do {
        printf("\nTraffic Management System\n");
        
        printf("1. Search Traffic Light Status\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            
            case 1:
                int search_hour;
                printf("Enter a time (in hours - 24 hour clock) to search for traffic light status (0-23): ");
                scanf("%d", &search_hour);
                search_light_status(junctions, search_hour, cycle_time);
                break;
            case 2:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 2);

    return 0;
}
