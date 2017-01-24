<html>
<head>
<title> Estructura de Datos Avanzados</title>
<link rel="stylesheet" type="text/css" href="estilo.css"/>
</head>
<body>
<h1>PROYECTO FINAL DE EDA
	<img class="img1" src="cs.jpg" width="80px" height="80px">
</h1>

<?php
	echo "<table>";
	for($i = 1;$i<4;$i++)
	{
		if($i%2!=0)
			echo "<tr>";
		echo "<td>";
		echo "<img src='img$i.jpg' width='400px' height='400px'><br>";
		echo "</td>";
		if($i%2==0)
			echo "</tr>";
	}
	echo "</table>";
?>