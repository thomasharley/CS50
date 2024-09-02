from cs50 import get_int
import re

def main():

    number = str(get_int("Number: "))

    if (check(number)):
        if len(number) == 15 and int(number[0]) == 3: # AMEX
            if int(number[1]) == 4 or int(number[1]) == 7:
                print("AMEX")
                return True

        elif len(number) == 13 and int(number[0]) == 4: # VISA
            print("VISA")
            return True
        
        elif len(number) == 16 and int(number[0]) == 4: # VISA
            print("VISA")
            return True
        
        elif len(number) == 16 and int(number[0]) == 5: # MASTERCARD
            if int(number[1]) == 1 or int(number[1]) == 2 or int(number[1]) == 3 or int(number[1]) == 4 or int(number[1]) == 5:
                print("MASTERCARD")
                return True
    
    return False

def check(number):

    length = len(number)

    i = length - 2
    odds = []
    while i >= 0:  
        if int(number[i])*2 > 9:
            odds.append((int(number[i])*2 % 10)+1)
        else:
            odds.append(int(number[i])*2)
        i=i-2
    
    i = length - 1
    evens = []
    while i >= 0:    
        evens.append(int(number[i]))
        i=i-2

    total = sum(odds) + sum(evens)
                
    if total % 10 == 0:
        return True
    else:
        return False
        
    
if main() == False:
    print("INVALID")

