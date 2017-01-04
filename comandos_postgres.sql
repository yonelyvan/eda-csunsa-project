-----------config

export PATH=$HOME/project/bin:$PATH
export PGDATA=DemoDir
initdb

----------comandos
psql -l       --ver/listar bases de datos
psql name_db  --seleccionar una base de datos "name_db"
\dt           --ver/listar tablas
\df           --ver/listar funciones

\q            --salir


----------- algunas consultas
drop function funcion(text);  --eliminar funciones: DROP FUNCTION name ( [ type [, ...] ] );



