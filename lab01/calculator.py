#!/usr/bin/env python3

import math

class Calculator:

    def __init__(self):
        self.result = 0.0
        self.sum = 0.0
        self.count = 0
        # The menu only seems to appear sometimes.
        # This variable indicates whether print_menu() should be run.
        self.show_menu = True

    # Prints the menu.
    def print_menu(self):
        print(f'Current Result: {self.result}')
        print()
        print('Calculator Menu')
        print('---------------')
        print('0. Exit Program')
        print('1. Addition')
        print('2. Subtraction')
        print('3. Multiplication')
        print('4. Division')
        print('5. Exponentiation')
        print('6. Logarithm')
        print('7. Display Average')
        print()

    # Prints the prompt and inputs an operand from the user.
    # Supports RESULT as an alias for the previous result.
    def get_operand(self, prompt):
        text = input(prompt)
        if text.lower() == 'result':
            return self.result
        else:
            return float(text)

    # Prompts the user for two operands and returns them as a tuple.
    def get_operands(self):
        a = self.get_operand('Enter first operand: ')
        b = self.get_operand('Enter second operand: ')
        print()
        return (a, b)

    def push_result(self, result):
        self.result = result
        self.sum += result
        self.count += 1

    def add(self):
        (a, b) = self.get_operands()
        self.push_result(a + b)
        self.show_menu = True

    def subtract(self):
        (a, b) = self.get_operands()
        self.push_result(a - b)
        self.show_menu = True

    def multiply(self):
        (a, b) = self.get_operands()
        self.push_result(a * b)
        self.show_menu = True

    def divide(self):
        (a, b) = self.get_operands()
        self.push_result(a / b)
        self.show_menu = True

    def exponent(self):
        (a, b) = self.get_operands()
        self.push_result(a ** b)
        self.show_menu = True

    def logarithm(self):
        (a, b) = self.get_operands()
        self.push_result(math.log(b, a))
        self.show_menu = True

    def average(self):
        print()
        self.show_menu = False
        if self.count == 0:
            print('Error: No calculations yet to average!')
            print()
            return
        average = round(self.sum / self.count, 2)
        print(f'Sum of calculations: {self.sum}')
        print(f'Number of calculations: {self.count}')
        print(f'Average of calculations: {average}')
        print()

def main():
    calc = Calculator()

    while True:
        if calc.show_menu:
            calc.print_menu()
        sel = input('Enter Menu Selection: ')
        match sel:
            case '0':
                break
            case '1':
                calc.add()
            case '2':
                calc.subtract()
            case '3':
                calc.multiply()
            case '4':
                calc.divide()
            case '5':
                calc.exponent()
            case '6':
                calc.logarithm()
            case '7':
                calc.average()
            case _:
                print()
                print('Error: Invalid selection!')
                print()
                calc.show_menu = False

    print()
    print('Thanks for using this calculator. Goodbye!')

if __name__ == '__main__':
    main()
