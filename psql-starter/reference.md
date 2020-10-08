Postgres
- Start server: sudo pg_ctlcluster 12 main start
- Check if server is up: service postgresql status
Switch to user 'postgres' with su postgres
psql poketest
\dt to show tables, \d to show data associated

Join tables on ability array:
select * from pkmn JOIN abilities ON abilities.ab_id = ANY(pkmn.ab_array);

To update an existing pokemon, you have to specify where name = pokemon's name:
UPDATE pkmn SET ab_array = '{1, 2}' WHERE name = 'Pumpkaboo';

Adding rows:
INSERT INTO abilities VALUES ('Frisk', 'Frisk description', 2);

Adding columns:
ALTER TABLE pkmn ADD COLUMN name type;
