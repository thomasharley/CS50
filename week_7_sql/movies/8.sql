-- List the names of all people who starred in Toy Story
SELECT name
FROM people, movies, stars
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND title = 'Toy Story';