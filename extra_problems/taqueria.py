# declare dictionary
d = {
    "baja taco": 4.25,
    "burrito": 7.50,
    "bowl": 8.50,
    "nachos": 11.00,
    "quesadilla": 8.50,
    "super burrito": 8.50,
    "super quesadilla": 9.50,
    "taco": 3.00,
    "tortilla salad": 8.00
}

# main
def main():

    total_value = 0 # value

    while(True):
        try:
            Input = str.lower(input("Item: "))
            if Input in d: # check if item exists in dictionary
                total_value = total_value + d[Input]
                print(f"Total: ${total_value:.2f}") # print
                
        except EOFError: # type ctrl+z + enter to end program.
            return

# call main
main()