-- List the names of songs that are by Post Malone
SELECT songs.name 
FROM songs, artists
WHERE artist_id = artists.id 
AND artists.name = 'Post Malone';