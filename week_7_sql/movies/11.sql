-- List the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
SELECT title
FROM people, stars, movies, ratings
WHERE people.id = stars.person_id 
AND stars.movie_id = movies.id 
AND movies.id = ratings.movie_id
AND name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;