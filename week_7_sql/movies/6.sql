-- Determine the average rating of all movies release in 2012.
SELECT AVG(rating)
FROM movies, ratings
WHERE movies.id = ratings.movie_id
AND year = 2012;

