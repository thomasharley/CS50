-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * 
FROM crime_scene_reports 
WHERE street = 'Humphrey Street' 
AND day = 28 
AND month = 7;
-- Found that it took place at 10:15am, there were 3 witnesses, every witness mentions the bakery.
SELECT name, transcript 
FROM interviews 
WHERE month = 7 
AND day = 28;
-- From querying the interviews table found the following interview texts (easy to identify as they all mention a bakery):

-- Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. 
--       If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot 
--       in that time frame.

-- Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--         I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.  

-- Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard
--          the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the 
--          person on the other end of the phone to purchase the flight ticket.  

-- Dealing with Ruths interview first, we can check bakery security logs, within 10 minutes of crime at 10:15am:

SELECT license_plate 
FROM bakery_security_logs 
WHERE year = 2023 
AND month = 7 
AND day = 28 
AND hour = 10 
AND minute >= 15 
AND minute <= 25 
AND activity = 'exit'; 

-- This finds possible license plates, we have narrowed suspects down to 8 plates.
-- 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

-- Now Eugene's testimony, we will check ATM transactions that morning before 10:15am
SELECT account_number 
FROM atm_transactions 
WHERE year = 2023 
AND month = 7 
AND day = 28 
AND atm_location = 'Leggett Street' 
AND transaction_type = 'withdraw';

-- account numbers: 28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199

-- Find person IDs associated with these bank accounts:
SELECT person_id 
FROM bank_accounts 
WHERE account_number IN 
    (SELECT account_number 
     FROM atm_transactions 
     WHERE year = 2023 
     AND month = 7 
     AND day = 28 
     AND atm_location = 'Leggett Street' 
     AND transaction_type = 'withdraw'
    );

-- Final interview is Raymond, check the phone logs, get caller and receiver information:
SELECT caller, receiver 
FROM phone_calls 
WHERE year = 2023 
AND month = 7 
AND day = 28 
AND duration < 60;

--+----------------+----------------+
--|     caller     |    receiver    |
--+----------------+----------------+
--| (130) 555-0289 | (996) 555-8899 |
--| (499) 555-9472 | (892) 555-8872 |
--| (367) 555-5533 | (375) 555-8161 |
--| (499) 555-9472 | (717) 555-1342 |
--| (286) 555-6063 | (676) 555-6554 |
--| (770) 555-1861 | (725) 555-3243 |
--| (031) 555-6622 | (910) 555-3251 |
--| (826) 555-1652 | (066) 555-9701 |
--| (338) 555-6650 | (704) 555-2131 |
--+----------------+----------------+

-- find ID of earliest flight out of fiftyville airport:
SELECT ID 
FROM airports 
WHERE city = 'Fiftyville' 
-- airport ID is 8.

-- this will find the correct ID.
SELECT id 
FROM flights 
WHERE origin_airport_id = 8 
AND year = 2023 
AND month = 7 
AND day = 29 
ORDER BY hour, minute ASC 
LIMIT 1;     
-- Turns out to be ID = 36

-- At this point we can find the destination by querying destination of flight ID 36.
SELECT city 
FROM airports
WHERE ID = 
    (SELECT destination_airport_id
     FROM flights
     WHERE origin_airport_id = 8 
     AND year = 2023 
     AND month = 7 
     AND day = 29 
     ORDER BY hour, minute ASC 
     LIMIT 1
    );

--+---------------+
--|     city      |
--+---------------+
--| New York City |
--+---------------+

-- Now check passengers of this flight
SELECT passport_number 
FROM passengers 
WHERE flight_id = 36;

-- Now we know the potential passport numbers, 
-- By combining all this information we can query the "people" database and find if we have only 1 suspect left with a single SQL query:

SELECT name 
FROM people 
WHERE phone_number IN 
    (SELECT caller
     FROM phone_calls 
     WHERE year = 2023 
     AND month = 7 
     AND day = 28 
     AND duration < 60)
AND passport_number IN
    (SELECT passport_number 
     FROM passengers 
     WHERE flight_id = 36)
AND license_plate IN 
    (SELECT license_plate 
     FROM bakery_security_logs 
     WHERE year = 2023 
     AND month = 7 
     AND day = 28 
     AND hour = 10 
     AND minute >= 15 
     AND minute <= 25 
     AND activity = 'exit')
AND id IN
    (SELECT person_id 
     FROM bank_accounts 
     WHERE account_number IN 
        (SELECT account_number 
         FROM atm_transactions 
         WHERE year = 2023 
         AND month = 7 
         AND day = 28 
         AND atm_location = 'Leggett Street' 
         AND transaction_type = 'withdraw'
        )
    );

-- This narrows our potential suspects down to 1:

--+--------+
--|  name  |
--+--------+
--| Bruce  |
--+--------+

-- Now we can simply look up the phone number of Bruce, to find his accomplice:

SELECT phone_number 
FROM people 
WHERE name = 'Bruce';

--+----------------+
--|  phone_number  |
--+----------------+
--| (367) 555-5533 |
--+----------------+

-- We just look at who the receiver of the phone call Bruce made is. This will find that in a single query.

SELECT name
FROM people
WHERE phone_number = 
    (SELECT receiver
     FROM phone_calls 
     WHERE year = 2023 
     AND month = 7 
     AND day = 28 
     AND duration < 60
     AND caller = 
        (SELECT phone_number 
         FROM people 
         WHERE name = 'Bruce'
        )
    );

--+-------+
--| name  |
--+-------+
--| Robin |
--+-------+

-- Task is now complete!








