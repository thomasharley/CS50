CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT NOT NULL,
    hash TEXT NOT NULL,
    cash NUMERIC NOT NULL DEFAULT 10000.00
);

CREATE TABLE sqlite_sequence (
    name,
    seq
);

CREATE UNIQUE INDEX username ON users (username);

CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    symbol TEXT NOT NULL,
    shares INTEGER NOT NULL,
    price NUMERIC NOT NULL,
    time TEXT NOT NULL,
    type TEXT NOT NULL
);

CREATE TABLE transactions_assignment (
    user_id INTEGER NOT NULL,
    transaction_id INTEGER NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id),
    FOREIGN KEY(transaction_id) REFERENCES transactions(id)
);