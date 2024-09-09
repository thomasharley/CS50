-- List the title of all movies in which both Bradley Cooper and Jennifer Lawrence Starred
SELECT title
FROM movies, people, stars
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND name IN ('Bradley Cooper', 'Jennifer Lawrence')
GROUP BY title HAVING COUNT(*) > 1;