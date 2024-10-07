import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# List of valid months/ days
MONTHS = [str(day) for day in range(1, 13)]
DAYS = [str(day) for day in range(1, 32)]

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Validate submission
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if not name or (month not in MONTHS) or (day not in DAYS):
            return redirect ("/")

        # Store birthday to database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        # Confirm birthday submission
        return redirect("/")

    else:

        # Print out birthday entries
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

@app.route("/delete", methods=["POST"])
def delete():

    # Remove birthday
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays where id = ?", id)

    # Return
    return redirect("/")

@app.route("/edit_page", methods=["POST"])
def edit_page():

    # Return edit page
    id = request.form.get("id")
    return render_template("edit.html", id=id)

@app.route("/edit", methods=["POST"])
def edit():

    # Validate edit submission
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")
    if not name or (month not in MONTHS) or (day not in DAYS):
        return redirect ("/")

    # Edit birthday in database
    id = request.form.get("id")
    if id:
        db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", name, month, day, id)

    return redirect("/")
        


