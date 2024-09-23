from cs50 import SQL
import csv

db = SQL("sqlite:///roster.db")

rows = []
i = 1

houses = ["Gryffindor", "Hufflepuff", "Ravenclaw", "Slytherin"]
house_heads = ["Minerva McGonagall", "Pomona Sprout", "Filius Flitwick", "Severus Snape"]

for house in houses:

    db.execute("INSERT INTO HOUSES (id, house_name, house_head) VALUES (?, ?, ?)", i, house, house_heads[i-1])
    i+=1

with open ("students.csv") as file:
    reader = csv.DictReader(file)

    for row in reader:

        db.execute("INSERT INTO STUDENTS (id, student_name, house, head) VALUES (?, ?, ?, ?)", row["id"], row["student_name"], row["house"], row["head"])
        if row["house"] == "Gryffindor":
            house_id = 1
        elif row["house"] == "Hufflepuff":
            house_id = 2
        elif row["house"] == "Ravenclaw":
            house_id = 3
        else:
            house_id = 4
        db.execute("INSERT INTO HOUSE_ASSIGNMENTS (house_id, student_id) VALUES (?, ?)", house_id, row["id"])






