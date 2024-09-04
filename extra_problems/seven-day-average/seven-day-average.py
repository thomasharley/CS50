import csv
from numpy import average
import requests
import math

def main():

    # Construct 14 day lists of new cases for each states
    new_cases = calculate()

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate():

    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()

    new_cases = {}

    state_names = ["Alaska", "Alabama", "Arkansas", "American Samoa", "Arizona", "California", "Colorado", "Connecticut", "District of Columbia", 
                   "Delaware", "Florida", "Georgia", "Guam", "Hawaii", "Iowa", "Idaho", "Illinois", "Indiana", "Kansas", "Kentucky", "Louisiana", "Massachusetts", 
                   "Maryland", "Maine", "Michigan", "Minnesota", "Missouri", "Mississippi", "Montana", "North Carolina", "North Dakota", "Nebraska", 
                   "New Hampshire", "New Jersey", "New Mexico", "Nevada", "New York", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Puerto Rico", "Rhode Island", 
                   "South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Virginia", "Virgin Islands", "Vermont", "Washington", "Wisconsin", "West Virginia", "Wyoming"]

    for i in state_names:
        previous = 0
        list = []
        reader = csv.DictReader(file)
        for row in reader: 
            if(row["state"] == i):
                if len(list) < 14:
                    list.append(int(row["cases"]) - previous)
                    previous = int(row["cases"])
                else:
                    list.pop(0)
                    list.append(int(row["cases"]) - previous)
                    previous = int(row["cases"])

        new_cases[i] = list

    # print(new_cases)
    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    
    for state in states:
        this_week = average(new_cases[state][7:]) 
        previous_week = average(new_cases[state][:7])

        if this_week >= previous_week:
            change = "an increase"
            try:
                result = int(round(((this_week-previous_week)/previous_week) * 100, 0))
            except ZeroDivisionError: # if previous week is zero, treat growth as infinitiy
                result = "inf"
        elif this_week < previous_week:
            change = "a decrease"
            result = int(round(((previous_week-this_week)/previous_week) * 100, 0))

        print(f"{state} had a 7-day average of {int(round(this_week, 0))} and {change} of {result}%")

main()
