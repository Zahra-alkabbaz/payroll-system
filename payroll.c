#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Declaring the variables outside the function to make them global variables
float annualSalary, personalAllowance, taxableIncome, annualIncomeTax, annualNatInsurance, monthlyNetpay, avg, total, TotalNetpay = 0, maxIncomeTax,
minIncomeTax, annualTotal = 0, max = 0, min = 99999999999999999; // TotalNetpay is the sum of the  money the company pays.
int age, n = 0; // age is an integer because it is in years and n is the number of employees.




//Returns the personal allowance of a person with the given annual salary
float compute_personal_allowance ( float annualSalary ) {
  if ( annualSalary > 0 && annualSalary <= 100000) // specifying the range of the personal allowance that equals 11850.
    personalAllowance = 11850;

  else if (annualSalary > 100000 && annualSalary <= 123700) // Specifying the given range which the following equation applies for.
    personalAllowance = (11850 - ((annualSalary-100000)/2) ); //This is simplified as 1*(11850 -(annualSalary-100000)) = 11850 - (annualSalary-100000)
  else
    personalAllowance = 0; // as after a certain number (123700) there would not be personal allowance
  return personalAllowance;
}


//Returns the taxable income of a person with the given annual salary and personal allowance
float compute_taxable_income(float annualSalary, float personalAllowance) {
  if ( annualSalary <= 11850) //as if the annualSalary is smaller than the given fixed personal allowance there cannot be a taxable income and no tax apply.
    taxableIncome = 0;
else
  taxableIncome = annualSalary - personalAllowance;
  /* If the taxable income is not less than 11850, then the taxableIncome is the annualSalary minus the calculated personal allowance from the previous function.
  where the tax is applied after a certain amount.*/
  return taxableIncome;
}


//Returns the annual income tax of a person with the given taxable income
float compute_annual_income_tax ( float taxableIncome ) {
  if (taxableIncome <= 34500 )
    annualIncomeTax = (0.2 * taxableIncome);

  else if ( taxableIncome >= 34501 && taxableIncome < 150000)
       annualIncomeTax = (6900  + 0.4 * (taxableIncome - 34500));
  // The answer of the multiplication is directly written as 0.20*34500 = 6900 in the first part

  else
    annualIncomeTax = (6900 + 46200 + 0.45 * (taxableIncome - 150000));
  // Here the middle value 46200 was found by substracting the second range limits 150000-34500= 115500 and 0.4*115500 = 46200
  return annualIncomeTax;

}

//Returns the annual national insurance for a person with the given annual salary and age.

float compute_annual_national_insurance ( float annual_salary, int age ) {
  if ( age >= 65 || annual_salary < 8424)
    annualNatInsurance = 0;

  else if ( annual_salary >= 8424 && annual_salary <= 46350)
     annualNatInsurance = 0.12 * (annual_salary - 8424);

  else
    annualNatInsurance = (4551.12) + 0.02 *( annual_salary - 46350);
  // as 46350-8424 = 37926 and  0.12 *(37926)= 4551.12 for the first part of the equation
  return annualNatInsurance;

}

//Computes the monthly net pay of a person with the given annual salary, annual income tax, and annual national insurance
float compute_monthly_net_pay ( float annualSalary, float annualIncomeTax, float annualNatInsurance ) {
  monthlyNetpay =  ( annualSalary - annualIncomeTax - annualNatInsurance) / 12; // the anuual net pay divided by 12 to get the monthly net pay
  return monthlyNetpay;
}



/*Enters a person with a given annual salary and age into the system.

This function uses the functions above to compute and update the cumulative statistics, namely:

A. The total amount of money paid out by the company to all employees.
B. The average net monthly salary.
C. The maximum income tax paid by any employee.
D. The minimum income tax paid by any employee.
hint: store the values into global variables, so that the function below can return them.
*/

