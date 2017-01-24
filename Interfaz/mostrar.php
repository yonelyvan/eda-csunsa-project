
<!DOCTYPE html>
<html>
<body>
<h1>My first PHP page</h1>
<?php

$conn  = pg_connect("user=micaela password='' host=localhost dbname=imagenes");
$query = pg_query($conn, "SELECT * FROM lista;");

while($row=pg_fetch_row($query))
{
	echo $row[0];
	//echo $row[1];

	$image = pg_unescape_bytea($row[2]);
	$token = explode(".", $image);
	$header= explode("/", $token[0]); 
	echo "<img src='JPG/".$header[1].".jpg"."'/>";
}
pg_close($conn);
?>
</body>
</html>