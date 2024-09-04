import pyfiglet 
from sys import argv

def main():

    valid_fonts = pyfiglet.FigletFont.getFonts()
    # print(valid_fonts)

    if len(argv) != 3 and len(argv) != 1 or argv[1] != "-f":
        print("Usage: 'python figlet.py', for random font or 'python figlet.py -f/--font [VALID FONT]'")
        return

    if len(argv) == 3:
        if argv[2] in valid_fonts:
            text = input("Input: ")
            output = pyfiglet.figlet_format(f"{text}", font = f"{argv[2]}")
        else:
            print("Usage: 'python figlet.py', for random font or 'python figlet.py -f/--font [VALID FONT]'")
            return
    else:
        text = input("Input: ")
        output = pyfiglet.figlet_format(f"{text}")

    print(output)

main()
    