void add_person ( float annualSalary, int age ) {
  float monthlysalary; // to declare a variable to use in converting the annual salary to monthly
  // calling the previous functions to use them for calculating the values of the coming functions
  compute_personal_allowance (annualSalary);
  compute_taxable_income (annualSalary, personalAllowance);
  compute_annual_income_tax (taxableIncome);
  compute_annual_national_insurance (annualSalary, age);
  compute_monthly_net_pay (annualSalary, annualIncomeTax, annualNatInsurance);
  n += 1; // number of employees entered into the system adding every employee added to the count.
  monthlysalary = annualSalary/12; // to get the monthly salary of each employee we divide the annual salary by 12 (months) as it is the same for each month
  total += monthlysalary; // to compute the monthlySalaries of all the employees in the company we add all monrhly salaries to each other
  TotalNetpay += monthlyNetpay; // we count the netpay of all employees of the company entered into the system

  if (taxableIncome < min) // to find the minimum income tax we need to find the minimum taxableincome as it depends on it and same thing for the maximum.
    min = taxableIncome;
  if (taxableIncome > max)
    max = taxableIncome;
}
//Returns the total money paid by the company to the employees entered
//into the system through add_person()
float get_total_money_paid() {
  return total; // returning the calculated  value in add_person() earlier
}

//Returns the average net salary of all the employees entered into the
//system through add_person()
float get_average_net_salary() {
  avg = TotalNetpay /n; // TotalNetPay has been calculated earlier in add_person() and we divide it by n to get the avgerage.
  return avg;
 // the total netpay of all emploies divdied by the number of employees to get the average
}

//Returns the maximum income tax paid by any of the employees entered into the
//system through add_person()
float get_maximum_income_tax() {
  // we substitute with max for the taxableIncome in the function to get the maximum income tax of the entered employees
  maxIncomeTax = compute_annual_income_tax (max) / 12; // to find the monthly maximum income tax of employees we divide by 12 months because it is annually
  return maxIncomeTax;
}

//Returns the minumum income tax paid by any of the employees entered into the
//system through add_person()
float get_minimum_income_tax() {
  // we substitute for taxableIncome with min to get the minimum income tax of the employees entered into the system.
  minIncomeTax = compute_annual_income_tax (min) / 12; // to find the monthly minimum income tax of all employees we divide by 12 months as it is annually
  return minIncomeTax;
}


int main (int argc, char **argv) {
  int option; // the option that the user will enter when the menu is displayed
  while ( 1 ) // to make the menu loop unless the user enters choice 3 to exit
    {
      printf("Main menu:\n");
      printf("1- Compute and Print the pay of an employee.\n");
      printf("2- Show sums and staistics.\n");
      printf("3- Quit the program.\n\n");
      printf("Please enter your choice (1, 2 or 3): ");
      scanf("%i", &option);

      if (option == 1 ) // once the user chooses 1 in the menu these input request sentences will be displayed and what follows
	{
	  printf("Please enter the employee's annual Salary: \n"); // we ask the user for the annual Salary of an employee
	  scanf("%f", &annualSalary); // to give the input value a variable
	  printf("Please enter the employee's age: \n"); // we ask the user for the employees age for national contribution calculations
	  scanf("%i", &age); // assigning a name for the value given.
	  add_person(annualSalary, age); // we recall the add_person() function to pass the values of the variables
	  // giving the user the payslip of the entered employee.
	  printf("The payslip of the employee:\n");
	  printf("1- The age of the employee is: %i\n", age);
	  printf("2- The annual Salary of the employee is: %.2f\n", annualSalary);
	  printf("3- The taxable income of the employee is: %.2f\n", taxableIncome);
	  printf("4- The monthly income tax of the employee is: %.2f\n", annualIncomeTax/12);
	  printf("5- The monthly national contribution is: %.2f\n", annualNatInsurance/12);
	  printf("6- The monthly net pay of the employee is : %.2f\n\n", monthlyNetpay);
	}
      if ( option == 2) // once the user choses 2 from the menu the following sentences and function values will be printed
	{
	  printf("The payroll of the month:\n "); // giving the payroll of the month for all the entered employees and showing statistics.
	  printf("A- The total money paid by the company is: %.2f\n", get_total_money_paid());
	  printf("B- The average net salary for the employees is: %.2f\n", get_average_net_salary());
	  printf("C- The maximum income tax of the employees is: %.2f\n", get_maximum_income_tax());
	  printf("D- The minimum income tax of the employees is: %.2f\n\n", get_minimum_income_tax());
	}
      if (option == 3) // once the user choses 3 to quit the program this will let the user exit the program
	exit(0);
  else {
    printf("\n\n***************Invalid Choice, please enter your choice (1, 2 or 3)*******************\n\n");
  }
    }


  return 0;
}
