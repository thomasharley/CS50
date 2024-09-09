-- List the names of all people who starred in a movie released in 2004, ordered by birth year
SELECT DISTINCT name, birth
FROM people, movies, stars
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND year = '2004'
ORDER BY birth;