#include <stdio.h>
#include <stdlib.h>


// Function prototypes
void monthly_report(double *sales, char **months);
void summary_report(double *sales, char **months);
void six_month_moving_average(double *sales, char **months);
void slow_sort(double *sales, int *indices);
void highest_to_lowest(double *sales, char **months);

/*
 * Main function. Defines the sales for each month and calls 
 * the monthly_report, summary_report, and six_month_report 
 * functions.
 */
int main() 
{   

    // Define the sales for each month
    double sales[12];

    // Define two variables for reading from the file
    FILE *file;
    double num;

    // Open the file in read mode
    file = fopen("test_input.txt", "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        // If not, print an error message
        printf("Could not open file\n");
        // Exit the program
        return 1;
    }

    // Read numbers from the file
    int line = 0;
    // Read numbers from the file
    while (fscanf(file, "%lf", &num) == 1) {
        // Add the number to the sales array
        sales[line] = num;
        // Increment the line counter
        line++;
    }

    // Close the file
    fclose(file);

    // Define the sales for each month
    char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    // Print a blank line
    printf("\n");
    // Call the monthly_report function
    monthly_report(sales, months);
    // Print a blank line
    printf("\n");
    // Call the summary_report function
    summary_report(sales, months);
    // Print a blank line
    printf("\n");
    // Call the six_month_report function
    six_month_moving_average(sales, months);
    // Print a blank line
    printf("\n");
    highest_to_lowest(sales, months);
    return 0;
}

/*
 * Prints the sales for each month.
 */
void monthly_report(double *sales, char **months)
{  
    // Print the monthly sales report
    printf("Monthly Sales Report for 2024\n\n");
    printf("Month       Sales\n");

    // Iterate through the months and print the sales for each month
    for (int i = 0; i < 12; i++)
    {   
        // Print the month and the sales for the month
        printf("%-9s   %.2lf\n", months[i], sales[i]);
    }
}

/*
 * Prints the minimum, maximum, and average sales for the year.
 */
void summary_report(double *sales, char **months)
{   
    // Define the number of months
    const double NUM_MONTHS = 12;
    // Define the minimum and maximum sales
    int min_indx = 0;
    int max_indx = 0;
    // Define the sum of the sales
    double sum = 0;

    // Iterate through the sales and find the minimum and maximum sales
    // and the sum of the sales
    for (int i = 0; i < NUM_MONTHS; i++)
    {   
        // Check if the current sale is less than the minimum sale
        if (sales[i] < sales[min_indx])
            // Set the minimum sale to the current sale
            min_indx = i;

        // Check if the current sale is greater than the maximum sale
        if (sales[i] > sales[max_indx])
            // Set the maximum sale to the current sale 
            max_indx = i;

        // Add the current sale to the sum of the sales
        sum += sales[i];
    }

    // Calculate the average sales
    double average = sum / NUM_MONTHS;

    // Print the sales summary report
    printf("Sales summary report:\n\n");
    // Print the minimum sales
    printf("Minimum sales:  %lf (%s)\n", sales[min_indx], months[min_indx]);
    // Print the maximum sales
    printf("Maximum sales:  %lf (%s)\n", sales[max_indx], months[max_indx]);
    // Print the average sales
    printf("Average sales:  %lf\n", average);
}

/*
 * Prints the six-month moving average for each month.
 */
void six_month_moving_average(double *sales, char **months)
{   
    // Define the number of windows and the size of the window
    const int NUM_WINDOWS = 7;
    const int WINDOW_SIZE = 6;

    // Define an array to store the moving average for each window
    double moving_averages[NUM_WINDOWS];
    // Define a variable to store the sum of the sales in the window
    double sum = 0.00;

    // Initialize the sum to the sum of the first window
    for (int i = 0; i < WINDOW_SIZE - 1; i++)
    {   
        // Add the current sale to the sum
        sum += sales[i];
    }

    // Calculate the moving average for each window
    double average;
    // Iterate through the windows
    for (int i = 0; i < NUM_WINDOWS; i++)
    {   
        // Calculate the moving average for the window
        average = sum / WINDOW_SIZE;
        // Store the moving average in the array
        moving_averages[i] = average;

        //  If there are more windows, update the sum for the next window
        if (i < WINDOW_SIZE)
        {   
            // Remove the first sale from the sum
            sum -= sales[i];
            // Add the next sale to the sum
            sum += sales[i + WINDOW_SIZE];
        }
    }
    
    // Print the six-month moving average report
    printf("Six-Month moving average report:\n\n");
    
    /// Iterate through the windows and print the moving average for each window
    for (int i = 0; i < NUM_WINDOWS; i++)
    {   
        // Print the window and the moving average for the window
        char month_range[15];
        sprintf(month_range, "%s-%s", months[i], months[i + WINDOW_SIZE - 1]);
        printf("%-15s %12.2lf\n", month_range, moving_averages[i]);
    }
}


/* The code below, compare() and sort(), I have borrowed from an article on quick sort in c:
 * https://www.geeksforgeeks.org/c-program-to-sort-an-array-in-ascending-order/
*/

// If a should be placed before b, compare function should
// return positive value, if it should be placed after b,
// it should return negative value. Returns 0 otherwise
int compare(const void* a, const void* b) {
      
      // If a is smaller, positive value will be returned
    return (*(double*)a - *(double*)b);
}

void sort(double *arr) {
    int n = sizeof(arr) / sizeof(arr[0]);

    // Sort the array using qsort
    qsort(arr, n, sizeof(double), compare);
}

/*
 * Prints the sales from highest to lowest.
 */
void highest_to_lowest(double *sales, char **months)
{   
    // Print the sales from highest to lowest
    printf("Month         Sales\n");

    // Initialize an array to store the indices of the sales
    double salesCopy[12];
    for (int i = 0; i < 12; i++)
    {
        salesCopy[i] = sales[i];
    }

    // Sort the sales from lowest to highest
    sort(salesCopy);

    // Print the sales from highest to lowest
    for (int i = 11; i >= 0; i--)
    {   
        // Find the index of the sale
        int index = 0;
        // Iterate through the sales
        for (int j = 0; j < 12; j++)
        {   
            // If the sale is found, set index and break out of the loop
            if (salesCopy[i] == sales[j])
            {   
                // Set the index
                index = j;
                // Break out of the loop
                break;
            }
        }

        // Print the month and the sale
        printf("%-9s     $%.2lf\n", months[index], sales[i]);
    }
}