-- Return the average energy of songs that are by Drake
SELECT AVG(energy)
FROM songs, artists
WHERE artist_od = artists.id
AND artists.name = 'Drake';