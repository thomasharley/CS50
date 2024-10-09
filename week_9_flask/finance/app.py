import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Find all user's stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) FROM transactions WHERE id IN (SELECT transaction_id from transactions_assignment WHERE user_id = ?) GROUP BY symbol HAVING SUM(shares) > 0", 
        session["user_id"]
    )

    total_stocks = 0

    # Add price and total fields
    for stock in stocks:
        price = lookup(stock["symbol"])["price"]
        stock['price'] = usd(price)
        stock['total'] = usd(price * stock['SUM(shares)'])
        total_stocks += (price * stock['SUM(shares)'])

    # Fetch cash
    user_info = db.execute(
        "SELECT * FROM users WHERE id = ?", session["user_id"]
    )
    cash = user_info[0]["cash"]

    # Fetch total
    total = cash + total_stocks

    # Return main page
    return render_template("index.html", stocks=stocks, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure symbol submitted
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol or not shares:
            return apology("must provide symbol and shares", 403)

        # Lookup symbol
        quoted = lookup(symbol)

        # Check if symbol invalid
        if quoted == None:
            return apology("invalid symbol", 403)

        # Check if shares invalid
        try:
            shares = int(shares)
            if shares < 1:
                return apology("invalid shares")
        except ValueError:
            return apology("invalid shares")

        # Add stock purchase to the database
        price = quoted["price"]
        
        # Check we have enough cash
        user_info = db.execute(
            "SELECT * FROM users WHERE id = ?", session["user_id"]
        )
        cash = user_info[0]["cash"]

        if (price * shares > cash):
            return apology("insufficient funds")

        # Update user's remaining cash
        cash -= (price * shares)
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"]
        )

        # Fetch time
        time = datetime.datetime.now()

        # Add transaction
        transaction_id = db.execute(
            "INSERT INTO transactions (symbol, shares, price, time, type) VALUES (?, ?, ?, ?, ?)", symbol, shares, usd(price), time, "BUY"
        )

        # Link transaction entry to the correct user_id from the session token
        db.execute(
            "INSERT INTO transactions_assignment (user_id, transaction_id) VALUES (?, ?)", session["user_id"], transaction_id
        )

        # Redirect user to home page
        flash('Bought!')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")
    

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Find transactions for logged in user
    transactions = db.execute(
        "SELECT * FROM transactions WHERE id IN (SELECT transaction_id from transactions_assignment WHERE user_id = ?)", session["user_id"]
    )

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username and password were submitted
        username = request.form.get("username")
        password = request.form.get("password")
        if not username or not password:
            return apology("must provide username and password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", username
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], password
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in & their name
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        flash('Logged In!')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure symbol submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 403)

        # Lookup symbol
        quoted = lookup(symbol)

        # Check if symbol invalid
        if quoted == None:
            return apology("invalid symbol", 403)

        # Return infomation about the stock
        price = usd(quoted["price"])
        name = quoted["name"]
        return render_template("quoted.html", name=name, symbol=symbol, price=price)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure all fields were submitted
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username or not password or not confirmation:
            return apology("please fill in all fields", 403)

        # Ensure second password entry matches first
        elif confirmation != password:
            return apology("passwords must match", 403)

        # Attempt to add new username to database
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", 
                username, 
                generate_password_hash(password, method='pbkdf2', salt_length=16)
            )
        except ValueError:
            return apology("username already exists", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", username
        )

        # Remember which user has logged in & their name
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        flash('Registered!')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure all fields were submitted
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not shares:
            return apology("must provide symbol and shares", 403)

        # Check if shares invalid
        try:
            shares = int(shares)
            if shares < 1:
                return apology("invalid shares")
        except ValueError:
            return apology("invalid shares")

        # Find shares of chosen symbol
        stocks = db.execute(
            "SELECT SUM(shares) FROM transactions WHERE id IN (SELECT transaction_id from transactions_assignment WHERE user_id = ?) AND symbol = ? GROUP BY symbol", 
            session["user_id"], symbol
        )

        # Check if requesting to sell too many stocks
        if shares > int(stocks[0]["SUM(shares)"]):
            return apology("you do not own enough shares", 403)

        # Fetch cash
        user_info = db.execute(
            "SELECT * FROM users WHERE id = ?", session["user_id"]
        )
        cash = user_info[0]["cash"]

        # Update user's remaining cash
        price = lookup(symbol)["price"]
        cash += (price * shares)
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"]
        )

        # Fetch time
        time = datetime.datetime.now()

        # Add transaction
        transaction_id = db.execute(
            "INSERT INTO transactions (symbol, shares, price, time, type) VALUES (?, ?, ?, ?, ?)", symbol, -shares, usd(price), time, "SELL"
        )

        # Link transaction entry to the correct user_id from the session token
        db.execute(
            "INSERT INTO transactions_assignment (user_id, transaction_id) VALUES (?, ?)", session["user_id"], transaction_id
        )

        # Redirect user to home page
        flash('Sold!')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Find all user's stocks
        stocks = db.execute(
            "SELECT symbol FROM transactions WHERE id IN (SELECT transaction_id from transactions_assignment WHERE user_id = ?) GROUP BY symbol HAVING SUM(shares) > 0", 
            session["user_id"]
        )

        return render_template("sell.html", stocks=stocks)

@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Deposit more cash"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure all fields were submitted
        cash = request.form.get("cash")

        if not cash:
            return apology("must provide cash amount", 403)

        # Check if cash amount invalid
        try:
            cash = float(cash)
            if cash < 1 or cash > 10000:
                return apology("invalid cash amount")
        except ValueError:
            return apology("invalid cash amount")

        # Fetch cash
        user_info = db.execute(
            "SELECT * FROM users WHERE id = ?", session["user_id"]
        )
        total_cash = user_info[0]["cash"]

        # Update user's cash
        total_cash += cash
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", total_cash, session["user_id"]
        )

        # Redirect user to home page
        flash('Deposited!')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        return render_template("deposit.html")

    
@app.route("/settings", methods=["GET", "POST"])
@login_required
def update_password():
    """Update users password"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure all fields were submitted
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")
        if not old_password or not new_password or not confirmation:
            return apology("please fill in all fields", 403)

        # Ensure old password is correct
        user_info = db.execute(
            "SELECT * FROM users WHERE id = ?", session["user_id"]
        )
        if not check_password_hash(
            user_info[0]["hash"], old_password
        ):
            return apology("old password is incorrect", 403)

        # Ensure second password entry matches first
        elif confirmation != new_password:
            return apology("new passwords must match", 403)

        #Ensure new password is different to the old
        elif new_password == old_password:
            return apology("new password must be different to the old password", 403)

        # Update password to new password 
        db.execute(
            "UPDATE users SET hash = ? WHERE id = ?", 
            generate_password_hash(new_password, method='pbkdf2', salt_length=16),
            session["user_id"]
        )

        # Redirect user to home page
        flash('Password Changed!')
        return redirect("/")
        

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        return render_template("settings.html")

@app.route("/admin")
@login_required
def admin():
    """Admin panel to view all users"""
    # Find all users in the database
    users = db.execute(
        "SELECT * FROM users"
    )

    # Find all transactions in the database
    transactions = db.execute(
        "SELECT * FROM transactions"
    )

    # Find user id for each transaction
    for transaction in transactions:
        user_id = db.execute(
            "SELECT user_id FROM transactions_assignment WHERE transaction_id = ?", transaction['id']
        )
        transaction['user_id'] = user_id[0]['user_id'] 

    return render_template("admin.html", users=users, transactions=transactions)
