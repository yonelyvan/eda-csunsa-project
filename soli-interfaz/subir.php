<?php
if(isset($_POST["subir"])){
	$tipo = $_FILES['archivo']['type'];
	$nombre = $_FILES['archivo']['name'];
	$tmp = $_FILES['archivo']['tmp_name'];
	$fichero_subido = basename($_FILES['archivo']['name']);
	echo $nombre."<br>";
	echo $tipo."<br>";
	echo $fichero_subido;
	if(($_FILES["archivo"]["type"]=="image/x-portable-pixmap"))

	$data = file_get_contents($nombre);//la direccion de la imagen
	$image = pg_escape_bytea($data);
	$conn = pg_connect("user=eda password=123 dbname=imagenes host=localhost");
	$query = "insert into images values ('1','".$nombre."','".$nombre."')";
//	echo $query;
	pg_query($conn, $query);
	pg_close($conn);
}
?>