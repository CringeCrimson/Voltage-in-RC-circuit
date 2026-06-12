#include <stdio.h>
#include <math.h> 
#include "Charge.h" 
#include "Discharge.h"

// Global physical variables
double V = 10.0;
double R = 5.0;
double C = 0.1;
double dt = 0.01;
double t_max = 4.0;

int Charge() {
    FILE *fp = fopen("rc_simulation.csv", "w");
    if (fp == NULL) {
        printf("Error: Cannot create file!\n");
        return 1;
    }
    // Write CSV header
    fprintf(fp, "Time(s),Vc(V),Current_Charge(A)\n");
     
    for (double t = 0; t <= t_max; t += dt) { 
        fprintf(fp, "%.4f,%.4f,%.4f\n", t, Vc(V, R, C, t), current_C(V, R, C, t));
    }

    fclose(fp);
    printf("Success: Charging simulation data saved to 'rc_simulation.csv'\n");
    return 0;
} 

int Discharge() {
    FILE *fp = fopen("rc_simulation_D.csv", "w");
    if (fp == NULL) {
        printf("Error: Cannot create file!\n");
        return 1;
    }
    // Write CSV header
    fprintf(fp, "Time(s),Vc(V),Current_Discharge(A)\n");
     
    for (double t = 0; t <= t_max; t += dt) {
        fprintf(fp, "%.4f,%.4f,%.4f\n", t, Vr(V, R, C, t), current_D(V, R, C, t));
    }

    fclose(fp);
    printf("Success: Discharging simulation data saved to 'rc_simulation_D.csv'\n");
    return 0;
} 

// Feature 1: Query voltage at a specific timestamp
void QueryVoltage() {
    double target_t;
    char input[100];
    
    printf("\n--- Query Voltage at Specific Time ---\n");
    printf("Enter target time (seconds): ");
    
    if (fgets(input, sizeof(input), stdin)) {
        if (sscanf(input, "%lf", &target_t) == 1) {
            if (target_t < 0) {
                printf("Error: Time cannot be negative!\n");
                return;
            }
            printf("\n[Results at time = %.4f s]\n", target_t);
            printf("Charging Vc   : %.4f V\n", Vc(V, R, C, target_t));
            printf("Discharging Vc: %.4f V\n", Vr(V, R, C, target_t));
        } else {
            printf("Invalid input. Please enter a valid number.\n");
        }
    }
}

// Feature 2: Modify initial physical parameters
void ModifyVariables() {
    char input[100];
    int choice;
    
    while (1) {
        printf("\n--- Modify Initial Variables ---\n");
        printf("Current Settings: V = %.2fV, R = %.2f Ohm, C = %.4f F, dt = %.4f s, t_max = %.2f s\n", V, R, C, dt, t_max);
        printf("1. Modify Voltage (V)\n");
        printf("2. Modify Resistance (R)\n");
        printf("3. Modify Capacitance (C)\n");
        printf("4. Modify Time Step (dt)\n");
        printf("5. Modify Total Simulation Time (t_max)\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice (1-6): ");
        
        if (!fgets(input, sizeof(input), stdin)) break; // Handle EOF
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Invalid selection. Please enter a number between 1 and 6.\n");
            continue;
        }
        
        if (choice == 6) break;
        
        printf("Enter new value: ");
        if (!fgets(input, sizeof(input), stdin)) break;
        
        double val;
        if (sscanf(input, "%lf", &val) != 1) {
            printf("Error: Modification failed. Invalid numeric value!\n");
            continue;
        }
        
        switch (choice) {
            case 1: V = val; break;
            case 2: 
                if (val <= 0) { printf("Error: Resistance must be greater than 0!\n"); } else { R = val; }
                break;
            case 3: 
                if (val <= 0) { printf("Error: Capacitance must be greater than 0!\n"); } else { C = val; }
                break;
            case 4: 
                if (val <= 0) { printf("Error: dt must be greater than 0!\n"); } else { dt = val; }
                break;
            case 5: 
                if (val <= 0) { printf("Error: t_max must be greater than 0!\n"); } else { t_max = val; }
                break;
            default:
                printf("Invalid selection. Please try again.\n");
                break;
        }
    }
}

int main() {
    int number;       
    char input[100];  

    // Infinite loop until exit command or EOF is triggered
    while (1) {
        printf("\n====================================\n");
        printf("        RC Circuit Simulator\n");
        printf("====================================\n");
        printf("1. Run Charging Simulation & Export CSV\n");
        printf("2. Run Discharging Simulation & Export CSV\n");
        printf("3. Query Voltage at a Specific Time\n");
        printf("4. Adjust Initial Variables (V, R, C, dt, t_max)\n");
        printf("5. Exit Program (or press Ctrl+Z / Ctrl+D for EOF)\n");
        printf("------------------------------------\n");
        printf("Enter option number (1-5): ");
        
        // Handle EOF (End-Of-File) safely
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nEOF detected. Exiting program safely.\n");
            break; 
        }
        
        // Parse user selection
        if (sscanf(input, "%d", &number) != 1) {
            printf("Invalid input! Please enter an integer between 1 and 5.\n");
            continue; 
        }
        
        // Handle explicit exit selection
        if (number == 5) {
            printf("Exiting program. Goodbye!\n");
            break;
        }
        
        // Main menu routing
        switch(number) {
            case 1:
                Charge();
                break;
            case 2:
                Discharge();
                break;
            case 3:
                QueryVoltage();
                break;
            case 4:
                ModifyVariables();
                break;
            default:
                printf("Option out of range! Please try again.\n");
                break;
        }
    }

    return 0;
}