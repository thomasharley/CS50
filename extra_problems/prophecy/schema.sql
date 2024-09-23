CREATE TABLE houses (
    id INTEGER,
    house_name TEXT,
    house_head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE house_assignments (
    house_id INTEGER NOT NULL,
    student_id INTEGER NOT NULL,
    FOREIGN KEY(house_id) REFERENCES houses(id),
    FOREIGN KEY(student_id) REFERENCES students(id)
);