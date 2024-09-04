
def main():

    greeting = str.lower(input("Greeting: "))

    if greeting.startswith("hello") == True:
        print("$0")    
    elif greeting.startswith("h") == True:
        print("$20")
    else:
        print("$100")

main()

    