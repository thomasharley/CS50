-- List the names of all people who starred in a moive in which Kevin Bacon also starred
SELECT DISTINCT name
FROM people, stars
WHERE people.id = stars.person_id
AND stars.movie_id IN -- fetch all movie IDs with kevin bacon
    (SELECT movies.id
    FROM people, stars, movies
    WHERE people.id = stars.person_id
    AND stars.movie_id = movies.id
    AND name = 'Kevin Bacon'
    AND birth = '1958')
AND name != 'Kevin Bacon' -- remove Kevin from the list
