/*
 * File: main.cpp
 * Author: Fatima Avila Cobian
 * KUID: 2977231
 * Date: 3.8.24
 * Lab: Lab 5
 * Purpose: Prints sales report from input file.
*/

#include <iostream>
#include <fstream>
#include <string>

void print_summary(double sales[], std::string months[]) {

    /* Input: sales array, months array */
    /* Prints minimum, maximum, and average of sales. */

    int min_id = 0; // array index of minimum
    int max_id = 0; // array index of maximum
    double min = sales[0]; // minimum sale
    double max = sales[0]; // maximum sale
    double avg = 0; // average of sales

    for (int i = 0; i < 12; i++) {
        // if sales[i] is less than min
        if (min > sales[i]) {
            min = sales[i]; // move min to sales[i]
            min_id = i; // set min index
        }

        // if sales[i] is greater than max
        if (max < sales[i]) {
            max = sales[i]; // move max to sales[i]
            max_id = i; // set max index
        }

        avg += sales[i]; // add up sales
    }

    avg = avg / 12; // compute average

    printf("Minimum sales:\t$%.2f    * %s\n", min, months[min_id].c_str()); // print minimum
    printf("Maximum sales:\t$%.2f    * %s\n", max, months[max_id].c_str()); // print maximum
    printf("Average sales:\t$%.2f\n", avg); // print average

}

void print_movavg(double sales[], std::string months[]) {

    /* Input: sales array, months array */
    /* Prints six-month moving average report. */

    for (int i = 0; i < 7; i++) {
        double six_avg = sales[i]; // six-month average
        for (int j = 1; j < 6; j++) {
            // add sales of six-month interval
            six_avg += sales[i+j];
        }
        six_avg = six_avg / 6; // compute average
        printf("%s -\t%s\t$%.2f\n", months[i].c_str(), months[i+5].c_str(), six_avg); // print average
    }

}

void print_ordered(double sales[], std::string months[]) {

    /* Input: sales array, months array */
    /* Prints sales in order from highest to lowest. */

    double cp[12]; // copy of sales array
    for (int i = 0; i < 12; i++) {
        cp[i] = sales[i]; // add values in sales to copy array
    }

    for (int i = 0; i < 12; i++) {
        double cp_max = cp[0]; // maximum sale
        int cp_id = 0; // array index of maximum 

        for (int j = 0; j < 12; j++) {
            // if cp[j] is greater than max
            if (cp_max < cp[j]) {
                cp_max = cp[j]; // move max to cp[j]
                cp_id = j; // set max index
            }
        }

        printf("%s\t$%.2f\n", months[cp_id].c_str(), sales[cp_id]); // print maximum
        cp[cp_id] = 0; // set index of maximum to 0
    }

}

void report(double sales[]) {

    /* Input: sales array */
    /* Wrapper function. Initializes month array and calls print functions. */

    // array of months
    std::string months[12] = {"January  ", "February ", "March    ", "April    ", "May      ", "June     ", "July     ",
                                "August   ", "September", "October  ", "November ", "December "};

    std::cout << "\nMonthly sales report for 2024:\n\n";
    std::cout << "Month\t\tSales\n\n";

    // print sales data by month
    for (int i = 0; i < 12; i++) {
        printf("%s\t$%.2f\n", months[i].c_str(), sales[i]);
    }

    std::cout << "\nSales summary:\n\n";
    // call print_summary()
    print_summary(sales, months);

    std::cout << "\nSix-Month Moving Average Report:\n\n";
    // call print_movavg()
    print_movavg(sales, months);

    std::cout << "\nSales Report (Highest to Lowest):\n\n";
    std::cout << "Month\t\tSales\n\n";
    // call print_ordered()
    print_ordered(sales, months);

}

int main(int argc, char* argv[]) {

    // check for valid arguments
    if (argc != 2) {
        // if invalid, print error message
        std::cout << "<Error> Must provide input file.\n";
        std::cout << "Format: ./prog <filename>\n";
        return 0; // exit
    }

    std::ifstream infile;
    infile.open(argv[1]);

    // try to open input file
    if (infile.is_open()) {
        
        double inp;
        double sales[12]; // array to hold input values
        int i = 0;

        // read input from file
        while (infile >> inp) {
            // add input to sales array
            sales[i] = inp;
            i++;
        }

        // if file contains invalid amount of data
        if (i != 12) {
            // print error message
            std::cout << "<Error> File must contain 12 monthly sales.\n";
            return 0; // exit
        }

        report(sales); // call report()
        std::cout << "\n";

    } else { 
        // if file cannot open, print error message
        std::cout << "<Error> File could not be opened.\n";
    }

    infile.close();

    return 0;
    
}