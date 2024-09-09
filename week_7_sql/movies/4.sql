-- Determine the number of movies with an IMDb rating of 10.0.
SELECT COUNT(*)
FROM movies, ratings
WHERE movies.id = ratings.movie_id
AND ratings = 10;